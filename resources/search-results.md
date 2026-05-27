# 桌面卫星气象站资源搜索结果 | Desk Satellite Weather Station Resource Search Results

搜索日期：2026-05-27 | Search Date: 2026-05-27

---

## 一、原项目资源 | Original Project Resources

### 1.1 原作者视频 | Original Video

**A Desk Satellite You Can Actually Build!** — Huy Vector
- **链接 / Link:** https://www.youtube.com/watch?v=0zJG3wExY-c
- **时长：** 约 10 分钟
- **简介：** 原作者完整展示了桌面卫星气象站的制作过程，从铜线弯制到最终成品展示。视频展示了 TFT 彩色显示时钟和温湿度信息，配合铜线卫星外壳的独特造型。
- **推荐度：** 必看（了解最终效果和制作流程的最好参考）

> Complete build video showing copper wire bending, soldering, and final assembled desk satellite with TFT color display. Essential viewing for understanding the final result.

### 1.2 原作者网站 | Author Website

**Huy Vector — Desk Satellite**
- **链接 / Link:** https://www.huyvector.org/clocks/desk-satellite
- **简介：** 原作者的项目页面，包含项目介绍、制作日志和参考资料。

> Author's project page with introduction, build log, and reference materials.

### 1.3 材料与电路图 | Materials & Circuit Diagram

**Google Sites — huy-materials-used/desk-satellite**
- **链接 / Link:** https://sites.google.com/view/huy-materials-used/clocks/desk-satellite
- **简介：** 详细的材料清单和电路接线说明。包含所有使用的电子元件、铜线和黄铜管等结构材料的规格说明。

> Detailed materials list and circuit wiring instructions. Includes specifications for all electronic components, copper wire, and brass tube structural materials.

### 1.4 源代码 | Source Code

**Google Drive — Desk Satellite Code**
- **链接 / Link:** https://drive.google.com/file/d/1SwpgMWkXY9MKINmAqNVY9-ZhVx53Qo-p/view?usp=sharing
- **语言：** Arduino C/C++
- **简介：** 原作者提供的 Arduino 源代码，包含 ESP32-C3 驱动 TFT 显示、读取 SHT31-D 传感器数据、WiFi/NTP 时间同步等功能。这是本项目代码的参考起点。

> Original Arduino source code for ESP32-C3 driving TFT display, reading SHT31-D sensor, and WiFi/NTP time sync. This is the reference starting point for the project code.

### 1.5 电路图 | Circuit Diagram

**Google Drive — Desk Satellite Diagram**
- **链接 / Link:** https://drive.google.com/file/d/1ZVTx1QfvIgG53i-0iDBSIXXhRO96I1h1/view?usp=sharing
- **简介：** 完整的电路接线图，标注了 ESP32-C3 与 ST7735 TFT、SHT31-D、电源模块之间的连接关系。

> Complete circuit wiring diagram showing connections between ESP32-C3, ST7735 TFT, SHT31-D, and power modules.

### 1.6 原作者频道 | Author Channel

**YouTube — @HuyVector**
- **链接 / Link:** https://www.youtube.com/@HuyVector
- **简介：** Huy Vector 的 YouTube 频道，包含大量铜线 DIY 电子项目，风格独特。可以学习铜线弯制和焊接的技巧。
- **社区：** Facebook Group — https://www.facebook.com/groups/huyvectorlab

> Huy Vector's YouTube channel featuring many copper wire DIY electronics projects. Great for learning copper wire bending and soldering techniques.

---

## 二、ESP32-C3 资源 | ESP32-C3 Resources

### 2.1 官方文档 | Official Documentation

