// =============================================================================
// Desk Satellite - 桌面气象卫星 / Desk Weather Satellite
// =============================================================================
//
// 硬件平台: ESP32-C3
// 功能: 温湿度显示 + 网络时钟 + 触摸控制
// Features: Temperature/Humidity display + Network clock + Touch control
//
// 硬件连接 / Hardware Connections:
//   - ST7735 TFT 显示屏 (SPI): MOSI=7, SCK=6, CS=10, DC=2, RST=3, BL=8
//   - SHT31-D 温湿度传感器 (I2C): SDA=4, SCL=5
//   - 触摸开关: GPIO 9
//   - LED 指示灯: GPIO 0
//   - 3.7V LiPo 电池 + Type-C 充电 + 太阳能输入
//
// 作者 / Author: Based on project by Huy Vector
// 许可 / License: MIT
//
// =============================================================================

#include "config.h"

// =============================================================================
// 库引用 / Library Includes
// =============================================================================

#include <WiFi.h>
#include <Wire.h>
#include <SPI.h>
#include <time.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_SHT31.h>
#include <esp_sleep.h>

// =============================================================================
// 全局对象 / Global Objects
// =============================================================================

// TFT 显示屏对象 / TFT display object
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// SHT31 温湿度传感器对象 / SHT31 sensor object
Adafruit_SHT31 sht31 = Adafruit_SHT31();

// =============================================================================
// 全局状态变量 / Global State Variables
// =============================================================================

// 传感器数据 / Sensor data
float currentTemp = 0.0;           // 当前温度 (摄氏度) / Current temperature (Celsius)
float currentHumidity = 0.0;       // 当前湿度 (百分比) / Current humidity (percent)
bool sensorOK = false;             // 传感器是否正常 / Sensor health status

// WiFi 状态 / WiFi status
bool wifiConnected = false;        // WiFi 是否已连接 / WiFi connection status
int wifiReconnectAttempts = 0;     // 重连尝试计数 / Reconnection attempt counter

// 时间状态 / Time status
bool timeSynced = false;           // 时间是否已同步 / Time sync status
struct tm timeinfo;                // 当前时间结构 / Current time structure
char timeStr[9];                   // 时钟字符串 "HH:MM:SS" / Clock string
char dateStr[16];                  // 日期字符串 / Date string

// 显示状态 / Display state
bool screenOn = true;              // 屏幕是否开启 / Screen on/off state
unsigned long lastScreenActivity = 0; // 上次屏幕活动时间 / Last screen activity time

// 定时器变量 / Timer variables
unsigned long lastSensorUpdate = 0;    // 上次传感器更新 / Last sensor update time
unsigned long lastDisplayUpdate = 0;   // 上次显示更新 / Last display update time
unsigned long lastNtpSync = 0;         // 上次 NTP 同步 / Last NTP sync time
unsigned long lastWifiCheck = 0;       // 上次 WiFi 检查 / Last WiFi check time

// 触摸开关状态 / Touch switch state
volatile bool touchTriggered = false;      // 触摸中断标志 / Touch interrupt flag
volatile unsigned long touchTime = 0;       // 触摸时间戳 / Touch timestamp
bool wasTouched = false;                    // 上一周期触摸状态 / Previous touch state

// 错误计数 / Error counters
int sensorErrorCount = 0;          // 传感器错误计数 / Sensor error counter
int wifiErrorCount = 0;            // WiFi 错误计数 / WiFi error counter

// 显示缓冲 / Display buffer
char buffer[32];                   // 通用格式化缓冲 / General format buffer

// =============================================================================
// 函数声明 / Function Declarations
// =============================================================================

void initWiFi();
void initDisplay();
void initSensor();
void initTouch();
void initNTP();
void connectWiFi();
void checkWiFi();
bool syncNTP();
void readSensor();
void updateDisplay();
void displayClock();
void displayDate();
void displayTemperature();
void displayHumidity();
void displayWiFiStatus();
void displaySensorError();
void displayStartupScreen();
void displaySleepScreen();
void turnScreenOn();
void turnScreenOff();
void handleTouch();
void enterDeepSleep();
void IRAM_ATTR onTouchInterrupt();
void setLED(bool state);
void blinkLED(int times, int intervalMs);
void debugPrint(const char* message);
void debugPrintln(const char* message);
void drawCenteredText(const char* text, int y, int textSize, uint16_t color);
void drawProgressBar(int x, int y, int w, int h, int progress, uint16_t color);

