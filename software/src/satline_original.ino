#include <WiFi.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include "time.h"
#include <Preferences.h>
#include "esp_sleep.h"

// ====== Touch module ======
#define TOUCH_PIN 1
Preferences prefs;

// ====== WiFi ======
const char* ssid = "your_wifi";
const char* password = "pass";

// ====== NTP ======
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 7 * 3600;
const int daylightOffset_sec = 0;

// ====== SHT31 ======
#define SDA_PIN 2
#define SCL_PIN 0
Adafruit_SHT31 sht31 = Adafruit_SHT31();

// ====== TFT wiring ======
#define TFT_CS   21
#define TFT_DC   20
#define TFT_RST  10
#define TFT_MOSI 9
#define TFT_SCLK 8
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

// ====== Colors ======
#define CYBER_BG      ST77XX_BLACK
#define CYBER_GREEN   0x07E0  
#define CYBER_ACCENT  0x07FF  
#define CYBER_LIGHT   0xFD20  
#define CYBER_MIX     0x05FF  
#define CYBER_BLUE    0x07FF  
#define CYBER_PINK    0xF81F

// ====== Variables ======
int sweepAngle = 0;
int prevSecond = -1;
String prevSecStr = "--";
String prevHourStr = "--";
String prevMinStr = "--";
bool pulse = false;

// ====== Connecting WiFi + SyncTime ======
void connectWiFiAndSyncTime() {
  tft.fillScreen(CYBER_BG);
  tft.setTextColor(CYBER_LIGHT);
  tft.setTextSize(1);
  tft.setCursor(10, 30);
  tft.print("Connecting to Earth");

  WiFi.begin(ssid, password);
  uint8_t retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry < 20) {
    delay(300);
    tft.print(".");
    retry++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    tft.fillScreen(CYBER_BG);
    tft.setCursor(10, 30);
    tft.print("Syncing time...");
    delay(1000);
  } else {
    tft.fillScreen(CYBER_BG);
    tft.setCursor(10, 30);
    tft.setTextColor(ST77XX_RED);
    tft.print("WiFi FAILED!");
    delay(1500);
  }
}

// ====== Get time ======
String getTimeStr(char type) {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) return "--";
  char buf[8];
  if (type == 'H') strftime(buf, sizeof(buf), "%H", &timeinfo);
  else if (type == 'M') strftime(buf, sizeof(buf), "%M", &timeinfo);
  else if (type == 'S') strftime(buf, sizeof(buf), "%S", &timeinfo);
  return String(buf);
}

// ====== Radar base ======
uint16_t dimColor(uint16_t color, float factor) {
  uint8_t r = ((color >> 11) & 0x1F) * 255 / 31;
  uint8_t g = ((color >> 5) & 0x3F) * 255 / 63;
  uint8_t b = (color & 0x1F) * 255 / 31;
  r = (uint8_t)(r * factor);
  g = (uint8_t)(g * factor);
  b = (uint8_t)(b * factor);
  return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
}

void drawRadarBase() {
  int cx = 135, cy = 70;
  int radiusMax = 35;
  int radiusStep = 3;
  tft.fillRect(cx - radiusMax - 1, cy - radiusMax - 1, (radiusMax + 1) * 2, (radiusMax + 1) * 2, CYBER_BG);
  int n = radiusMax / radiusStep;
  for (int i = 0; i <= n; i++) {
    float factor = 1.0 - (float)i / n * 0.8;
    uint16_t c = dimColor(CYBER_LIGHT, factor);
    tft.drawCircle(cx, cy, radiusMax - i * radiusStep, c);
  }
}

// ====== Radar sweep ======
void drawRadarSweep() {
  int cx = 135, cy = 70;
  float rad = sweepAngle * 3.14159 / 180.0;
  int x2 = cx + cos(rad) * 35;
  int y2 = cy + sin(rad) * 35;
  tft.drawLine(cx, cy, x2, y2, CYBER_BLUE);
  delay(20);
  tft.drawLine(cx, cy, x2, y2, CYBER_BG);
  sweepAngle += 10;
  if (sweepAngle >= 360) sweepAngle = 0;
}

// ====== Clock ======
void drawClock(String hourStr, String minStr) {
  if (hourStr != prevHourStr || minStr != prevMinStr) {
    prevHourStr = hourStr;
    prevMinStr = minStr;
    tft.fillRect(5, 20, 100, 35, CYBER_BG);
    tft.setTextColor(CYBER_LIGHT);
    tft.setTextSize(3);
    tft.setCursor(5, 20);
    tft.print(hourStr);
    tft.print(":");
    tft.print(minStr);
  }
}

// ====== Seconds ======
void updateSeconds(String secStr) {
  if (secStr != prevSecStr) {
    prevSecStr = secStr;
    int cursorX = 80, cursorY = 5, barX = 110, barY = 7, barMaxWidth = 40;
    tft.setTextSize(1);
    tft.setTextColor(ST77XX_WHITE, CYBER_BG);
    tft.setCursor(cursorX - 73, cursorY);
    tft.print("///////////");
    tft.setTextColor(CYBER_GREEN, CYBER_BG);
    tft.setCursor(cursorX, cursorY);
    tft.print(secStr + "s");
    int barWidth = map(secStr.toInt(), 0, 59, 0, barMaxWidth);
    tft.fillRect(barX, barY, barMaxWidth, 6, CYBER_BG);
    tft.drawRect(barX, barY, barMaxWidth, 6, CYBER_ACCENT);
    tft.fillRect(barX, barY, barWidth, 6, CYBER_GREEN);
  }
}