| 资源 Resource | 链接 Link | 说明 Description |
|-------------|---------|-----------------|
| ESP32-C3 技术参考手册 | https://www.espressif.com/sites/default/files/documentation/esp32-c3_technical_reference_manual_en.pdf | 完整的芯片技术文档，包含所有外设寄存器说明 |
| ESP32-C3 数据手册 | https://www.espressif.com/sites/default/files/documentation/esp32-c3_datasheet_en.pdf | 芯片引脚定义、电气特性、封装信息 |
| ESP32 Arduino Core 文档 | https://docs.espressif.com/projects/arduino-esp32/en/latest/ | Arduino 开发环境下的 ESP32 编程指南 |
| ESP-IDF 编程指南 | https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/ | 乐鑫官方 IoT 开发框架文档 |
| ESP32-C3 快速入门 | https://docs.espressif.com/projects/arduino-esp32/en/latest/esp32c3/getting_started.html | Arduino IDE 配置 ESP32-C3 开发环境的步骤指南 |

### 2.2 教程 | Tutorials

1. **太极创客 ESP32-C3 教程（中文）**
   - **链接：** http://www.taichi-maker.com/homepage/esp32-c3/
   - **简介：** 中文 ESP32-C3 入门教程，涵盖基础 GPIO、WiFi、SPI、I2C 等内容。
   - **推荐度：** 强烈推荐（中文、详细、适合初学者）

2. **Random Nerd Tutorials — ESP32-C3**
   - **链接：** https://randomnerdtutorials.com/getting-started-with-esp32-c3/
   - **简介：** 英文教程，ESP32-C3 快速入门指南，包含 Arduino IDE 配置和第一个程序。

3. **ESP32-C3 Arduino 入门（B 站）**
   - **搜索关键词：** "ESP32-C3 Arduino 入门教程"
   - **B 站搜索：** https://search.bilibili.com/all?keyword=ESP32-C3%20Arduino%20%E5%85%A5%E9%97%A8
   - **推荐内容：** ESP32-C3 开发环境搭建、GPIO 控制、WiFi 连接等基础教程

4. **ESP32 低功耗设计教程**
   - **搜索关键词：** "ESP32 deep sleep 低功耗"
   - **B 站搜索：** https://search.bilibili.com/all?keyword=ESP32%20deep%20sleep%20%E4%BD%8E%E5%8A%9F%E8%80%97
   - **推荐内容：** 深度睡眠模式、定时唤醒、功耗优化技巧

### 2.3 ESP32-C3 核心规格 | Key Specifications

| 参数 Parameter | 规格 Specification |
|-------------|-------------------|
| 架构 | RISC-V 32-bit 单核 |
| 主频 | 160 MHz |
| Flash | 4 MB（外部） |
| SRAM | 400 KB |
| WiFi | 802.11 b/g/n (2.4 GHz) |
| 蓝牙 | Bluetooth 5 (LE) |
| GPIO | 22 个可编程 GPIO |
| ADC | 2 个 12-bit SAR ADC，6 通道 |
| SPI | 1 个通用 SPI（GP-SPI） |
| I2C | 1 个 I2C 控制器 |
| UART | 2 个 UART |
| PWM | 6 通道 LED PWM |
| 工作电压 | 3.0V - 3.6V |

---

## 三、ST7735 TFT 显示屏资源 | ST7735 TFT Display Resources

### 3.1 数据手册与文档 | Datasheets & Docs

| 资源 Resource | 链接 Link | 说明 Description |
|-------------|---------|-----------------|
| ST7735 数据手册 | https://www.displayfuture.com/Display/datasheet/controller/ST7735.pdf | ST7735 控制器完整数据手册 |
| ST7735S 规格书 | https://www.crystalfontz.com/controllers/Sitronix/ST7735R/ | ST7735R/S 版本详细规格 |
| Adafruit ST7735 学习指南 | https://learn.adafruit.com/1-8-tft-display | Adafruit 官方 TFT 显示教程（含接线图） |
| 0.96" TFT 80x160 引脚说明 | 搜索 "0.96 TFT ST7735 pinout" | 常见的 8 引脚模块接线说明 |

