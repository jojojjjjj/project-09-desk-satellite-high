# Day 4: WiFi 联网与 NTP 时间同步 | WiFi & NTP Time Sync

## 今日目标 | Today's Goals

- 掌握 WiFi Station 模式连接路由器
- 理解 NTP 网络时间协议的工作原理
- 实现通过 NTP 获取精确时间
- 配置时区（东八区 UTC+8）
- 完成网络调试和连接稳定性测试

---

## 上午 (3h) | Morning Session

### 1. WiFi Station 模式深入 (1.5h)

**WiFi 工作模式**：

ESP32-C3 支持三种 WiFi 模式：
1. **Station 模式 (STA)**：作为客户端连接到路由器（本项目使用）
2. **AP 模式 (Access Point)**：自己作为热点，让其他设备连接
3. **STA + AP 混合模式**：同时连接路由器并提供热点

**WiFi 连接流程**：

```
ESP32-C3                    路由器 Router                    NTP 服务器
   │                            │                              │
   │  1. WiFi.begin(ssid, pwd)  │                              │
   │──────────────────────────▶│                              │
   │  2. DHCP 获取 IP 地址       │                              │
   │◀──────────────────────────│                              │
   │  3. WiFi.status() ==       │                              │
   │     WL_CONNECTED           │                              │
   │                            │  4. NTP 请求 (UDP port 123)  │
   │──────────────────────────────────────────────────────────▶│
   │                            │  5. NTP 响应 (时间戳)         │
   │◀──────────────────────────────────────────────────────────│
```

**健壮的 WiFi 连接函数**：

```cpp
// WiFi 连接管理器
#include <WiFi.h>

const char* WIFI_SSID     = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

bool connectWiFi(int timeoutSeconds = 15) {
  Serial.printf("Connecting to WiFi: %s\n", WIFI_SSID);

  WiFi.mode(WIFI_STA);        // 设置为 Station 模式
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < timeoutSeconds * 2) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi connected successfully!");
    Serial.print("  IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.print("  Gateway: ");
    Serial.println(WiFi.gatewayIP());
    Serial.print("  DNS: ");
    Serial.println(WiFi.dnsIP());
    Serial.print("  RSSI: ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
    return true;
  } else {
    Serial.println("WiFi connection FAILED!");
    Serial.printf("  Status code: %d\n", WiFi.status());
    return false;
  }
}

// WiFi 状态码含义
void printWiFiStatus() {
  switch (WiFi.status()) {
    case WL_IDLE_STATUS:     Serial.println("Idle"); break;
    case WL_NO_SSID_AVAIL:   Serial.println("SSID not found"); break;
    case WL_SCAN_COMPLETED:  Serial.println("Scan completed"); break;
    case WL_CONNECTED:       Serial.println("Connected"); break;
    case WL_CONNECT_FAILED:  Serial.println("Connection failed"); break;
    case WL_CONNECTION_LOST: Serial.println("Connection lost"); break;
    case WL_DISCONNECTED:    Serial.println("Disconnected"); break;
    default:                 Serial.println("Unknown status"); break;
  }
}

// WiFi 断线重连
void checkWiFiConnection() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected! Reconnecting...");
    connectWiFi(10);
  }
}
```

**讨论**：
- 为什么 WiFi 连接可能失败？（密码错误、信号弱、路由器限制 MAC、信道不兼容）
- WiFi 状态码有什么用？（调试时判断失败原因）
- 为什么需要断线重连？（WiFi 信号不稳定、路由器重启）

### 2. NTP 协议原理 (1.5h)

**什么是 NTP？**

NTP (Network Time Protocol) 是一种通过网络获取精确时间的协议：
- 使用 UDP 协议（端口 123）
- 精度可达毫秒级
- 通过层级（Stratum）传播时间：原子钟 -> 一级服务器 -> 二级服务器 -> 我们的设备

**NTP 工作流程**：

