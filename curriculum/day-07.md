# Day 7: 交互功能与低功耗设计 | Interaction & Low Power Design

## 今日目标 | Today's Goals

- 实现触摸开关控制（TTP223 触摸传感器）
- 实现 LED 指示灯控制
- 学习 ESP32-C3 深度睡眠（Deep Sleep）模式
- 理解中断处理机制
- 设计低功耗运行策略

---

## 上午 (3h) | Morning Session

### 1. 触摸开关控制 (1.5h)

**TTP223 触摸传感器模块**：

```
TTP223 触摸开关模块：
- 工作电压：2.0V - 5.5V
- 输出：HIGH（触摸时）/ LOW（未触摸）
- 灵敏度可调（模块背面的电容）
- 响应速度快（< 60ms）
- 功耗极低（待机约 2.5uA）

引脚：
  VCC - 电源 (3.3V)
  GND - 地线
  SIG - 信号输出 (连接到 ESP32-C3 GPIO)
```

**接线与基本使用**：

```
ESP32-C3          TTP223 触摸模块
─────────         ───────────────
3V3         ────▶ VCC
GND         ────▶ GND
GPIO2       ────▶ SIG (信号输出)
```

```cpp
// 触摸开关基本读取
#define TOUCH_PIN 2

bool touchPressed = false;
bool lastTouchState = false;
unsigned long lastDebounceTime = 0;
#define DEBOUNCE_DELAY 200  // 消抖延迟 200ms

void setup() {
  Serial.begin(115200);
  pinMode(TOUCH_PIN, INPUT);
}

void loop() {
  int reading = digitalRead(TOUCH_PIN);

  // 消抖处理
  if (reading != lastTouchState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    if (reading != touchPressed) {
      touchPressed = reading;

      if (touchPressed) {
        Serial.println("Touch: PRESSED");
        onTouchUpInside();
      } else {
        Serial.println("Touch: RELEASED");
        onTouchRelease();
      }
    }
  }

  lastTouchState = reading;
}
```

**触摸开关功能设计**：

```cpp
// 触摸开关功能定义
// 短按 (< 1s)：切换屏幕
// 长按 (> 2s)：进入/退出睡眠模式

unsigned long touchPressTime = 0;
bool isSleeping = false;

void handleTouchEvent() {
  if (touchPressed && touchPressTime == 0) {
    // 刚按下
    touchPressTime = millis();
  }

  if (!touchPressed && touchPressTime > 0) {
    // 刚释放
    unsigned long pressDuration = millis() - touchPressTime;

    if (pressDuration < 1000) {
      // 短按：切换屏幕
      int nextScreen = (currentScreen + 1) % SCREEN_COUNT;
      switchScreen(nextScreen);
      Serial.printf("Short press -> Screen %d\n", nextScreen);

    } else if (pressDuration >= 2000) {
      // 长按：切换睡眠模式
      if (isSleeping) {
        wakeUp();
      } else {
        goToSleep();
      }
    }

    touchPressTime = 0;
  }

  // 持续按住时的反馈
  if (touchPressed && touchPressTime > 0) {
    unsigned long elapsed = millis() - touchPressTime;
    if (elapsed > 500 && elapsed < 2000) {
      // 显示"正在长按"的视觉反馈
      tft.fillCircle(80, 40, 3, ST7735_YELLOW);
    }
    if (elapsed >= 2000) {
      // 显示"即将进入睡眠"的视觉反馈
      tft.fillCircle(80, 40, 5, ST7735_RED);
    }
  }
}
```

**讨论**：
- 为什么触摸开关需要消抖？（电容触摸传感器可能有抖动）
- 短按和长按的区别有什么实际用途？
- 触摸开关和物理按钮各有什么优缺点？

### 2. LED 指示灯控制 (1.5h)

**LED 指示灯设计**：

Desk Satellite 使用 LED 指示灯显示不同的工作状态：

```
LED 指示灯功能：
- 电源指示灯（常亮/灭）：设备是否开机
- WiFi 指示灯：WiFi 连接状态
- 充电指示灯：充电状态
- 状态灯（呼吸效果）：正常工作中
```

