# Day 8: 系统整合与调试 | System Integration & Debugging

## 今日目标 | Today's Goals

- 完成全功能系统整合（TFT + SHT31-D + WiFi + NTP + 电源 + 触摸 + LED）
- 理解看门狗定时器（Watchdog Timer）的作用和使用
- 实现健壮的异常处理机制
- 进行系统稳定性测试
- 优化代码结构和性能

---

## 上午 (3h) | Morning Session

### 1. 全功能系统整合 (2h)

**最终程序架构**：

```
desk_satellite.ino 程序结构：

├── config.h           (配置文件：WiFi、引脚、常量)
├── setup()
│   ├── 初始化串口
│   ├── 初始化 I2C + SHT31-D
│   ├── 初始化 SPI + ST7735 TFT
│   ├── 显示启动画面
│   ├── 连接 WiFi
│   ├── 同步 NTP 时间
│   ├── 初始化 LED + 触摸开关
│   └── 初始化看门狗定时器
│
└── loop()
    ├── 处理触摸事件
    ├── 更新显示（多屏切换）
    ├── 读取传感器（SHT31-D）
    ├── 更新 LED 状态
    ├── 检查 WiFi 连接
    ├── NTP 重新同步
    ├── 更新电池状态
    ├── 功耗管理
    └── 喂狗（重置看门狗）
```

**完整的主程序框架**：

```cpp
// desk_satellite.ino - Desk Satellite 主程序
// 桌面卫星气象站 - 完整版

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_SHT31.h>
#include <SPI.h>
#include <Wire.h>
#include <WiFi.h>
#include <esp_sleep.h>
#include <esp_task_wdt.h>
#include "time.h"

// ========== 配置 ==========
#include "config.h"

// ========== 全局对象 ==========
Adafruit_ST7735 tft(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
Adafruit_SHT31  sht31;

// ========== 全局状态 ==========
struct SystemState {
  // WiFi
  bool wifiConnected;
  unsigned long lastWiFiCheck;

  // NTP
  unsigned long lastNTPSync;
  bool ntpSynced;

  // 传感器
  float temperature;
  float humidity;
  unsigned long lastSensorRead;

  // 电池
  float batteryVoltage;
  int batteryPercent;
  ChargeStatus chargeStatus;
  unsigned long lastBatteryUpdate;

  // 显示
  int currentScreen;
  unsigned long lastDisplayUpdate;
  unsigned long screenChangeTime;

  // 交互
  bool touchPressed;
  unsigned long touchPressTime;
  unsigned long lastActivityTime;

  // LED
  LEDMode statusLEDMode;

  // 功耗
  PowerMode powerMode;

  // 统计
  unsigned long bootTime;
  int bootCount;
};

SystemState state;
RTC_DATA_ATTR int rtcBootCount = 0;

// ========== 初始化 ==========
void setup() {
  Serial.begin(115200);
  delay(1000);

  rtcBootCount++;
  state.bootCount = rtcBootCount;
  state.bootTime = millis();

  Serial.println("========================================");
  Serial.println("  Desk Satellite v1.0");
  Serial.printf("  Boot #%d\n", state.bootCount);
  Serial.println("========================================");

  // 检查唤醒原因
  checkWakeupReason();

  // 初始化硬件
  initI2C();
  initTFT();
  initLED();
  initTouch();

  // 显示启动画面
  showSplashScreen();

  // 连接网络
  state.wifiConnected = connectWiFi();
  if (state.wifiConnected) {
    state.ntpSynced = syncNTP();
  }

  // 初始化看门狗
  initWatchdog();

  // 初始化传感器
  readSensorData();

  Serial.println("System ready!");
}

void loop() {
  unsigned long now = millis();

  // 核心任务循环
  handleTouch();
  updateDisplay(now);
  updateSensor(now);
  updateWiFi(now);
  updateNTP(now);
  updateBattery(now);
  updateLED();
  managePower(now);

  // 喂狗
  esp_task_wdt_reset();

  delay(10);  // 给系统一点喘息时间
}
```

### 2. 看门狗定时器 (1h)

