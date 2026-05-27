# Day 2: SPI 通信与 TFT 显示 | SPI Communication & TFT Display

## 今日目标 | Today's Goals

- 理解 SPI 通信协议的原理（与 I2C 对比）
- 完成 ST7735 TFT 显示屏的接线
- 学会使用 Adafruit ST7735 + GFX 库驱动彩色 TFT
- 能在 TFT 上显示文字、图形、形状和颜色

---

## 上午 (3h) | Morning Session

### 1. SPI 通信协议原理 (1.5h)

**什么是 SPI？**

SPI (Serial Peripheral Interface) 是一种**四线制**高速同步串行通信协议：
- **SCLK** (Serial Clock) -- 时钟线，控制通信节奏
- **MOSI** (Master Out Slave In) -- 主机输出数据线
- **MISO** (Master In Slave Out) -- 主机输入数据线
- **CS / SS** (Chip Select) -- 片选线，选择目标设备

**SPI vs I2C 对比**：

| 特性 Feature | SPI | I2C |
|-------------|-----|-----|
| 信号线数量 Lines | 4 线 (+ 额外控制线) | 2 线 (SCL + SDA) |
| 速度 Speed | 快（可达数十 MHz） | 慢（标准 100kHz，快速 400kHz） |
| 全双工 Full Duplex | 是（同时收发） | 否（半双工） |
| 寻址方式 Addressing | 片选线（每个设备一根 CS） | 地址（每个设备有唯一 I2C 地址） |
| 适用场景 Use Case | 显示屏、SD 卡、Flash | 传感器、EEPROM |
| 复杂度 Complexity | 接线较多 | 接线简单 |

**类比理解**：
- I2C = 一个老师（MCU）用学号（地址）点名提问多个学生（设备），一次只能问一个
- SPI = 一个老师（MCU）用专线（CS）直接连接每个学生（设备），可以同时说和听

**TFT 显示的 SPI 接线**：

ST7735 TFT 显示屏除了标准 SPI 4 线外，还需要两根控制线：

```
引脚名称    功能              ESP32-C3 GPIO
─────────────────────────────────────────
SCLK       SPI 时钟线        GPIO4
MOSI/SDA   SPI 数据线        GPIO5
CS         片选（低有效）     GPIO6
DC/RS      数据/命令选择     GPIO7
RST        复位（低有效）     GPIO10
VCC        电源 (3.3V)       3.3V
GND        地线              GND
BL         背光控制          3.3V (常亮) 或 GPIO
```

**DC/RS 引脚的重要性**：
- DC = Data/Command（数据/命令）
- 当 DC 为 LOW 时，SPI 传输的是**命令**（如"清屏"、"设置亮度"）
- 当 DC 为 HIGH 时，SPI 传输的是**数据**（如像素颜色值）
- 这是 SPI 显示屏特有的控制线，I2C OLED 通过不同的 I2C 地址区分

### 2. TFT 显示屏接线实战 (1.5h)

**面包板接线**：

```
ESP32-C3          ST7735 TFT (0.96" 80x160)
─────────         ─────────────────────────
3V3         ────▶ VCC
GND         ────▶ GND
GPIO4       ────▶ SCLK
GPIO5       ────▶ MOSI (SDA)
GPIO6       ────▶ CS
GPIO7       ────▶ DC (RS/A0)
GPIO10      ────▶ RST
3V3         ────▶ BL (背光，直接接 3.3V 常亮)
```

**接线注意事项**：
1. VCC 必须接 **3.3V**，不能接 5V
2. BL（背光）直接接 3.3V 即可常亮
3. 杜邦线要插紧，接触不良会导致显示异常
4. 建议先用面包板测试，确认无误后再焊接

**验证接线**：
- 使用万用表确认 VCC 和 GND 之间的电压为 3.3V
- 检查每根线是否插在正确的 GPIO 上

**讨论**：
- 为什么 SPI 比 I2C 快？全双工和半双工的区别是什么？
- ST7735 TFT 有 8 个引脚，而 SSD1306 OLED 只有 4 个引脚，多出来的引脚有什么用？
- 为什么 TFT 需要背光（BL）而 OLED 不需要？

---

## 下午 (4h) | Afternoon Session

### 3. Adafruit ST7735 + GFX 库安装 (0.5h)

**安装步骤**：
1. Arduino IDE -> 工具 -> 管理库
2. 搜索并安装以下库：
   - **Adafruit ST7735 and ST7789 Library**（ST7735 驱动）
   - **Adafruit GFX Library**（基础图形库）
   - **Adafruit BusIO**（I2C/SPI 通信底层）
3. 以上库会自动安装依赖

### 4. TFT 初始化与基本使用 (1.5h)

**初始化 TFT 显示屏**：

```cpp
// ST7735 TFT 初始化
#include <Adafruit_GFX.h>     // 基础图形库
#include <Adafruit_ST7735.h>   // ST7735 驱动库
#include <SPI.h>               // SPI 通信库

// 引脚定义 Pin Definitions
#define TFT_SCLK 4
#define TFT_MOSI 5
#define TFT_CS   6
#define TFT_DC   7
#define TFT_RST  10

// 创建 TFT 对象（软件 SPI）
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

// 或者使用硬件 SPI（更快，但需要使用指定引脚）：
// Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);
  Serial.println("ST7735 TFT Test");

  // 初始化 TFT - 0.96" 80x160 屏幕
  tft.initR(INITR_144GREENTAB);  // 或 INITR_MINI160x80 根据你的屏幕型号

  // 如果你的是 0.96" 80x160 的屏幕，可能需要：
  // tft.initR(INITR_GREENTAB160x80);

  tft.setRotation(1);  // 设置屏幕方向 (0-3)
  tft.fillScreen(ST7735_BLACK);  // 清屏为黑色

  Serial.println("TFT initialized successfully!");
}

void loop() {
  // 暂时空循环
}
```