// =============================================================================
// 初始化设置 / Setup
// =============================================================================

void setup() {
  // 初始化串口 / Initialize serial
  #if DEBUG_ENABLED
  Serial.begin(SERIAL_BAUD_RATE);
  delay(1000);
  debugPrintln("=== Desk Satellite 启动中... ===");
  debugPrintln("=== Desk Satellite Starting... ===");
  #endif

  // 初始化 LED 引脚 / Initialize LED pin
  pinMode(LED_PIN, OUTPUT);
  setLED(false);

  // 初始化触摸开关 / Initialize touch switch
  initTouch();

  // 初始化显示屏 / Initialize display
  initDisplay();

  // 显示启动画面 / Show startup screen
  displayStartupScreen();

  // 初始化传感器 / Initialize sensor
  initSensor();

  // 连接 WiFi / Connect to WiFi
  connectWiFi();

  // 同步 NTP 时间 / Sync NTP time
  if (wifiConnected) {
    initNTP();
  }

  // LED 指示初始化完成 / LED indicates init complete
  blinkLED(3, 100);
  setLED(true);

  // 初始化定时器 / Initialize timers
  unsigned long now = millis();
  lastSensorUpdate = now;
  lastDisplayUpdate = now;
  lastNtpSync = now;
  lastWifiCheck = now;
  lastScreenActivity = now;

  // 首次读取传感器 / First sensor reading
  readSensor();

  debugPrintln("=== 初始化完成! ===");
  debugPrintln("=== Initialization Complete! ===");
}

// =============================================================================
// 主循环 / Main Loop
// =============================================================================

void loop() {
  unsigned long now = millis();

  // ---- 处理触摸开关 / Handle touch switch ----
  handleTouch();

  // ---- 检查屏幕自动关闭 / Check screen auto-off ----
  #if SCREEN_TIMEOUT_MS > 0
  if (screenOn && (now - lastScreenActivity >= SCREEN_TIMEOUT_MS)) {
    debugPrintln("屏幕超时，自动关闭 / Screen timeout, auto-off");
    turnScreenOff();
  }
  #endif

  // 如果屏幕关闭，跳过大部分处理 / Skip processing if screen is off
  if (!screenOn) {
    delay(100);
    return;
  }

  // ---- WiFi 状态检查 / WiFi status check ----
  if (now - lastWifiCheck >= WIFI_CHECK_INTERVAL_MS) {
    lastWifiCheck = now;
    checkWiFi();
  }

  // ---- NTP 时间同步 / NTP time sync ----
  if (wifiConnected && (now - lastNtpSync >= NTP_SYNC_INTERVAL_MS)) {
    lastNtpSync = now;
    syncNTP();
  }

  // ---- 传感器数据更新 / Sensor data update ----
  if (now - lastSensorUpdate >= SENSOR_UPDATE_INTERVAL_MS) {
    lastSensorUpdate = now;
    readSensor();
  }

  // ---- 显示刷新 / Display refresh ----
  if (now - lastDisplayUpdate >= DISPLAY_UPDATE_INTERVAL_MS) {
    lastDisplayUpdate = now;
    updateDisplay();
  }

  // 短暂延时，避免过度占用 CPU / Short delay to avoid excessive CPU usage
  delay(50);
}

// =============================================================================
// WiFi 连接 / WiFi Connection
// =============================================================================

/**
 * 连接到 WiFi 网络 / Connect to WiFi network
 * 带有重试机制和超时处理 / With retry mechanism and timeout handling
 */
