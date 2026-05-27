# Day 1: ESP32-C3 入门与开发环境 | ESP32-C3 Basics & Dev Environment

## 今日目标 | Today's Goals

- 了解项目全貌和最终效果
- 认识 ESP32-C3 硬件及其与 ESP8266 的区别
- 配置 Arduino IDE 开发环境
- 成功烧录第一个程序（Blink）
- 理解 GPIO 概念并完成 WiFi 扫描

---

## 上午 (3h) | Morning Session

### 1. 项目介绍与演示 (1h)

**展示最终成品**：

播放 Huy Vector 的原始视频（https://www.youtube.com/watch?v=0zJG3wExY-c），让学员直观了解最终目标。如果有已完成的实物，现场演示：

- 卫星造型外壳（铜线 + 黄铜管）
- TFT 彩色显示屏：时钟、温度、湿度
- 触摸开关控制开关机
- 太阳能板充电效果
- LED 指示灯状态

**介绍项目全貌**：

```
Desk Satellite 系统架构：

  ┌──────────────┐
  │  太阳能板 x2  │────┐
  └──────────────┘    │   ┌──────────────┐
                      ├──▶│  充电控制器    │──▶ 3.7V 锂电池
  ┌──────────────┐    │   └──────────────┘    │
  │  Type-C 充电  │────┘                      │
  └──────────────┘                            ▼
                                         ┌─────────┐
  ┌──────────────┐    SPI (4线)           │ ESP32-C3 │◀── I2C (2线) ── SHT31-D
  │ ST7735 TFT   │◀───────────────────────│  主控    │                  温湿度
  │ 0.96" 彩色屏  │                        └─────────┘
  └──────────────┘       │          │
                      WiFi/NTP    GPIO
                                  │
                      ┌───────────┼──────────┐
                      ▼           ▼          ▼
                  触摸开关    LED 指示灯   电量指示
```

**讨论**：
- 你觉得这个项目最难的部分是什么？（焊接？SPI？电源？铜线弯制？）
- 你最期待完成哪个部分？
- ESP32-C3 和 ESP8266 有什么区别？（提前思考）

### 2. ESP32-C3 硬件认知 (1h)

**认识手上的开发板**：

```
ESP32-C3 开发板实物观察：
- USB Type-C 接口（用于供电和烧录）
- ESP32-C3 芯片（黑色小方块，RISC-V 32-bit）
- 4MB Flash 存储
- 板载 LED（通常在 GPIO8 或 GPIO19）
- Boot 按钮 + Reset 按钮
- 多个 GPIO 引脚（排针或焊盘）
- PCB 天线（WiFi/BLE 信号收发）
```

**ESP32-C3 vs ESP8266 对比**：

| 特性 Feature | ESP8266 | ESP32-C3 |
|-------------|---------|----------|
| 架构 Architecture | Xtensa 32-bit | RISC-V 32-bit |
| 主频 Clock Speed | 80/160 MHz | 160 MHz |
| WiFi | 802.11 b/g/n | 802.11 b/g/n |
| 蓝牙 Bluetooth | 无 No | BLE 5.0 |
| Flash | 通常 2MB | 4MB |
| GPIO 数量 | 最多 17 | 最多 22 |
| 工作电压 Voltage | 3.3V | 3.3V |
| 价格 Price | ~8 元 | ~15-25 元 |
| 适合场景 Use Case | 简单 IoT | 复杂 IoT + BLE |

**关键知识点**：
- **工作电压 3.3V**（不是 5V！接 5V 可能损坏）
- ESP32-C3 使用 RISC-V 开源架构，是未来嵌入式趋势
- 内置 WiFi + BLE 5.0，蓝牙在本项目中不使用但未来可扩展
- 4MB Flash 足够存储程序和简单的文件系统

### 3. Arduino IDE 安装与配置 (1h)

**安装步骤**：
1. 访问 https://www.arduino.cc/en/software
2. 下载 Windows 版本（Win10+, 64bit）
3. 安装（全部默认选项）

