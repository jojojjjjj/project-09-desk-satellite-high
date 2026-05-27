# Day 6: 显示界面设计 | Display UI Design

## 今日目标 | Today's Goals

- 设计多屏切换的用户界面架构
- 实现精美的时钟显示界面
- 设计温湿度数据展示界面
- 学习动画效果的实现方法
- 实现状态栏（WiFi、电池、时间等）

---

## 上午 (3h) | Morning Session

### 1. UI 设计原则与架构 (1h)

**嵌入式 UI 设计原则**：

1. **信息层级**：最重要的信息最大、最醒目
2. **一致性**：颜色、字体大小、布局风格保持统一
3. **可读性**：文字与背景有足够对比度
4. **效率**：减少不必要的重绘，避免闪烁
5. **状态可见**：用户应能随时了解设备状态

**Desk Satellite 界面规划**：

```
屏幕布局 (160 x 80 横屏)：

┌──────────────────────────────────────────┐
│ [WiFi] [电池]                    [状态] │  <- 状态栏 (8px)
├──────────────────────────────────────────┤
│                                          │
│         主内容区域                        │  <- 主显示区 (64px)
│    (时钟 / 温湿度 / 设置)                 │
│                                          │
├──────────────────────────────────────────┤
│            底部信息栏                     │  <- 底部栏 (8px)
└──────────────────────────────────────────┘

多屏切换：
  Screen 0: 时钟主界面 (时间 + 日期)
  Screen 1: 温湿度详情 (温度 + 湿度 + 露点)
  Screen 2: 系统信息 (WiFi / 电池 / 运行时间)
```

**多屏管理架构**：

```cpp
// 屏幕管理器
#define SCREEN_CLOCK    0  // 时钟界面
#define SCREEN_WEATHER  1  // 温湿度界面
#define SCREEN_SYSTEM   2  // 系统信息界面
#define SCREEN_COUNT    3  // 总屏幕数

int currentScreen = SCREEN_CLOCK;
unsigned long screenChangeTime = 0;
#define AUTO_SWITCH_INTERVAL 10000  // 10 秒自动切换

void switchScreen(int screen) {
  if (screen >= 0 && screen < SCREEN_COUNT) {
    currentScreen = screen;
    screenChangeTime = millis();
    tft.fillScreen(ST7735_BLACK);  // 切换时清屏
  }
}

void autoSwitchScreen() {
  if (millis() - screenChangeTime >= AUTO_SWITCH_INTERVAL) {
    int nextScreen = (currentScreen + 1) % SCREEN_COUNT;
    switchScreen(nextScreen);
  }
}
```

### 2. 时钟界面设计 (2h)

**精美的数字时钟**：

```cpp
// 时钟界面 - 大字号数字时钟
void displayClockScreen(struct tm* timeinfo) {
  // === 状态栏 (顶部 8px) ===
  drawStatusBar();

  // === 主时钟 (中央) ===
  // 时:分 (大字号)
  tft.setTextSize(4);
  tft.setTextColor(ST7735_WHITE);

  char timeStr[6];
  strftime(timeStr, sizeof(timeStr), "%H:%M", timeinfo);

  // 计算居中位置
  int textWidth = 5 * 24;  // 5 characters x 24 pixels (textSize 4)
  int xPos = (160 - textWidth) / 2;
  tft.setCursor(xPos, 14);
  tft.print(timeStr);

  // 秒数 (小字号，在右侧)
  tft.setTextSize(2);
  tft.setTextColor(ST7735_CYAN);
  tft.setCursor(xPos + textWidth + 2, 22);
  char secStr[3];
  strftime(secStr, sizeof(secStr), "%S", timeinfo);
  tft.print(secStr);

  // === 日期 (下方) ===
  tft.setTextSize(1);
  tft.setTextColor(ST7735_YELLOW);
  tft.setCursor(10, 55);

  char dateStr[20];
  // 中文星期
  const char* weekdays[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  sprintf(dateStr, "%04d-%02d-%02d %s",
          timeinfo->tm_year + 1900,
          timeinfo->tm_mon + 1,
          timeinfo->tm_mday,
          weekdays[timeinfo->tm_wday]);
  tft.print(dateStr);

  // === 温湿度摘要 (底部) ===
  tft.setTextSize(1);
  tft.setTextColor(ST7735_GREEN);
  tft.setCursor(10, 68);
  tft.printf("%.1fC / %.0f%%", currentTemp, currentHum);

  // === 底部栏 ===
  drawBottomBar();
}
```

**时钟界面进阶 -- 冒号闪烁**：