### 3.2 Arduino 库 | Arduino Libraries

1. **Adafruit ST7735 Library（推荐）**
   - **GitHub:** https://github.com/adafruit/Adafruit-ST7735-Library
   - **Arduino IDE 安装：** 库管理器搜索 "Adafruit ST7735"
   - **简介：** Adafruit 官方 ST7735 驱动库，支持多种尺寸 TFT 屏幕（0.96"/1.44"/1.8"）。提供 `initR()` 方法初始化不同版本的屏幕。
   - **关键函数：** `fillScreen()`, `setCursor()`, `setTextColor()`, `setTextSize()`, `drawLine()`, `fillRect()`

2. **Adafruit GFX Library（依赖）**
   - **GitHub:** https://github.com/adafruit/Adafruit-GFX-Library
   - **Arduino IDE 安装：** 库管理器搜索 "Adafruit GFX Library"
   - **简介：** 基础图形绘制库，提供文字、线条、矩形、圆形等绘制功能。ST7735 库依赖此库。
   - **字体支持：** 内置字体 + 可加载自定义字体

3. **TFT_eSPI（高性能替代）**
   - **GitHub:** https://github.com/Bodmer/TFT_eSPI
   - **简介：** 高性能 TFT 驱动库，使用 ESP32 专用 SPI 优化，帧率更高。适合需要快速刷新的场景。
   - **注意：** 需要修改 `User_Setup.h` 配置引脚，配置比 Adafruit 库稍复杂。

### 3.3 ST7735 常见版本说明 | Common ST7735 Variants

| 版本 Variant | 初始化方法 | 颜色 | 说明 |
|------------|----------|------|------|
| 黑标签 Black Tab | `initR(INITR_BLACKTAB)` | 标准 65K 色 | 最常见版本 |
| 绿标签 Green Tab | `initR(INITR_GREENTAB)` | 颜色偏移 | 需要设置列/行偏移 |
| 红标签 Red Tab | `initR(INITR_REDTAB)` | 标准 65K 色 | 1.8 寸常见 |
| 迷你 144x128 | `initR(INITR_144GREENTAB)` | 标准 | 1.44 寸 |

> Most common 0.96" TFT modules use black tab. If the display shows shifted or garbled content, try different `initR()` options.

### 3.4 SPI 接线参考 | SPI Wiring Reference

| TFT 引脚 | 功能 | ESP32-C3 引脚（参考） |
|---------|------|-------------------|
| SCLK / CLK | SPI 时钟 | GPIO 2 (默认) |
| SDA / MOSI / DIN | SPI 数据 | GPIO 3 (默认) |
| CS / CE | 片选 | GPIO 7 (可自定义) |
| DC / RS | 数据/命令 | GPIO 6 (可自定义) |
| RST / RES | 复位 | GPIO 10 (可自定义) |
| VCC | 电源 | 3.3V 或 5V（看模块） |
| GND | 地 | GND |
| BL / LED | 背光 | 3.3V（常亮）或 PWM 控制 |

> Default SPI pins on ESP32-C3: SCLK=GPIO2, MOSI=GPIO3. CS, DC, RST can be any free GPIO.

---

## 四、SHT31-D 温湿度传感器资源 | SHT31-D Sensor Resources

### 4.1 数据手册 | Datasheets

| 资源 Resource | 链接 Link | 说明 Description |
|-------------|---------|-----------------|
| SHT31-D 数据手册（官方） | https://sensirion.com/media/documents/213E6A3B/63A5A569/Datasheet_SHT3x_DIS.pdf | Sensirion 官方完整数据手册 |
| SHT3x 系列对比 | https://sensirion.com/products/catalog/SHT3x-DIS/ | SHT30/SHT31/SHT32 精度对比 |

### 4.2 SHT31-D 核心规格 | Key Specifications

