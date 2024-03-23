#include "font.c"

#define MAX_W 400
#define MAX_H 300

void text12(const char *str, int16_t x, int16_t y, uint16_t fg_color, uint16_t bg_color);

void peiwang() {
  int pos_y=50;
  display.setFullWindow();
  display.firstPage();   
  display.fillScreen(GxEPD_WHITE);
  do {  
  u8g2Fonts.setFont(logo_24_35);
  u8g2Fonts.setForegroundColor(GxEPD_BLACK);
  int16_t ww = (u8g2Fonts.getUTF8Width("E-Paper Desktop"));   
  u8g2Fonts.drawUTF8((MAX_W-ww)/2, pos_y, "E-Paper Desktop"); pos_y+=30;// 在透明背景上绘制文本
  u8g2Fonts.setFont(u8g2_font_wqy12_t_gb2312);
  int16_t aa = (u8g2Fonts.getUTF8Width("WIFI连接失败"));
  int16_t bb = (u8g2Fonts.getUTF8Width("请用手机或者笔记本连接下面wifi进行配网"));
  int16_t cc = (u8g2Fonts.getUTF8Width("SSID:桌面多功能E-paper"));
  int16_t dd = (u8g2Fonts.getUTF8Width("连接后访问:192.168.4.1进行设置"));
  int16_t ee = (u8g2Fonts.getUTF8Width("配置成功后请耐心等待,获取到天气等所有数据后进行刷新"));
  text12("WIFI连接失败", (MAX_W-aa)/2, pos_y, GxEPD_BLACK, GxEPD_WHITE); pos_y+=30; 
  text12("请用手机或者笔记本连接下面wifi进行配网", (MAX_W-bb)/2, pos_y, GxEPD_BLACK, GxEPD_WHITE);  pos_y+=30;
  text12("SSID:桌面多功能E-paper", (MAX_W-cc)/2, pos_y, GxEPD_BLACK, GxEPD_WHITE);  pos_y+=30;
  text12("连接后访问:192.168.4.1进行设置", (MAX_W-dd)/2, pos_y, GxEPD_BLACK, GxEPD_WHITE);  pos_y+=30;
  text12("配置成功后请耐心等待,获取到天气等所有数据后进行刷新", (MAX_W-ee)/2, pos_y, GxEPD_BLACK, GxEPD_WHITE);  
  } while (display.nextPage());
  display.powerOff();
}

void displaymain() {
  display.drawFastHLine(0, 78, MAX_W, GxEPD_BLACK);
  display.drawFastHLine(0, MAX_H-25, MAX_W, GxEPD_BLACK);
  display.drawFastVLine(195, 24, MAX_H-24, GxEPD_BLACK);
  display.fillRect(0, 0, MAX_W, 24, GxEPD_RED);
  display.fillRect(0, MAX_H-24, MAX_W, 25, GxEPD_BLACK);
  text12("桌面多功能E-Paper", 10, 7, GxEPD_WHITE, GxEPD_RED);
  display.drawBitmap(MAX_W/2-40, 3, dingmid, 80, 17, GxEPD_WHITE);
  display.drawInvertedBitmap(10, MAX_H-18, weizhi, 9, 12, GxEPD_WHITE);

  display.drawInvertedBitmap(210, 34, weiboBW, 131, 34, GxEPD_BLACK);
  display.drawInvertedBitmap(210, 34, weiboR, 131, 34, GxEPD_RED);

  //"更新于" 信息显示
  time_t now = time(nullptr);
  char timeStr[20];
  strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localtime(&now));
  String shijian = timeStr;
  int16_t aa = (u8g2Fonts.getUTF8Width(shijian.c_str()));
  display.drawInvertedBitmap(MAX_W-aa-20-15, 8, refresh, 14, 12, GxEPD_WHITE);
  text12(shijian.c_str(), MAX_W-aa-20, 8, GxEPD_WHITE, GxEPD_RED);

  if (WiFi.status() == WL_CONNECTED) {
    display.drawBitmap(MAX_W-18, 8, digital_ok, 16, 13, GxEPD_WHITE);      
  } else {
    display.drawBitmap(MAX_W-18, 8, digital_no, 16, 13, GxEPD_WHITE);      
  }
}