# 第一周进度报告 | Week 1 Progress Report

## 概述 | Overview

第一周进度报告用于评估学员在 Day 1-5 的学习成果。学员需要展示开发环境搭建完成、ESP32-C3 基础编程掌握、SPI 显示驱动正常、I2C 传感器数据读取成功、WiFi/NTP 网络时间同步可用，以及电源管理电路基本搭建完毕。报告须在 Day 5 结束前提交，字数 800-1200 中文字符。

> The Week 1 progress report evaluates learning outcomes from Day 1-5. Students must demonstrate a working development environment, ESP32-C3 basic programming mastery, SPI display driving, I2C sensor data reading, WiFi/NTP time sync functionality, and basic power management circuit assembly. Due by end of Day 5. Word count: 800-1200 Chinese characters.

---

## 截止日期 | Due Date

**Day 5 下课前 | Before class ends on Day 5**

---

## 学生/团队信息 | Student / Team Information

| 字段 Field | 内容 Content |
|-----------|-------------|
| **团队名称 / Team Name** | |
| **成员姓名 / Members** | |
| **项目仓库链接 / Repo URL** | |
| **报告日期 / Report Date** | |
| **指导教师 / Instructor** | |

---

## 一、已完成功能清单 | Completed Features Checklist

请填写下表，记录 Day 1-5 期间各项功能的完成状态。

> Fill in the table below to record the completion status of each feature during Day 1-5.

| 功能 Feature | 状态 Status | 备注 Notes |
|-------------|------------|-----------|
| Arduino IDE 安装与 ESP32-C3 开发板支持 | 未开始 / 进行中 / 已完成 | |
| ESP32-C3 Blink 程序烧录与运行 | 未开始 / 进行中 / 已完成 | |
| WiFi 扫描功能测试（Station 模式） | 未开始 / 进行中 / 已完成 | |
| SPI 通信理解与 ST7735 TFT 接线 | 未开始 / 进行中 / 已完成 | |
| ST7735 TFT 显示文字与图形 | 未开始 / 进行中 / 已完成 | |
| I2C Scanner 扫描到 SHT31-D（地址 0x44） | 未开始 / 进行中 / 已完成 | |
| SHT31-D 温度数据读取 | 未开始 / 进行中 / 已完成 | |
| SHT31-D 湿度数据读取 | 未开始 / 进行中 / 已完成 | |
| WiFi 连接到路由器（硬编码 SSID） | 未开始 / 进行中 / 已完成 | |
| NTP 网络时间同步成功 | 未开始 / 进行中 / 已完成 | |
| TFT 显示实时时钟界面 | 未开始 / 进行中 / 已完成 | |
| Type-C 充电模块接线与测试 | 未开始 / 进行中 / 已完成 | |
| 太阳能充电控制器接线（如有） | 未开始 / 进行中 / 已完成 | |
| 电池电量指示模块测试（如有） | 未开始 / 进行中 / 已完成 | |
| 触摸开关（TTP223）功能测试 | 未开始 / 进行中 / 已完成 | |

> Status options: Not Started / In Progress / Completed. Notes should include specific values, error messages, or observations.

---

## 二、遇到的问题 | Problems Encountered

请详细描述在第一周遇到的技术问题，包括问题描述、尝试的解决方案和当前状态。至少记录 2 个问题。

> Describe in detail the technical problems encountered during Week 1, including the problem description, attempted solutions, and current status. Record at least 2 problems.

### 问题 1 | Problem 1

**问题描述 / Problem Description:**

（在此描述你遇到的问题。例如：ST7735 TFT 屏幕只显示白屏，没有任何内容输出。）

> Describe your problem here. For example: The ST7735 TFT screen only shows a white screen with no content.

**尝试的解决方案 / Attempted Solutions:**

（你做了什么来解决这个问题？例如：检查接线、更换引脚、调整 SPI 时钟频率。）

> What did you do to try to solve it? For example: Checked wiring, changed pins, adjusted SPI clock frequency.

**当前状态 / Current Status:** 已解决 / 部分解决 / 未解决

