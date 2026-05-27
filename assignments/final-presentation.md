# 最终展示要求 | Final Presentation Requirements

## 概述 | Overview

最终展示是桌面卫星气象站项目的重要环节。学员将向老师和同学展示团队构建的桌面卫星气象站成品，包括设备实物演示、代码讲解、组装过程回顾、技术挑战与解决方案，以及 Demo 网站演示。

> The final presentation is a critical component of the Desk Satellite Weather Station project. Students present their completed device to teachers and classmates, including a live hardware demo, code walkthrough, assembly process review, technical challenges and solutions, and a Demo website walkthrough.

---

## 展示时间 | Presentation Time

**Day 12 下午 | Day 12 Afternoon**

| 环节 Segment | 时间 Time | 说明 Description |
|-------------|----------|-----------------|
| 设备准备与测试 Setup & Testing | 2 分钟 | 上电、连接 WiFi、确认功能正常 |
| 实物演示 Live Demo | 5 分钟 | 展示所有核心功能 |
| 技术讲解与代码走读 Tech Talk & Code Walkthrough | 3 分钟 | 架构说明、关键代码讲解 |
| 问答环节 Q&A | 2 分钟（或更长） | 回答老师和同学的问题 |

> Setup (2 min): Power on, connect WiFi, verify functions. Live Demo (5 min): Show all core features. Tech Talk (3 min): Architecture and key code walkthrough. Q&A (2+ min): Answer questions.

---

## 一、展示结构详解 | Presentation Structure Details

### 1. 设备准备与测试 (2 分钟) | Setup & Testing (2 min)

**必须完成：**
- [ ] 设备上电，确认 ESP32-C3 正常启动
- [ ] WiFi 连接成功，NTP 时间同步
- [ ] TFT 显示屏正常显示
- [ ] SHT31-D 传感器读取温湿度数据
- [ ] 确认触摸开关和 LED 指示灯正常

**提示：** 提前将设备放置在展示位置，确保 WiFi 信号良好，电池充满电。

> Power on and verify: ESP32-C3 boots normally; WiFi connects and NTP syncs; TFT display works; SHT31-D reads data; touch switch and LED indicators functional. Tip: Place device at demo position in advance, ensure good WiFi signal, fully charge battery.

---

### 2. 实物演示 (5 分钟) | Live Demo (5 min)

**必须展示的功能 / Required Demonstrations：**

- [ ] **时钟功能 / Clock Function** — TFT 显示实时网络时间（时:分:秒），秒数实时跳动
- [ ] **温度显示 / Temperature Display** — TFT 显示当前环境温度（来自 SHT31-D）
- [ ] **湿度显示 / Humidity Display** — TFT 显示当前环境湿度（来自 SHT31-D）
- [ ] **多屏切换 / Screen Switching** — 通过触摸开关在不同界面间切换
- [ ] **WiFi 连接状态 / WiFi Status** — 展示设备连接 WiFi 的过程或状态
- [ ] **电源系统 / Power System** — 展示 Type-C 充电或太阳能充电效果

**加分展示（如有）/ Bonus Demonstrations：**
- 电池电量指示功能
- 省电模式切换
- LED 灯光效果
- 太阳能板实时充电演示
- 自定义显示动画

**演示注意事项：**
- 如果设备在现场出现 WiFi 连接问题，可以提前录制演示视频作为 Plan B
- 建议准备一个 USB 充电宝或移动电源作为备用供电
- 演示时注意让观众同时看到设备和 TFT 屏幕内容

> Required: Real-time NTP clock on TFT, temperature reading, humidity reading, multi-screen switching via touch, WiFi connection status, power system demonstration. Bonus: battery level indicator, power saving mode, LED effects, solar charging demo, custom animations.

---

### 3. 技术讲解与代码走读 (3 分钟) | Tech Talk & Code Walkthrough (3 min)

**内容要求 / Content Requirements：**