// ====== Env ======
void drawEnv(float temp, float hum) {
  int baseY = 50;
  tft.setTextSize(1);
  tft.setTextColor(CYBER_GREEN, CYBER_BG);
  tft.setCursor(5, baseY);
  tft.print("TEM");
  int tempBoxX = 46, tempBoxY = baseY - 3, tempBoxW = 35, tempBoxH = 14;
  tft.fillRect(tempBoxX, tempBoxY, tempBoxW, tempBoxH, CYBER_BG);
  tft.drawLine(5, baseY + 10, 35, baseY + 10, CYBER_GREEN);
  tft.drawLine(35, baseY + 10, 45, baseY + 5, CYBER_GREEN);
  tft.drawRect(tempBoxX, tempBoxY, tempBoxW, tempBoxH, CYBER_GREEN);
  tft.setCursor(tempBoxX + 2, baseY);
  tft.printf("%.1fC", temp);
  tft.setTextColor(CYBER_PINK, CYBER_BG);
  tft.setCursor(5, baseY + 14);
  tft.print("HUM");
  int humBoxX = 46, humBoxY = baseY + 11, humBoxW = 24, humBoxH = 14;
  tft.fillRect(humBoxX, humBoxY, humBoxW, humBoxH, CYBER_BG);
  tft.drawLine(5, baseY + 24, 35, baseY + 24, CYBER_PINK);
  tft.drawLine(35, baseY + 24, 45, baseY + 19, CYBER_PINK);
  tft.drawRect(humBoxX, humBoxY, humBoxW, humBoxH, CYBER_PINK);
  tft.setCursor(humBoxX + 2, baseY + 14);
  tft.printf("%.0f%%", hum);
}

// ====== Neon border ======
void neonPulse() {
  uint16_t c = pulse ? CYBER_LIGHT : CYBER_LIGHT;
  tft.drawRect(0, 0, 160, 80, c);
  pulse = !pulse;
}

// ====== Sleep ======
#include "esp_sleep.h"

void goToSleep() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(1);
// ===== Zzz...=====
  for (int i = 0; i < 5; i++) {
    int x = 60 + i * 10;
    int y = 50 - i * 3;
    tft.setCursor(x, y);
    tft.print("Z");
    delay(200);
    tft.setTextColor(ST77XX_BLACK);
    tft.setCursor(x, y);
    tft.print("Z");
    tft.setTextColor(ST77XX_GREEN);
  }

  // ===== Dòng chính giữa =====
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextSize(1);
  tft.setCursor(35, 30);
  tft.print("touch to scan Earth");
  delay(1000);

  // ===== Chuẩn bị ngủ =====
  pinMode(TOUCH_PIN, INPUT_PULLDOWN);
  esp_deep_sleep_enable_gpio_wakeup(1ULL << TOUCH_PIN, ESP_GPIO_WAKEUP_GPIO_HIGH);

  Serial.println("💤 Going to deep sleep...");
  delay(100);
  esp_deep_sleep_start();
}

// ====== Setup ======
void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);
  prefs.begin("state", false);

  bool isSleeping = prefs.getBool("sleeping", false);
  pinMode(TOUCH_PIN, INPUT);

  tft.initR(INITR_MINI160x80);
  tft.setRotation(1);
  tft.fillScreen(CYBER_BG);

  if (isSleeping) {
    prefs.putBool("sleeping", false);
    tft.setCursor(10, 30);
    tft.setTextColor(CYBER_LIGHT);
    tft.print("Woke up!");
    delay(800);
  }

  connectWiFiAndSyncTime();
  sht31.begin(0x44);
  drawRadarBase();
  drawClock(getTimeStr('H'), getTimeStr('M'));
  updateSeconds(getTimeStr('S'));
  drawEnv(sht31.readTemperature(), sht31.readHumidity());
}

// ====== Loop ======
void loop() {
  drawRadarSweep();
  neonPulse();

  if (WiFi.status() != WL_CONNECTED) WiFi.reconnect();

  struct tm timeinfo;
  if (getLocalTime(&timeinfo)) {
    int sec = timeinfo.tm_sec;
    if (sec != prevSecond) {
      prevSecond = sec;
      updateSeconds(getTimeStr('S'));
      if (sec % 10 == 0) {
        drawClock(getTimeStr('H'), getTimeStr('M'));
        drawEnv(sht31.readTemperature(), sht31.readHumidity());
      }
    }
  }

  // ====== Chạm 1 lần để sleep ======
  if (digitalRead(TOUCH_PIN) == HIGH) {
    delay(50); // chống dội
    if (digitalRead(TOUCH_PIN) == HIGH) {
      Serial.println("Sleep requested...");
      
      // Đợi nhả tay ra để tránh tự bật lại khi còn đang HIGH
      while (digitalRead(TOUCH_PIN) == HIGH) {
        delay(10);
      }

      goToSleep();
    }
  }
}