void connectWiFi() {
  debugPrintln("正在连接 WiFi... / Connecting to WiFi...");

  // 显示 WiFi 连接状态 / Show WiFi connecting status
  tft.fillRect(0, DISPLAY_HEIGHT - 12, DISPLAY_WIDTH, 12, COLOR_BG);
  tft.setTextColor(COLOR_WIFI);
  tft.setTextSize(1);
  tft.setCursor(2, DISPLAY_HEIGHT - 10);
  tft.print("WiFi:");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < WIFI_MAX_RETRIES * 4) {
    delay(500);
    attempts++;

    // 更新进度指示 / Update progress indicator
    tft.setCursor(30, DISPLAY_HEIGHT - 10);
    for (int i = 0; i < (attempts % 4); i++) {
      tft.print(".");
    }

    // LED 闪烁表示正在连接 / LED blinks to show connecting
    setLED(attempts % 2 == 0);
  }

  if (WiFi.status() == WL_CONNECTED) {
    wifiConnected = true;
    wifiErrorCount = 0;
    debugPrint("WiFi 已连接! IP: / WiFi Connected! IP: ");
    debugPrintln(WiFi.localIP().toString().c_str());

    tft.fillRect(0, DISPLAY_HEIGHT - 12, DISPLAY_WIDTH, 12, COLOR_BG);
    tft.setTextColor(ST7735_GREEN);
    tft.setTextSize(1);
    tft.setCursor(2, DISPLAY_HEIGHT - 10);
    tft.print("WiFi OK");
  } else {
    wifiConnected = false;
    wifiErrorCount++;
    debugPrintln("WiFi 连接失败! / WiFi Connection Failed!");

    tft.fillRect(0, DISPLAY_HEIGHT - 12, DISPLAY_WIDTH, 12, COLOR_BG);
    tft.setTextColor(COLOR_ERROR);
    tft.setTextSize(1);
    tft.setCursor(2, DISPLAY_HEIGHT - 10);
    tft.print("WiFi FAIL");
  }

  setLED(wifiConnected);
  delay(1000);
}

/**
 * 检查 WiFi 连接状态，断开时自动重连 / Check WiFi and auto-reconnect
 */
void checkWiFi() {
  if (WiFi.status() == WL_CONNECTED) {
    if (!wifiConnected) {
      wifiConnected = true;
      wifiErrorCount = 0;
      debugPrintln("WiFi 已重新连接 / WiFi Reconnected");
    }
    return;
  }

  wifiConnected = false;
  wifiErrorCount++;
  debugPrint("WiFi 断开! 重连中... / WiFi Disconnected! Reconnecting... (");
  debugPrint(String(wifiErrorCount).c_str());
  debugPrintln(")");

  // 超过最大重试次数后等待更长时间 / Wait longer after max retries
  if (wifiErrorCount > WIFI_MAX_RETRIES * 3) {
    debugPrintln("WiFi 重连次数过多，等待 60 秒 / Too many retries, waiting 60s");
    delay(60000);
    wifiErrorCount = 0;
  }

  // 尝试重连 / Attempt to reconnect
  WiFi.disconnect();
  WiFi.reconnect();

  int timeout = 0;
  while (WiFi.status() != WL_CONNECTED && timeout < 20) {
    delay(500);
    timeout++;
  }

  wifiConnected = (WiFi.status() == WL_CONNECTED);
  if (wifiConnected) {
    wifiErrorCount = 0;
    debugPrintln("WiFi 重连成功 / WiFi Reconnected successfully");
    // 重新同步时间 / Re-sync time
    syncNTP();
  }
}

// =============================================================================
// NTP 时间同步 / NTP Time Synchronization
// =============================================================================

/**
 * 初始化 NTP 并配置时区 / Initialize NTP and configure timezone
 */
void initNTP() {
  debugPrintln("正在同步 NTP 时间... / Syncing NTP time...");

  // 配置 NTP 服务器 / Configure NTP servers
  configTime(
    TIMEZONE_OFFSET_HOURS * 3600,    // 时区偏移 (秒) / Timezone offset (seconds)
    DST_OFFSET_HOURS * 3600,         // 夏令时偏移 (秒) / DST offset (seconds)
    NTP_SERVER_1,
    NTP_SERVER_2,
    NTP_SERVER_3
  );

  // 等待时间同步 / Wait for time sync
  int attempts = 0;
  while (!getLocalTime(&timeinfo) && attempts < 20) {
    delay(500);
    attempts++;
  }

  if (getLocalTime(&timeinfo)) {
    timeSynced = true;
    debugPrintln("NTP 时间同步成功! / NTP time sync successful!");
  } else {
    timeSynced = false;
    debugPrintln("NTP 时间同步失败! / NTP time sync failed!");
  }
}

