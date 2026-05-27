# Day 3: I2C 传感器与数据采集 | I2C Sensor & Data Acquisition

## 今日目标 | Today's Goals

- 理解 I2C 通信协议的原理（与 SPI 对比复习）
- 完成 SHT31-D 温湿度传感器的接线
- 学会使用 Adafruit SHT31 库读取温度和湿度数据
- 理解传感器数据校准的基本方法

---

## 上午 (3h) | Morning Session

### 1. I2C 协议原理复习与深入 (1h)

**I2C 回顾**（对比 Day 2 学过的 SPI）：

I2C (Inter-Integrated Circuit) 是一种**两线制**串行通信协议：
- **SCL** (Serial Clock) -- 时钟线，由主机驱动
- **SDA** (Serial Data) -- 数据线，双向传输

**I2C 通信的 5 个关键步骤**：

```
1. 主机发送 START 信号（SDA 从高变低，同时 SCL 为高）
2. 主机发送 7 位设备地址 + 读/写位
3. 从机应答（ACK）
4. 数据传输（8 位数据 + ACK）
5. 主机发送 STOP 信号（SDA 从低变高，同时 SCL 为高）
```

**I2C 地址**：
- 每个 I2C 设备有一个 7 位地址（0x00 - 0x7F）
- SHT31-D 默认地址：**0x44**（ADDR 引脚接地）或 **0x45**（ADDR 引脚接高电平）
- 同一条 I2C 总线上不能有两个相同地址的设备

**类比理解**：
- I2C 总线 = 一间教室
- SCL = 老师拍手的节奏（时钟）
- SDA = 学生们轮流发言（数据）
- 地址 = 学号（老师叫到哪个学号，哪个学生回答）

### 2. SHT31-D 传感器接线 (1h)

**认识 SHT31-D 模块**：

```
SHT31-D 模块实物观察：
- Sensirion SHT31-D 芯片（小黑色方块）
- 4 个引脚：VCC, GND, SCL, SDA
- 有些模块有 ADDR 引脚（选择 I2C 地址）
- 精度：温度 ±0.3°C，湿度 ±2% RH
- 工作电压：2.15V - 5.5V（兼容 3.3V）
```

**接线表**：

```
ESP32-C3          SHT31-D
─────────         ───────
3V3         ────▶ VCC
GND         ────▶ GND
GPIO1       ────▶ SCL    (I2C 时钟线)
GPIO0       ────▶ SDA    (I2C 数据线)
```

**重要说明**：
- ESP32-C3 的默认 I2C 引脚：SDA = GPIO8, SCL = GPIO9（但可以任意配置）
- 本项目使用 GPIO0 (SDA) 和 GPIO1 (SCL)，避免与其他功能冲突
- SHT31-D 模块通常已内置上拉电阻，无需额外添加
- I2C 总线需要上拉电阻（SCL 和 SDA 各一个 4.7k-10k 欧姆电阻到 VCC）

**I2C 地址扫描工具**：

```cpp
// I2C Scanner - 扫描 I2C 总线上的设备
#include <Wire.h>

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n=== I2C Device Scanner ===");

  Wire.begin(0, 1);  // SDA=GPIO0, SCL=GPIO1
}

void loop() {
  Serial.println("Scanning I2C bus...");

  int deviceCount = 0;

  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("Device found at address 0x");
      if (address < 16) Serial.print("0");
      Serial.print(address, HEX);
      Serial.println();

      if (address == 0x44) {
        Serial.println("  -> SHT31-D detected! (default address)");
      }

      deviceCount++;
    }
  }

  if (deviceCount == 0) {
    Serial.println("No I2C devices found! Check wiring.");
  } else {
    Serial.printf("Found %d device(s).\n", deviceCount);
  }

  Serial.println("--- Rescan in 5 seconds ---\n");
  delay(5000);
}
```

**讨论**：
- 为什么 I2C 只需要 2 根线，而 SPI 需要 4 根以上？
- 如果扫描不到 SHT31-D，可能是什么原因？（接线错误、地址不对、模块损坏）
- 能否在同一个 I2C 总线上挂多个传感器？

### 3. SPI + I2C 共存方案 (1h)

**Desk Satellite 的双总线架构**：