```cpp
// LED 控制模块
#define LED_POWER_PIN   3   // 电源指示 LED
#define LED_STATUS_PIN  8   // 状态指示 LED (板载)

typedef enum {
  LED_OFF,           // 关闭
  LED_ON,            // 常亮
  LED_BLINK_SLOW,    // 慢闪 (1s)
  LED_BLINK_FAST,    // 快闪 (200ms)
  LED_BREATHE,       // 呼吸灯效果
  LED_BLINK_ERROR    // 错误闪烁 (SOS)
} LEDMode;

LEDMode statusLEDMode = LED_BREATHE;

void updateStatusLED() {
  static unsigned long lastToggle = 0;
  static bool ledState = false;
  static int breatheValue = 0;
  static int breatheDir = 1;

  unsigned long now = millis();

  switch (statusLEDMode) {
    case LED_OFF:
      digitalWrite(LED_STATUS_PIN, LOW);
      break;

    case LED_ON:
      digitalWrite(LED_STATUS_PIN, HIGH);
      break;

    case LED_BLINK_SLOW:
      if (now - lastToggle >= 1000) {
        ledState = !ledState;
        digitalWrite(LED_STATUS_PIN, ledState);
        lastToggle = now;
      }
      break;

    case LED_BLINK_FAST:
      if (now - lastToggle >= 200) {
        ledState = !ledState;
        digitalWrite(LED_STATUS_PIN, ledState);
        lastToggle = now;
      }
      break;

    case LED_BREATHE:
      // 呼吸灯效果 (使用 PWM 模拟)
      breatheValue += breatheDir * 5;
      if (breatheValue >= 255 || breatheValue <= 0) {
        breatheDir = -breatheDir;
      }
      // ESP32-C3 支持 ledcWrite 进行 PWM 输出
      ledcWrite(0, breatheValue);
      break;

    case LED_BLINK_ERROR:
      // SOS 闪烁 (... --- ...)
      // 简化版：快速闪烁
      if (now - lastToggle >= 100) {
        ledState = !ledState;
        digitalWrite(LED_STATUS_PIN, ledState);
        lastToggle = now;
      }
      break;
  }
}

// 设置 LED 模式
void setLEDMode(LEDMode mode) {
  statusLEDMode = mode;

  // 初始化 PWM（呼吸灯模式）
  if (mode == LED_BREATHE) {
    ledcSetup(0, 5000, 8);      // 通道 0, 5kHz, 8-bit
    ledcAttachPin(LED_STATUS_PIN, 0);
  }
}
```

**LED 状态映射**：

```cpp
// 根据系统状态自动设置 LED 模式
void updateLEDBySystemState() {
  if (!wifiConnected) {
    setLEDMode(LED_BLINK_FAST);   // WiFi 未连接 -> 快闪
  } else if (currentChargeStatus == CHARGE_STATUS_CHARGING) {
    setLEDMode(LED_BREATHE);      // 充电中 -> 呼吸灯
  } else {
    setLEDMode(LED_BREATHE);      // 正常工作 -> 呼吸灯
  }
}
```

---

## 下午 (4h) | Afternoon Session

### 3. 深度睡眠模式 (1.5h)

**ESP32-C3 低功耗模式**：

```
ESP32-C3 功耗模式：

模式            功耗          WiFi   CPU    RAM    唤醒方式
──────────────────────────────────────────────────────────
Active          ~120 mA       ON     ON     ON     -
Modem Sleep     ~15 mA        OFF    ON     ON     定时器
Light Sleep     ~8 mA         OFF    暂停   ON     GPIO / 定时器
Deep Sleep      ~5-15 uA      OFF    OFF   RTC    GPIO / 定时器 / 触摸
```

**Deep Sleep 的核心概念**：
- CPU 和大部分外设关闭，仅 RTC（实时时钟）运行
- RAM 数据丢失（需要保存到 RTC 内存）
- 通过 GPIO 或定时器唤醒
- 唤醒后程序从头开始运行（类似重启）

