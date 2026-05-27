# 接线指南 | Wiring Guide

> 本文档提供 Desk Satellite 的完整接线说明，包括 ESP32-C3 引脚分配、SPI/I2C 总线连接和电源系统接线。
> This document provides complete wiring instructions for the Desk Satellite, including ESP32-C3 pin assignments, SPI/I2C bus connections, and power system wiring.

---

## 概述 | Overview

Desk Satellite 使用两种通信协议连接外部设备：

- **SPI 总线**：连接 ST7735 TFT 彩色显示屏（高速数据传输）
- **I2C 总线**：连接 SHT31-D 温湿度传感器（低速精简接线）

此外还有电源管理系统（Type-C 充电 + 太阳能充电 + 电池电量指示）和控制电路（触摸开关 + 拨动开关）。

> The Desk Satellite uses two communication protocols:
> - **SPI bus**: ST7735 TFT color display (high-speed data transfer)
> - **I2C bus**: SHT31-D temperature/humidity sensor (low-speed, minimal wiring)
> Plus power management (Type-C charging + solar + battery indicator) and control circuits (touch switch + toggle switch).

---

## ESP32-C3 引脚分配 | ESP32-C3 Pin Assignment

### 完整引脚分配表 | Complete Pin Assignment Table

| ESP32-C3 GPIO | 功能 Function | 连接目标 Target | 方向 Direction | 备注 Notes |
|---------------|-------------|---------------|-------------|----------|
| GPIO 0 | I2C SCL | SHT31-D SCL 引脚 | 输出 Output | I2C 时钟线 |
| GPIO 1 | 数字输入 | TTP223 触摸开关 OUT | 输入 Input | 高电平触发 / HIGH trigger |
| GPIO 2 | I2C SDA | SHT31-D SDA 引脚 | 双向 Bi-directional | I2C 数据线 |
| GPIO 8 | SPI SCLK | ST7735 TFT SCLK (CLK) | 输出 Output | SPI 时钟线 |
| GPIO 9 | SPI MOSI | ST7735 TFT SDA (MOSI) | 输出 Output | SPI 数据线 |
| GPIO 10 | 数字输出 | ST7735 TFT RST (RES) | 输出 Output | 显示屏复位 |
| GPIO 20 | SPI DC | ST7735 TFT DC (A0/RS) | 输出 Output | 数据/命令选择 |
| GPIO 21 | SPI CS | ST7735 TFT CS | 输出 Output | 片选（低有效） |
| 3V3 | 电源输出 | 传感器/显示屏 VCC | 输出 Output | 3.3V 稳压输出 |
| 5V (VBUS) | 电源输出 | 充电模块/电量指示 | 输出 Output | USB 供电时 5V |
| GND | 地线 | 所有设备公共地 | — | 最重要！务必共地 |

---

## SPI 总线接线（TFT 显示屏）| SPI Bus Wiring (TFT Display)

### 引脚连接表 | Pin Connection Table

| TFT 显示屏引脚 TFT Pin | ESP32-C3 GPIO | 线色建议 Wire Color | 说明 Description |
|----------------------|---------------|-------------------|-----------------|
| VCC | 3V3 或 5V | 红色 Red | 供电（查看模块标注，通常 3.3V-5V） |
| GND | GND | 黑色 Black | 公共地 |
| SCLK (CLK/SCK) | GPIO 8 | 橙色 Orange | SPI 时钟 |
| SDA (MOSI/DIN) | GPIO 9 | 黄色 Yellow | SPI 数据 |
| CS (Chip Select) | GPIO 21 | 绿色 Green | 片选信号 |
| DC (A0/RS) | GPIO 20 | 蓝色 Blue | 数据/命令选择 |
| RST (RES) | GPIO 10 | 紫色 Purple | 复位信号 |
| BL (Backlight) | 3V3 或悬空 | 白色 White | 背光（可直接接 3V3 常亮） |

> 注：不同厂家的 TFT 模块引脚命名可能不同。SCLK=CLK=SCK, SDA=MOSI=DIN, DC=A0=RS。
> Note: TFT module pin naming varies by manufacturer. SCLK=CLK=SCK, SDA=MOSI=DIN, DC=A0=RS.

### SPI 接线图 | SPI Wiring Diagram

