# 第二周进度报告 | Week 2 Progress Report

## 概述 | Overview

第二周进度报告用于评估学员在 Day 6-10 的学习成果，重点检查电源管理系统完成度、显示界面设计效果、交互功能实现、系统整合稳定性，以及铜线结构组装进展。报告须在 Day 10 结束前提交，字数 800-1200 中文字符。

> The Week 2 progress report evaluates learning outcomes from Day 6-10, focusing on power management system completion, display interface design, interactive features, system integration stability, and copper wire structure assembly progress. Due by end of Day 10. Word count: 800-1200 Chinese characters.

---

## 截止日期 | Due Date

**Day 10 下课前 | Before class ends on Day 10**

---

## 学生/团队信息 | Student / Team Information

| 字段 Field | 内容 Content |
|-----------|-------------|
| **团队名称 / Team Name** | |
| **成员姓名 / Members** | |
| **项目仓库链接 / Repo URL** | |
| **报告日期 / Report Date** | |
| **第一周得分 / Week 1 Score** | |

---

## 一、已完成功能清单 | Completed Features Checklist

请填写下表，记录 Day 6-10 期间各项功能的完成状态。

> Fill in the table below to record the completion status of each feature during Day 6-10.

### 电源管理系统 | Power Management System

| 功能 Feature | 状态 Status | 备注 Notes |
|-------------|------------|-----------|
| Type-C 充电模块接线与测试 | 未开始 / 进行中 / 已完成 | 测量充电电压是否为 4.2V |
| 3.7V 锂电池连接与保护板检查 | 未开始 / 进行中 / 已完成 | 确认电池电压在 3.0-4.2V 范围 |
| 太阳能充电控制器接线 | 未开始 / 进行中 / 已完成 | 太阳能板输出 5V 接入控制器 |
| 电池电量指示模块测试 | 未开始 / 进行中 / 已完成 | 4 个 LED 电量等级显示正常 |
| 电源供电链路整体测试 | 未开始 / 进行中 / 已完成 | 电池 -> ESP32-C3 + TFT + SHT31 同时供电 |

> Verify charging voltage reaches 4.2V; battery voltage stays within 3.0-4.2V range; solar panel outputs 5V to controller; 4-LED battery level indicator works; full power chain delivers stable voltage to all components.

### 显示界面设计 | Display Interface Design

| 功能 Feature | 状态 Status | 备注 Notes |
|-------------|------------|-----------|
| 时钟界面（时间 + 日期显示） | 未开始 / 进行中 / 已完成 | TFT 显示小时:分钟:秒 |
| 温度显示界面 | 未开始 / 进行中 / 已完成 | 显示 SHT31-D 读取的温度值 |
| 湿度显示界面 | 未开始 / 进行中 / 已完成 | 显示 SHT31-D 读取的湿度值 |
| 多屏切换功能 | 未开始 / 进行中 / 已完成 | 至少 2 个界面可切换 |
| 显示动画或过渡效果 | 未开始 / 进行中 / 已完成 | 切屏动画、数字变化动画等 |
| 状态栏信息（WiFi/电量） | 未开始 / 进行中 / 已完成 | 显示 WiFi 连接状态和电池电量 |

### 交互功能 | Interactive Features

| 功能 Feature | 状态 Status | 备注 Notes |
|-------------|------------|-----------|
| 触摸开关（TTP223）控制开关机 | 未开始 / 进行中 / 已完成 | 触摸一次开/关机 |
| LED 指示灯状态显示 | 未开始 / 进行中 / 已完成 | 不同颜色/闪烁模式表示不同状态 |
| 省电模式或低功耗设计 | 未开始 / 进行中 / 已完成 | 无操作一段时间后降低刷新率 |

### 系统整合 | System Integration