```cpp
// Deep Sleep 使用
#include <esp_sleep.h>

// RTC 内存（Deep Sleep 后不丢失）
RTC_DATA_ATTR int bootCount = 0;
RTC_DATA_ATTR float lastTemp = 0;
RTC_DATA_ATTR float lastHum = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);

  bootCount++;
  Serial.printf("Boot count: %d\n", bootCount);

  // 检查唤醒原因
  esp_sleep_wakeup_cause_t wakeupReason = esp_sleep_get_wakeup_cause();

  switch (wakeupReason) {
    case ESP_SLEEP_WAKEUP_TIMER:
      Serial.println("Woke up from timer");
      break;
    case ESP_SLEEP_WAKEUP_GPIO:
      Serial.println("Woke up from GPIO (touch switch)");
      break;
    default:
      Serial.println("Normal boot (not from sleep)");
      break;
  }
}

// 进入 Deep Sleep
void goToSleep(int sleepSeconds) {
  Serial.printf("Going to deep sleep for %d seconds...\n", sleepSeconds);

  // 关闭外设
  tft.fillScreen(ST7735_BLACK);
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

  // 设置唤醒源

  // 1. 定时器唤醒（每 sleepSeconds 秒唤醒一次）
  esp_sleep_enable_timer_wakeup(sleepSeconds * 1000000);  // 微秒

  // 2. GPIO 唤醒（触摸开关）
  esp_sleep_enable_gpio_wakeup();
  gpio_wakeup_enable(GPIO_NUM_2, GPIO_INTR_LOW_LEVEL);

  // 进入 Deep Sleep
  esp_deep_sleep_start();

  // 这行代码永远不会执行
  Serial.println("This will never be printed");
}

void loop() {
  // 正常工作模式
  readSensors();
  displayData();

  // 如果一段时间无操作，进入睡眠
  if (millis() - lastActivityTime > 300000) {  // 5 分钟无操作
    goToSleep(60);  // 睡眠 60 秒后唤醒更新数据
  }
}
```

**智能功耗管理策略**：

```cpp
// 智能功耗管理
typedef enum {
  POWER_MODE_ACTIVE,     // 全速运行 (屏幕亮, WiFi 开)
  POWER_MODE_DIM,        // 降低亮度 (屏幕暗, WiFi 开)
  POWER_MODE_SAVE,       // 省电模式 (屏幕关, WiFi 开, 降低刷新率)
  POWER_MODE_SLEEP       // 深度睡眠 (全部关闭)
} PowerMode;

PowerMode currentPowerMode = POWER_MODE_ACTIVE;
unsigned long lastActivityTime = 0;

void updatePowerMode() {
  unsigned long idleTime = millis() - lastActivityTime;

  if (idleTime > 300000) {       // 5 分钟无操作
    currentPowerMode = POWER_MODE_SLEEP;
    goToSleep(60);
  } else if (idleTime > 180000) { // 3 分钟无操作
    currentPowerMode = POWER_MODE_SAVE;
    // 降低刷新频率
  } else if (idleTime > 60000) {  // 1 分钟无操作
    currentPowerMode = POWER_MODE_DIM;
    // 降低屏幕亮度
  } else {
    currentPowerMode = POWER_MODE_ACTIVE;
  }
}
```

### 4. 中断处理 (1h)

**什么是中断？**

中断是一种硬件机制，当特定事件发生时，CPU 暂停当前程序，跳转到中断服务函数（ISR）执行，处理完后返回原程序。

```
正常程序流程：
  ┌───┐   ┌───┐   ┌───┐   ┌───┐
  │ A │──▶│ B │──▶│ C │──▶│ D │
  └───┘   └───┘   └───┘   └───┘

中断发生时：
  ┌───┐   ┌───┐         ┌───┐   ┌───┐
  │ A │──▶│ B │──▶ ISR ──▶│ C │──▶│ D │
  └───┘   └───┘   ↑      └───┘   └───┘
                   │
              中断触发信号
```

**ESP32-C3 GPIO 中断**：