/**
 * 重新同步 NTP 时间 / Re-sync NTP time
 */
bool syncNTP() {
  if (!wifiConnected) {
    return false;
  }

  if (getLocalTime(&timeinfo)) {
    timeSynced = true;
    lastNtpSync = millis();
    return true;
  }

  timeSynced = false;
  return false;
}

// =============================================================================
// 传感器操作 / Sensor Operations
// =============================================================================

/**
 * 初始化 SHT31-D 传感器 / Initialize SHT31-D sensor
 */
void initSensor() {
  debugPrintln("正在初始化 SHT31-D 传感器... / Initializing SHT31-D sensor...");

  Wire.begin(I2C_SDA, I2C_SCL);

  if (sht31.begin(SHT31_I2C_ADDR)) {
    sensorOK = true;
    debugPrintln("SHT31-D 传感器初始化成功! / SHT31-D sensor initialized!");

    // 配置加热器 / Configure heater
    #if SHT31_HEATER_ENABLED
    sht31.heater(true);
    debugPrintln("SHT31 加热器已启用 / SHT31 heater enabled");
    #endif
  } else {
    sensorOK = false;
    debugPrintln("SHT31-D 传感器初始化失败! / SHT31-D sensor init failed!");
    debugPrintln("请检查 I2C 接线 / Check I2C wiring");
  }
}

/**
 * 读取温湿度数据 / Read temperature and humidity data
 */
void readSensor() {
  if (!sensorOK) {
    // 尝试重新初始化传感器 / Try to re-initialize sensor
    sensorErrorCount++;
    if (sensorErrorCount % 10 == 0) {
      debugPrintln("尝试重新初始化传感器 / Attempting sensor re-init");
      initSensor();
    }
    return;
  }

  float temp = sht31.readTemperature();
  float hum = sht31.readHumidity();

  // 检查读取是否成功 / Check if reading was successful
  if (!isnan(temp) && !isnan(hum)) {
    currentTemp = temp;
    currentHumidity = hum;
    sensorErrorCount = 0;

    #if DEBUG_ENABLED
    Serial.print("温度 / Temp: ");
    Serial.print(currentTemp, 1);
    Serial.print(" C  湿度 / Hum: ");
    Serial.print(currentHumidity, 1);
    Serial.println(" %");
    #endif
  } else {
    sensorErrorCount++;
    debugPrintln("传感器读取失败! / Sensor read failed!");

    // 多次失败后尝试重置传感器 / Reset sensor after multiple failures
    if (sensorErrorCount >= 5) {
      debugPrintln("传感器多次失败，重新初始化 / Sensor failed multiple times, re-init");
      initSensor();
    }
  }
}

// =============================================================================
// 显示屏操作 / Display Operations
// =============================================================================

/**
 * 初始化 ST7735 TFT 显示屏 / Initialize ST7735 TFT display
 */
void initDisplay() {
  debugPrintln("正在初始化显示屏... / Initializing display...");

  // 初始化 SPI 和显示屏 / Initialize SPI and display
  SPI.begin(TFT_SCK, -1, TFT_MOSI, TFT_CS);
  tft.initR(ST7735_TAB_TYPE);
  tft.setRotation(DISPLAY_ROTATION);
  tft.fillScreen(COLOR_BG);

  // 设置背光 / Set backlight
  pinMode(TFT_BL, OUTPUT);
  analogWrite(TFT_BL, BACKLIGHT_BRIGHTNESS);

  debugPrintln("显示屏初始化完成! / Display initialized!");
}

/**
 * 显示启动画面 / Display startup screen
 */
void displayStartupScreen() {
  tft.fillScreen(COLOR_BG);

  // 标题 / Title
  tft.setTextColor(ST7735_MAGENTA);
  tft.setTextSize(1);
  drawCenteredText("Desk Satellite", 8, 1, ST7735_MAGENTA);
  drawCenteredText("-- xi tong qi dong --", 20, 1, COLOR_LABEL);
  drawCenteredText("System Starting...", 32, 1, COLOR_LABEL);

  // 进度条 / Progress bar
  drawProgressBar(10, 50, DISPLAY_WIDTH - 20, 6, 30, ST7735_BLUE);
}