```
1. ESP32-C3 发送 NTP 请求到 time.nist.gov 或 pool.ntp.org
   - 请求很小（48 字节 UDP 数据包）
   - 包含发送时间戳 T1

2. NTP 服务器回复
   - 包含 T1（客户端发送时间）
   - T2（服务器收到时间）
   - T3（服务器回复时间）
   - 客户端收到时间为 T4

3. 计算时间偏差
   - 往返延迟 = (T4 - T1) - (T3 - T2)
   - 时间偏差 = ((T2 - T1) + (T3 - T4)) / 2
   - 校正后的时间 = T4 + 时间偏差
```

**ESP32 上的 NTP 使用**：

ESP32 Arduino Core 内置了简化的 NTP 支持，使用 `configTime()` 函数：

```cpp
#include <WiFi.h>
#include "time.h"

// NTP 服务器配置
const char* NTP_SERVER_1 = "pool.ntp.org";       // 全球 NTP 池
const char* NTP_SERVER_2 = "time.nist.gov";      // 美国国家标准与技术研究院
const char* NTP_SERVER_3 = "cn.ntp.org.cn";      // 中国 NTP 服务器

// 时区配置
// 东八区 (北京时间) = UTC + 8 小时
// gmtOffset_sec = 8 * 3600 = 28800 秒
// daylightOffset_sec = 0 (中国不使用夏令时)
const long GMT_OFFSET_SEC = 8 * 3600;   // UTC+8
const int  DAYLIGHT_OFFSET_SEC = 0;     // 无夏令时

void setupNTP() {
  // 配置 NTP
  configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC,
             NTP_SERVER_1, NTP_SERVER_2, NTP_SERVER_3);

  Serial.println("Waiting for NTP time sync...");

  struct tm timeinfo;
  int attempts = 0;
  while (!getLocalTime(&timeinfo) && attempts < 20) {
    Serial.print(".");
    delay(500);
    attempts++;
  }
  Serial.println();

  if (attempts < 20) {
    Serial.println("NTP time synchronized!");
    Serial.println(&timeinfo, "  Current time: %A, %B %d %Y %H:%M:%S");
  } else {
    Serial.println("NTP sync failed!");
  }
}
```

---

## 下午 (4h) | Afternoon Session

### 3. 时区配置详解 (0.5h)

**全球时区对照表**：

| 地区 Region | 时区 Timezone | gmtOffset_sec | daylightOffset_sec |
|------------|--------------|--------------|-------------------|
| 中国北京 Beijing | UTC+8 | 28800 | 0 |
| 日本东京 Tokyo | UTC+9 | 32400 | 0 |
| 美国东部 US Eastern | UTC-5 | -18000 | 3600 |
| 美国西部 US Pacific | UTC-8 | -28800 | 3600 |
| 英国伦敦 London | UTC+0 | 0 | 3600 |
| 德国柏林 Berlin | UTC+1 | 3600 | 3600 |

```cpp
// 时区配置示例 - 修改这两行即可切换时区
const long GMT_OFFSET_SEC = 8 * 3600;      // 北京时间 UTC+8
const int  DAYLIGHT_OFFSET_SEC = 0;         // 中国无夏令时
```

### 4. 完整的时钟程序 (2h)

**目标**：在 TFT 上显示实时时钟 + 日期 + 温湿度