| 参数 Parameter | 规格 Specification |
|-------------|-------------------|
| 工作电压 | 2.15V - 5.5V |
| 温度范围 | -40°C ~ 125°C |
| 温度精度 | ±0.3°C（SHT31）、±0.2°C（SHT31-ARP） |
| 湿度范围 | 0% ~ 100% RH |
| 湿度精度 | ±2% RH |
| 通信接口 | I2C（地址 0x44 或 0x45） |
| 最大 I2C 速度 | 1 MHz |
| 测量时间 | 约 15ms（高重复性模式） |
| 功耗 | 约 2mW（测量时） |

### 4.3 Arduino 库 | Arduino Libraries

1. **Adafruit SHT31 Library（推荐）**
   - **GitHub:** https://github.com/adafruit/Adafruit_SHT31
   - **Arduino IDE 安装：** 库管理器搜索 "Adafruit SHT31"
   - **简介：** Adafruit 官方 SHT31 驱动库，支持单次和周期测量模式。
   - **关键函数：** `begin()`, `readTemperature()`, `readHumidity()`, `heater(true/false)`

2. **SHT31 Arduino Library (ClosedCube)**
   - **GitHub:** https://github.com/closedcube/ClosedCube_SHT31D
   - **简介：** 另一个 SHT31 驱动库，支持单次/周期/ART 等多种模式。

### 4.4 I2C 接线参考 | I2C Wiring Reference

| SHT31-D 引脚 | 功能 | ESP32-C3 引脚 |
|-------------|------|-------------|
| SDA | I2C 数据 | GPIO 8 (默认 SDA) |
| SCL | I2C 时钟 | GPIO 9 (默认 SCL) |
| VDD | 电源 | 3.3V |
| GND / VSS | 地 | GND |
| ADDR | 地址选择 | 接 GND = 0x44, 接 VDD = 0x45 |
| ALERT | 警报输出 | 可不接 |

> Default I2C pins on ESP32-C3: SDA=GPIO8, SCL=GPIO9. The ADDR pin determines the I2C address (0x44 when grounded).

### 4.5 调试工具 | Debug Tools

- **I2C Scanner Sketch:** Arduino IDE 示例程序，扫描 I2C 总线上的所有设备地址
  ```
  Arduino IDE -> 文件 -> 示例 -> Wire -> i2c_scanner
  ```
- 运行后串口监视器应输出：`I2C device found at address 0x44`

---

## 五、太阳能充电资源 | Solar Charging Resources

### 5.1 基础知识 | Basics

1. **锂电池充电基础**
   - 单节锂电池标称电压：3.7V
   - 满充电压：4.2V
   - 放电截止电压：2.75V - 3.0V
   - 充电模式：恒流（CC）-> 恒压（CV）-> 截止

2. **太阳能充电控制器**
   - 功能：将太阳能板的不稳定输出转换为适合锂电池充电的稳定电压/电流
   - 常用 IC：TP4056（线性）、CN3791（MPPT）、TP5100（开关型）
   - 5V 太阳能板输出经控制器后对 3.7V 锂电池充电

### 5.2 充电 IC 资料 | Charging IC Resources

| IC 型号 | 类型 | 输入电压 | 充电电流 | 说明 |
|--------|------|---------|---------|------|
| TP4056 | 线性 | 4.5-6.5V | 1A | 最常见、最便宜，适合 USB 充电 |
| TP4055 | 线性 | 4.0-6.0V | 500mA | 小型化版本 |
| TP5100 | 开关型 | 4.5-18V | 2A | 效率高，支持太阳能输入 |
| CN3791 | MPPT | 4.5-28V | 可编程 | MPPT 最大功率点追踪，太阳能专用 |

### 5.3 太阳能板选择 | Solar Panel Selection

| 参数 | 推荐值 | 说明 |
|------|--------|------|
| 输出电压 | 5V-6V | 经控制器降压到 4.2V 充电 |
| 功率 | 0.5W - 1W | 迷你太阳能板，适合桌面设备 |
| 尺寸 | 50x50mm ~ 80x60mm | 配合卫星外壳尺寸 |
| 类型 | 单晶硅 | 效率最高，约 15-20% |

