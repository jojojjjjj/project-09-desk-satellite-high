# 硬件故障排除 | Hardware Troubleshooting

> 本文档列出 Desk Satellite 项目中常见的硬件问题及其解决方案。
> This document lists common hardware issues and solutions for the Desk Satellite project.

---

## 调试方法论 | Debugging Methodology

遇到问题时，按以下三步排查：

1. **分而治之**：将系统拆分为独立模块（电源、显示、传感器、WiFi），逐一测试
2. **从简到繁**：先用最简单的测试程序验证每个模块，再运行完整程序
3. **串口日志**：打开 Arduino IDE 串口监视器（115200 波特率），查看错误信息

> When troubleshooting: (1) Isolate each module and test independently; (2) Use the simplest test program first; (3) Check serial monitor output at 115200 baud.

---

## 显示屏问题 | Display Issues

### 症状：TFT 屏幕完全黑屏，无任何显示

| 可能原因 Possible Cause | 解决方案 Solution |
|----------------------|-----------------|
| VCC/GND 未连接或接反 | 用万用表确认 TFT 模块 VCC 引脚有 3.3V 电压 |
| 背光引脚 (BL) 未连接 | 将 BL 引脚连接到 3V3（或通过 220Ω 电阻接 3V3） |
| ESP32-C3 未正常启动 | 检查 ESP32-C3 的 LED 是否闪烁，尝试上传 Blink 程序 |
| TFT 模块损坏 | 替换一块新的 TFT 模块测试 |

**最小测试程序：**
```cpp
#include <Adafruit_ST7735.h>
Adafruit_ST7735 tft(21, 20, 9, 8, 10);  // CS, DC, MOSI, SCLK, RST
void setup() {
  tft.initR(INITR_MINI160x80);
  tft.setRotation(1);
  tft.fillScreen(ST7735_RED);
}
void loop() {}
```

### 症状：屏幕亮起但显示乱码/花屏

| 可能原因 Possible Cause | 解决方案 Solution |
|----------------------|-----------------|
| SPI 接线错误或松动 | 逐一检查 SCLK、MOSI、CS、DC、RST 五根线 |
| 显示屏类型不匹配 | 确认使用的是 ST7735（不是 ST7789 或 ILI9341） |
| 初始化参数错误 | 尝试 `INITR_144GREENTAB` 替代 `INITR_MINI160x80` |
| 接线过长导致信号干扰 | SPI 线尽量短（< 10cm），远离电源线 |

### 症状：颜色不对（红蓝反色等）

| 可能原因 Possible Cause | 解决方案 Solution |
|----------------------|-----------------|
| RGB/BGR 设置问题 | 在初始化后添加 `tft.invertDisplay(true);` 或 `false` |
| 不同批次的 ST7735 有不同的颜色顺序 | 尝试切换 invertDisplay 参数 |

---

## 传感器问题 | Sensor Issues

### 症状：I2C Scanner 找不到 SHT31-D（无 0x44 地址）

| 可能原因 Possible Cause | 解决方案 Solution |
|----------------------|-----------------|
| SDA/SCL 接线错误 | 确认 SDA → GPIO 2，SCL → GPIO 0 |
| 传感器 VCC/GND 未接 | 用万用表确认传感器有 3.3V 供电 |
| I2C 地址不正确 | 确认 ADDR 引脚悬空或接 GND（应为 0x44），尝试 0x45 |
| 传感器模块损坏 | 替换新的 SHT31-D 模块 |

**I2C Scanner 测试程序：**
```cpp
#include <Wire.h>
void setup() {
  Serial.begin(115200);
  Wire.begin(2, 0);  // SDA=GPIO2, SCL=GPIO0
  Serial.println("Scanning I2C...");
  for (byte addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.print("Found device at 0x");
      Serial.println(addr, HEX);
    }
  }
}
void loop() {}
```

### 症状：温度/湿度读数异常（如 -45°C 或 100%+）

| 可能原因 Possible Cause | 解决方案 Solution |
|----------------------|-----------------|
| 传感器供电不稳定 | 确保 3.3V 供电稳定，可加 0.1μF 去耦电容 |
| I2C 通信干扰 | 缩短 SDA/SCL 线长度，远离 SPI 线 |
| 传感器靠近热源 | 将 SHT31-D 移离 ESP32-C3 和电池 |
| 读取了无效数据（NaN） | 在代码中添加数据有效性检查 |

---

## WiFi 和 NTP 问题 | WiFi & NTP Issues

### 症状：无法连接 WiFi

| 可能原因 Possible Cause | 解决方案 Solution |
|----------------------|-----------------|
| SSID 或密码错误 | 检查代码中的 WiFi 名称和密码（区分大小写） |
| WiFi 频段不兼容 | ESP32-C3 仅支持 2.4GHz，确认路由器不是仅 5GHz |
| 路由器限制了连接数 | 尝试连接其他 WiFi 网络 |
| 信号太弱 | 将设备靠近路由器测试 |