```
ESP32-C3 引脚分配：

SPI 总线 (TFT 显示):
  GPIO4  - SCLK
  GPIO5  - MOSI
  GPIO6  - CS
  GPIO7  - DC
  GPIO10 - RST

I2C 总线 (SHT31-D):
  GPIO0  - SDA
  GPIO1  - SCL

其他:
  GPIO8  - 板载 LED / 状态指示
  GPIO2  - 触摸开关 (后续)
  GPIO3  - LED 指示灯 (后续)
```

**为什么 SPI 和 I2C 可以共存？**
- 它们使用完全不同的引脚和通信协议
- ESP32-C3 可以同时使用硬件 SPI 和硬件 I2C
- 在代码中分别初始化两个总线即可

---

## 下午 (4h) | Afternoon Session

### 4. SHT31-D 驱动与数据读取 (1.5h)

**安装 Adafruit SHT31 库**：
1. Arduino IDE -> 工具 -> 管理库
2. 搜索 "Adafruit SHT31"
3. 安装 "Adafruit SHT31 by Adafruit"
4. 会自动安装依赖 "Adafruit BusIO"

**读取温湿度数据**：

```cpp
// SHT31-D 温湿度传感器测试
#include <Adafruit_SHT31.h>
#include <Wire.h>

// 创建传感器对象
Adafruit_SHT31 sht31 = Adafruit_SHT31();

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("=== SHT31-D Sensor Test ===");

  // 初始化 I2C (SDA=GPIO0, SCL=GPIO1)
  Wire.begin(0, 1);

  // 初始化 SHT31-D (地址 0x44)
  if (!sht31.begin(0x44)) {
    Serial.println("ERROR: Could not find SHT31-D sensor!");
    Serial.println("Check wiring: SDA=GPIO0, SCL=GPIO1");
    while (1) delay(1);  // 停在这里
  }

  Serial.println("SHT31-D sensor found and initialized!");

  // 启用传感器内置加热器（可选，用于除湿）
  // sht31.heater(true);  // 一般不需要开启
}

void loop() {
  // 读取温度（摄氏度）
  float temperature = sht31.readTemperature();

  // 读取湿度（百分比）
  float humidity = sht31.readHumidity();

  // 检查读取是否有效
  if (!isnan(temperature)) {
    Serial.printf("Temperature: %.2f C\n", temperature);
  } else {
    Serial.println("ERROR: Failed to read temperature!");
  }

  if (!isnan(humidity)) {
    Serial.printf("Humidity: %.2f %%\n", humidity);
    } else {
    Serial.println("ERROR: Failed to read humidity!");
  }

  // 计算露点温度（ Dew Point）
  if (!isnan(temperature) && !isnan(humidity)) {
    float dewPoint = temperature - ((100 - humidity) / 5.0);
    Serial.printf("Dew Point: %.1f C\n", dewPoint);
  }

  Serial.println("---");
  delay(2000);  // 每 2 秒读取一次
}
```

**传感器读取频率**：
- SHT31-D 最大采样率约 2Hz（每秒 2 次）
- 建议间隔 >= 500ms 读取一次
- 读取过于频繁会导致传感器自热，影响温度精度

### 5. 数据校准与处理 (1.5h)

**为什么需要校准？**

即使是高精度的 SHT31-D（±0.3°C），实际测量值也可能有偏差。常见偏差来源：
- 传感器模块自热（工作电流产生热量）
- ESP32-C3 自热传导
- 环境因素（通风不良、阳光直射）

**简单校准方法**：

```cpp
// 温湿度数据校准
// 方法 1：固定偏移校准
float calibrateTemperature(float rawTemp) {
  // 与标准温度计对比，确定偏移量
  // 例如：传感器读数比实际高 0.5°C
  float offset = -0.5;  // 根据实际测试调整
  return rawTemp + offset;
}

float calibrateHumidity(float rawHumidity) {
  // 湿度偏移校准
  float offset = 2.0;  // 例如传感器读数比实际低 2%
  return rawHumidity + offset;
}

// 方法 2：滑动平均滤波（减少读数波动）
#define FILTER_SIZE 10

float tempReadings[FILTER_SIZE];
float humReadings[FILTER_SIZE];
int filterIndex = 0;

void addReading(float temp, float hum) {
  tempReadings[filterIndex] = temp;
  humReadings[filterIndex] = hum;
  filterIndex = (filterIndex + 1) % FILTER_SIZE;
}

float getAverageTemp() {
  float sum = 0;
  for (int i = 0; i < FILTER_SIZE; i++) {
    sum += tempReadings[i];
  }
  return sum / FILTER_SIZE;
}

float getAverageHumidity() {
  float sum = 0;
  for (int i = 0; i < FILTER_SIZE; i++) {
    sum += humReadings[i];
  }
  return sum / FILTER_SIZE;
}
```

