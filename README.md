# 桌面卫星气象站 "Desk Satellite" | Desktop Satellite Weather Station

> 面向高中生的暑期 IoT 进阶实践项目 | An Advanced Summer IoT Practicum Project for High School Students

---

## 开源声明 | Open Source Credits

本项目基于 **Huy Vector** 的开源 DIY 项目改编，用于教学目的。

> This project is adapted from **Huy Vector's** open-source DIY project for educational purposes.

| 资源 Resource | 链接 Link |
|-------------|---------|
| 原始视频 Original Video | [YouTube: A Desk Satellite You Can Actually Build!](https://www.youtube.com/watch?v=0zJG3wExY-c) |
| 原作者网站 Author Site | [huyvector.org/clocks/desk-satellite](https://www.huyvector.org/clocks/desk-satellite) |
| 材料与电路图 Materials & Diagram | [Google Sites: huy-materials-used/desk-satellite](https://sites.google.com/view/huy-materials-used/clocks/desk-satellite) |
| 源代码 Source Code | [Google Drive: Desk Satellite Code](https://drive.google.com/file/d/1SwpgMWkXY9MKINmAqNVY9-ZhVx53Qo-p/view?usp=sharing) |
| 电路图 Circuit Diagram | [Google Drive: Desk Satellite Diagram](https://drive.google.com/file/d/1ZVTx1QfvIgG53i-0iDBSIXXhRO96I1h1/view?usp=sharing) |
| 原作者频道 Author Channel | [YouTube: @HuyVector](https://www.youtube.com/@huyvector) |
| 音乐许可 Music License | "Meditation Impromptu 03" by Kevin MacLeod, [CC BY 3.0](http://creativecommons.org/licenses/by/3.0/) |

> 本项目视频背景音乐使用 Kevin MacLeod 的 "Meditation Impromptu 03"，基于 Creative Commons Attribution 3.0 许可。
> The background music uses Kevin MacLeod's "Meditation Impromptu 03" under Creative Commons Attribution 3.0.

---

## 项目概述 | Project Overview

本项目将带领学员从零开始构建一台**桌面迷你卫星气象站**，使用 ESP32-C3 微控制器驱动 0.96 寸 TFT 彩色显示屏，通过 WiFi 获取 NTP 网络时间，搭配 SHT31-D 传感器实时采集温度和湿度数据。设备由 3.7V 锂电池供电，支持 Type-C 充电和太阳能板充电，并配有 LED 指示灯。外壳使用铜线和黄铜管手工弯制，呈现独特的卫星造型。学员将掌握 ESP32 编程、TFT 显示驱动、I2C 传感器通信、WiFi 联网、NTP 时间同步、太阳能充电系统设计以及手工焊接与结构组装等核心技能。

> This project guides students to build a **desktop mini satellite weather station** from scratch. It uses an ESP32-C3 microcontroller to drive a 0.96-inch TFT color display, fetches NTP network time via WiFi, and pairs with an SHT31-D sensor for real-time temperature and humidity data. The device is powered by a 3.7V lithium battery with Type-C charging and solar panel support, featuring LED indicators. The enclosure is hand-crafted from copper wire and brass tubes for a unique satellite aesthetic. Students will master ESP32 programming, TFT display driving, I2C sensor communication, WiFi networking, NTP time sync, solar charging system design, and hands-on soldering & structural assembly.

---

## 最终效果 | Final Result

完成本项目后，你将拥有一台：

Upon completing this project, you will own a device that can:

- 通过 WiFi 自动同步 NTP 网络时间，精确到秒
- 实时显示温度和湿度数据（SHT31-D 高精度传感器）
- 在 0.96 寸 TFT 彩色显示屏上展示时钟、温度、湿度信息
- 支持 Type-C 有线充电（3.7V 锂电池）
- 支持太阳能板充电，实现绿色能源供电
- LED 指示灯显示工作状态
- 手工铜线 + 黄铜管卫星造型外壳，兼具科技感与装饰性
- 触摸开关控制开关机
- 电池电量显示模块
- Automatically sync network time via NTP with second precision
- Display real-time temperature and humidity (SHT31-D high-precision sensor)
- Show clock, temperature, and humidity on a 0.96-inch TFT color display
- Support Type-C wired charging (3.7V lithium battery)
- Support solar panel charging for green energy
- LED indicators showing operating status
- Hand-crafted copper wire + brass tube satellite-shaped enclosure, both tech-inspired and decorative
- Touch switch for power control
- Battery level indicator module

---

## 核心技术 | Core Technologies

| 技术 Technology | 用途 Purpose | 说明 Description |
|----------------|-------------|-----------------|
| ESP32-C3 | 主控制器 | RISC-V 32-bit MCU, 160MHz, WiFi + BLE 5 内置, 4MB Flash |
| ST7735 TFT Display | 显示 | 0.96 寸 80x160 像素, SPI 通信, 65K 彩色 |
| SHT31-D | 温湿度传感器 | I2C 通信, ±0.3°C 精度, ±2% RH 精度 |
| Adafruit GFX Library | 显示驱动 | 基础图形绘制库, 支持文字/线条/矩形等 |
| Adafruit ST7735 Library | TFT 驱动 | ST7735 芯片专用驱动库 |
| Adafruit SHT31 | 传感器驱动 | SHT31-D 传感器 I2C 通信驱动 |
| WiFi (ESP32) | 网络连接 | Station 模式连接路由器获取网络时间 |
| NTP 协议 | 时间同步 | 通过网络时间服务器获取精确时间 |
| Type-C 充电模块 | 电池充电 | 4.2V 锂电池充电管理, Type-C 接口 |
| 太阳能充电控制器 | 太阳能充电 | MPPT/PWM 太阳能充电管理 |
| 电池电量指示模块 | 电量显示 | LED 指示电池剩余电量 |

---

## 硬件清单 | Hardware List

### 电子元件 Electronic Components

| 部件 Component | 规格 Specification | 数量 | 参考价格 Price | 购买参考 Source |
|---------------|-------------------|------|--------------|----------------|
| ESP32-C3 开发板 | ESP32-C3, 4MB Flash, WiFi+BLE | 1 | 15-25 元 | 淘宝搜索"ESP32-C3" |
| ST7735 TFT 显示屏 | 0.96寸 80x160 SPI 彩色 | 1 | 10-15 元 | 淘宝搜索"0.96 TFT ST7735" |
| SHT31-D 温湿度传感器 | I2C, ±0.3°C, ±2%RH | 1 | 8-15 元 | 淘宝搜索"SHT31 温湿度" |
| 3.7V 锂电池 | 103040 或类似, 带保护板 | 1 | 10-15 元 | 淘宝搜索"3.7V 锂电池" |
| Type-C 充电模块 | 4.2V 锂电充电, TP4055/TP5100 | 1 | 3-5 元 | 淘宝搜索"Type-C 锂电充电模块" |
| 太阳能充电控制器 | 5V 输入, 锂电充电管理 | 1 | 5-10 元 | 淘宝搜索"太阳能充电控制器" |
| 迷你太阳能板 | 5V 0.5W-1W | 1-2 | 5-10 元 | 淘宝搜索"迷你太阳能板 5V" |
| 电池电量指示模块 | 4LED 电量指示 | 1 | 3-5 元 | 淘宝搜索"电池电量指示模块" |
| 触摸开关 | TTP223 触摸传感器模块 | 1 | 2-3 元 | 淘宝搜索"TTP223 触摸开关" |
| 拨动开关 | 微型滑动开关 | 1 | 1 元 | 淘宝搜索"微型拨动开关" |
| Type-C 母座 | USB Type-C 母座接口 | 1 | 1-2 元 | 淘宝搜索"Type-C 母座" |
| LED 指示灯 | 3mm 或 5mm, 多色 | 若干 | 1-2 元 | 淘宝搜索"LED 3mm" |

### 结构材料 Structural Materials

| 部件 Component | 规格 Specification | 数量 | 参考价格 Price | 购买参考 Source |
|---------------|-------------------|------|--------------|----------------|
| 铜线 Copper Wire | 1mm 直径 | 若干 | 5-10 元 | 淘宝/五金店 |
| 铜线 Copper Wire | 0.7mm/0.8mm 直径 | 若干 | 5-10 元 | 淘宝/五金店 |
| 黄铜管 Brass Tube | 3mm 外径 | 若干 | 5-10 元 | 淘宝搜索"黄铜管 3mm" |
| 竹杯垫/底座 Bamboo Coaster Base | 6cm 直径 | 1 | 3-5 元 | 淘宝搜索"竹杯垫" |

### 工具 Tools

| 工具 Tool | 用途 Purpose | 参考价格 Price |
|-----------|-------------|--------------|
| 电烙铁焊台 Soldering Iron Station | 焊接元件 | 50-100 元 |
| 焊锡丝 Solder Wire | 焊接耗材 | 10-20 元 |
| 助焊剂 Solder Flux | 提高焊接质量 | 5-10 元 |
| 烙铁架夹具 Iron Stand Clamp | 固定烙铁/元件 | 15-30 元 |
| 吸锡器 Desoldering Pump | 拆焊 | 10-15 元 |
| 迷你钳子/剪线钳 Mini Pliers Cutter | 剪线/弯线 | 10-20 元 |
| 切割垫 Cutting Pad | 保护桌面 | 10-15 元 |
| 圆规刀 Circle Cutter | 切割圆形底座 | 10-15 元 |

| **合计 Total** | | | **约 150-250 元（不含工具）** | **远低于 500 元预算** |

> 注：本项目难度较高，涉及较多焊接和结构组装工作。建议两人一组合作完成，一人负责电路焊接，一人负责结构组装。
> Note: This is a higher-difficulty project involving significant soldering and structural assembly. Teamwork in pairs is recommended: one for circuit soldering, one for structural assembly.

---

## 软件环境 | Software Environment

| 工具 Tool | 版本 Version | 用途 Purpose | 获取方式 |
|-----------|-------------|-------------|---------|
| Arduino IDE | 2.x | 代码编写与编译烧录 | arduino.cc 免费下载 |
| ESP32 开发板支持包 | 2.0+ | ESP32-C3 编译工具链 | Arduino IDE 开发板管理器 |
| Adafruit SHT31 库 | 最新版 | SHT31-D 传感器驱动 | Arduino IDE 库管理器 |
| Adafruit GFX Library | 最新版 | 基础图形绘制 | Arduino IDE 库管理器 |
| Adafruit ST7735 Library | 最新版 | ST7735 TFT 显示驱动 | Arduino IDE 库管理器 |
| USB 数据线 | Type-C | 程序烧录与供电 | 随开发板附带 |

---

## 快速开始 | Quick Start

### 硬件准备 Hardware Setup

1. 准备 ESP32-C3 开发板、ST7735 TFT 显示屏、SHT31-D 传感器等电子元件
2. 准备铜线（1mm 和 0.7mm）、黄铜管（3mm）、竹杯垫等结构材料
3. 按照 `hardware/wiring-guide.md` 接线（SPI 显示 + I2C 传感器 + 电源管理）
4. 按照 `hardware/assembly-steps.md` 组装卫星外壳结构

### 软件准备 Software Setup

1. 安装 Arduino IDE 2.x，添加 ESP32 开发板支持（选择 ESP32-C3）
2. 安装 Adafruit SHT31、Adafruit GFX、Adafruit ST7735 库
3. 在代码中填入你的 WiFi SSID 和密码
4. 设置时区偏移（例如东八区为 `8 * 3600`）
5. 编译并烧录代码到 ESP32-C3

### 第一次运行 First Run

1. 上电后 ESP32-C3 自动连接 WiFi
2. 连接成功后通过 NTP 同步网络时间
3. TFT 显示屏显示时钟界面（时间、日期）
4. SHT31-D 传感器开始采集温度和湿度数据
5. 太阳能板在光照条件下为电池充电
6. 触摸开关控制设备开关机

---

## 项目结构 | Project Structure

```
project-09-desk-satellite-high/
├── README.md                              # 本文件，项目总览
├── curriculum/                            # 课程文档
│   ├── overview.md                        # 课程大纲总览
│   ├── prerequisites.md                   # 前置知识与准备
│   ├── assignments.md                     # 作业说明
│   ├── grading-rubric.md                  # 详细评分标准
│   └── day-01.md ~ day-12.md              # 每日课程内容
├── hardware/                              # 硬件相关
│   ├── BOM.md                             # 物料清单
│   ├── wiring-guide.md                    # 接线指南
│   ├── assembly-steps.md                  # 组装步骤
│   └── troubleshooting.md                 # 硬件故障排除
├── software/                              # 软件代码
│   ├── requirements.txt                   # Arduino 库依赖列表
│   ├── config.template.h                  # 配置模板（WiFi、引脚等）
│   └── src/
│       └── desk_satellite.ino             # 主程序（参考源码）
├── assignments/                           # 作业与评分
│   ├── week-1-checkin.md                  # 第一周进度报告
│   ├── week-2-checkin.md                  # 第二周进度报告
│   ├── final-presentation.md              # 最终展示要求
│   └── rubric.md                          # 详细评分表
└── resources/
    └── search-results.md                  # 资源搜索结果
```

---

## 课程安排 | Course Schedule

12 天全日制课程，分为三个阶段：

12-day full-time course, divided into three phases:

### 第一阶段 Phase 1：嵌入式基础与开发环境 | Embedded Basics & Dev Environment (Day 1-4)

| 天数 Day | 主题 Topic | 核心内容 Key Content |
|----------|----------|---------------------|
| Day 1 | 项目启动与 ESP32-C3 入门 | ESP32-C3 架构、Arduino IDE 配置、第一个 Blink 程序、WiFi 扫描 |
| Day 2 | SPI 通信与 TFT 显示 | SPI 协议原理、ST7735 驱动、Adafruit GFX 库、彩色文字与图形 |
| Day 3 | I2C 传感器与数据采集 | I2C 协议原理、SHT31-D 驱动、温度湿度数据读取与校准 |
| Day 4 | WiFi 联网与 NTP 时间 | WiFi Station 模式、NTP 协议、网络时间获取与时区转换 |

### 第二阶段 Phase 2：核心功能开发与电源系统 | Core Features & Power System (Day 5-8)

| 天数 Day | 主题 Topic | 核心内容 Key Content |
|----------|----------|---------------------|
| Day 5 | 电源管理系统 | 锂电池充放电、Type-C 充电模块、太阳能充电控制器、电量指示 |
| Day 6 | 显示界面设计 | 多屏切换、动画效果、TFT 布局设计、状态栏与信息展示 |
| Day 7 | 交互功能开发 | 触摸开关控制、LED 指示灯控制、省电模式、低功耗设计 |
| Day 8 | 系统整合与调试 | 全功能整合、异常处理、看门狗定时器、稳定性测试 |

### 第三阶段 Phase 3：结构组装与展示 | Assembly & Presentation (Day 9-12)

| 天数 Day | 主题 Topic | 核心内容 Key Content |
|----------|----------|---------------------|
| Day 9 | 铜线结构与焊接基础 | 铜线弯制技巧、黄铜管连接、基础焊接技术、安全操作 |
| Day 10 | 卫星外壳组装 | 主体框架搭建、面板安装、线路整理、结构加固 |
| Day 11 | 整机组装与美化 | 电路集成入外壳、底座固定、最终调试与细节打磨 |
| Day 12 | 项目展示与总结 | 成果演示、Demo 网站部署、技术分享、项目复盘 |

---

## 评分标准 | Grading Rubric

| 维度 Dimension | 权重 Weight | 说明 Description |
|----------------|-----------|-----------------|
| 技术实现 Technical Implementation | 35% | 功能完整度、数据准确性、显示稳定性、电源管理可靠性 |
| 文档质量 Documentation | 9% | README、注释、接线图、原理说明 |
| 演示展示 Presentation | 17% | 最终展示的清晰度、深度与表达能力 |
| 进度汇报 Check-ins | 17% | 每周进度报告的质量与及时性 |
| 团队协作 Collaboration | 9% | Git 记录、分工合理性、互助精神 |
| Demo 网站 Project Demo Website | 13% | 项目展示网站的内容完整性、视觉呈现、技术深度 |

---

## 学习资源 | Learning Resources

### 原作者相关 | Original Creator Resources

1. **Huy Vector YouTube Channel** - 项目原作者频道
   - https://www.youtube.com/@huyvector
   - 大量铜线 DIY 电子项目，风格独特

2. **Huy Vector Facebook Group** - 社区讨论
   - https://www.facebook.com/groups/huyvectorlab

### 推荐 B 站视频 | Recommended Bilibili Videos

1. **ESP32-C3 入门教程** - 太极创客
   - 搜索 "ESP32-C3 Arduino 入门"

2. **TFT 彩屏显示教程**
   - 搜索 "ST7735 TFT Arduino 教程"

3. **I2C 通信协议详解**
   - 搜索 "I2C 协议 单片机"

4. **ESP32 低功耗设计**
   - 搜索 "ESP32 deep sleep 低功耗"

### GitHub 开源项目 | Open Source Projects

| 项目 Project | 说明 Description |
|-------------|-----------------|
| [Adafruit ST7735 Library](https://github.com/adafruit/Adafruit-ST7735-Library) | Adafruit 官方 ST7735 驱动库 |
| [Adafruit SHT31 Library](https://github.com/adafruit/Adafruit_SHT31) | Adafruit 官方 SHT31 传感器库 |
| [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library) | Adafruit 基础图形库 |

### 参考文档 | Reference Docs

- [ESP32-C3 技术参考手册](https://www.espressif.com/sites/default/files/documentation/esp32-c3_technical_reference_manual_en.pdf)
- [ESP32 Arduino Core 文档](https://docs.espressif.com/projects/arduino-esp32/en/latest/)
- [SHT31-D 数据手册](https://sensirion.com/media/documents/213E6A3B/63A5A569/Datasheet_SHT3x_DIS.pdf)
- [ST7735 数据手册](https://www.displayfuture.com/Display/datasheet/controller/ST7735.pdf)
- [Adafruit GFX 图形指南](https://learn.adafruit.com/adafruit-gfx-graphics-library)

---

## 与 Weather Cube 对比 | Comparison with Weather Cube

| 特性 Feature | Weather Cube (Easy) | Desk Satellite (High) |
|-------------|--------------------|-----------------------|
| 主控 MCU | ESP8266 (ESP-01S) | ESP32-C3 (RISC-V) |
| 显示屏 Display | OLED 128x64 (I2C) | TFT 80x160 彩色 (SPI) |
| 温湿度 Sensor | 无（网络 API 获取） | SHT31-D 本地传感器 |
| 天气数据 Weather | 和风天气 API | 无（本地传感器） |
| 电源 Power | USB 供电 | 锂电池 + Type-C + 太阳能 |
| 外壳 Enclosure | 无 / 3D 打印 | 铜线 + 黄铜管手工制作 |
| WiFi 配网 Provisioning | wifi_link_tool | 代码硬编码 SSID |
| 通信协议 Protocol | I2C (OLED) | SPI (TFT) + I2C (SHT31) |
| 难度 Difficulty | 入门 Easy | 进阶 High |
| 估计成本 Cost | ~45 元 | ~150-250 元 |

---

## 常见问题 | FAQ

**Q: 本项目和 Weather Cube 相比难度在哪里？**
A: Desk Satellite 在三个方面更难：(1) 电源管理涉及锂电池、太阳能充电和电量指示的完整供电系统；(2) 结构组装需要手工弯制铜线、焊接黄铜管，对动手能力要求高；(3) SPI 显示比 I2C OLED 接线更复杂。建议先完成 Weather Cube 再挑战本项目。

> What makes this harder than the Weather Cube? (1) Power management with lithium battery, solar charging, and battery indicator; (2) Structural assembly requiring hand-bending copper wire and soldering brass tubes; (3) SPI display wiring is more complex than I2C OLED. Recommend completing Weather Cube first.

**Q: ESP32-C3 和 ESP8266 有什么区别？**
A: ESP32-C3 使用 RISC-V 架构（vs ESP8266 的 Xtensa），性能更强（160MHz vs 80MHz），内置蓝牙 5.0，Flash 更大（4MB vs 2MB），且功耗更低。引脚数量也更多，方便扩展。

> ESP32-C3 uses RISC-V (vs ESP8266's Xtensa), is faster (160MHz vs 80MHz), has built-in BLE 5.0, larger Flash (4MB vs 2MB), lower power consumption, and more GPIO pins.

**Q: 太阳能板是必须的吗？**
A: 不是必须的。太阳能板是可选的扩展功能，设备可以通过 Type-C 充电正常使用。但如果想实现真正的"卫星"体验——利用太阳能持续供电——建议配备。5V 0.5W 的迷你太阳能板即可。

> The solar panel is optional. The device works fine with Type-C charging alone. But for the true "satellite" experience of solar-powered operation, it's recommended. A 5V 0.5W mini solar panel is sufficient.

**Q: 没有铜线弯制经验怎么办？**
A: Day 9 会从基础铜线弯制技巧开始教起。建议先用废旧铜线练习弯制简单形状（圆形、三角形），掌握力度和角度后再开始正式组装。使用圆棒或圆管作为弯制模具效果更好。

> Day 9 starts with basic copper wire bending techniques. Practice with scrap wire first (circles, triangles) before starting the actual assembly. Using round rods or tubes as bending jigs helps.

**Q: 可以用其他显示屏替代 ST7735 TFT 吗？**
A: 可以，但需要修改代码中的驱动库。常见替代方案：(1) SSD1306 OLED（0.96寸 I2C）—— 最简单，但只有黑白两色；(2) ST7789 TFT（1.3寸/1.54寸）—— 同系列但尺寸更大。Adafruit 提供了统一的 GFX 接口，切换相对容易。

> Yes, but the display driver code needs modification. Alternatives: (1) SSD1306 OLED (0.96" I2C) -- easiest, monochrome only; (2) ST7789 TFT (1.3"/1.54") -- same family, larger. Adafruit's unified GFX interface makes switching relatively easy.

**Q: SHT31-D 和 DHT11 有什么区别？为什么选 SHT31-D？**
A: SHT31-D 精度远高于 DHT11（温度 ±0.3°C vs ±2°C，湿度 ±2% vs ±5%），且使用 I2C 总线（数字输出），不受信号线长度影响。价格虽然贵几元，但在桌面设备的精确度要求下非常值得。如果预算紧张，可以降级使用 DHT22（±0.5°C）。

> SHT31-D is far more accurate than DHT11 (±0.3°C vs ±2°C temp, ±2% vs ±5% humidity), uses I2C (digital), and isn't affected by wire length. A few CNY more but worth it for a desk device. For budget, DHT22 (±0.5°C) is a good middle ground.

---

## 许可证 | License

本项目课程文档采用 [CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/) 协议发布。

原始项目由 Huy Vector 创建，代码基于原作者提供的 Google Drive 链接分发。

> This project course materials are released under CC BY-NC-SA 4.0.
> The original project was created by Huy Vector; code is distributed via the author's Google Drive link.

---

*最后更新：2026-05-27*
*Last updated: 2026-05-27*