**什么是看门狗？**

看门狗定时器（WDT）是一种硬件保护机制：
- 程序必须定期"喂狗"（重置定时器）
- 如果超时未喂狗，WDT 会自动重启系统
- 用于防止程序死循环或卡死

```
正常工作：
  喂狗 → 运行 → 喂狗 → 运行 → 喂狗 → ...

程序卡死：
  喂狗 → 运行 → 卡死... → 超时！→ 系统重启
```

```cpp
// 看门狗定时器初始化
#define WDT_TIMEOUT_SEC 30  // 30 秒超时

void initWatchdog() {
  Serial.println("Initializing Watchdog Timer...");
  esp_task_wdt_init(WDT_TIMEOUT_SEC, true);  // true = 超时后重启
  esp_task_wdt_add(NULL);  // 将当前任务添加到看门狗监控
  Serial.printf("Watchdog set to %d seconds\n", WDT_TIMEOUT_SEC);
}

// 在主循环中定期喂狗
void loop() {
  // ... 所有正常任务 ...

  // 每次循环结束喂狗
  esp_task_wdt_reset();
}
```

**注意**：
- 看门狗超时时间不能太短（否则正常操作可能触发重启）
- 也不能太长（否则卡死后要等很久才重启）
- 30 秒是一个合理的默认值

---

## 下午 (4h) | Afternoon Session

### 3. 异常处理机制 (1.5h)

**健壮的错误处理**：

```cpp
// 错误码定义
typedef enum {
  ERROR_NONE = 0,
  ERROR_WIFI_CONNECT_FAILED,
  ERROR_NTP_SYNC_FAILED,
  ERROR_SENSOR_READ_FAILED,
  ERROR_BATTERY_LOW,
  ERROR_DISPLAY_INIT_FAILED,
  ERROR_WATCHDOG_RESET
} ErrorCode;

// 错误处理函数
void handleError(ErrorCode error) {
  Serial.printf("[ERROR] Code: %d\n", error);

  switch (error) {
    case ERROR_WIFI_CONNECT_FAILED:
      // WiFi 连接失败：继续运行，定期重试
      setLEDMode(LED_BLINK_FAST);
      state.wifiConnected = false;
      // 不影响本地传感器数据显示
      break;

    case ERROR_NTP_SYNC_FAILED:
      // NTP 同步失败：使用上次的时间或显示 "NO NTP"
      state.ntpSynced = false;
      Serial.println("NTP sync failed, time may be inaccurate");
      break;

    case ERROR_SENSOR_READ_FAILED:
      // 传感器读取失败：显示上次的值，标记为过期
      Serial.println("Sensor read failed, using cached values");
      break;

    case ERROR_BATTERY_LOW:
      // 电池电量低：降低刷新频率，提示用户充电
      if (state.batteryPercent < 10) {
        tft.setTextSize(1);
        tft.setTextColor(ST7735_RED);
        tft.setCursor(40, 40);
        tft.print("LOW BATTERY!");
        // 进入低功耗模式
        state.powerMode = POWER_MODE_SAVE;
      }
      break;

    case ERROR_DISPLAY_INIT_FAILED:
      // 显示初始化失败：只能通过串口输出调试
      Serial.println("FATAL: Display init failed!");
      break;

    default:
      Serial.println("Unknown error");
      break;
  }
}
```

**超时保护**：

```cpp
// 带超时的操作封装
bool executeWithTimeout(std::function<bool()> operation,
                        unsigned long timeoutMs,
                        const char* description) {
  unsigned long startTime = millis();

  while (!operation()) {
    if (millis() - startTime > timeoutMs) {
      Serial.printf("[TIMEOUT] %s exceeded %lu ms\n", description, timeoutMs);
      return false;
    }
    delay(100);
    esp_task_wdt_reset();  // 超时等待时也要喂狗
  }

  return true;
}
```

### 4. 稳定性测试 (1.5h)

**测试方案**：