| 功能 Feature | 状态 Status | 备注 Notes |
|-------------|------------|-----------|
| 所有传感器模块同时工作 | 未开始 / 进行中 / 已完成 | SHT31-D + TFT + WiFi 同时运行 |
| 系统连续运行 10 分钟以上不崩溃 | 未开始 / 进行中 / 已完成 | 测试稳定性 |
| 异常处理机制 | 未开始 / 进行中 / 已完成 | WiFi 断线重连、传感器读取失败处理 |
| 看门狗定时器设置 | 未开始 / 进行中 / 已完成 | 防止系统死机 |

### 硬件组装进度 | Hardware Assembly Progress

| 功能 Feature | 状态 Status | 备注 Notes |
|-------------|------------|-----------|
| 铜线弯制练习完成 | 未开始 / 进行中 / 已完成 | 圆形、三角形等基本形状 |
| 黄铜管切割与连接 | 未开始 / 进行中 / 已完成 | 3mm 黄铜管按尺寸切割 |
| 卫星主体框架搭建 | 未开始 / 进行中 / 已完成 | 主体结构基本成型 |
| 底座（竹杯垫）固定 | 未开始 / 进行中 / 已完成 | 元件固定到底座上 |
| 线路整理与焊接 | 未开始 / 进行中 / 已完成 | 飞线整理、关键节点焊接 |

---

## 二、系统整合状态 | System Integration Status

请描述当前系统的整体运行状态，各模块之间的协同工作情况。

> Describe the current overall system operation status and how modules work together.

### 2.1 系统工作流程 | System Workflow

（请描述设备上电后的工作流程。例如：上电 -> 连接 WiFi -> NTP 同步时间 -> 读取传感器数据 -> TFT 显示时钟界面 -> 定时刷新温湿度。）

> Describe the device workflow after power-on. For example: Power on -> Connect WiFi -> NTP sync time -> Read sensor data -> TFT displays clock -> Periodically refresh temperature/humidity.

**工作流程描述 / Workflow Description:**

---

### 2.2 模块协同状态 | Module Collaboration Status

| 模块 Module | 正常工作 / 有问题 | 问题描述（如有） |
|------------|-----------------|----------------|
| ESP32-C3 主控 | | |
| ST7735 TFT 显示 | | |
| SHT31-D 温湿度传感器 | | |
| WiFi 连接 | | |
| NTP 时间同步 | | |
| Type-C 充电 | | |
| 太阳能充电 | | |
| 电池电量指示 | | |
| 触摸开关 | | |
| LED 指示灯 | | |

---

### 2.3 演示准备状态 | Demo Preparation Status

| 准备项目 Item | 完成度 (1-5) | 备注 |
|--------------|-------------|------|
| **硬件功能完整性** | | |
| Hardware Feature Completeness | | |
| **软件稳定性** | | |
| Software Stability | | |
| **外壳组装进度** | | |
| Enclosure Assembly Progress | | |
| **Demo 网站进度** | | |
| Demo Website Progress | | |
| **演示排练状态** | | |
| Demo Rehearsal Status | | |
| **文档完整度** | | |
| Documentation Completeness | | |

---

## 三、遇到的问题 | Problems Encountered

请详细描述在第二周遇到的技术问题。至少记录 3 个问题。

> Describe in detail the technical problems encountered during Week 2. Record at least 3 problems.

### 问题 1 | Problem 1

**问题描述 / Problem Description:**

**尝试的解决方案 / Attempted Solutions:**

**当前状态 / Current Status:** 已解决 / 部分解决 / 未解决

---

### 问题 2 | Problem 2

**问题描述 / Problem Description:**

**尝试的解决方案 / Attempted Solutions:**

**当前状态 / Current Status:** 已解决 / 部分解决 / 未解决

---

### 问题 3 | Problem 3

**问题描述 / Problem Description:**

**尝试的解决方案 / Attempted Solutions:**

**当前状态 / Current Status:** 已解决 / 部分解决 / 未解决

---

### 问题 4 | Problem 4（如有）

**问题描述 / Problem Description:**

**尝试的解决方案 / Attempted Solutions:**

**当前状态 / Current Status:** 已解决 / 部分解决 / 未解决

---

## 四、第三天剩余计划 | Remaining Plan (Day 11-12)

