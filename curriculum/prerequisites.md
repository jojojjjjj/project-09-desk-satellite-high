# 前置知识 | Prerequisites

## 必备基础 | Required Basics

### C 语言基础 | C Language Fundamentals

- 变量与数据类型（`int`, `float`, `char`, `String`, `uint8_t`, `uint16_t`）
- 条件判断（`if` / `else if` / `else`）
- 循环（`for`, `while`）
- 函数定义与调用
- 数组基础
- 预处理器指令（`#include`, `#define`）
- 结构体基础（`struct`）-- 可选但推荐

### 电子基础 | Electronics Basics

- 知道什么是电压（3.3V vs 5V），什么是电流，什么是电阻
- 知道什么是 GND（地线），什么是 VCC（电源正极）
- 了解面包板的基本用法
- 了解电阻、电容的基本功能
- **本项目需要焊接**，但无需焊接经验（Day 9 从零教起）

### 编程工具基础 | Tool Basics

- 会使用浏览器和搜索引擎查找资料
- 会下载和安装软件
- 了解什么是文件（`.ino`, `.h`, `.cpp` 文件类型）
- 了解基本的文件路径概念

---

## 推荐自学资源 | Recommended Self-Study Resources

### C 语言速成 | C Language Crash Course (2 天)

- [菜鸟教程 C 语言](https://www.runoob.com/cprogramming/c-tutorial.html) -- 阅读 1-12 章即可
- [C 语言入门视频](https://www.bilibili.com/video/BV1q54y1q79w/) -- 2 小时快速入门
- 重点掌握：变量、条件、循环、函数、数组

### 电子基础 | Electronics Fundamentals (1 天)

- [面包板使用教程](https://www.bilibili.com/video/BV1Bt411q7pJ/) -- 5 分钟学会
- [电阻色环识别](https://www.bilibili.com/video/BV1Yb411H7qL/) -- 10 分钟了解
- [电压电流电阻基础](https://www.bilibili.com/video/BV1Wt41157oY/) -- 30 分钟入门

### Arduino / ESP32 入门 | Arduino & ESP32 Basics (1-2 天，可选)

- [Arduino 官方入门教程](https://www.arduino.cc/en/Guide) -- 了解 Arduino 基本概念
- [太极创客 ESP32 教程](https://www.taichi-maker.com/homepage/esp32-c3devkitc-getting-started/) -- ESP32-C3 入门
- [ESP32-C3 Arduino 编程指南](https://docs.espressif.com/projects/arduino-esp32/en/latest/esp32c3/) -- 官方文档

### 焊接入门 | Soldering Basics (1 天，可选)

- [焊接基础教学视频](https://www.bilibili.com/video/BV1XW411F7NQ/) -- 20 分钟入门
- 认识电烙铁、焊锡丝、助焊剂
- Day 9 会在课堂上从零教学，但提前了解概念会有帮助

---

## 名词速查 | Quick Glossary

| 名词 Term | 英文 | 解释 Explanation |
|-----------|------|-----------------|
| **MCU** | Microcontroller Unit | 微控制器（单片机），一颗小小的"电脑芯片" |
| **ESP32-C3** | ESP32-C3 | 乐鑫出品的 RISC-V 架构 MCU，内置 WiFi + BLE 5.0，160MHz，4MB Flash |
| **RISC-V** | RISC-V | 一种开源指令集架构（ISA），ESP32-C3 使用的处理器架构 |
| **GPIO** | General Purpose I/O | 通用输入输出引脚，MCU 的"手和眼睛" |
| **SPI** | Serial Peripheral Interface | 一种四线制高速通信协议（SCLK、MOSI、MISO、CS），用于驱动显示屏 |
| **I2C** | Inter-Integrated Circuit | 一种两线制通信协议（SCL 时钟 + SDA 数据），用于连接传感器 |
| **SCL** | Serial Clock Line | I2C 时钟线，控制通信节奏 |
| **SDA** | Serial Data Line | I2C 数据线，传输实际信息 |
| **SCLK** | Serial Clock | SPI 时钟线 |
| **MOSI** | Master Out Slave In | SPI 主机输出线（数据从 MCU 发出到设备） |
| **MISO** | Master In Slave Out | SPI 主机输入线（数据从设备返回 MCU） |
| **CS / SS** | Chip Select / Slave Select | SPI 片选线，用于选择通信的设备 |
| **DC / RS** | Data/Command | SPI 数据/命令控制线，区分发送的是命令还是数据 |
| **TFT** | Thin Film Transistor | 薄膜晶体管液晶显示屏，每个像素有独立开关，色彩丰富 |
| **ST7735** | ST7735 | 控制 TFT 屏幕的驱动芯片型号，常见于 0.96 寸/1.44 寸彩色屏 |
| **SHT31-D** | SHT31-D | Sensirion 出品的高精度温湿度传感器，I2C 接口，温度 ±0.3°C |
| **NTP** | Network Time Protocol | 网络时间协议，从网络服务器获取精确时间 |
| **WiFi Station** | WiFi Station Mode | WiFi 站点模式，MCU 作为客户端连接到路由器 |
| **LiPo** | Lithium Polymer | 锂聚合物电池，轻量高能量密度的可充电电池 |
| **MPPT** | Maximum Power Point Tracking | 最大功率点跟踪，太阳能充电中优化能量转换的技术 |
| **PWM** | Pulse Width Modulation | 脉宽调制，用数字信号模拟模拟输出的技术 |
| **DC / RS** | Data/Command Register Select | TFT 显示中区分数据信号和命令信号的控制线 |
| **LED** | Light Emitting Diode | 发光二极管，用于指示灯 |
| **NTP Server** | NTP Server | NTP 时间服务器，如 `pool.ntp.org`，提供精确的网络时间 |
| **GMT / UTC** | Greenwich Mean Time / Coordinated Universal Time | 格林尼治标准时间 / 协调世界时，网络时间的基准 |
| **Deep Sleep** | Deep Sleep Mode | 深度睡眠模式，ESP32 的极低功耗运行模式 |
| **Watchdog Timer** | Watchdog Timer (WDT) | 看门狗定时器，检测并恢复系统死机的保护机制 |
| **GFX** | Graphics Library | Adafruit 提供的统一图形绘制库，支持文字/线条/矩形/圆形等 |
| **Flash** | Flash Memory | 闪存，ESP32-C3 内置 4MB，存储程序和文件系统 |
| **3D RAM** | Framebuffer | 显示缓存，存储屏幕上每个像素的颜色数据 |