| 测试项 Test Item | 方法 Method | 预期结果 Expected |
|----------------|------------|-----------------|
| WiFi 断线重连 | 关闭路由器 30 秒后开启 | 自动重连成功 |
| NTP 精度 | 对比手机时间 | 误差 < 2 秒 |
| 传感器连续读取 | 运行 30 分钟 | 无 NaN 值 |
| 内存泄漏 | 运行 2 小时，监控内存 | 内存使用稳定 |
| 长时间运行 | 运行 12 小时 | 无重启/死机 |
| 触摸响应 | 频繁触摸 100 次 | 每次都正确响应 |
| 屏幕切换 | 连续切换 200 次 | 无闪烁/乱码 |
| Deep Sleep 唤醒 | 进入睡眠并唤醒 10 次 | 每次都正常唤醒 |

**内存监控**：

```cpp
// 内存使用监控
void printMemoryInfo() {
  Serial.println("--- Memory Info ---");
  Serial.printf("  Free Heap: %d bytes\n", ESP.getFreeHeap());
  Serial.printf("  Min Free Heap: %d bytes\n", ESP.getMinFreeHeap());
  Serial.printf("  Flash Size: %d bytes\n", ESP.getFlashChipSize());
  Serial.printf("  CPU Freq: %d MHz\n", ESP.getCpuFreqMHz());
  Serial.printf("  Uptime: %lu s\n", millis() / 1000);
}
```

**压力测试代码**：

```cpp
// 压力测试：快速循环所有功能
void stressTest() {
  Serial.println("Starting stress test...");

  for (int i = 0; i < 1000; i++) {
    // 切换屏幕
    switchScreen(i % SCREEN_COUNT);

    // 读取传感器
    float t = sht31.readTemperature();
    float h = sht31.readHumidity();

    // 更新显示
    struct tm timeinfo;
    getLocalTime(&timeinfo);

    // 检查 WiFi
    wifiConnected = (WiFi.status() == WL_CONNECTED);

    // 检查内存
    if (i % 100 == 0) {
      Serial.printf("Stress test iteration %d, Heap: %d\n",
                    i, ESP.getFreeHeap());
    }

    delay(100);
  }

  Serial.println("Stress test completed!");
}
```

### 5. 代码优化 (1h)

**优化建议**：

```cpp
// 1. 使用 PROGMEM 存储常量字符串（节省 RAM）
const char WEEKDAYS[][4] PROGMEM = {
  "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};

// 读取 PROGMEM 字符串
void printWeekday(int day) {
  char buffer[4];
  strcpy_P(buffer, (char*)pgm_read_word(&(WEEKDAYS[day])));
  Serial.println(buffer);
}

// 2. 避免频繁的 String 操作（使用 char[] 和 sprintf）
// 不好：
//   String msg = "Temp: " + String(temp) + "C";
// 好：
char msg[32];
sprintf(msg, "Temp: %.1fC", temp);

// 3. 减少不必要的浮点运算
// 使用整数运算替代（如果精度允许）
int tempInt = (int)(temp * 10);  // 25.3 -> 253 (0.1°C 精度的整数)

// 4. 避免在 loop() 中创建大对象
// 将大对象声明为全局变量或 static

// 5. 使用 const 和 #define 区分
// 编译时常量用 #define 或 const
// 运行时变量用普通变量
```

---

## 今日作业 | Today's Task

1. 完成全功能系统整合，所有模块正常协同工作
2. 看门狗定时器正常工作（故意制造卡死测试重启）
3. 完成稳定性测试（至少运行 2 小时无问题）
4. 代码优化：消除所有编译警告，使用 PROGMEM 存储常量
5. 编写完整的 README.md 文档
6. 整理代码结构，确保注释清晰

## 今日检查点 | Checkpoint

- [ ] 所有硬件模块（TFT、SHT31-D、WiFi、LED、触摸）正常工作？
- [ ] 看门狗定时器能检测卡死并重启系统？
- [ ] WiFi 断线能自动重连？
- [ ] 运行 2 小时以上无内存泄漏或重启？
- [ ] 代码无编译警告？
- [ ] 程序能正常进入和退出 Deep Sleep？
- [ ] 错误处理函数对各种异常情况都有应对？
- [ ] README.md 文档已编写完成？
