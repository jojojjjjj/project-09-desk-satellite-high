# Day 5: 电源管理系统 | Power Management System

## 今日目标 | Today's Goals

- 理解锂电池（LiPo）的基本参数和安全使用
- 了解 Type-C 充电模块的工作原理
- 学习太阳能充电控制器的原理
- 实现电池电量指示功能
- 设计完整的电源系统架构

---

## 上午 (3h) | Morning Session

### 1. 锂电池基础知识 (1.5h)

**锂电池参数解读**：

```
3.7V 103040 锂电池：

标称电压：3.7V (Nominal Voltage)
充满电压：4.2V (Fully Charged)
放电截止：2.75V - 3.0V (Discharge Cutoff)
容量：103040 → 10mm x 30mm x 40mm → 约 1000-1200mAh
能量：3.7V x 1.2Ah ≈ 4.44 Wh
```

**锂电池安全规则**（必须遵守！）：

1. **绝对不能短路**：正负极直接相连会导致起火/爆炸
2. **不能过充**：电压不能超过 4.2V（充电模块会自动控制）
3. **不能过放**：电压不能低于 2.75V（保护板会自动切断）
4. **不能刺穿或挤压**：会引发内部短路
5. **充电时有人看管**：不要在无人时充电
6. **远离高温环境**：不要放在阳光直射或暖气旁

**锂电池保护板**：

```
保护板功能：
- 过充保护：电压 > 4.25V 时自动断开充电
- 过放保护：电压 < 2.4V 时自动断开放电
- 过流保护：电流 > 3A 时自动断开
- 短路保护：短路时瞬间断开

识别方法：电池背面有一块小 PCB，有 DW01/8205A 等芯片
```

**续航估算**：

```
ESP32-C3 功耗估算：
- WiFi 活跃模式：~80-120 mA
- WiFi Light Sleep：~8-15 mA
- Deep Sleep：~5-15 uA (微安)
- ST7735 TFT (背光)：~20-30 mA
- SHT31-D 传感器：~1-2 mA

总计（正常工作）：约 100-150 mA
电池容量：1200 mAh
理论续航：1200 / 150 ≈ 8 小时（连续工作）

实际续航更长，因为不需要一直全速运行。
加入 Deep Sleep 后可延长到数天甚至数周。
```

**讨论**：
- 为什么锂电池的标称电压是 3.7V 而不是恒定的？
- 电池保护板的作用是什么？没有保护板会怎样？
- 如何延长 Desk Satellite 的续航时间？

### 2. Type-C 充电模块 (1h)

**TP4055 / TP5100 充电模块**：

```
Type-C 充电模块功能：
- 输入：USB Type-C (5V)
- 输出：4.2V (锂电池充电)
- 充电电流：500mA - 1000mA (取决于型号)
- 充电指示：
  - 红灯亮：正在充电
  - 蓝灯/绿灯亮：充电完成
  - 灯灭：未接电池或异常

充电曲线：
  4.2V ─────────╮
                  │ 恒压充电
  4.0V ──────────╮│ (电流逐渐减小)
                   ││
  3.7V ───────────╯│
  恒流充电          ╯ (充电完成)
  (电流恒定 500mA)
```

**接线方式**：

```
Type-C 充电模块接线：

  USB Type-C ───▶ [充电模块] ───▶ 锂电池
                   │  BAT+ ──▶ 电池正极
                   │  BAT- ──▶ 电池负极
                   │
                   └─ OUT+ / OUT- ──▶ ESP32-C3 供电
                     (输出电压 = 电池电压 3.0-4.2V)

  注意：ESP32-C3 的 VCC 引脚可以接受 3.0-3.6V
        但锂电池满电时 4.2V 可能过高！
        需要检查你的 ESP32-C3 开发板的输入电压范围。
        如果开发板有稳压器（如 LDO），可以直接连接。
```

### 3. 太阳能充电控制器 (0.5h)

**太阳能充电原理**：

```
太阳能充电系统：

  迷你太阳能板 (5V 0.5W)
       │
       ▼
  [太阳能充电控制器]
       │     │
       ▼     ▼
  锂电池    系统供电
  (储能)    (给 ESP32-C3 供电)

太阳能板参数：
- 输出电压：5V (开路电压约 6V)
- 输出电流：100-200 mA (晴天)
- 功率：0.5W - 1W
- 尺寸：约 60mm x 60mm

充电控制器功能：
- MPPT/PWM 充电管理
- 防倒充（夜间不会从电池放电到太阳能板）
- 过充保护
- 输出稳压 (5V 或直接电池电压)
```

