// =============================================================================
// Desk Satellite 配置模板 / Desk Satellite Configuration Template
// =============================================================================
//
// 使用说明 / Usage:
//   1. 将此文件复制为 config.h (Copy this file as config.h)
//   2. 根据你的环境修改下方的配置值 (Modify values below for your setup)
//   3. config.h 不会被 Git 跟踪 (config.h will not be tracked by Git)
//
// =============================================================================

#ifndef CONFIG_H
#define CONFIG_H

// =============================================================================
// WiFi 配置 / WiFi Configuration
// =============================================================================

// WiFi 网络名称 / WiFi network name (SSID)
// 替换为你的 WiFi 名称 / Replace with your WiFi network name
#define WIFI_SSID       "YourWiFiName"

// WiFi 密码 / WiFi password
// 替换为你的 WiFi 密码 / Replace with your WiFi password
#define WIFI_PASSWORD   "YourWiFiPassword"

// WiFi 连接超时 (毫秒) / WiFi connection timeout (milliseconds)
#define WIFI_TIMEOUT_MS 20000

// WiFi 重连尝试次数 / WiFi reconnection attempts
#define WIFI_MAX_RETRIES 3

// WiFi 重连间隔 (毫秒) / WiFi reconnection interval (milliseconds)
#define WIFI_RETRY_INTERVAL_MS 5000

// =============================================================================
// NTP 时间同步配置 / NTP Time Sync Configuration
// =============================================================================

// NTP 服务器地址 / NTP server addresses
// 中国地区推荐使用国家授时中心 / China: use National Time Service Center
// 其他地区可使用 pool.ntp.org / Other regions: use pool.ntp.org
#define NTP_SERVER_1    "ntp.aliyun.com"       // 阿里云 NTP / Alibaba Cloud NTP
#define NTP_SERVER_2    "cn.ntp.org.cn"         // 中国 NTP / China NTP pool
#define NTP_SERVER_3    "pool.ntp.org"           // 全球 NTP 池 / Global NTP pool

// 时区偏移 (小时) / Timezone offset (hours)
// 北京时间 UTC+8 / Beijing time UTC+8
// 东京 UTC+9 / Tokyo UTC+9
// 纽约 UTC-5 / New York UTC-5
// 伦敦 UTC+0 / London UTC+0
#define TIMEZONE_OFFSET_HOURS 8

// 夏令时偏移 (小时) / Daylight saving offset (hours)
// 中国不使用夏令时，设为 0 / China does not use DST, set to 0
// 如果你的地区使用夏令时，设为 1 / Set to 1 if your region uses DST
#define DST_OFFSET_HOURS 0

// NTP 同步间隔 (毫秒) / NTP sync interval (milliseconds)
// 默认每 1 小时同步一次 / Default: sync every 1 hour
#define NTP_SYNC_INTERVAL_MS 3600000

// =============================================================================
// SPI 引脚定义 (ST7735 TFT 显示屏) / SPI Pin Definitions (ST7735 TFT Display)
// =============================================================================

// ESP32-C3 SPI 引脚映射 / ESP32-C3 SPI pin mapping
// 注意: ESP32-C3 的 GPIO 编号可能与开发板丝印不同
// Note: ESP32-C3 GPIO numbers may differ from board silkscreen labels

// SPI 数据引脚 (MOSI) / SPI data pin (Master Out Slave In)
#define TFT_MOSI    9

// SPI 时钟引脚 (SCK) / SPI clock pin (Serial Clock)
#define TFT_SCK     8

// TFT 片选引脚 (CS) / TFT chip select pin (Chip Select)
#define TFT_CS      21

// TFT 数据/命令引脚 (DC) / TFT data/command pin (Data/Command)
#define TFT_DC      20

// TFT 复位引脚 (RST) / TFT reset pin
#define TFT_RST     10

// TFT 背光引脚 (BL) / TFT backlight pin
// 如果未使用背光控制，可以保持未连接
// If not using backlight control, leave disconnected
#define TFT_BL      -1

// =============================================================================
// I2C 引脚定义 (SHT31-D 温湿度传感器) / I2C Pin Definitions (SHT31-D Sensor)
// =============================================================================

// I2C 数据引脚 (SDA) / I2C data pin (Serial Data)
#define I2C_SDA     2

// I2C 时钟引脚 (SCL) / I2C clock pin (Serial Clock)
#define I2C_SCL     0

// =============================================================================
// 触摸开关和 LED / Touch Switch and LED
// =============================================================================

// 触摸开关引脚 / Touch switch pin
// 用于控制屏幕开关和进入深度睡眠 / Controls screen on/off and deep sleep
#define TOUCH_PIN   1

// LED 指示灯引脚 / LED indicator pin
// 显示 WiFi 连接状态和数据更新状态
// Shows WiFi connection status and data update status
// 如果未使用 LED，设为 -1 / Set to -1 if not using LED
#define LED_PIN     -1

// 触摸开关去抖时间 (毫秒) / Touch switch debounce time (milliseconds)
#define TOUCH_DEBOUNCE_MS 300

// 长按触发时间 (毫秒) / Long press trigger time (milliseconds)
// 长按进入深度睡眠模式 / Long press enters deep sleep mode
#define TOUCH_LONG_PRESS_MS 2000

// =============================================================================
// 显示屏设置 / Display Settings
// =============================================================================