### 症状：WiFi 连接成功但时间不正确

| 可能原因 Possible Cause | 解决方案 Solution |
|----------------------|-----------------|
| 时区设置错误 | 检查 `gmtOffset_sec` 值（UTC+8 = `8 * 3600`） |
| NTP 服务器无法访问 | 更换 NTP 服务器（如 `ntp.aliyun.com`、`pool.ntp.org`） |
| 夏令时设置错误 | 确认 `daylightOffset_sec` 为 0（中国不使用夏令时） |

---

## 电源问题 | Power Issues

### 症状：电池无法充电

| 可能原因 Possible Cause | 解决方案 Solution |
|----------------------|-----------------|
| Type-C 充电模块接线错误 | 确认 BAT+/BAT- 正确连接电池，IN+/IN- 连接 Type-C |
| 充电模块与电池不匹配 | 确认充电模块输出 4.2V（匹配 3.7V 锂电池） |
| 电池电压过低（< 3.0V） | 电池可能已过放，尝试用专用充电器恢复 |
| Type-C 线不支持数据/充电 | 更换支持充电的 Type-C 线 |

### 症状：电池电量消耗很快（< 2 小时）

| 可能原因 Possible Cause | 解决方案 Solution |
|----------------------|-----------------|
| WiFi 持续工作 | 启用 Deep Sleep 模式，按需唤醒 WiFi |
| TFT 背光常亮 | 降低背光亮度或设置自动关屏 |
| 电池容量不足 | 使用更大容量的电池（如 2000mAh 以上） |
| 存在短路 | 断电后用万用表检查各模块电流消耗 |

### 症状：太阳能板不充电

| 可能原因 Possible Cause | 解决方案 Solution |
|----------------------|-----------------|
| 太阳能板输出不足 | 确保阳光直射，面板朝向正确 |
| 太阳能控制器接线错误 | 确认 VIN+/VIN- 接太阳能板，BAT+/BAT- 接电池 |
| 太阳能板电压不足 | 5V 太阳能板在弱光下可能输出不足，更换更大功率面板 |

---

## 组装问题 | Assembly Issues

### 症状：框架松动/晃动

| 可能原因 Possible Cause | 解决方案 Solution |
|----------------------|-----------------|
| 焊点不牢 | 重新补焊，确保焊点饱满 |
| 黄铜管底座固定不牢 | 在管底与底座之间加环氧树脂胶 |
| 铜线弯曲力度不均 | 重新调整铜线弯曲角度 |

### 症状：铜线容易断裂

| 可能原因 Possible Cause | 解决方案 Solution |
|----------------------|-----------------|
| 反复弯折导致金属疲劳 | 铜线一次弯制到位，避免反复弯折同一位置 |
| 使用了镀层铜线（易断） | 使用纯铜线，延展性更好 |
| 弯曲半径太小 | 使用圆棒/圆管作为模具，避免锐角弯折 |

### 症状：焊点不牢固（虚焊）

| 可能原因 Possible Cause | 解决方案 Solution |
|----------------------|-----------------|
| 铜线表面氧化 | 用砂纸打磨焊接处露出金属光泽 |
| 烙铁温度不够 | 提高烙铁温度到 350-380°C |
| 助焊剂不足 | 涂足助焊剂再焊接 |
| 焊接时间太短 | 每个焊点至少加热 2-3 秒 |

---

## 调试工具 | Debug Tools

### 串口监视器常用命令

在代码中添加以下调试输出：

```cpp
// 检查 WiFi 状态
Serial.printf("WiFi Status: %d (3=连接成功)\n", WiFi.status());
Serial.printf("IP Address: %s\n", WiFi.localIP().toString().c_str());
Serial.printf("RSSI: %d dBm\n", WiFi.RSSI());

// 检查传感器
Serial.printf("Temperature: %.1f°C\n", sht31.readTemperature());
Serial.printf("Humidity: %.1f%%\n", sht31.readHumidity());

// 检查电池电压（如果连接了 ADC）
Serial.printf("Battery: %.2fV\n", analogRead(ADC_PIN) * 3.3 / 4095.0 * 2);
```

### 万用表测量要点

| 测量项 Measurement | 正常值 Expected | 测量点 Test Points |
|-------------------|---------------|-------------------|
| 电池电压 | 3.0V - 4.2V | 电池正负极 |
| ESP32-C3 3V3 输出 | 3.25V - 3.35V | ESP32-C3 的 3V3 引脚 |
| TFT 工作电流 | 15-30mA | TFT VCC 串联测量 |
| SHT31 工作电流 | 0.1-1mA | SHT31 VCC 串联测量 |
| 总工作电流 | 50-150mA | 电池正极串联测量 |
| 深度睡眠电流 | < 1mA | 电池正极串联测量 |

---

*最后更新：2026-05-27*
*Last updated: 2026-05-27*