> Current Status: Resolved / Partially Resolved / Unresolved

---

### 问题 2 | Problem 2

**问题描述 / Problem Description:**

**尝试的解决方案 / Attempted Solutions:**

**当前状态 / Current Status:** 已解决 / 部分解决 / 未解决

---

### 问题 3 | Problem 3（如有）

**问题描述 / Problem Description:**

**尝试的解决方案 / Attempted Solutions:**

**当前状态 / Current Status:** 已解决 / 部分解决 / 未解决

---

## 三、第二周计划 | Week 2 Plan

请列出 Day 6-10 的具体学习计划，包括预期完成的功能和目标。

> List your specific study plan for Day 6-10, including expected features and goals.

| 天数 Day | 计划内容 Planned Work | 预期目标 Expected Goal |
|----------|---------------------|----------------------|
| Day 6 | 电源管理系统完善 | Type-C 充电 + 太阳能充电 + 电量指示全部可用 |
| Day 7 | 显示界面设计与多屏切换 | 时钟/温湿度/状态多屏切换，动画效果 |
| Day 8 | 交互功能与系统整合 | 触摸开关控制、LED 指示、全功能整合调试 |
| Day 9 | 铜线结构与焊接基础 | 铜线弯制练习、黄铜管连接、基础焊接 |
| Day 10 | 卫星外壳组装 | 主体框架搭建、面板安装、线路整理 |

---

## 四、个人反思 | Personal Reflection

请写一段 300-500 字的反思，涵盖以下内容：

> Write a 300-500 word reflection covering the following:

1. **学习感受 / Learning Experience：** 第一周的学习中，你觉得最有趣和最困难的部分分别是什么？
   > What was the most interesting and most difficult part of Week 1?

2. **知识收获 / Knowledge Gained：** 你学到了哪些新知识或新技能？对 SPI、I2C、WiFi 等通信协议的理解有什么变化？
   > What new knowledge or skills did you gain? How has your understanding of SPI, I2C, WiFi protocols changed?

3. **团队协作 / Teamwork：** 你和搭档是如何分工合作的？分工是否合理？有什么需要改进的地方？
   > How did you and your partner divide the work? Was the division reasonable? What needs improvement?

4. **自我评价 / Self-Evaluation：** 你对自己第一周的表现满意吗？如果重新开始，你会做哪些改变？
   > Are you satisfied with your Week 1 performance? If you could start over, what would you change?

---

**反思内容 / Reflection Content:**

（在此撰写你的反思，300-500 字）

---

## 五、代码提交状态 | Code Submission Status

- [ ] 所有代码已推送到团队 Git 仓库
- [ ] Commit 信息清晰规范（如 `feat: add SHT31 temperature reading`）
- [ ] 至少 5 个有意义的 commit（Day 1-5 每天至少 1 个）
- [ ] 仓库包含 README.md 文件

> All code pushed to team repo; clear commit messages; at least 5 meaningful commits; repo contains README.md.

**仓库链接 / Repo URL:** _______________________

**Git 提交记录（最近 5 次以上）/ Recent Git Commits (5+):**

| 序号 | Commit Message | 日期 |
|------|---------------|------|
| 1 | | |
| 2 | | |
| 3 | | |
| 4 | | |
| 5 | | |

---

## 六、自我评估 | Self-Assessment

请对以下维度进行 1-5 分评分（1 = 需要大量帮助，5 = 完全独立完成）。

> Rate each dimension 1-5 (1 = need significant help, 5 = completed independently).

| 维度 Dimension | 评分 Score (1-5) | 备注 Notes |
|---------------|-----------------|-----------|
| **开发环境搭建** | | |
| Development Environment Setup | | |
| **ESP32-C3 基础编程** | | |
| ESP32-C3 Basic Programming | | |
| **SPI/TFT 显示驱动** | | |
| SPI/TFT Display Driving | | |
| **I2C/传感器数据读取** | | |
| I2C/Sensor Data Reading | | |
| **WiFi/NTP 网络时间** | | |
| WiFi/NTP Network Time | | |
| **电源管理电路搭建** | | |
| Power Management Circuit | | |
| **代码质量与注释** | | |
| Code Quality & Comments | | |
| **Git 使用规范** | | |
| Git Usage Standards | | |
| **团队协作** | | |
| Team Collaboration | | |