```cpp
// Desk Satellite - 完整时钟 + 温湿度
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_SHT31.h>
#include <SPI.h>
#include <Wire.h>
#include <WiFi.h>
#include "time.h"

// ========== 配置 Configuration ==========
const char* WIFI_SSID     = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
const long  GMT_OFFSET    = 8 * 3600;    // UTC+8 北京时间
const int   DST_OFFSET    = 0;           // 无夏令时

// ========== 引脚定义 Pin Definitions ==========
#define TFT_SCLK 4
#define TFT_MOSI 5
#define TFT_CS   6
#define TFT_DC   7
#define TFT_RST  10
#define I2C_SDA  0
#define I2C_SCL  1

// ========== 全局对象 Global Objects ==========
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
Adafruit_SHT31 sht31 = Adafruit_SHT31();

// ========== 全局变量 Global Variables ==========
unsigned long lastDisplayUpdate = 0;
unsigned long lastSensorRead    = 0;
unsigned long lastNTPSync       = 0;
float currentTemp = 0;
float currentHum  = 0;
bool wifiConnected = false;

// ========== WiFi 连接 ==========
bool connectWiFi() {
  Serial.printf("Connecting to %s ", WIFI_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 30) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("WiFi connected! IP: ");
    Serial.println(WiFi.localIP());
    return true;
  }
  Serial.println("WiFi connection failed.");
  return false;
}

// ========== NTP 同步 ==========
void syncNTP() {
  configTime(GMT_OFFSET, DST_OFFSET, "pool.ntp.org", "time.nist.gov");

  struct tm timeinfo;
  if (getLocalTime(&timeinfo)) {
    Serial.println("NTP sync successful!");
    lastNTPSync = millis();
  } else {
    Serial.println("NTP sync failed.");
  }
}

// ========== 显示时钟 ==========
void displayClock() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to get time");
    return;
  }

  tft.fillScreen(ST7735_BLACK);

  // 时间 (大字号)
  tft.setTextSize(3);
  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(10, 5);

  char timeStr[10];
  strftime(timeStr, sizeof(timeStr), "%H:%M:%S", &timeinfo);
  tft.print(timeStr);

  // 日期
  tft.setTextSize(1);
  tft.setTextColor(ST7735_CYAN);
  tft.setCursor(10, 32);

  char dateStr[20];
  strftime(dateStr, sizeof(dateStr), "%Y-%m-%d %A", &timeinfo);
  tft.print(dateStr);

  // 分隔线
  tft.drawFastHLine(5, 42, 150, ST7735_CYAN);

  // 温度
  tft.setTextSize(2);
  tft.setTextColor(ST7735_YELLOW);
  tft.setCursor(10, 48);
  tft.printf("%.1fC", currentTemp);

  // 湿度
  tft.setTextColor(ST7735_GREEN);
  tft.setCursor(90, 48);
  tft.printf("%.0f%%", currentHum);

  // WiFi 状态
  tft.setTextSize(1);
  tft.setTextColor(wifiConnected ? ST7735_GREEN : ST7735_RED);
  tft.setCursor(10, 70);
  tft.print(wifiConnected ? "WiFi:OK" : "WiFi:NO");
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("=== Desk Satellite Starting ===");

  // 初始化 I2C 和传感器
  Wire.begin(I2C_SDA, I2C_SCL);
  if (!sht31.begin(0x44)) {
    Serial.println("SHT31-D init failed!");
  } else {
    Serial.println("SHT31-D initialized.");
  }

  // 初始化 TFT
  tft.initR(INITR_GREENTAB160x80);
  tft.setRotation(1);
  tft.fillScreen(ST7735_BLACK);
  tft.setTextSize(1);
  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(5, 30);
  tft.print("Connecting WiFi...");

  // 连接 WiFi
  wifiConnected = connectWiFi();

  if (wifiConnected) {
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(5, 30);
    tft.print("Syncing time...");
    syncNTP();
  }
}

void loop() {
  unsigned long now = millis();

  // 每 1 秒更新显示
  if (now - lastDisplayUpdate >= 1000) {
    displayClock();
    lastDisplayUpdate = now;
  }

  // 每 5 秒读取传感器
  if (now - lastSensorRead >= 5000) {
    float t = sht31.readTemperature();
    float h = sht31.readHumidity();
    if (!isnan(t)) currentTemp = t;
    if (!isnan(h)) currentHum  = h;
    lastSensorRead = now;
  }

  // 每小时重新同步 NTP
  if (now - lastNTPSync >= 3600000) {
    if (WiFi.status() == WL_CONNECTED) {
      syncNTP();
    }
  }

  // 检查 WiFi 连接
  if (WiFi.status() != WL_CONNECTED && wifiConnected) {
    wifiConnected = false;
    Serial.println("WiFi lost! Reconnecting...");
    wifiConnected = connectWiFi();
    if (wifiConnected) syncNTP();
  }
}
```

### 5. 网络调试技巧 (1h)

**串口调试输出**：