/**
 * 更新显示内容 / Update display content
 */
void updateDisplay() {
  // 获取当前时间 / Get current time
  if (getLocalTime(&timeinfo)) {
    timeSynced = true;
  }

  // 清屏 / Clear screen
  tft.fillScreen(COLOR_BG);

  // ---- 绘制时钟 / Draw clock ----
  displayClock();

  // ---- 绘制分隔线 / Draw divider ----
  tft.drawFastHLine(4, 30, DISPLAY_WIDTH - 8, COLOR_DIVIDER);

  // ---- 绘制日期 / Draw date ----
  displayDate();

  // ---- 绘制分隔线 / Draw divider ----
  tft.drawFastHLine(4, 46, DISPLAY_WIDTH - 8, COLOR_DIVIDER);

  // ---- 绘制温度和湿度 / Draw temperature and humidity ----
  displayTemperature();
  displayHumidity();

  // ---- 绘制底部状态栏 / Draw bottom status bar ----
  tft.drawFastHLine(4, DISPLAY_HEIGHT - 12, DISPLAY_WIDTH - 8, COLOR_DIVIDER);
  displayWiFiStatus();
}

/**
 * 显示时钟 / Display clock
 */
void displayClock() {
  if (!timeSynced) {
    drawCenteredText("--:--:--", 2, 3, COLOR_CLOCK);
    return;
  }

  // 格式化时间字符串 / Format time string
  snprintf(timeStr, sizeof(timeStr), "%02d:%02d:%02d",
           timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);

  // 大字体显示时钟 / Display clock in large font
  drawCenteredText(timeStr, 2, 3, COLOR_CLOCK);
}

/**
 * 显示日期 / Display date
 */
void displayDate() {
  if (!timeSynced) {
    drawCenteredText("----/--/--", 33, 1, COLOR_DATE);
    return;
  }

  // 格式化日期字符串 / Format date string
  // 显示: 2025-01-15 Wed / 2025-01-15 三
  const char* weekdays[] = {
    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
  };

  snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d %s",
           timeinfo.tm_year + 1900,
           timeinfo.tm_mon + 1,
           timeinfo.tm_mday,
           weekdays[timeinfo.tm_wday]);

  drawCenteredText(buffer, 33, 1, COLOR_DATE);
}

/**
 * 显示温度 / Display temperature
 */
void displayTemperature() {
  if (!sensorOK) {
    tft.setTextColor(COLOR_ERROR);
    tft.setTextSize(1);
    tft.setCursor(4, 50);
    tft.print("T: ---");
    return;
  }

  // 温度图标和数值 / Temperature icon and value
  tft.setTextColor(COLOR_LABEL);
  tft.setTextSize(1);
  tft.setCursor(4, 50);
  tft.print("T:");

  tft.setTextColor(COLOR_TEMP);
  tft.setTextSize(2);
  tft.setCursor(16, 48);

  // 根据温度决定显示颜色 / Color based on temperature
  uint16_t tempColor = COLOR_TEMP;
  if (currentTemp >= 35.0) {
    tempColor = COLOR_ERROR;         // 高温红色 / High temp red
  } else if (currentTemp <= 5.0) {
    tempColor = ST7735_BLUE;         // 低温蓝色 / Low temp blue
  }
  tft.setTextColor(tempColor);

  dtostrf(currentTemp, 4, 1, buffer);
  tft.print(buffer);
  tft.setTextSize(1);
  tft.print("C");
}

/**
 * 显示湿度 / Display humidity
 */
