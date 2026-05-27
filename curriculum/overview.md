# 课程大纲总览 | Curriculum Overview

## 课程定位 | Course Positioning

本课程是面向高中生的**嵌入式 IoT 进阶实践课程**。学员将在 12 天内从零开始构建一台桌面迷你卫星气象站（Desk Satellite），使用 ESP32-C3 微控制器驱动彩色 TFT 显示屏，搭配高精度温湿度传感器，通过 WiFi 同步网络时间，并使用铜线手工打造独特的卫星造型外壳。本项目难度为**高**，涉及 SPI 显示驱动、I2C 传感器通信、锂电池电源管理、太阳能充电以及大量焊接与结构组装工作。

> This is an **advanced embedded IoT practicum course** for high school students. In 12 days, students will build a desktop mini satellite weather station (Desk Satellite) from scratch, using an ESP32-C3 microcontroller to drive a color TFT display, paired with a high-precision temperature/humidity sensor, syncing network time via WiFi, and hand-crafting a unique satellite-shaped enclosure from copper wire. This project is rated **High** difficulty, involving SPI display driving, I2C sensor communication, lithium battery power management, solar charging, and extensive soldering and structural assembly.

**前置建议**：建议学员在挑战本项目前先完成 Weather Cube（入门级）或具备同等经验。

> **Prerequisite recommendation**: Students are advised to complete the Weather Cube (Easy level) or have equivalent experience before attempting this project.

---

## 学习目标 | Learning Objectives

### 知识目标 Knowledge Goals

- 理解 ESP32-C3 RISC-V 微控制器的架构和 Arduino 编程模型
- 掌握 SPI 总线通信协议的原理与 ST7735 TFT 显示驱动
- 掌握 I2C 总线通信协议的原理与 SHT31-D 传感器数据采集
- 理解 WiFi Station 模式联网和 NTP 网络时间同步机制
- 理解锂电池充放电原理和太阳能充电系统设计
- 了解嵌入式系统的低功耗设计策略（深睡眠模式）

### 技能目标 Skill Goals

- 能够使用 Arduino IDE 编写、编译、烧录 ESP32-C3 程序
- 能够使用 Adafruit GFX + ST7735 库驱动彩色 TFT 显示屏
- 能够设计多屏切换 UI 界面，包含时钟、温度、湿度和状态信息
- 能够集成电源管理系统（锂电池 + Type-C 充电 + 太阳能）
- 能够进行铜线弯制和精密焊接，完成卫星外壳结构组装
- 能够进行系统级调试与稳定性测试

### 素养目标 Quality Goals

- 培养工程思维：需求分析 → 方案设计 → 实现 → 测试 → 迭代
- 培养动手能力：焊接、弯线、组装等精密手工操作
- 培养调试能力：使用串口输出、看门狗定时器定位问题
- 培养文档习惯：记录开发过程、接线图和调试日志
- 培养团队协作能力：两人一组分工合作完成复杂项目

---

## 项目灵感来源 | Project Inspiration

本项目基于 **Huy Vector** 的开源 DIY 桌面卫星项目改编，用于教学目的。Huy Vector 是一位擅长使用铜线和黄铜管制作精美电子设备的创客，其 YouTube 频道有大量独特的 DIY 作品。

> This project is adapted from **Huy Vector's** open-source DIY desk satellite project for educational purposes. Huy Vector is a maker skilled in crafting beautiful electronic devices using copper wire and brass tubes, with many unique DIY projects on his YouTube channel.