### 5.4 教程链接 | Tutorial Links

1. **ESP32 太阳能供电教程**
   - 搜索关键词： "ESP32 太阳能供电 锂电池"
   - B 站搜索： https://search.bilibili.com/all?keyword=ESP32%20%E5%A4%AA%E9%98%B3%E8%83%BD%20%E9%94%82%E7%94%B5%E6%B1%A0

2. **TP4056 充电模块使用教程**
   - 搜索关键词： "TP4056 充电模块 使用教程"
   - B 站搜索： https://search.bilibili.com/all?keyword=TP4056%20%E5%85%85%E7%94%B5%E6%A8%A1%E5%9D%97

3. **太阳能 DIY 项目**
   - 搜索关键词： "DIY 太阳能充电宝 ESP32"
   - B 站搜索： https://search.bilibili.com/all?keyword=DIY%20%E5%A4%AA%E9%98%B3%E8%83%BD%20ESP32

---

## 六、铜线弯制技术资源 | Copper Wire Bending Techniques

### 6.1 基础工具 | Basic Tools

| 工具 Tool | 用途 Purpose | 参考价格 |
|----------|-------------|---------|
| 尖嘴钳 | 弯制小角度、夹持铜线 | 10-15 元 |
| 圆嘴钳 | 弯制圆弧和圆环 | 10-15 元 |
| 平嘴钳 | 夹直铜线、压扁端头 | 10-15 元 |
| 剪线钳 | 切割铜线 | 10-15 元 |
| 圆棒/圆管 | 作为弯制模具（M3 螺丝刀、铁钉等） | 1-5 元 |
| 尺子/卡尺 | 测量铜线长度 | 5-15 元 |
| 记号笔 | 在铜线上标记弯折位置 | 2 元 |

### 6.2 弯制技巧 | Bending Techniques

1. **圆形弯制 / Circle Bending**
   - 将铜线绕在圆棒上（如 M3 螺丝刀杆）
   - 保持均匀力度，一圈一圈绕制
   - 绕完后取下，用平嘴钳修整

2. **直角弯制 / Right Angle Bending**
   - 在弯折点用记号笔标记
   - 用尖嘴钳夹住标记点
   - 用拇指推弯，保持角度 90 度
   - 不要反复弯折同一位置（铜线会断裂）

3. **螺旋弯制 / Spiral Bending**
   - 将铜线沿圆棒螺旋绕制
   - 每圈间距保持一致
   - 适合制作卫星"天线"造型

4. **焊接连接 / Soldering Connections**
   - 铜线焊接需要使用助焊剂（松香或焊锡膏）
   - 烙铁温度建议 300-350°C
   - 焊接前先用砂纸打磨铜线表面氧化层
   - 先涂助焊剂，再上焊锡

### 6.3 参考教程 | Tutorial References

1. **Huy Vector 铜线项目合集**
   - YouTube 播放列表：https://www.youtube.com/@HuyVector/videos
   - 观察原作者的弯制手法和设计思路

2. **铜线手工艺品教程**
   - 搜索关键词： "铜线手工艺品 弯制教程"
   - B 站搜索： https://search.bilibili.com/all?keyword=%E9%93%9C%E7%BA%BF%E6%89%8B%E5%B7%A5%E8%89%BA%E5%93%81%20%E5%BC%AF%E5%88%B6

3. **电子焊接入门教程**
   - 搜索关键词： "电子焊接入门 基础教程"
   - B 站搜索： https://search.bilibili.com/all?keyword=%E7%94%B5%E5%AD%90%E7%84%8A%E6%8E%A5%20%E5%85%A5%E9%97%A8%20%E5%9F%BA%E7%A1%80