```
  ESP32-C3                    ST7735 TFT (0.96")
  ┌─────────┐                ┌──────────────────┐
  │      3V3├────────────────┤VCC               │
  │      GND├────────────────┤GND               │
  │   GPIO 8├────────────────┤SCLK (CLK)        │
  │   GPIO 9├────────────────┤SDA  (MOSI/DIN)   │
  │  GPIO 21├────────────────┤CS                │
  │  GPIO 20├────────────────┤DC   (A0/RS)      │
  │  GPIO 10├────────────────┤RST  (RES)        │
  │      3V3├────────────────┤BL   (Backlight)  │
  └─────────┘                └──────────────────┘
```

---

## I2C 总线接线（SHT31-D 传感器）| I2C Bus Wiring (SHT31-D Sensor)

### 引脚连接表 | Pin Connection Table

| SHT31-D 引脚 Sensor Pin | ESP32-C3 GPIO | 线色建议 Wire Color | 说明 Description |
|-------------------------|---------------|-------------------|-----------------|
| VCC (VIN) | 3V3 | 红色 Red | 供电 3.3V |
| GND | GND | 黑色 Black | 公共地 |
| SDA | GPIO 2 | 黄色 Yellow | I2C 数据线 |
| SCL | GPIO 0 | 橙色 Orange | I2C 时钟线 |
| ADDR | 悬空或接 GND | — | 地址选择：悬空/GND = 0x44 |

> 注：SHT31-D 的 ADDR 引脚决定 I2C 地址。接 GND 或悬空 = 0x44，接 VDD = 0x45。本项目使用 0x44。
> Note: SHT31-D ADDR pin determines I2C address. GND/floating = 0x44, VDD = 0x45. This project uses 0x44.

### I2C 接线图 | I2C Wiring Diagram

```
  ESP32-C3                    SHT31-D Sensor
  ┌─────────┐                ┌──────────────┐
  │      3V3├────────────────┤VCC (VIN)     │
  │      GND├────────────────┤GND           │
  │   GPIO 2├────────────────┤SDA           │
  │   GPIO 0├────────────────┤SCL           │
  └─────────┘                │ADDR (悬空)    │
                             └──────────────┘
```

---

## 电源系统接线 | Power System Wiring

### 电源架构图 | Power Architecture

```
                         ┌──────────────┐
                         │  太阳能板     │
                         │  Solar Panel │
                         │  (5V 0.5W)   │
                         └──────┬───────┘
                                │
                         ┌──────▼───────┐
                         │ 太阳能充电     │
                         │ 控制器         │
                         │ Solar Charge  │
                         │ Controller    │
                         └──────┬───────┘
                                │
  ┌──────────────┐       ┌──────▼───────┐
  │ Type-C 充电   │       │              │
  │ 模块 (4.2V)   ├──┬────┤  3.7V 锂电池  │
  │ TP5100/TP4055 │  │    │  LiPo Battery│
  └───────┬──────┘  │    └──────┬───────┘
          │         │           │
    Type-C 接口     │           │
    (外部供电)      │           │
                    │    ┌──────▼───────┐
                    │    │ 电池电量指示   │
                    │    │ 模块          │
                    │    │ Battery Level │
                    │    └──────────────┘
                    │
              ┌─────▼─────┐
              │ ESP32-C3   │
              │ (3.3V 工作) │
              │ 通过板载    │
              │ 稳压器供电  │
              └────────────┘
```

### 电源接线说明 | Power Wiring Details

1. **电池**：3.7V 锂电池正极接 Type-C 充电模块 BAT+，负极接 BAT-
2. **Type-C 充电**：充电模块的 IN+/IN- 连接 Type-C 母座的 VBUS/GND
3. **太阳能充电**：太阳能板正极接太阳能充电控制器 VIN+，负极接 VIN-，控制器的 BAT+/BAT- 并联到电池
4. **电池电量指示**：电量指示模块的 BAT+/BAT- 并联到电池正负极
5. **ESP32-C3 供电**：ESP32-C3 的 5V/VIN 引脚接电池正极（通过拨动开关），GND 接电池负极

> 重要：电池接线时注意正负极！反接可能损坏元件。建议先用万用表确认电压。
> Important: Watch battery polarity! Reverse connection can damage components. Use a multimeter to verify voltage first.

---

## 控制电路接线 | Control Circuit Wiring

### 触摸开关 | Touch Switch (TTP223)

