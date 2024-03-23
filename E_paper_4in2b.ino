/* Includes ------------------------------------------------------------------*/
#include <U8g2_for_Adafruit_GFX.h>
#include <Time.h>
#include <stdlib.h>
#include <WiFiManager.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "ESP32_config.h"
#include "jpg.h"
#include "data.h"

#define NORMAL_FONT u8g2_font_wqy16_t_gb2312  //设置NORMAL_FONT默认字体
#define TZ 8      // 时区偏移值，以 UTC+8 为例
#define DST_MN 0  // 夏令时持续时间（分钟）
#define TZ_SEC ((TZ)*3600)     // 时区偏移值（秒）
#define DST_SEC ((DST_MN)*60)  // 夏令时持续时间（秒）

U8G2_FOR_ADAFRUIT_GFX u8g2Fonts;
hw_timer_t *timer = NULL;

void configModeCallback(WiFiManager *myWiFiManager) {
  Serial.println("开始配网");
  peiwang();
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");
  // *** special handling for Waveshare ESP32 Driver board *** //
  // ********************************************************* //
#if defined(ESP32) && defined(USE_HSPI_FOR_EPD)
  hspi.begin(13, 12, 14, 15); // remap hspi for EPD (swap pins)
  display.epd2.selectSPI(hspi, SPISettings(4000000, MSBFIRST, SPI_MODE0));
#endif
  // *** end of special handling for Waveshare ESP32 Driver board *** //
  // **************************************************************** //
  display.init(115200);
  display.setRotation(0);  //  0 是横向
  u8g2Fonts.begin(display);
  u8g2Fonts.setFontDirection(0);
  u8g2Fonts.setForegroundColor(GxEPD_BLACK);  // 设置前景色
  u8g2Fonts.setBackgroundColor(GxEPD_WHITE);  // 设置背景色
  u8g2Fonts.setFont(NORMAL_FONT);

  // logo_show();  //显示正在连接wifi开机画面
  // delay(5000);

  WiFiManager wifiManager;

  Serial.println("连接结果:");
  Serial.println(WiFi.waitForConnectResult());  
  wifiManager.setAPCallback(configModeCallback);
  wifiManager.autoConnect("桌面多功能E-paper");  //wifiManager自动配网开始
  Serial.println("连接结果2:");
  Serial.println(WiFi.waitForConnectResult());
  uint8_t i = 0;
  if (WiFi.status() == WL_CONNECTED) {
    i = 0;
    Serial.print("NTP");
    configTime(TZ_SEC, DST_SEC, "ntp1.aliyun.com");  // 向 NTP 服务器请求时间，使用给定的时区和夏令时参数
    while ((time(nullptr) < 1000000000) & (i < 20)) {
      i++;
      Serial.print(".");
      delay(500);
    }
    Serial.println("时间同步成功");
  }
  //确定时间更新成功
  time_t now = time(nullptr);
  while((timeinfo.tm_year + 1900)<=1970)
  {
    time(&now);
    localtime_r(&now, &timeinfo);
  }
  //首次更新显示数据
  data_get();
  refresh_all();
  // 启动1小时定时器
  timer = timerBegin(0, 80, true);  // Timer 0, prescaler 80, count up
  timerAttachInterrupt(timer, &refresh_all, true);  // Attach the getData function to the timer interrupt
  timerAlarmWrite(timer, 3600000000, true);  // Set the timer to trigger every hour (3600 seconds * 1000 milliseconds * 1000 microseconds)
  timerAlarmEnable(timer);  // Enable the timer
  Serial.println("启动1小时定时器");
}

void loop() 
{

}