4. **黄铜管焊接技巧**
   - 搜索关键词： "黄铜管 焊接 技巧"
   - B 站搜索： https://search.bilibili.com/all?keyword=%E9%BB%84%E9%93%9C%E7%AE%A1%20%E7%84%8A%E6%8E%A5%20%E6%8A%80%E5%B7%A7

---

## 七、Arduino ESP32 开发教程 | Arduino ESP32 Tutorials

### 7.1 开发环境 | Development Environment

| 工具 Tool | 下载链接 Download | 说明 |
|----------|-----------------|------|
| Arduino IDE 2.x | https://www.arduino.cc/en/software | 官方 IDE，推荐版本 |
| ESP32 开发板支持包 | Arduino IDE 开发板管理器 | 搜索 "esp32" 安装 |
| USB 驱动（CH340） | http://www.wch-ic.com/downloads/CH341SER_EXE.html | ESP32-C3 开发板常用 CH340 芯片 |
| USB 驱动（CP2102） | https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers | 另一种常见 USB 转串口芯片 |

### 7.2 入门教程 | Beginner Tutorials

1. **Arduino ESP32 官方入门**
   - **链接：** https://docs.espressif.com/projects/arduino-esp32/en/latest/esp32c3/getting_started.html
   - **内容：** IDE 安装、开发板配置、第一个 Blink 程序

2. **太极创客 ESP32 教程（中文，推荐）**
   - **链接：** http://www.taichi-maker.com/homepage/esp32-c3/
   - **内容：** GPIO、WiFi、SPI、I2C、定时器等完整教程

3. **ESP32 SPI 通信教程**
   - **搜索关键词：** "ESP32 SPI 通信 教程"
   - **B 站搜索：** https://search.bilibili.com/all?keyword=ESP32%20SPI%20%E9%80%9A%E4%BF%A1%20%E6%95%99%E7%A8%8B

4. **ESP32 I2C 通信教程**
   - **搜索关键词：** "ESP32 I2C 通信 教程"
   - **B 站搜索：** https://search.bilibili.com/all?keyword=ESP32%20I2C%20%E9%80%9A%E4%BF%A1%20%E6%95%99%E7%A8%8B

5. **ESP32 WiFi 编程教程**
   - **搜索关键词：** "ESP32 WiFi 编程 Arduino"
   - **B 站搜索：** https://search.bilibili.com/all?keyword=ESP32%20WiFi%20%E7%BC%96%E7%A8%8B%20Arduino

### 7.3 NTP 时间同步 | NTP Time Sync

1. **Arduino ESP32 NTP 教程**
   - **链接：** https://randomnerdtutorials.com/esp32-ntp-client-date-time-arduino-ide/
   - **内容：** 使用 `configTime()` 函数设置时区并通过 NTP 获取网络时间

2. **NTP 代码示例**
   ```cpp
   #include <WiFi.h>
   #include "time.h"

   const char* ntpServer = "pool.ntp.org";
   const long  gmtOffset_sec = 8 * 3600;   // UTC+8 东八区
   const int   daylightOffset_sec = 0;

   void setup() {
     WiFi.begin(ssid, password);
     configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
   }

   void loop() {
     struct tm timeinfo;
     if(getLocalTime(&timeinfo)){
       Serial.println(&timeinfo, "%H:%M:%S");
     }
   }
   ```

3. **常用 NTP 服务器**
   - `pool.ntp.org` — 全球 NTP 服务器池（推荐）
   - `cn.pool.ntp.org` — 中国 NTP 服务器池
   - `ntp.aliyun.com` — 阿里云 NTP 服务器

---

## 八、Adafruit 库文档 | Adafruit Library Documentation

### 8.1 Adafruit GFX 图形指南