// 显示屏宽度 (像素) / Display width (pixels)
// 0.96" 显示屏通常为 160 / 0.96" display is typically 160
// 1.44" 显示屏通常为 128 / 1.44" display is typically 128
#define DISPLAY_WIDTH   160

// 显示屏高度 (像素) / Display height (pixels)
#define DISPLAY_HEIGHT  80

// 显示屏旋转角度 / Display rotation
// 0 = 竖屏 (Portrait), 1 = 横屏 (Landscape)
// 2 = 竖屏翻转 (Portrait inverted), 3 = 横屏翻转 (Landscape inverted)
#define DISPLAY_ROTATION 3

// ST7735 显示屏类型 / ST7735 display type
// 如果是 0.96" (160x80) 显示屏，使用 INITR_144GREENTAB 或 INITR_MINI160x80
// If using 0.96" (160x80) display, use INITR_144GREENTAB or INITR_MINI160x80
// 如果是 1.44" (128x128) 显示屏，使用 INITR_144GREENTAB
// If using 1.44" (128x128) display, use INITR_144GREENTAB
#define ST7735_TAB_TYPE INITR_MINI160x80

// 背光亮度 (0-255) / Backlight brightness (0-255)
// 仅在背光连接到支持 PWM 的引脚时有效
// Only effective if backlight is connected to a PWM-capable pin
#define BACKLIGHT_BRIGHTNESS 200

// =============================================================================
// SHT31-D 传感器设置 / SHT31-D Sensor Settings
// =============================================================================

// SHT31-D I2C 地址 / SHT31-D I2C address
// 默认地址: 0x44 (ADDR 引脚接地或悬空)
// Default address: 0x44 (ADDR pin connected to GND or floating)
// 替代地址: 0x45 (ADDR 引脚接 VDD)
// Alternate address: 0x45 (ADDR pin connected to VDD)
#define SHT31_I2C_ADDR  0x44

// SHT31-D 加热器 / SHT31-D heater
// 设为 true 可在潮湿环境中启用加热器以减少测量误差
// Set to true to enable heater in humid environments to reduce measurement error
// 正常使用建议设为 false / Recommended false for normal use
#define SHT31_HEATER_ENABLED false

// =============================================================================
// 更新间隔配置 / Update Interval Configuration
// =============================================================================

// 传感器读取间隔 (毫秒) / Sensor reading interval (milliseconds)
// 建议 2000-5000ms，太频繁会影响传感器寿命
// Recommended 2000-5000ms, too frequent may affect sensor lifespan
#define SENSOR_UPDATE_INTERVAL_MS   2000

// 显示刷新间隔 (毫秒) / Display refresh interval (milliseconds)
// 时钟显示建议 1000ms / Clock display recommended 1000ms
#define DISPLAY_UPDATE_INTERVAL_MS  1000

// NTP 时间同步间隔 (毫秒) / NTP time sync interval (milliseconds)
#define NTP_UPDATE_INTERVAL_MS      3600000

// WiFi 状态检查间隔 (毫秒) / WiFi status check interval (milliseconds)
#define WIFI_CHECK_INTERVAL_MS      30000

// 屏幕自动关闭超时 (毫秒) / Screen auto-off timeout (milliseconds)
// 设为 0 禁用自动关闭 / Set to 0 to disable auto-off
#define SCREEN_TIMEOUT_MS           300000  // 5 分钟 / 5 minutes

// =============================================================================
// 深度睡眠配置 / Deep Sleep Configuration
// =============================================================================

// 深度睡眠唤醒引脚 / Deep sleep wake-up pin
// 使用触摸开关引脚唤醒 / Uses touch switch pin to wake up
#define DEEP_SLEEP_WAKEUP_PIN   TOUCH_PIN

// 唤醒触发电平 / Wake-up trigger level
// 0 = 低电平唤醒, 1 = 高电平唤醒
// 0 = wake on LOW, 1 = wake on HIGH
#define DEEP_SLEEP_WAKEUP_LEVEL 0

// =============================================================================
// 显示颜色定义 / Display Color Definitions
// =============================================================================

// 背景色 / Background color
#define COLOR_BG        ST7735_BLACK

// 时钟文字颜色 / Clock text color
#define COLOR_CLOCK     ST7735_WHITE

// 日期文字颜色 / Date text color
#define COLOR_DATE      ST7735_CYAN

// 温度文字颜色 / Temperature text color
#define COLOR_TEMP      ST7735_YELLOW

// 湿度文字颜色 / Humidity text color
#define COLOR_HUMIDITY  ST7735_GREEN

// WiFi 状态颜色 / WiFi status color
#define COLOR_WIFI      ST7735_BLUE

// 错误提示颜色 / Error message color
#define COLOR_ERROR     ST7735_RED

// 标签文字颜色 / Label text color
#define COLOR_LABEL     ST7735_GRAY

// 分隔线颜色 / Divider line color
#define COLOR_DIVIDER   0x39E7  // 深灰 / Dark gray

// =============================================================================
// 调试配置 / Debug Configuration
// =============================================================================

// 启用串口调试输出 / Enable serial debug output
// 设为 0 关闭调试输出以节省内存 / Set to 0 to disable and save memory
#define DEBUG_ENABLED   1

// 串口波特率 / Serial baud rate
#define SERIAL_BAUD_RATE 115200

#endif // CONFIG_H