```cpp
// 冒号闪烁效果（每秒切换一次）
void displayClockWithBlink(struct tm* timeinfo) {
  static bool colonVisible = true;
  colonVisible = !colonVisible;  // 每次调用切换状态

  // 小时
  tft.setTextSize(4);
  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(10, 14);
  tft.printf("%02d", timeinfo->tm_hour);

  // 冒号
  if (colonVisible) {
    tft.setTextColor(ST7735_CYAN);
  } else {
    tft.setTextColor(ST7735_BLACK);  // 隐藏冒号
  }
  tft.print(":");

  // 分钟
  tft.setTextColor(ST7735_WHITE);
  tft.printf("%02d", timeinfo->tm_min);
}
```

---

## 下午 (4h) | Afternoon Session

### 3. 温湿度详情界面 (1.5h)

**温湿度可视化界面**：

```cpp
// 温湿度详情界面
void displayWeatherScreen() {
  drawStatusBar();

  // 标题
  tft.setTextSize(1);
  tft.setTextColor(ST7735_CYAN);
  tft.setCursor(5, 12);
  tft.println("Weather Data");

  // 分隔线
  tft.drawFastHLine(5, 22, 150, ST7735_DARKGREY);

  // 温度 (左侧)
  tft.setTextSize(1);
  tft.setTextColor(ST7735_YELLOW);
  tft.setCursor(5, 28);
  tft.print("Temp");

  tft.setTextSize(2);
  tft.setCursor(5, 40);
  tft.printf("%.1f", currentTemp);
  tft.setTextSize(1);
  tft.print("C");

  // 温度条形图
  int tempBarWidth = map(constrain(currentTemp, 0, 40), 0, 40, 0, 60);
  tft.fillRect(5, 58, tempBarWidth, 6, ST7735_YELLOW);
  tft.drawRect(5, 58, 60, 6, ST7735_YELLOW);

  // 湿度 (右侧)
  tft.setTextSize(1);
  tft.setTextColor(ST7735_GREEN);
  tft.setCursor(85, 28);
  tft.print("Humidity");

  tft.setTextSize(2);
  tft.setCursor(85, 40);
  tft.printf("%.0f", currentHum);
  tft.setTextSize(1);
  tft.print("%");

  // 湿度条形图
  int humBarWidth = map(constrain(currentHum, 0, 100), 0, 100, 0, 60);
  tft.fillRect(85, 58, humBarWidth, 6, ST7735_GREEN);
  tft.drawRect(85, 58, 60, 6, ST7735_GREEN);

  drawBottomBar();
}
```

### 4. 动画效果实现 (1.5h)

**局部刷新避免闪烁**：

```cpp
// 局部刷新 -- 只更新变化的部分
void updateTimeDisplay(struct tm* timeinfo) {
  static int lastSecond = -1;
  static int lastMinute = -1;

  if (timeinfo->tm_sec != lastSecond) {
    // 只重绘秒数区域
    tft.fillRect(120, 14, 30, 16, ST7735_BLACK);  // 清除秒数区域
    tft.setTextSize(2);
    tft.setTextColor(ST7735_CYAN);
    tft.setCursor(120, 14);
    tft.printf("%02d", timeinfo->tm_sec);
    lastSecond = timeinfo->tm_sec;
  }

  if (timeinfo->tm_min != lastMinute) {
    // 只重绘小时:分钟区域
    tft.fillRect(10, 14, 100, 32, ST7735_BLACK);
    tft.setTextSize(4);
    tft.setTextColor(ST7735_WHITE);
    tft.setCursor(10, 14);
    tft.printf("%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min);
    lastMinute = timeinfo->tm_min;
  }
}
```

**启动动画**：

```cpp
// 启动画面动画
void showSplashScreen() {
  tft.fillScreen(ST7735_BLACK);

  // 渐入效果 - 逐行绘制
  for (int y = 0; y < 80; y += 2) {
    uint16_t color = tft.color565(0, 0, y * 3);  // 蓝色渐变
    tft.drawFastHLine(0, y, 160, color);
    delay(10);
  }

  // 标题
  tft.setTextSize(2);
  tft.setTextColor(ST7735_WHITE);
  int titleWidth = 14 * 12;  // "Desk Satellite" 14 chars x 12px (size 2)
  tft.setCursor((160 - titleWidth) / 2, 20);
  tft.print("Desk Satellite");

  // 加载进度条
  tft.setTextSize(1);
  tft.setTextColor(ST7735_CYAN);
  tft.setCursor(30, 55);
  tft.print("Initializing...");

  tft.drawRect(30, 65, 100, 6, ST7735_CYAN);
  for (int i = 0; i < 100; i++) {
    tft.fillRect(31, 66, i, 4, ST7735_CYAN);
    delay(20);
  }

  delay(500);
  tft.fillScreen(ST7735_BLACK);
}
```