- **官方教程：** https://learn.adafruit.com/adafruit-gfx-graphics-library
- **GitHub：** https://github.com/adafruit/Adafruit-GFX-Library
- **核心功能：**
  - `drawPixel(x, y, color)` — 绘制像素点
  - `drawLine(x0, y0, x1, y1, color)` — 绘制线段
  - `drawRect(x, y, w, h, color)` — 绘制矩形边框
  - `fillRect(x, y, w, h, color)` — 填充矩形
  - `drawCircle(x, y, r, color)` — 绘制圆形
  - `fillCircle(x, y, r, color)` — 填充圆形
  - `setCursor(x, y)` — 设置文字光标位置
  - `setTextSize(s)` — 设置文字大小
  - `setTextColor(color)` — 设置文字颜色
  - `print()` / `println()` — 输出文字

### 8.2 Adafruit ST7735 驱动

- **官方教程：** https://learn.adafruit.com/1-8-tft-display
- **GitHub：** https://github.com/adafruit/Adafruit-ST7735-Library
- **初始化示例（0.96" 80x160）：**
  ```cpp
  #include <Adafruit_GFX.h>
  #include <Adafruit_ST7735.h>

  #define TFT_CS    7
  #define TFT_DC    6
  #define TFT_RST   10

  Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

  void setup() {
    tft.initR(INITR_BLACKTAB);    // 0.96" 黑标签屏
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(5, 5);
    tft.setTextColor(ST7735_WHITE);
    tft.setTextSize(2);
    tft.print("Desk Satellite");
  }
  ```

### 8.3 Adafruit SHT31 驱动

- **官方教程：** https://learn.adafruit.com/adafruit-sht31-digital-temperature-humidity-sensor
- **GitHub：** https://github.com/adafruit/Adafruit_SHT31
- **使用示例：**
  ```cpp
  #include <Adafruit_SHT31.h>

  Adafruit_SHT31 sht31 = Adafruit_SHT31();

  void setup() {
    sht31.begin(0x44);  // I2C 地址 0x44
  }

  void loop() {
    float t = sht31.readTemperature();
    float h = sht31.readHumidity();
    Serial.printf("Temp: %.1f C, Humidity: %.1f %%\n", t, h);
    delay(2000);
  }
  ```

---

## 九、硬件采购参考 | Hardware Procurement Reference

### 9.1 国内采购渠道（淘宝）| Domestic Sources (Taobao)

| 元器件 Component | 搜索关键词 Search Keywords | 参考价格 Price |
|-----------------|--------------------------|--------------|
| ESP32-C3 开发板 | "ESP32-C3 开发板" | 15-25 元 |
| ST7735 TFT 0.96寸 | "0.96 TFT ST7735 80x160" | 10-15 元 |
| SHT31-D 温湿度模块 | "SHT31 温湿度模块" | 8-15 元 |
| 3.7V 锂电池 103040 | "103040 锂电池 3.7V" | 10-15 元 |
| Type-C 充电模块 TP4055 | "TP4055 Type-C 充电模块" | 3-5 元 |
| 太阳能充电控制器 | "太阳能充电控制器 5V 锂电" | 5-10 元 |
| 迷你太阳能板 | "迷你太阳能板 5V 0.5W" | 5-10 元 |
| 电池电量指示模块 | "4LED 电池电量指示模块" | 3-5 元 |
| TTP223 触摸开关 | "TTP223 触摸传感器模块" | 2-3 元 |
| LED 3mm | "LED 3mm 发光二极管" | 1-2 元（若干） |
| 铜线 1mm | "纯铜线 1mm 工艺" | 5-10 元 |
| 铜线 0.7mm | "纯铜线 0.7mm 手工" | 5-10 元 |
| 黄铜管 3mm | "黄铜管 3mm 外径" | 5-10 元 |
| 竹杯垫 | "竹杯垫 6cm" | 3-5 元 |

### 9.2 国际采购渠道 | International Sources