1. **系统架构 / System Architecture (1 分钟)**
   - 展示系统架构框图（硬件 + 软件）
   - 说明各模块之间的关系：ESP32-C3 主控 -> SPI(TFT) + I2C(SHT31) + WiFi(NTP)
   - 数据流：SHT31-D 传感器 -> ESP32-C3 处理 -> TFT 显示

2. **关键代码讲解 / Key Code Explanation (1 分钟)**
   - 选择 1-2 个核心功能进行代码走读
   - 推荐讲解：
     - SPI 驱动 ST7735 TFT 初始化和显示
     - I2C 读取 SHT31-D 温湿度数据
     - WiFi + NTP 时间同步流程
     - 多屏切换状态机逻辑

3. **组装过程 / Assembly Process (1 分钟)**
   - 展示铜线弯制和焊接的过程照片或视频
   - 说明卫星外壳的设计思路
   - 介绍结构设计中遇到的挑战

> System architecture (1 min): block diagram showing ESP32-C3, SPI (TFT), I2C (SHT31), WiFi (NTP), data flow. Key code (1 min): walk through 1-2 core functions. Assembly (1 min): copper wire bending and soldering process photos/video, satellite design rationale.

---

### 4. 问答环节 (2+ 分钟) | Q&A (2+ min)

**可能的提问方向 / Expected Question Areas：**

- 为什么选择 SPI 而不是 I2C 驱动 TFT？（速度、引脚数量、分辨率）
- SHT31-D 的精度和 I2C 地址是多少？（±0.3°C / ±2%RH / 0x44）
- NTP 时间同步的原理是什么？（UDP 协议向时间服务器请求时间戳）
- 铜线弯制过程中最大的困难是什么？
- 电池续航时间大约多久？太阳能充电效率如何？
- 如果重新做这个项目，你会改进什么？

> Possible questions: Why SPI over I2C for TFT? SHT31-D specs? NTP sync principle? Biggest challenge in copper wire bending? Battery life and solar charging efficiency? What would you improve?

---

## 二、Demo 网站要求 | Demo Website Requirements

### 部署要求 | Deployment Requirements

网站必须部署到以下平台之一（均免费）：

> The website must be deployed on one of these free platforms:

- **GitHub Pages:** https://pages.github.com/ （推荐，最简单）
- **Vercel:** https://vercel.com/ （适合有前端基础的同学）
- **Netlify:** https://www.netlify.com/

### 内容要求 | Content Requirements

| 内容 Content | 必需/加分 Required/Bonus | 说明 Description |
|-------------|------------------------|-----------------|
| 项目描述 Project Description | 必需 | 中英双语介绍桌面卫星气象站 |
| 照片/视频 Photos/Video | 必需 | 设备成品照片、功能演示视频、组装过程照片 |
| 技术文档 Technical Docs | 必需 | 系统架构说明、通信协议（SPI/I2C）简介、接线图 |
| 团队信息 Team Info | 必需 | 成员介绍、分工说明 |
| 原理图/接线图 Wiring Diagram | 加分 | 硬件接线示意图 |
| 传感器数据展示 Sensor Data Display | 加分 | 温度/湿度历史数据图表 |
| 交互功能 Interactive Features | 加分 | 网页端查看实时数据的接口 |
| 响应式设计 Responsive Design | 加分 | 适配手机/平板访问 |

### 技术建议 | Technical Suggestions

- **最简方案：** HTML/CSS/JS 静态页面 + GitHub Pages（零门槛）
- **进阶方案：** React/Vue + Vercel（适合有前端经验的同学）
- **可视化方案：** Chart.js / ECharts（用于温湿度数据图表）

---

## 三、展示技巧 | Presentation Tips

### 应该做的 Do's

- [ ] 提前排练至少 2 次，控制时间在 10 分钟以内
- [ ] 准备演示视频作为 Plan B（以防硬件故障）
- [ ] PPT 或网页展示包含清晰的系统架构图
- [ ] 演示时同时展示设备实物和屏幕内容
- [ ] 讲解时使用中英文术语对照（如 SPI 串行外设接口）
- [ ] 准备好回答常见技术问题
- [ ] 确保电池充满电，准备备用供电
- [ ] 组装过程照片提前整理好，按时间顺序排列
- [ ] 团队成员分工明确，每人都有展示部分
- [ ] 保持自信，声音洪亮，语速适中