**实际效果估算**：

```
晴天户外：
  太阳能板输出：5V x 150mA = 0.75W
  ESP32-C3 功耗：3.7V x 100mA = 0.37W
  结论：晴天太阳能可以维持设备运行 + 给电池充电

室内窗边：
  太阳能板输出：5V x 30-50mA = 0.15-0.25W
  结论：只能补充部分电量，需要 Type-C 充电辅助
```

---

## 下午 (4h) | Afternoon Session

### 4. 电池电量指示 (1.5h)

**ADC 读取电池电压**：

ESP32-C3 内置 12 位 ADC（模拟-数字转换器），可以读取电池电压：

```cpp
// 电池电量检测
// 原理：通过分压电阻将电池电压降到 ADC 可读范围
// ESP32-C3 ADC 范围：0 - 2.5V (衰减 11dB 模式下约 0 - 3.3V)

#define BATTERY_PIN 3  // 电池电压检测引脚 (GPIO3)

// 如果电池电压直接接到 GPIO3 (无分压)：
// 满电 4.2V 超出 ADC 范围，需要分压！
// 分压电路：BAT ──[R1 100K]──┬──[R2 100K]──GND
//                             │
//                          GPIO3 (ADC)
// 分压后电压 = 电池电压 x R2 / (R1 + R2) = 4.2V x 0.5 = 2.1V (安全)

// 电池电量计算
float readBatteryVoltage() {
  // 多次采样取平均，减少 ADC 噪声
  long sum = 0;
  for (int i = 0; i < 16; i++) {
    sum += analogRead(BATTERY_PIN);
  }
  float avgReading = sum / 16.0;

  // ESP32-C3 ADC: 12-bit (0-4095), 参考电压约 3.3V
  // 如果使用分压电阻 (R1=R2=100K)：
  float adcVoltage = avgReading / 4095.0 * 3.3;  // ADC 引脚电压
  float batteryVoltage = adcVoltage * 2.0;        // 还原实际电池电压

  // 如果使用电量指示模块，直接读取模块输出
  return batteryVoltage;
}

// 电压转百分比
int voltageToPercent(float voltage) {
  // 锂电池电压-容量近似映射
  if (voltage >= 4.20) return 100;
  if (voltage >= 4.10) return 90;
  if (voltage >= 4.00) return 80;
  if (voltage >= 3.90) return 70;
  if (voltage >= 3.82) return 60;
  if (voltage >= 3.75) return 50;
  if (voltage >= 3.70) return 40;
  if (voltage >= 3.65) return 30;
  if (voltage >= 3.60) return 20;
  if (voltage >= 3.50) return 10;
  if (voltage >= 3.30) return 5;
  return 0;  // 电池电量过低
}

// 电量指示模块 (4 LED 版本)
void displayBatteryLevel(int percent) {
  // 4 LED 指示灯
  if (percent > 75) {
    // 4 个 LED 亮 - 电量充足
  } else if (percent > 50) {
    // 3 个 LED 亮 - 电量良好
  } else if (percent > 25) {
    // 2 个 LED 亮 - 电量一般
  } else if (percent > 10) {
    // 1 个 LED 亮 - 电量低
  } else {
    // LED 闪烁 - 电量极低，需要充电
  }
}
```

### 5. 完整电源系统设计 (1.5h)

**电源系统架构图**：

```
完整电源系统：

  ┌──────────────┐
  │  太阳能板 x2  │──────┐        ┌──────────┐
  └──────────────┘      │        │          │
                   ┌────┴────┐   │  充电     │
                   │太阳能充  │──▶│  控制     │
                   │电控制器  │   │          │
                   └─────────┘   └────┬─────┘
                                      │
  ┌──────────────┐                    │     ┌──────────────┐
  │  Type-C USB  │────────────────────┤     │  锂电池       │
  │  (5V 输入)   │                    │     │  3.7V 1200mAh│
  └──────────────┘                    │     └──────┬───────┘
                                      │            │
                                      ▼            ▼
                                ┌──────────────────┐
                                │   系统供电        │
                                │   3.0 - 4.2V     │
                                └────────┬─────────┘
                                         │
                        ┌────────────────┼────────────────┐
                        ▼                ▼                ▼
                   ┌─────────┐    ┌───────────┐   ┌──────────┐
                   │ ESP32-C3│    │ ST7735 TFT│   │ SHT31-D  │
                   │ (主控)   │    │ (显示)     │   │ (传感器)  │
                   └─────────┘    └───────────┘   └──────────┘
```