| 平台 Platform | 链接 Link | 适用场景 |
|-------------|---------|---------|
| AliExpress | https://www.aliexpress.com/ | 面向海外，搜索 "ESP32-C3 development board" |
| Amazon | https://www.amazon.com/ | 搜索 "ESP32-C3 dev board"、"ST7735 TFT" |
| Adafruit | https://www.adafruit.com/ | 高品质电子元件，搜索对应产品编号 |
| AliExpress ESP32-C3 | https://www.aliexpress.com/w/wholesale-esp32-c3.html | ESP32-C3 开发板 |
| AliExpress ST7735 | https://www.aliexpress.com/w/wholesale-st7735-tft.html | ST7735 TFT 显示屏 |

### 9.3 预算估算 | Budget Estimate

| 类别 Category | 估算 Cost |
|-------------|----------|
| 电子元件 Electronic Components | 约 80-120 元 |
| 结构材料 Structural Materials | 约 20-40 元 |
| 充电与电源 Charging & Power | 约 25-45 元 |
| **合计 Total（不含工具）** | **约 150-250 元** |

> Total estimated cost: approximately 150-250 CNY (excluding tools), well within the 500 CNY budget.

---

## 十、推荐学习路线 | Recommended Learning Path

### 第一阶段：基础准备（课前自学）| Phase 1: Pre-course Self-Study

- [ ] 了解 ESP32-C3 基础（Arduino IDE 配置、GPIO 控制）
- [ ] 了解 SPI 通信协议基础
- [ ] 了解 I2C 通信协议基础
- [ ] 了解锂电池安全使用知识
- [ ] 观看 Huy Vector 原作者视频

### 第二阶段：跟随课程 Day 1-4 | Phase 2: Follow Course Day 1-4

- [ ] ESP32-C3 开发环境搭建
- [ ] ST7735 TFT 显示驱动
- [ ] SHT31-D 传感器数据读取
- [ ] WiFi/NTP 时间同步

### 第三阶段：核心开发 Day 5-8 | Phase 3: Core Development Day 5-8

- [ ] 电源管理系统搭建
- [ ] 显示界面设计与多屏切换
- [ ] 交互功能与系统整合

### 第四阶段：组装与展示 Day 9-12 | Phase 4: Assembly & Presentation Day 9-12

- [ ] 铜线结构弯制与焊接
- [ ] 卫星外壳组装
- [ ] 整机调试与美化
- [ ] Demo 网站部署
- [ ] 最终展示

---

## 十一、补充搜索建议 | Supplementary Search Suggestions

### B 站搜索关键词 | Bilibili Search Keywords

- "ESP32-C3 Arduino 入门" — ESP32-C3 基础教程
- "ST7735 TFT Arduino 教程" — TFT 显示驱动教程
- "SHT31 Arduino" — 温湿度传感器教程
- "ESP32 NTP 时钟" — 网络时钟项目参考
- "铜线手工艺品 卫星" — 铜线造型灵感
- "电子焊接入门" — 焊接基础教程
- "ESP32 太阳能 低功耗" — 太阳能供电方案
- "锂电池充电 TP4056" — 充电模块教程
- "I2C 协议 单片机" — I2C 通信原理
- "SPI 协议 TFT 彩屏" — SPI 显示原理

### GitHub 搜索 | GitHub Search

- `ESP32-C3 TFT ST7735` — 类似项目参考
- `ESP32 weather station` — ESP32 气象站项目
- `SHT31 ESP32 Arduino` — SHT31 驱动代码
- `ESP32 NTP clock TFT` — NTP 时钟项目

### 技术论坛 | Technical Forums

- **Arduino 中文社区：** https://www.arduino.cn/
- **ESP32 官方论坛：** https://esp32.com/
- **立创开源硬件平台：** https://oshwhub.com/
- **CSDN：** 搜索 ESP32/SPI/I2C 相关技术文章
- **Huy Vector Facebook Group：** https://www.facebook.com/groups/huyvectorlab

---

*最后更新：2026-05-27 | Last updated: 2026-05-27*