### 不应该做的 Don'ts

- [ ] 不要照着 PPT 念稿——用自己的话讲解
- [ ] 不要花太多时间在一个功能上——合理分配时间
- [ ] 不要在演示过程中修改代码——提前锁定最终版本
- [ ] 不要忽略失败的功能——诚实说明遇到的问题和解决尝试
- [ ] 不要在演示时进行首次测试——提前充分验证
- [ ] 不要使用太多专业术语而不解释——照顾非技术观众
- [ ] 不要让团队成员站在一旁无所事事——人人参与
- [ ] 不要忘记介绍团队和各成员的贡献

---

## 四、提交清单 | Submission Checklist

### 代码提交 | Code Submission

- [ ] 所有源代码已推送到 Git 仓库
- [ ] 代码有充分的中文注释
- [ ] 包含 `config.template.h`（WiFi 配置模板）
- [ ] 包含 `README.md`（项目说明文档）
- [ ] 包含接线说明文档
- [ ] Commit 历史完整规范

### 硬件交付 | Hardware Delivery

- [ ] 桌面卫星气象站成品（功能完整）
- [ ] 卫星外壳组装完成（铜线 + 黄铜管 + 底座）
- [ ] 所有电子元件固定牢固
- [ ] 线路整理整洁，无裸露短路风险
- [ ] 电池充电功能正常
- [ ] 设备可以独立运行（不依赖电脑供电）

### Demo 网站 | Demo Website

- [ ] 网站已部署并可在线访问
- [ ] 包含中英双语项目描述
- [ ] 包含设备照片和演示视频
- [ ] 包含技术文档和架构说明
- [ ] 包含团队信息和分工
- [ ] 网站视觉设计整洁美观

### 文档 | Documentation

- [ ] README.md 完整（项目简介、功能列表、硬件清单、使用说明）
- [ ] 代码注释清晰（关键函数有中文说明）
- [ ] 接线图（手绘或软件绘制均可）
- [ ] 项目总结（500 字以上，含学习收获和未来改进）

---

## 五、评分标准 | Grading Criteria

### 评分维度 | Scoring Dimensions

| 维度 Dimension | 满分 Points | 说明 Description |
|---------------|------------|-----------------|
| **实物演示效果** Device Demo | 25 | 设备功能完整，演示流畅，TFT 显示清晰 |
| **技术讲解深度** Technical Depth | 20 | 架构清晰，代码讲解到位，原理理解透彻 |
| **Demo 网站** Demo Website | 20 | 已部署、内容完整、设计美观 |
| **PPT/展示质量** Presentation Quality | 15 | 美观专业、图文并茂、中英双语 |
| **沟通表达** Communication | 10 | 清晰流畅、逻辑连贯、互动良好 |
| **问答环节** Q&A | 10 | 回答准确、思路清晰、能深入讨论 |

### 等级描述 | Level Descriptions

**A 级（优秀 Excellent）/ 90-100 分：**
- 设备功能完整，演示流畅无故障
- TFT 显示界面精美，多屏切换流畅
- 技术讲解深入，能清晰解释 SPI/I2C/WiFi 原理
- Demo 网站设计精美，内容丰富，有技术深度
- 问答环节回答准确全面
- 组装工艺精良，铜线结构美观稳固

**C 级（及格 Pass）/ 60-74 分：**
- 设备基本功能可用（时钟 + 温湿度显示）
- 技术讲解能说明基本原理
- Demo 网站已部署，包含基本内容
- 演示过程可能有小问题但能继续
- 问答环节能回答基本问题

**D 级（不及格 Fail）/ 60 分以下：**
- 设备核心功能不工作（无法显示或传感器不读取）
- 无法讲解技术原理
- Demo 网站未部署或内容极其简陋
- 演示无法进行或完全失败
- 无法回答基本技术问题