void displayHumidity() {
  if (!sensorOK) {
    tft.setTextColor(COLOR_ERROR);
    tft.setTextSize(1);
    tft.setCursor(4, 65);
    tft.print("H: ---");
    return;
  }

  // 湿度图标和数值 / Humidity icon and value
  tft.setTextColor(COLOR_LABEL);
  tft.setTextSize(1);
  tft.setCursor(4, 66);
  tft.print("H:");

  tft.setTextColor(COLOR_HUMIDITY);
  tft.setTextSize(2);
  tft.setCursor(16, 64);

  // 根据湿度决定显示颜色 / Color based on humidity
  uint16_t humColor = COLOR_HUMIDITY;
  if (currentHumidity >= 80.0) {
    humColor = ST7735_BLUE;          // 高湿蓝色 / High humidity blue
  } else if (currentHumidity <= 30.0) {
    humColor = COLOR_ERROR;          // 低湿红色 / Low humidity red
  }
  tft.setTextColor(humColor);

  dtostrf(currentHumidity, 4, 1, buffer);
  tft.print(buffer);
  tft.setTextSize(1);
  tft.print("%");
}

/**
 * 显示 WiFi 状态 / Display WiFi status
 */
void displayWiFiStatus() {
  tft.setTextSize(1);

  if (wifiConnected) {
    tft.setTextColor(ST7735_GREEN);
    tft.setCursor(2, DISPLAY_HEIGHT - 10);
    tft.print("WiFi");

    // 显示信号强度 / Show signal strength
    int rssi = WiFi.RSSI();
    tft.setTextColor(COLOR_LABEL);
    tft.setCursor(28, DISPLAY_HEIGHT - 10);
    snprintf(buffer, sizeof(buffer), "%ddBm", rssi);
    tft.print(buffer);
  } else {
    tft.setTextColor(COLOR_ERROR);
    tft.setCursor(2, DISPLAY_HEIGHT - 10);
    tft.print("WiFi:OFF");
  }

  // 显示时间同步状态 / Show time sync status
  tft.setTextColor(timeSynced ? ST7735_GREEN : COLOR_ERROR);
  tft.setCursor(DISPLAY_WIDTH - 22, DISPLAY_HEIGHT - 10);
  tft.print(timeSynced ? "NTP" : "---");
}

/**
 * 显示传感器错误 / Display sensor error
 */
void displaySensorError() {
  tft.fillScreen(COLOR_BG);
  tft.setTextColor(COLOR_ERROR);
  drawCenteredText("Sensor Error!", 30, 1, COLOR_ERROR);
  drawCenteredText("Check wiring", 45, 1, COLOR_LABEL);
}

/**
 * 显示睡眠画面 / Display sleep screen
 */
void displaySleepScreen() {
  tft.fillScreen(COLOR_BG);
  drawCenteredText("Zzz...", DISPLAY_HEIGHT / 2 - 8, 2, COLOR_LABEL);
  delay(500);
}

// =============================================================================
// 触摸开关处理 / Touch Switch Handling
// =============================================================================

/**
 * 初始化触摸开关 / Initialize touch switch
 */
void initTouch() {
  pinMode(TOUCH_PIN, INPUT_PULLUP);

  // 配置深度睡眠唤醒源 / Configure deep sleep wake-up source
  esp_sleep_enable_ext0_wakeup(
    (gpio_num_t)DEEP_SLEEP_WAKEUP_PIN,
    DEEP_SLEEP_WAKEUP_LEVEL
  );

  debugPrintln("触摸开关已初始化 / Touch switch initialized");
}

/**
 * 触摸中断服务函数 / Touch interrupt service routine
 */
void IRAM_ATTR onTouchInterrupt() {
  touchTriggered = true;
  touchTime = millis();
}

/**
 * 处理触摸事件 / Handle touch events
 * 短按: 开关屏幕 / Short press: toggle screen
 * 长按: 进入深度睡眠 / Long press: enter deep sleep
 */