```cpp
// GPIO 中断处理
volatile bool touchInterruptFlag = false;

// 中断服务函数 (ISR) - 必须尽量简短！
void IRAM_ATTR onTouchInterrupt() {
  touchInterruptFlag = true;
}

void setup() {
  Serial.begin(115200);

  // 配置触摸引脚为输入 + 内部上拉
  pinMode(TOUCH_PIN, INPUT_PULLUP);

  // 附加中断：下降沿触发（触摸时信号从高变低）
  attachInterrupt(digitalPinToInterrupt(TOUCH_PIN),
                  onTouchInterrupt,
                  FALLING);
}

void loop() {
  // 在主循环中处理中断标志
  if (touchInterruptFlag) {
    touchInterruptFlag = false;  // 清除标志
    handleTouch();
  }

  // 其他正常任务...
}

void handleTouch() {
  Serial.println("Touch interrupt detected!");
  lastActivityTime = millis();  // 更新活动时间

  // 如果在睡眠模式，唤醒
  // 如果在正常模式，切换屏幕
}
```

**ISR 规则**（必须遵守）：
1. **必须简短**：尽快返回，不要在 ISR 中做复杂操作
2. **不能使用 delay()**：ISR 中 delay() 不会工作
3. **不能使用 Serial**：串口输出可能不可靠
4. **使用 volatile 变量**：与主循环共享的变量必须声明为 `volatile`
5. **使用 IRAM_ATTR**：将 ISR 放在内部 RAM 中（Flash 访问可能太慢）

### 5. 综合实战：完整的交互系统 (1.5h)

**整合触摸 + LED + 电源管理**：

```cpp
// 主循环框架 - 整合所有交互功能
void loop() {
  unsigned long now = millis();

  // 1. 处理触摸事件
  handleTouchEvent();

  // 2. 更新显示（根据当前屏幕和功耗模式）
  if (currentPowerMode != POWER_MODE_SLEEP) {
    if (now - lastDisplayUpdate >= DISPLAY_INTERVAL_MS) {
      switch (currentScreen) {
        case SCREEN_CLOCK:   displayClockScreen(&timeinfo); break;
        case SCREEN_WEATHER: displayWeatherScreen(); break;
        case SCREEN_SYSTEM:  displaySystemScreen(); break;
      }
      lastDisplayUpdate = now;
    }
  }

  // 3. 读取传感器（降低频率）
  if (now - lastSensorRead >= SENSOR_INTERVAL_MS) {
    float t = sht31.readTemperature();
    float h = sht31.readHumidity();
    if (!isnan(t)) currentTemp = t;
    if (!isnan(h)) currentHum  = h;
    lastSensorRead = now;
  }

  // 4. 更新 LED 状态
  updateStatusLED();

  // 5. 检查 WiFi 连接
  if (WiFi.status() != WL_CONNECTED && wifiConnected) {
    wifiConnected = false;
    setLEDMode(LED_BLINK_FAST);
    wifiConnected = connectWiFi();
    if (wifiConnected) setLEDMode(LED_BREATHE);
  }

  // 6. NTP 重新同步
  if (now - lastNTPSync >= NTP_SYNC_INTERVAL_MS && wifiConnected) {
    syncNTP();
  }

  // 7. 更新电池状态
  if (now - lastBatteryUpdate >= 30000) {  // 每 30 秒
    updatePowerStatus();
    lastBatteryUpdate = now;
  }

  // 8. 功耗管理
  updatePowerMode();
}
```

---

## 今日作业 | Today's Task

1. 完成触摸开关的接线，能检测触摸事件
2. 实现短按切换屏幕、长按进入睡眠的功能
3. LED 指示灯能根据系统状态自动切换模式
4. Deep Sleep 模式能正常进入和唤醒
5. 整合所有交互功能到主循环框架中
6. 测试功耗：测量正常工作和 Deep Sleep 时的电流（如有电流表）

## 今日检查点 | Checkpoint

- [ ] 触摸开关能正确检测触摸事件？
- [ ] 短按能切换屏幕（3 个界面循环）？
- [ ] LED 呼吸灯效果正常？
- [ ] LED 能根据 WiFi 状态自动切换模式？
- [ ] Deep Sleep 模式能正常进入？
- [ ] Deep Sleep 后能通过定时器或 GPIO 唤醒？
- [ ] 知道 ISR 中不能使用 delay() 和 Serial 吗？
- [ ] 知道 Deep Sleep 后 RAM 数据会丢失吗？（需要 RTC_DATA_ATTR）