请列出 Day 11-12 的具体计划。

> List your specific plan for Day 11-12.

| 天数 Day | 计划内容 Planned Work | 预期目标 Expected Goal |
|----------|---------------------|----------------------|
| Day 11 | 整机组装与美化 | 电路集成入外壳、底座固定、最终调试 |
| Day 12 | 项目展示与总结 | 成果演示、Demo 网站部署、技术分享 |

### Demo 网站准备状态 | Demo Website Readiness

- [ ] 网站框架已搭建（GitHub Pages / Vercel / Netlify）
- [ ] 项目描述内容已撰写（中英双语）
- [ ] 照片和视频素材已准备
- [ ] 技术文档已编写
- [ ] 团队信息已添加
- [ ] 网站已部署并可访问

> Website framework built; project description written (bilingual); photos and video prepared; technical documentation written; team info added; site deployed and accessible.

---

## 五、个人反思 | Personal Reflection

请写一段 300-500 字的反思，涵盖以下内容：

> Write a 300-500 word reflection covering the following:

1. **技术成长 / Technical Growth：** 第二周中，你在电源管理、显示设计、系统整合方面有哪些进步？遇到最大的技术挑战是什么？
   > How did you grow in power management, display design, and system integration? What was your biggest technical challenge?

2. **动手能力 / Hands-on Skills：** 铜线弯制和焊接工作体验如何？你觉得自己的动手能力有什么变化？
   > How was the copper wire bending and soldering experience? How has your hands-on skill changed?

3. **团队协作 / Teamwork：** 第二周的分工是否合理？有没有遇到意见分歧？如何解决的？
   > Was the Week 2 task division reasonable? Did you encounter disagreements? How were they resolved?

4. **项目展望 / Project Outlook：** 对最终展示有什么期待？还有什么需要特别关注的？
   > What are your expectations for the final presentation? What needs special attention?

---

**反思内容 / Reflection Content:**

（在此撰写你的反思，300-500 字）

---

## 六、代码提交状态 | Code Submission Status

- [ ] 所有代码已推送到团队 Git 仓库
- [ ] 包含完整的项目 README.md
- [ ] 代码有清晰的中文注释
- [ ] Commit 历史完整，信息规范
- [ ] 包含 WiFi 配置模板文件（config.template.h）

> All code pushed to team repo; complete README.md; clear Chinese comments; commit history complete; includes WiFi config template.

**仓库链接 / Repo URL:** _______________________

**总 Commit 数量 / Total Commits:** ______

**Git 提交记录（最近 10 次）/ Recent Git Commits (10):**

| 序号 | Commit Message | 日期 |
|------|---------------|------|
| 1 | | |
| 2 | | | 
| 3 | | |
| 4 | | |
| 5 | | |
| 6 | | |
| 7 | | |
| 8 | | |
| 9 | | |
| 10 | | |

---

## 七、自我评估 | Self-Assessment

请对以下维度进行 1-5 分评分（1 = 需要大量帮助，5 = 完全独立完成）。

> Rate each dimension 1-5 (1 = need significant help, 5 = completed independently).

| 维度 Dimension | 评分 Score (1-5) | 备注 Notes |
|---------------|-----------------|-----------|
| **电源管理系统** | | |
| Power Management System | | |
| **TFT 显示界面设计** | | |
| TFT Display Interface Design | | |
| **交互功能实现** | | |
| Interactive Features | | |
| **系统整合能力** | | |
| System Integration | | |
| **铜线结构组装** | | |
| Copper Wire Assembly | | |
| **焊接技术** | | |
| Soldering Skills | | |
| **问题解决能力** | | |
| Problem Solving | | |
| **团队合作** | | |
| Teamwork | | |
| **文档撰写** | | |
| Documentation | | |

---

## 八、提交证据 | Submission Evidence

### 必须提交的材料 | Required Submissions