**常见初始化问题**：
- 屏幕全白 -> 检查接线，特别是 CS 和 DC 引脚
- 屏幕有杂色 -> initR 参数不正确，尝试不同的 TAB 类型
- 显示偏移 -> 可能需要手动设置偏移量：`tft.setRowColStart(?, ?)`

### 5. 文字、图形、颜色实战 (2h)

**5a. 显示文字 Display Text**：

```cpp
void testText() {
  tft.fillScreen(ST7735_BLACK);  // 清屏

  // 设置文字大小和颜色
  tft.setTextSize(1);             // 最小字号 (6x8 像素/字符)
  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(0, 0);
  tft.println("Hello World!");

  tft.setTextSize(2);             // 2x 放大 (12x16 像素/字符)
  tft.setTextColor(ST7735_YELLOW);
  tft.println("Desk Satellite");

  tft.setTextSize(1);
  tft.setTextColor(ST7735_CYAN);
  tft.println("ESP32-C3 + ST7735");
  tft.println("Temperature: 25.3C");
  tft.println("Humidity: 65%");
}
```

**5b. 绘制图形 Draw Shapes**：

```cpp
void testShapes() {
  tft.fillScreen(ST7735_BLACK);

  // 画线 Draw lines
  tft.drawLine(0, 0, 80, 50, ST7735_RED);    // 从 (0,0) 到 (80,50) 的红线
  tft.drawFastHLine(0, 55, 80, ST7735_GREEN);  // 水平线
  tft.drawFastVLine(80, 0, 50, ST7735_BLUE);   // 垂直线

  // 画矩形 Draw rectangles
  tft.drawRect(5, 60, 40, 30, ST7735_YELLOW);     // 空心矩形
  tft.fillRect(50, 60, 30, 30, ST7735_MAGENTA);    // 实心矩形

  // 画圆 Draw circles
  tft.drawCircle(40, 110, 20, ST7735_CYAN);        // 空心圆
  tft.fillCircle(70, 110, 15, ST7735_ORANGE);       // 实心圆

  // 画三角形 Draw triangle
  tft.drawTriangle(10, 140, 40, 100, 70, 140, ST7735_WHITE);
}
```

**5c. 颜色系统 Color System**：

ST7735 使用 **RGB565** 颜色格式（16 位色，65536 色）：

```
RGB565 格式：
  RRRRR GGGGGG BBBBB
  5位红 6位绿  5位蓝
  (人眼对绿色更敏感，所以绿色多1位)
```

```cpp
// 预定义颜色 Predefined Colors
ST7735_BLACK    // 黑色
ST7735_WHITE    // 白色
ST7735_RED      // 红色
ST7735_GREEN    // 绿色
ST7735_BLUE     // 蓝色
ST7735_CYAN     // 青色
ST7735_MAGENTA  // 品红
ST7735_YELLOW   // 黄色
ST7735_ORANGE   // 橙色

// 自定义颜色 Custom Color
// tft.color565(R, G, B) - 将 8-bit RGB 转为 RGB565
uint16_t myColor = tft.color565(255, 128, 0);  // 自定义橙色
tft.fillRect(0, 0, 40, 40, myColor);

// 渐变色示例 Gradient Example
void drawGradient() {
  for (int y = 0; y < 80; y++) {
    uint16_t color = tft.color565(y * 3, 0, 255 - y * 3);
    tft.drawFastHLine(0, y, 160, color);
  }
}
```

**5d. 坐标系统 Coordinate System**：

```
ST7735 0.96" TFT 坐标系 (80 x 160 默认方向)：

(0,0) ──────────────────────── (159,0)
  │                                │
  │      160 x 80 像素 (横屏)      │
  │                                │
(0,79) ─────────────────────── (159,79)

setRotation(0): 80x160 竖屏 (默认)
setRotation(1): 160x80 横屏
setRotation(2): 80x160 竖屏（翻转）
setRotation(3): 160x80 横屏（翻转）
```

---

## 今日作业 | Today's Task

1. 完成 TFT 显示屏的接线，屏幕能正常点亮（显示黑色/白色）
2. 成功运行文字显示示例，在屏幕上显示 "Desk Satellite"
3. 完成图形绘制练习：画线、矩形、圆、三角形
4. **创意任务**：在 TFT 上绘制一个简单的"卫星"图案（圆形主体 + 线条"太阳能板"）
5. 预习：I2C 协议和 SHT31-D 温湿度传感器

## 今日检查点 | Checkpoint

- [ ] TFT 显示屏能正常点亮吗？（黑色背景）
- [ ] 能在 TFT 上显示彩色文字吗？
- [ ] 能画出矩形、圆形、三角形吗？
- [ ] 知道 SPI 的 4 根信号线分别叫什么吗？
- [ ] 知道 ST7735 使用什么颜色格式吗？（RGB565）
- [ ] 知道 TFT 为什么比 OLED 多几根接线吗？
- [ ] 了解 RGB565 中为什么绿色比红色和蓝色多 1 位吗？