void handleTouch() {
  bool currentlyTouched = (digitalRead(TOUCH_PIN) == LOW);

  if (currentlyTouched && !wasTouched) {
    // 检测到按下 / Press detected
    unsigned long pressStart = millis();

    // 等待释放或超时 (长按检测) / Wait for release or timeout (long press detect)
    while (digitalRead(TOUCH_PIN) == LOW) {
      if (millis() - pressStart >= TOUCH_LONG_PRESS_MS) {
        // 长按: 进入深度睡眠 / Long press: enter deep sleep
        debugPrintln("长按检测! 进入深度睡眠 / Long press! Entering deep sleep");
        enterDeepSleep();
        return;  // 不会执行到这里 / Won't reach here
      }
      delay(10);
    }

    // 短按: 切换屏幕状态 / Short press: toggle screen state
    unsigned long pressDuration = millis() - pressStart;

    // 去抖检查 / Debounce check
    if (pressDuration >= 30) {  // 最小按下时间 / Minimum press duration
      if (screenOn) {
        debugPrintln("短按: 关闭屏幕 / Short press: turning off screen");
        turnScreenOff();
      } else {
        debugPrintln("短按: 开启屏幕 / Short press: turning on screen");
        turnScreenOn();
      }
    }
  }

  wasTouched = currentlyTouched;
}

/**
 * 开启屏幕 / Turn screen on
 */
void turnScreenOn() {
  screenOn = true;
  analogWrite(TFT_BL, BACKLIGHT_BRIGHTNESS);
  lastScreenActivity = millis();

  // 立即更新显示 / Update display immediately
  unsigned long now = millis();
  lastSensorUpdate = 0;  // 强制传感器更新 / Force sensor update
  lastDisplayUpdate = 0; // 强制显示更新 / Force display update

  // 如果 WiFi 未连接，尝试重连 / Try to reconnect WiFi if disconnected
  if (!wifiConnected) {
    checkWiFi();
  }
}

/**
 * 关闭屏幕 / Turn screen off
 */
void turnScreenOff() {
  screenOn = false;
  displaySleepScreen();
  analogWrite(TFT_BL, 0);
}

/**
 * 进入深度睡眠模式 / Enter deep sleep mode
 */
void enterDeepSleep() {
  debugPrintln("=== 进入深度睡眠模式 ===");
  debugPrintln("=== Entering Deep Sleep Mode ===");

  // 关闭显示屏 / Turn off display
  tft.fillScreen(COLOR_BG);
  analogWrite(TFT_BL, 0);

  // 关闭 LED / Turn off LED
  setLED(false);

  // 断开 WiFi / Disconnect WiFi
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

  // 关闭 I2C / Turn off I2C
  Wire.end();

  delay(100);

  // 进入深度睡眠 / Enter deep sleep
  esp_deep_sleep_start();
}

// =============================================================================
// LED 控制 / LED Control
// =============================================================================

/**
 * 设置 LED 状态 / Set LED state
 */
void setLED(bool state) {
  digitalWrite(LED_PIN, state ? HIGH : LOW);
}

/**
 * LED 闪烁 / Blink LED
 */
void blinkLED(int times, int intervalMs) {
  for (int i = 0; i < times; i++) {
    setLED(true);
    delay(intervalMs);
    setLED(false);
    delay(intervalMs);
  }
}

// =============================================================================
// 显示辅助函数 / Display Helper Functions
// =============================================================================

/**
 * 绘制居中文字 / Draw centered text
 */
void drawCenteredText(const char* text, int y, int textSize, uint16_t color) {
  tft.setTextColor(color);
  tft.setTextSize(textSize);
  int16_t textWidth = strlen(text) * 6 * textSize;
  int x = (DISPLAY_WIDTH - textWidth) / 2;
  if (x < 0) x = 0;
  tft.setCursor(x, y);
  tft.print(text);
}

/**
 * 绘制进度条 / Draw progress bar
 */
void drawProgressBar(int x, int y, int w, int h, int progress, uint16_t color) {
  // 背景 / Background
  tft.drawRect(x, y, w, h, COLOR_DIVIDER);
  // 填充 / Fill
  int fillW = (w - 2) * progress / 100;
  tft.fillRect(x + 1, y + 1, fillW, h - 2, color);
}

// =============================================================================
// 调试输出 / Debug Output
// =============================================================================

/**
 * 调试打印 (不带换行) / Debug print (no newline)
 */
void debugPrint(const char* message) {
  #if DEBUG_ENABLED
  Serial.print(message);
  #endif
}

/**
 * 调试打印 (带换行) / Debug print (with newline)
 */
void debugPrintln(const char* message) {
  #if DEBUG_ENABLED
  Serial.println(message);
  #endif
}