**加载旋转动画**：

```cpp
// 旋转指示器 (WiFi 连接中、NTP 同步中等)
void drawSpinner(int x, int y, int step) {
  // 4 个位置的点，依次点亮
  int positions[4][2] = {
    {x, y - 4},      // 上
    {x + 4, y},      // 右
    {x, y + 4},      // 下
    {x - 4, y}       // 左
  };

  for (int i = 0; i < 4; i++) {
    if (i == step % 4) {
      tft.fillCircle(positions[i][0], positions[i][1], 2, ST7735_WHITE);
    } else {
      tft.fillCircle(positions[i][0], positions[i][1], 1, ST7735_DARKGREY);
    }
  }
}
```

### 5. 状态栏与系统信息 (1h)

**统一的状态栏**：

```cpp
// 顶部状态栏
void drawStatusBar() {
  // 状态栏背景
  tft.fillRect(0, 0, 160, 10, ST7735_DARKGREY);

  // WiFi 状态图标
  if (WiFi.status() == WL_CONNECTED) {
    tft.setTextColor(ST7735_GREEN);
    tft.setTextSize(1);
    tft.setCursor(2, 1);
    tft.print("W");  // WiFi OK
  } else {
    tft.setTextColor(ST7735_RED);
    tft.setTextSize(1);
    tft.setCursor(2, 1);
    tft.print("X");  // WiFi OFF
  }

  // 电池图标
  drawBatteryIcon(130, 1, batteryPercent);

  // 时间 (简短)
  struct tm timeinfo;
  if (getLocalTime(&timeinfo)) {
    tft.setTextColor(ST7735_WHITE);
    tft.setTextSize(1);
    tft.setCursor(55, 1);
    tft.printf("%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min);
  }
}

// 底部信息栏
void drawBottomBar() {
  tft.drawFastHLine(0, 74, 160, ST7735_DARKGREY);

  // 运行时间
  unsigned long uptime = millis() / 1000;
  int hours = uptime / 3600;
  int mins = (uptime % 3600) / 60;
  int secs = uptime % 60;

  tft.setTextSize(1);
  tft.setTextColor(ST7735_DARKGREY);
  tft.setCursor(5, 76);
  tft.printf("UP:%02d:%02d:%02d", hours, mins, secs);

  // 充电状态
  if (currentChargeStatus == CHARGE_STATUS_CHARGING) {
    tft.setTextColor(ST7735_YELLOW);
    tft.setCursor(120, 76);
    tft.print("CHG");
  }
}
```

**系统信息界面**：

```cpp
// 系统信息界面
void displaySystemScreen() {
  drawStatusBar();

  tft.setTextSize(1);
  tft.setTextColor(ST7735_CYAN);
  tft.setCursor(5, 14);
  tft.println("System Info");
  tft.drawFastHLine(5, 24, 150, ST7735_DARKGREY);

  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(5, 28);
  tft.printf("WiFi: %s", WiFi.status() == WL_CONNECTED ? "OK" : "OFF");

  tft.setCursor(5, 38);
  tft.printf("IP: %s", WiFi.localIP().toString().c_str());

  tft.setCursor(5, 48);
  tft.printf("RSSI: %d dBm", WiFi.RSSI());

  tft.setCursor(5, 58);
  float voltage = readBatteryVoltage();
  tft.printf("BAT: %.2fV (%d%%)", voltage, batteryPercent);

  tft.setCursor(5, 68);
  unsigned long uptime = millis() / 1000;
  tft.printf("Uptime: %lu s", uptime);

  drawBottomBar();
}
```

---

## 今日作业 | Today's Task

1. 完成多屏切换机制（时钟 / 温湿度 / 系统信息 三个界面）
2. 实现精美的时钟显示界面（大字号时间 + 日期 + 温湿度摘要）
3. 实现温湿度详情界面（数字 + 条形图）
4. 实现状态栏（WiFi + 电池 + 时间）
5. 添加启动动画效果
6. **提交 HW1：第一周进度汇报**（800-1200 字，提交到 `assignments/week-1-checkin.md`）

## 今日检查点 | Checkpoint

- [ ] 能在 3 个界面之间自动切换？
- [ ] 时钟显示格式正确、美观？
- [ ] 温湿度界面有条形图可视化？
- [ ] 状态栏显示 WiFi 和电池状态？
- [ ] 启动动画效果正常？
- [ ] 屏幕无闪烁（使用了局部刷新）？
- [ ] HW1 第一周进度汇报已提交？