**电源管理代码**：

```cpp
// 电源管理模块
#define PIN_BATTERY_ADC  3   // 电池电压检测
#define PIN_CHARGE_STAT  11  // 充电状态检测
#define PIN_LED_POWER    12  // 电源指示 LED

typedef enum {
  POWER_SOURCE_BATTERY,    // 电池供电
  POWER_SOURCE_USB,        // USB 供电 + 充电
  POWER_SOURCE_SOLAR       // 太阳能供电
} PowerSource;

typedef enum {
  CHARGE_STATUS_CHARGING,  // 正在充电
  CHARGE_STATUS_FULL,      // 充电完成
  CHARGE_STATUS_DISCHARGE  // 放电中 (未充电)
} ChargeStatus;

PowerSource currentPowerSource = POWER_SOURCE_BATTERY;
ChargeStatus currentChargeStatus = CHARGE_STATUS_DISCHARGE;
int batteryPercent = 0;

void updatePowerStatus() {
  // 读取电池电压
  float voltage = readBatteryVoltage();
  batteryPercent = voltageToPercent(voltage);

  // 判断充电状态（通过充电模块的状态引脚）
  int chargePin = digitalRead(PIN_CHARGE_STAT);
  // 不同模块的逻辑可能不同
  // 通常：LOW = 充电中, HIGH = 充电完成或未充电

  Serial.printf("Battery: %.2fV (%d%%)\n", voltage, batteryPercent);
}
```

### 6. 实战：TFT 显示电池电量 (1h)

**在时钟界面上添加电池指示器**：

```cpp
// 在 TFT 上显示电池图标和百分比
void drawBatteryIcon(int x, int y, int percent) {
  // 电池外壳 (矩形)
  tft.drawRect(x, y, 25, 12, ST7735_WHITE);
  // 电池正极 (小矩形)
  tft.fillRect(x + 25, y + 3, 3, 6, ST7735_WHITE);

  // 电池内部填充 (根据电量)
  int fillWidth = map(percent, 0, 100, 0, 23);
  uint16_t fillColor;
  if (percent > 50) {
    fillColor = ST7735_GREEN;
  } else if (percent > 25) {
    fillColor = ST7735_YELLOW;
  } else {
    fillColor = ST7735_RED;
  }
  tft.fillRect(x + 1, y + 1, fillWidth, 10, fillColor);

  // 百分比文字
  tft.setTextSize(1);
  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(x + 30, y + 2);
  tft.printf("%d%%", percent);
}

// 在主显示函数中调用
void displayMainScreen() {
  // ... 时钟、温湿度显示 ...

  // 右上角显示电池状态
  drawBatteryIcon(105, 2, batteryPercent);

  // 显示充电状态
  tft.setTextSize(1);
  if (currentChargeStatus == CHARGE_STATUS_CHARGING) {
    tft.setTextColor(ST7735_YELLOW);
    tft.setCursor(105, 16);
    tft.print("CHG");  // Charging
  }
}
```

---

## 今日作业 | Today's Task

1. 了解锂电池的安全使用规则，能够在纸上画出充放电曲线
2. 完成 Type-C 充电模块的接线，确认能正常为电池充电（LED 指示灯变色）
3. 完成电池电压 ADC 读取，串口打印电池电压和百分比
4. 在 TFT 屏幕上显示电池图标和电量百分比
5. 如有太阳能板，测试太阳能充电效果（室内窗边 vs 室外阳光下）
6. 整理电源系统的接线图，拍照记录

## 今日检查点 | Checkpoint

- [ ] 知道锂电池的安全使用规则？（至少 4 条）
- [ ] Type-C 充电模块能正常为电池充电？
- [ ] ADC 能正确读取电池电压？
- [ ] TFT 显示屏显示电池电量和图标？
- [ ] 能画出完整的电源系统架构图？
- [ ] 知道锂电池满电、标称、截止电压分别是多少？（4.2V, 3.7V, 3.0V）