- [ ] 电源管理系统接线照片
- [ ] TFT 多屏切换效果照片或视频
- [ ] 系统连续运行 10 分钟截图或视频
- [ ] 铜线弯制作品照片
- [ ] 卫星外壳框架照片（如有进展）
- [ ] 第二周进度报告（本文件）

> Required: power management wiring photo, TFT multi-screen switching photo/video, 10-minute continuous run evidence, copper wire bending work photo, satellite frame photo (if progress made), and this progress report.

---

## 评分标准 | Grading Criteria

| 项目 Item | 权重 Weight | 评分标准 Standard |
|----------|-----------|------------------|
| **完成度 Completeness** | 40% | Day 6-10 功能清单中至少完成 60% 为及格，80% 为良好，90% 以上为优秀。硬件组装有实质性进展。 |
| **问题分析 Problem Analysis** | 30% | 至少记录 3 个技术问题，描述详细，解决方案有逻辑性。系统整合相关问题的分析尤为重要。 |
| **计划质量 Plan Quality** | 20% | Day 11-12 计划具体可行；Demo 网站和最终展示有明确的准备步骤。 |
| **个人反思 Reflection** | 10% | 反思有深度，涵盖技术成长、动手能力、团队协作和项目展望。 |

> Completeness: 60% features = pass, 80% = good, 90% = excellent with hardware assembly progress. Problem Analysis: at least 3 problems with detailed descriptions and logical solutions. Plan Quality: specific and feasible for Day 11-12. Reflection: in-depth covering all four aspects.

---

## 常见问题 | FAQ

### Q1: 电源管理电路不稳定怎么办？
**A:** 排查步骤：
1. 用万用表测量各节点电压是否在预期范围内
2. 检查电池保护板是否正常工作（过充/过放保护）
3. 确认充电模块输出电压为 4.2V（锂电池满充电压）
4. 检查是否有短路或虚焊

### Q2: TFT 显示闪烁或不稳定？
**A:** 检查：
1. SPI 信号线是否过长（建议 < 10cm）
2. 供电是否稳定（TFT 背光消耗电流较大）
3. 刷新频率是否过高（建议 1 秒刷新一次即可）
4. 是否需要添加去耦电容（0.1uF + 10uF）

### Q3: 铜线弯制不规整怎么办？
**A:** 技巧：
1. 使用圆棒或圆管作为弯制模具
2. 先画好设计草图，按图施工
3. 从简单形状开始练习（圆形 -> 椭圆 -> 复杂曲线）
4. 用钳子辅助弯制直角和锐角
5. 不要一次弯太多，逐步调整

### Q4: WiFi 连接后经常断线？
**A:** 建议：
1. 添加 WiFi 重连逻辑（断线后自动重连）
2. 检查路由器信号强度
3. ESP32-C3 天线附近不要有金属遮挡
4. 适当增加 NTP 同步间隔（如每 10 分钟同步一次）

### Q5: 系统运行一段时间后死机？
**A:** 排查：
1. 检查是否有内存泄漏（String 对象未释放）
2. 添加看门狗定时器（Watchdog Timer）
3. 检查供电是否不足（电池电压是否低于 3.3V）
4. 减少不必要的全局变量

---

## 最终提交预告 | Final Submission Preview

Day 12 需要提交的完整材料清单：

### 代码 | Code
- [ ] 所有源代码提交到 Git
- [ ] 代码有适当注释
- [ ] WiFi 配置模板文件
- [ ] 接线说明文档

### 文档 | Documentation
- [ ] README 完善
- [ ] 接线图
- [ ] 硬件清单 (BOM)
- [ ] 项目总结

### 演示 | Demo
- [ ] 演示视频录制
- [ ] 演示脚本准备
- [ ] 设备最终调试

### Demo 网站 | Demo Website
- [ ] 网站已部署（GitHub Pages / Vercel / Netlify）
- [ ] 包含项目描述（中英双语）
- [ ] 包含照片/视频
- [ ] 包含技术文档
- [ ] 包含团队信息

---

*恭喜接近项目完成！Congratulations on nearing project completion!*
*最后更新：2026-05-27 | Last updated: 2026-05-27*