**添加 ESP32 开发板支持**：
1. 文件 -> 首选项 -> 附加开发板管理器网址
2. 填入：`https://espressif.github.io/arduino-esp32/package_esp32_index.json`
3. 工具 -> 开发板 -> 开发板管理器
4. 搜索 "ESP32" -> 安装 `esp32 by Espressif Systems`

**选择正确的开发板**：
1. 工具 -> 开发板 -> 选择 **ESP32C3 Dev Module**
2. 工具 -> 端口 -> 选择对应的 COM 口
3. 工具 -> USB CDC On Boot -> **Enabled**（重要！否则串口无输出）

---

## 下午 (4h) | Afternoon Session

### 4. 第一个程序：Blink (1h)

**目标**：让 ESP32-C3 上的 LED 闪烁。

```cpp
// Blink - 你的第一个 ESP32-C3 程序
// 让板载 LED 以 1 秒间隔闪烁
// ESP32-C3 Dev Kit 的板载 LED 通常在 GPIO8

#define LED_PIN 8  // 根据你的开发板修改引脚号

void setup() {
  Serial.begin(115200);       // 初始化串口通信，波特率 115200
  Serial.println("Desk Satellite starting...");
  pinMode(LED_PIN, OUTPUT);   // 设置 LED 引脚为输出模式
}

void loop() {
  digitalWrite(LED_PIN, HIGH);  // 点亮 LED
  Serial.println("LED ON");
  delay(1000);                  // 等待 1 秒

  digitalWrite(LED_PIN, LOW);   // 熄灭 LED
  Serial.println("LED OFF");
  delay(1000);                  // 等待 1 秒
}
```

**烧录步骤**：
1. 用 Type-C 数据线连接 ESP32-C3 到电脑
2. 确认 Arduino IDE 选择了正确的开发板和端口
3. 点击上传按钮 (->)
4. 等待编译和烧录完成
5. 观察板载 LED 是否闪烁

**常见问题排查**：
- 上传失败 "Failed to connect to ESP32" -> 按住 Boot 按钮再点击上传
- COM 口不显示 -> 检查 USB 线是否为数据线（不是充电线），安装 CP2102/CH340 驱动
- LED 不亮 -> 尝试不同的 GPIO 编号（8, 10, 18, 19，取决于开发板型号）
- 串口无输出 -> 确认 "USB CDC On Boot" 设置为 "Enabled"

### 5. GPIO 深入理解 (1h)

**什么是 GPIO？**

GPIO (General Purpose Input/Output) 是 MCU 与外部世界交互的接口。每个 GPIO 引脚可以：
- **输出 (OUTPUT)**：控制外部设备（LED、继电器等）
- **输入 (INPUT)**：读取外部信号（按钮、传感器等）

**ESP32-C3 GPIO 特点**：
- 支持 ADC（模拟输入）的引脚：GPIO0-5
- 支持 PWM 输出的引脚：大部分 GPIO
- 内置上拉/下拉电阻（可软件配置）
- 注意：某些引脚有特殊用途（Strapping pins），使用前需查阅文档

**实验：GPIO 输入与输出**

```cpp
// GPIO 实验：按钮控制 LED
#define LED_PIN 8
#define BTN_PIN 9   // 连接一个按钮到 GPIO9

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);  // 使用内部上拉电阻
}

void loop() {
  int btnState = digitalRead(BTN_PIN);

  if (btnState == LOW) {  // 按钮按下（低电平）
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Button pressed - LED ON");
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  delay(50);  // 简单消抖
}
```

### 6. WiFi 扫描实验 (2h)

**目标**：使用 ESP32-C3 扫描周围的 WiFi 网络。