```cpp
// 调试级别的串口输出
#define DEBUG_ENABLED true

#if DEBUG_ENABLED
  #define DBG(x) Serial.print(x)
  #define DBGLN(x) Serial.println(x)
  #define DBGF(...) Serial.printf(__VA_ARGS__)
#else
  #define DBG(x)
  #define DBGLN(x)
  #define DBGF(...)
#endif

// 使用示例
DBGF("WiFi status: %d, RSSI: %d dBm\n", WiFi.status(), WiFi.RSSI());
```

**常见网络问题及解决方法**：

| 问题 Problem | 可能原因 Cause | 解决方法 Solution |
|-------------|--------------|-----------------|
| WiFi 连接超时 | SSID/密码错误 | 检查大小写和特殊字符 |
| WiFi 连接超时 | 信号太弱 | 靠近路由器或检查天线 |
| NTP 同步失败 | DNS 无法解析 | 尝试使用 IP 地址 |
| NTP 同步失败 | UDP 被防火墙拦截 | 尝试其他 NTP 服务器 |
| 时间不准确 | 时区配置错误 | 检查 gmtOffset_sec 值 |
| WiFi 频繁断线 | 电源不稳定 | 确保 3.3V 供电充足 |

**WiFi 信号强度参考**：

| RSSI (dBm) | 信号质量 Signal Quality |
|-----------|----------------------|
| -30 to -50 | 极好 Excellent |
| -50 to -60 | 良好 Good |
| -60 to -70 | 一般 Fair |
| -70 to -80 | 较弱 Weak |
| < -80 | 极差 Very Poor |

### 6. 配置文件模板 (0.5h)

**创建独立的配置头文件**：

将 WiFi 密码等敏感信息与主程序分离，创建 `config.h`：

```cpp
// config.h - 配置文件（不要提交到 Git！）
// 在 .gitignore 中添加此文件

#ifndef CONFIG_H
#define CONFIG_H

// WiFi 配置
#define WIFI_SSID     "YourWiFiName"
#define WIFI_PASSWORD "YourWiFiPassword"

// 时区配置 (UTC+8 北京时间)
#define GMT_OFFSET_SEC  (8 * 3600)
#define DST_OFFSET_SEC  0

// NTP 服务器
#define NTP_SERVER_1 "pool.ntp.org"
#define NTP_SERVER_2 "time.nist.gov"

// 引脚定义 Pin Definitions
#define PIN_TFT_SCLK  4
#define PIN_TFT_MOSI  5
#define PIN_TFT_CS    6
#define PIN_TFT_DC    7
#define PIN_TFT_RST   10
#define PIN_I2C_SDA   0
#define PIN_I2C_SCL   1
#define PIN_LED       8
#define PIN_TOUCH     2

// 传感器配置
#define SHT31_ADDRESS  0x44
#define SENSOR_INTERVAL_MS  5000    // 传感器读取间隔
#define DISPLAY_INTERVAL_MS 1000    // 显示刷新间隔
#define NTP_SYNC_INTERVAL_MS 3600000 // NTP 重新同步间隔 (1小时)

#endif
```

---

## 今日作业 | Today's Task

1. 完成 WiFi 连接，成功获取 IP 地址
2. 完成 NTP 时间同步，串口打印当前时间
3. 完成完整时钟程序：TFT 显示时钟 + 日期 + 温湿度
4. 创建 config.h 配置文件，将 WiFi 信息与主程序分离
5. 测试断线重连功能：关闭路由器 10 秒再开启，观察设备是否自动重连
6. **HW1 准备**：整理 Day 1-4 的学习笔记，准备明天提交第一周进度汇报

## 今日检查点 | Checkpoint

- [ ] WiFi 能稳定连接到路由器？
- [ ] 串口打印的 NTP 时间准确？
- [ ] TFT 显示屏能显示实时时钟（精确到秒）？
- [ ] 时区配置正确（UTC+8）？
- [ ] 断线重连功能正常工作？
- [ ] 温湿度数据在 TFT 上实时更新？
- [ ] config.h 配置文件已创建？