```
  ESP32-C3                    TTP223 触摸模块
  ┌─────────┐                ┌──────────────┐
  │      3V3├────────────────┤VCC           │
  │      GND├────────────────┤GND           │
  │   GPIO 1├────────────────┤SIG (OUT)     │
  └─────────┘                └──────────────┘
```

- TTP223 默认模式：触摸时输出高电平 (HIGH)
- 触摸后进入深度睡眠，再次触摸唤醒
- 深度睡眠唤醒配置：`ESP_GPIO_WAKEUP_GPIO_HIGH`

### 拨动开关（电源总开关）| Toggle Switch (Main Power)

```
  电池正极 (BAT+) ──┤ 拨动开关 ├── ESP32-C3 VIN/5V
```

- 拨动开关串联在电池正极和 ESP32-C3 之间
- 作为设备总电源开关

---

## 完整接线图 | Complete Wiring Diagram

```
                           太阳能板
                             │
                       太阳能充电控制器
                             │
  Type-C ──充电模块──┬──── 3.7V 锂电池 ────电量指示模块
                     │         │
                     │    ┌────┤ 拨动开关
                     │    │    │
                     │    │  ┌─▼──────────┐
                     │    │  │  ESP32-C3   │
                     │    │  │             │
                     │    │  │ GPIO 0 ─────┤──── SHT31 SCL
                     │    │  │ GPIO 1 ─────┤──── TTP223 OUT
                     │    │  │ GPIO 2 ─────┤──── SHT31 SDA
                     │    │  │ GPIO 8 ─────┤──── TFT SCLK
                     │    │  │ GPIO 9 ─────┤──── TFT MOSI
                     │    │  │ GPIO 10 ────┤──── TFT RST
                     │    │  │ GPIO 20 ────┤──── TFT DC
                     │    │  │ GPIO 21 ────┤──── TFT CS
                     │    │  │ 3V3 ────────┤──── SHT31 VCC
                     │    │  │             │     TFT VCC+BL
                     │    │  │ GND ────────┤──── 所有 GND
                     │    │  └─────────────┘
                     │    │
                     └────┘
```

---

## 接线检查清单 | Wiring Checklist

使用以下清单逐项检查接线是否正确：

### 电源部分 Power
- [ ] 电池正极连接正确（通过拨动开关到 ESP32-C3 VIN/5V）
- [ ] 电池负极连接到所有设备公共 GND
- [ ] Type-C 充电模块正确连接电池和 Type-C 接口
- [ ] 太阳能充电控制器正确并联到电池
- [ ] 电量指示模块并联到电池正负极
- [ ] 用万用表测量：电池电压应在 3.0V-4.2V 之间

### SPI 显示屏 TFT Display
- [ ] TFT VCC 连接到 3V3
- [ ] TFT GND 连接到 GND
- [ ] TFT SCLK 连接到 GPIO 8
- [ ] TFT MOSI (SDA/DIN) 连接到 GPIO 9
- [ ] TFT CS 连接到 GPIO 21
- [ ] TFT DC (A0/RS) 连接到 GPIO 20
- [ ] TFT RST (RES) 连接到 GPIO 10
- [ ] TFT BL 连接到 3V3（或悬空）

### I2C 传感器 Sensor
- [ ] SHT31 VCC 连接到 3V3
- [ ] SHT31 GND 连接到 GND
- [ ] SHT31 SDA 连接到 GPIO 2
- [ ] SHT31 SCL 连接到 GPIO 0
- [ ] SHT31 ADDR 引脚悬空或接 GND（地址 = 0x44）

### 触摸开关 Touch Switch
- [ ] TTP223 VCC 连接到 3V3
- [ ] TTP223 GND 连接到 GND
- [ ] TTP223 OUT 连接到 GPIO 1

---

## 快速测试步骤 | Quick Test Steps

1. **不上电检查**：用万用表蜂鸣档检查所有连线是否导通
2. **电源测试**：拨动开关打开，测量 ESP32-C3 的 3V3 引脚电压应为 3.3V
3. **TFT 测试**：上传 Blink 程序确认 ESP32-C3 工作正常，然后上传 TFT 测试程序
4. **传感器测试**：上传 I2C Scanner 程序，确认能检测到 0x44 地址
5. **触摸开关测试**：上传数字输入测试程序，触摸时 GPIO 1 应读到 HIGH
6. **完整程序测试**：上传 desk_satellite.ino，检查所有功能

---

*最后更新：2026-05-27*
*Last updated: 2026-05-27*