```cpp
// WiFi Scan - 扫描周围 WiFi 网络
#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n=== Desk Satellite WiFi Scanner ===");
  Serial.println("ESP32-C3 WiFi Scan Starting...\n");

  // 设置 WiFi 为 Station 模式
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();  // 断开任何已有连接
  delay(100);
}

void loop() {
  Serial.println("Scanning WiFi networks...");

  int networkCount = WiFi.scanNetworks();

  if (networkCount == 0) {
    Serial.println("No networks found.");
  } else {
    Serial.print(networkCount);
    Serial.println(" networks found:\n");

    Serial.println("Nr | SSID             | RSSI | Channel | Encryption");
    Serial.println("---|------------------|------|---------|-----------");

    for (int i = 0; i < networkCount; i++) {
      // 打印网络信息
      Serial.printf("%2d | %-16s | %4d | %7d | ",
                    i + 1,
                    WiFi.SSID(i).c_str(),
                    WiFi.RSSI(i),
                    WiFi.channel(i));

      // 打印加密类型
      switch (WiFi.encryptionType(i)) {
        case WIFI_AUTH_OPEN:     Serial.print("Open"); break;
        case WIFI_AUTH_WEP:      Serial.print("WEP"); break;
        case WIFI_AUTH_WPA_PSK:  Serial.print("WPA-PSK"); break;
        case WIFI_AUTH_WPA2_PSK: Serial.print("WPA2-PSK"); break;
        default:                 Serial.print("Unknown"); break;
      }
      Serial.println();
    }
  }

  Serial.println("\n--- Scan complete. Rescan in 10 seconds ---\n");
  delay(10000);  // 每 10 秒扫描一次
}
```

**实验任务**：
1. 烧录 WiFi 扫描程序
2. 打开串口监视器（波特率 115200）
3. 记录扫描到的网络数量和信号强度
4. 找到你要连接的 WiFi（教室/家中的 WiFi）
5. **修改代码**：尝试连接到指定 WiFi 网络（提示：`WiFi.begin(ssid, password)`）

**连接 WiFi 的代码**：

```cpp
// 连接到指定 WiFi 网络
#include <WiFi.h>

const char* ssid     = "YOUR_WIFI_NAME";     // 替换为你的 WiFi 名称
const char* password = "YOUR_WIFI_PASSWORD";  // 替换为你的 WiFi 密码

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Signal Strength (RSSI): ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
  } else {
    Serial.println("\nWiFi connection failed!");
    Serial.println("Check SSID and password.");
  }
}

void loop() {
  // 每 5 秒打印一次连接状态
  Serial.printf("WiFi status: %d, RSSI: %d dBm\n",
                WiFi.status(), WiFi.RSSI());
  delay(5000);
}
```

**讨论**：
- 为什么扫描 WiFi 时要调用 `WiFi.disconnect()`？
- RSSI 值越大（越接近 0）信号越好还是越差？
- 连接失败时如何调试？（检查 SSID/密码、信号强度、路由器限制）

---

## 今日作业 | Today's Task

1. 确保 Blink 程序烧录成功，LED 正常闪烁
2. 完成 WiFi 扫描实验，记录扫描结果
3. 尝试连接到指定 WiFi 网络，成功获取 IP 地址
4. 在笔记本上画出 ESP32-C3 开发板的引脚图（标注 GPIO 编号）
5. 阅读 `curriculum/prerequisites.md`，标记你不理解的名词
6. 观看 Huy Vector 的原始视频，思考你觉得最有趣的部分

## 今日检查点 | Checkpoint

- [ ] Blink 程序烧录成功，LED 以 1 秒间隔闪烁？
- [ ] 串口监视器能看到 "LED ON" / "LED OFF" 输出？
- [ ] WiFi 扫描能发现周围的 WiFi 网络？
- [ ] 能成功连接到指定 WiFi 并获取 IP 地址？
- [ ] 知道 ESP32-C3 的工作电压是 3.3V？
- [ ] 知道 setup() 和 loop() 的区别？
- [ ] 知道 ESP32-C3 和 ESP8266 的至少 3 个区别？