| 资源 Resource | 链接 Link |
|-------------|---------|
| 原始视频 Original Video | [YouTube: A Desk Satellite You Can Actually Build!](https://www.youtube.com/watch?v=0zJG3wExY-c) |
| 材料与电路图 Materials & Diagram | [Google Sites](https://sites.google.com/view/huy-materials-used/clocks/desk-satellite) |
| 源代码 Source Code | [Google Drive](https://drive.google.com/file/d/1SwpgMWkXY9MKINmAqNVY9-ZhVx53Qo-p/view?usp=sharing) |

---

## 每日课程速览 | Daily Course At-a-Glance

### 第一阶段 Phase 1：嵌入式基础与开发环境 | Embedded Basics & Dev Environment (Day 1-4)

| 天数 Day | 主题 Topic | 上午 (3h) Morning | 下午 (4h) Afternoon |
|----------|----------|----------|----------|
| Day 1 | ESP32-C3 入门 ESP32-C3 Basics | 项目介绍 + 硬件认知 | Arduino IDE 配置 + Blink + WiFi 扫描 |
| Day 2 | SPI 与 TFT 显示 SPI & TFT Display | SPI 协议原理 + 接线 | ST7735 驱动 + 文字/图形/色彩 |
| Day 3 | I2C 与温湿度传感器 I2C & SHT31 Sensor | I2C 协议原理 + 接线 | SHT31-D 驱动 + 数据读取与校准 |
| Day 4 | WiFi 与 NTP 时间 WiFi & NTP Time | WiFi Station 模式 | NTP 同步 + 时区配置 + 网络调试 |

### 第二阶段 Phase 2：核心功能开发与电源系统 | Core Features & Power System (Day 5-8)

| 天数 Day | 主题 Topic | 上午 (3h) Morning | 下午 (4h) Afternoon |
|----------|----------|----------|----------|
| Day 5 | 电源管理系统 Power Management | 锂电池 + 充电模块原理 | 太阳能充电 + 电量指示实战 |
| Day 6 | 显示界面设计 Display UI Design | 多屏 UI 设计 + 时钟界面 | 天气数据展示 + 动画效果 |
| Day 7 | 交互与低功耗 Interaction & Low Power | 触摸开关 + LED 控制 | 深睡眠模式 + 中断处理 |
| Day 8 | 系统整合与调试 System Integration | 全功能整合 + 异常处理 | 看门狗 + 稳定性测试 + 代码优化 |

### 第三阶段 Phase 3：结构组装与展示 | Assembly & Presentation (Day 9-12)

| 天数 Day | 主题 Topic | 上午 (3h) Morning | 下午 (4h) Afternoon |
|----------|----------|----------|----------|
| Day 9 | 铜线结构与焊接基础 Copper Wire & Soldering | 铜线弯制 + 黄铜管切割 | 基础焊接练习 + 安全操作 |
| Day 10 | 卫星外壳组装 Satellite Enclosure | 主体框架搭建 | 面板安装 + 线路整理 + 加固 |
| Day 11 | 整机组装与美化 Final Assembly | 电路集成入外壳 + 底座固定 | 最终调试 + 细节打磨 |
| Day 12 | 项目展示与总结 Presentation & Wrap-up | 演示准备 + Demo 网站部署 | 成果展示 + 技术分享 + 复盘 |

---

## 考核方式 | Assessment

| 考核项 Assessment Item | 占比 Weight | 截止日期 Due Date |
|------------------------|-----------|-----------------|
| 第一周进度汇报 Week 1 Check-in | 17% | Day 6 结束前 |
| 第二周进度汇报 Week 2 Check-in | 17%（含最终进度） | Day 11 结束前 |
| 最终演示 Final Demo | 17% | Day 12 |
| 技术实现 Technical Implementation | 35% | Day 12 |
| 文档质量 Documentation | 9% | Day 12 |
| Demo 网站 Project Website | 13% | Day 12 |
| 团队协作 Collaboration | 9% | 全过程 Ongoing |

> 注：独立完成项目的学员，"团队协作"分数将转换为"自主学习"分数，考察独立解决问题的能力。
> Note: For students working independently, the "Collaboration" score converts to "Self-directed Learning", assessing independent problem-solving ability.

---

## 课程特色 | Course Highlights

- **双协议通信**：同时学习 SPI（显示屏）和 I2C（传感器）两种主流通信协议
- **电源系统设计**：涵盖锂电池、Type-C 充电、太阳能充电的完整供电方案
- **手工结构制作**：使用铜线和黄铜管手工打造卫星外壳，培养精密手工能力
- **真实开源项目**：基于 Huy Vector 的真实 DIY 项目，有视频参考和社区支持
- **系统级整合**：从硬件到软件到结构的完整工程实践