---

## 六、PPT 建议 | PPT Suggestions

### 整体要求 | Overall Requirements

- **总页数：** 8-12 页
- **风格：** 简洁专业，图文并茂
- **语言：** 中英双语

### 必含页面 | Required Pages

1. **封面页 Cover (1 页)**
   - 项目名称：桌面卫星气象站 / Desk Satellite Weather Station
   - 团队成员姓名
   - 日期

2. **项目概述 Project Overview (1-2 页)**
   - 项目简介和功能列表
   - 技术栈：ESP32-C3 + ST7735 TFT + SHT31-D + WiFi/NTP + 太阳能
   - 各成员贡献说明

3. **系统架构 System Architecture (1-2 页)**
   - 硬件架构图（ESP32-C3 -> SPI(TFT) + I2C(SHT31) + WiFi(NTP)）
   - 软件架构图（初始化 -> WiFi 连接 -> NTP 同步 -> 主循环）
   - 数据流图

4. **关键技术与代码 Key Tech & Code (2 页)**
   - SPI 驱动 TFT 显示
   - I2C 读取 SHT31-D
   - WiFi/NTP 时间同步
   - 多屏切换逻辑

5. **组装过程 Assembly Process (1-2 页)**
   - 铜线弯制过程照片
   - 焊接过程照片
   - 组装前后对比

6. **挑战与解决 Challenges & Solutions (1 页)**
   - 遇到的主要技术挑战
   - 解决方案

7. **Demo 网站展示 Demo Website (1 页)**
   - 网站截图
   - 部署链接

8. **总结与展望 Summary & Outlook (1 页)**
   - 学习收获
   - 未来改进方向

---

## 七、常见问题准备 | Common Q&A Preparation

### 技术问题 | Technical Questions

1. **为什么选择 ESP32-C3 而不是 ESP8266？**
   > ESP32-C3 使用 RISC-V 架构，性能更强（160MHz vs 80MHz），内置蓝牙 5.0，Flash 更大（4MB vs 2MB），功耗更低，GPIO 更多方便扩展。

2. **为什么使用 SPI 而不是 I2C 驱动 TFT？**
   > SPI 传输速度远高于 I2C（SPI 可达数十 MHz，I2C 通常 400kHz）。TFT 彩色显示屏需要快速刷新大量像素数据（80x160x16bit = 25.6KB），SPI 的高带宽是必需的。

3. **SHT31-D 的精度是多少？I2C 地址是什么？**
   > 温度精度 ±0.3°C，湿度精度 ±2% RH。默认 I2C 地址为 0x44（ADDR 引脚拉高为 0x45）。

4. **NTP 时间同步的原理是什么？**
   > NTP（Network Time Protocol）通过 UDP 协议向时间服务器（如 pool.ntp.org）发送请求，服务器返回当前 UTC 时间戳，ESP32-C3 加上时区偏移转换为本地时间。

5. **太阳能板的充电效率如何？**
   > 5V 0.5W 太阳能板在充足阳光下可提供约 100mA 充电电流。对于 300mAh 锂电池，充满大约需要 3-4 小时充足日照。实际使用中太阳能更多是辅助充电。

### 项目问题 | Project Questions

1. **最大的挑战是什么？**
   > 学员根据自己的实际经历回答，可能包括：铜线弯制的精确度、SPI 接线的正确性、多模块同时工作的电源稳定性、TFT 显示界面的布局设计等。

2. **学到了什么？**
   > 嵌入式开发（ESP32-C3 编程）、通信协议（SPI/I2C）、网络编程（WiFi/NTP）、电源管理（锂电池/太阳能）、手工制作（铜线弯制/焊接）、团队协作和项目管理。

3. **如果重新开始会做什么不同？**
   > 根据个人经历回答。常见建议：更早开始铜线练习、预留更多集成测试时间、提前规划线路布局。

---

*祝展示成功！Good luck with your presentation!*
*最后更新：2026-05-27 | Last updated: 2026-05-27*