**数据范围检查**：

```cpp
// 检查数据是否在合理范围内
bool isValidReading(float temp, float hum) {
  // SHT31-D 测量范围：温度 -40~125°C，湿度 0~100%
  bool tempValid = (temp >= -40.0 && temp <= 125.0);
  bool humValid  = (hum >= 0.0 && hum <= 100.0);
  return tempValid && humValid;
}
```

### 6. 综合实战：TFT 显示温湿度 (1h)

**将 SPI 显示 + I2C 传感器组合**：

```cpp
// 综合示例：TFT 显示屏 + SHT31-D 温湿度
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_SHT31.h>
#include <SPI.h>
#include <Wire.h>

// TFT 引脚
#define TFT_SCLK 4
#define TFT_MOSI 5
#define TFT_CS   6
#define TFT_DC   7
#define TFT_RST  10

// I2C 引脚
#define I2C_SDA  0
#define I2C_SCL  1

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
Adafruit_SHT31 sht31 = Adafruit_SHT31();

void setup() {
  Serial.begin(115200);

  // 初始化 I2C
  Wire.begin(I2C_SDA, I2C_SCL);

  // 初始化 SHT31-D
  if (!sht31.begin(0x44)) {
    Serial.println("SHT31-D init failed!");
    while (1) delay(1);
  }

  // 初始化 TFT
  tft.initR(INITR_GREENTAB160x80);
  tft.setRotation(1);
  tft.fillScreen(ST7735_BLACK);

  Serial.println("All systems initialized!");
}

void displaySensorData(float temp, float hum) {
  tft.fillScreen(ST7735_BLACK);

  // 标题
  tft.setTextSize(1);
  tft.setTextColor(ST7735_CYAN);
  tft.setCursor(5, 5);
  tft.println("Desk Satellite");

  // 分隔线
  tft.drawFastHLine(5, 16, 150, ST7735_CYAN);

  // 温度
  tft.setTextSize(2);
  tft.setTextColor(ST7735_YELLOW);
  tft.setCursor(5, 25);
  tft.print("T:");
  tft.print(temp, 1);
  tft.print("C");

  // 湿度
  tft.setTextColor(ST7735_GREEN);
  tft.setCursor(5, 50);
  tft.print("H:");
  tft.print(hum, 1);
  tft.print("%");

  // 状态
  tft.setTextSize(1);
  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(5, 72);
  tft.println("Sensor: SHT31-D OK");
}

void loop() {
  float temp = sht31.readTemperature();
  float hum  = sht31.readHumidity();

  if (!isnan(temp) && !isnan(hum)) {
    Serial.printf("Temp: %.1f C, Hum: %.1f %%\n", temp, hum);
    displaySensorData(temp, hum);
  } else {
    Serial.println("Sensor read error!");
  }

  delay(2000);
}
```

**实验任务**：
1. 完成接线（SPI + I2C 同时连接到 ESP32-C3）
2. 运行综合示例，TFT 上显示温度和湿度
3. 用手捂住 SHT31-D 传感器，观察温度和湿度变化
4. 对着传感器吹气，观察湿度变化
5. 记录 10 分钟内的温湿度变化趋势

---

## 今日作业 | Today's Task

1. 完成 SHT31-D 接线，能通过 I2C 扫描发现设备（地址 0x44）
2. 成功读取温度和湿度数据并在串口打印
3. 完成 TFT + SHT31-D 综合显示
4. 对传感器进行简单的校准（与教室温度计对比）
5. 记录至少 5 次温湿度读数，观察数据波动

## 今日检查点 | Checkpoint

- [ ] I2C 扫描能发现 SHT31-D（地址 0x44）？
- [ ] 串口能打印温度和湿度数据？
- [ ] 温度读数在合理范围内（15-35°C）？
- [ ] TFT 屏幕能显示温湿度数据？
- [ ] 知道 I2C 和 SPI 的主要区别吗？
- [ ] 知道 SHT31-D 的精度是多少吗？（温度 ±0.3°C，湿度 ±2%）
- [ ] SPI 和 I2C 可以同时使用吗？（可以！）