---

## 七、提交证据 | Submission Evidence

### 必须提交的材料 | Required Submissions

- [ ] ST7735 TFT 显示屏工作照片（显示时钟或文字）
- [ ] SHT31-D 串口输出截图（温度和湿度数值）
- [ ] NTP 时间同步成功截图
- [ ] 电源管理电路接线照片（如有）
- [ ] 第一周进度报告（本文件）

> Required: ST7735 TFT display working photo, SHT31-D serial output screenshot, NTP sync success screenshot, power management circuit photo (if applicable), and this progress report.

---

## 评分标准 | Grading Criteria

| 项目 Item | 权重 Weight | 评分标准 Standard |
|----------|-----------|------------------|
| **完成度 Completeness** | 40% | 功能清单中至少完成 60% 的项目为及格，80% 以上为良好，90% 以上为优秀。每项功能需有证据支持（照片、截图或代码）。 |
| **问题分析 Problem Analysis** | 30% | 问题描述清晰具体，包含错误现象和上下文；解决方案有逻辑性，体现了调试思路；至少记录 2 个有意义的技术问题。 |
| **计划质量 Plan Quality** | 20% | 第二周计划具体可行，与课程进度匹配；每项任务有明确的预期目标；计划体现了对项目整体进度的把握。 |
| **个人反思 Reflection** | 10% | 反思内容真诚有深度，不是简单的流水账；涵盖学习感受、知识收获、团队协作和自我评价四个方面。 |

> Completeness: 60% features = pass, 80% = good, 90% = excellent, each with evidence. Problem Analysis: clear descriptions with debugging logic, at least 2 problems. Plan Quality: specific, feasible, aligned with course schedule. Reflection: sincere and in-depth, covering all four aspects.

---

## 常见问题 | FAQ

### Q1: Arduino IDE 找不到 ESP32-C3 开发板怎么办？
**A:** 检查以下步骤：
1. 在 Arduino IDE 的"首选项"中添加 ESP32 开发板管理器 URL：`https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
2. 在"工具 > 开发板 > 开发板管理器"中搜索 "esp32" 并安装
3. 安装后在开发板列表中选择 "ESP32C3 Dev Module"

### Q2: ST7735 TFT 只显示白屏怎么排查？
**A:** 逐步检查：
1. 接线是否正确（SPI 四线：SCLK/MOSI/CS/DC + RST）
2. SPI 引脚是否匹配代码中的定义
3. 显示初始化参数是否正确（黑标签/红标签屏参数不同）
4. 供电是否充足（3.3V 或 5V，取决于模块）

### Q3: I2C Scanner 扫描不到 SHT31-D？
**A:** 检查：
1. SDA/SCL 接线是否正确（ESP32-C3 默认 GPIO8/GPIO9）
2. SHT31-D 的 I2C 地址（默认 0x44，ADDR 引脚拉高为 0x45）
3. 上拉电阻是否存在（大多数模块已内置）

### Q4: WiFi 连接失败怎么办？
**A:** 排查步骤：
1. 确认 SSID 和密码拼写正确
2. 确认路由器为 2.4GHz 频段（ESP32-C3 不支持 5GHz）
3. 尝试在代码中增加重连逻辑
4. 检查 WiFi 信号强度

---

## 下周预告 | Next Week Preview

第二周将进行：
- Day 6: 电源管理系统 — Type-C 充电、太阳能充电、电量指示模块集成
- Day 7: 显示界面设计 — 多屏切换、动画效果、TFT 布局优化
- Day 8: 系统整合与调试 — 全功能整合、异常处理、稳定性测试
- Day 9: 铜线结构与焊接基础 — 铜线弯制技巧、黄铜管连接
- Day 10: 卫星外壳组装 — 主体框架搭建、面板安装、线路整理

---

*最后更新：2026-05-27*
*Last updated: 2026-05-27*
