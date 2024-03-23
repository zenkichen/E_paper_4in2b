#include "data.h"

void text12(const char *str, int16_t x, int16_t y, uint16_t fg_color, uint16_t bg_color);
void text40(const char *str, int16_t x, int16_t y, uint16_t fg_color, uint16_t bg_color);
void text16(const char *str, int16_t x, int16_t y, uint16_t fg_color, uint16_t bg_color);

void drawBoldRoundRect(int x, int y, int w, int h, int r, int thickness, uint16_t color) {
  for (int i = 0; i < thickness; i++) {
     display.drawRoundRect(x + i, y + i, w - i * 2, h - i * 2, r, color);
  }
}

void time_show() {
    char str[20];
    //画日历图
    drawBoldRoundRect(55-50,104,85,79,4,2,GxEPD_RED);
    display.fillRoundRect(55-50,104,85,20,4,GxEPD_RED);
    drawBoldRoundRect(63-50,96,10,15,0,3,GxEPD_RED);
    drawBoldRoundRect(83-50,96,10,15,0,3,GxEPD_RED);
    drawBoldRoundRect(103-50,96,10,15,0,3,GxEPD_RED);
    drawBoldRoundRect(123-50,96,10,15,0,3,GxEPD_RED);

    //年 月
    u8g2Fonts.setFont(u8g2_font_wqy12_t_gb2312);
    sprintf(str, "%d年%d月", (timeinfo.tm_year + 1900),(timeinfo.tm_mon + 1));
    int16_t aa = (u8g2Fonts.getUTF8Width(str)); 
    text12(str, (85-aa)/2+55-50, 108,GxEPD_WHITE,GxEPD_RED);
    // //日
    u8g2Fonts.setFont(u8g2_font_fub42_tf);
    sprintf(str, "%d", timeinfo.tm_mday);
    int16_t bb = (u8g2Fonts.getUTF8Width(str));
    text40(str, (81-bb)/2+57-50, 131,GxEPD_BLACK,GxEPD_WHITE);
    //干支 生肖
    u8g2Fonts.setFont(u8g2_font_wqy12_t_gb2312);
    String scc=item.lunarYear + "  " + "生肖"+item.animalsYear;
    int16_t cc = (u8g2Fonts.getUTF8Width(scc.c_str())); 
    text12(scc.c_str(), (195-cc)/2-50, 191,GxEPD_BLACK,GxEPD_WHITE);
    //农历
    u8g2Fonts.setFont(u8g2_font_wqy12_t_gb2312);
    int16_t dd = (u8g2Fonts.getUTF8Width(item.lunar.c_str())); 
    text12(item.lunar.c_str(), 140-dd/2, 110,GxEPD_BLACK,GxEPD_WHITE);
    //星期
    u8g2Fonts.setFont(u8g2_font_wqy16_t_gb2312);
    int16_t ee = (u8g2Fonts.getUTF8Width(item.weekday.c_str())); 
    text16(item.weekday.c_str(),140-ee/2, 130,GxEPD_RED,GxEPD_WHITE);
    //节日
    ee = (u8g2Fonts.getUTF8Width(item.holiday.c_str())); 
    text16(item.holiday.c_str(),140-ee/2, 155,GxEPD_RED,GxEPD_WHITE);

    display.fillRoundRect(11,207,16,16,4,GxEPD_BLACK);
    display.fillRoundRect(11,225,16,16,4,GxEPD_RED);

    u8g2Fonts.setFont(u8g2_font_wqy12_t_gb2312);
    text12("宜",13, 209,GxEPD_WHITE,GxEPD_BLACK);
    text12("忌",13, 227,GxEPD_WHITE,GxEPD_RED);

    text12(item.yi.substring(0, 36).c_str(),33, 209,GxEPD_BLACK,GxEPD_WHITE);
    text12(item.ji.substring(0, 36).c_str(),33, 227,GxEPD_BLACK,GxEPD_WHITE);
}

void time_get() {
  HTTPClient http;
  char url[100];
  sprintf(url, "https://api.topthink.com/calendar/day?appCode=%s&date=%d-%d-%d",topthink_key, (timeinfo.tm_year + 1900),(timeinfo.tm_mon + 1),timeinfo.tm_mday);
  http.begin(url);
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();

    // 解析 JSON 响应
    DynamicJsonDocument jsonDoc(1024);
    deserializeJson(jsonDoc, payload);

    // 提取数据
    item.animalsYear = jsonDoc["data"]["animalsYear"].as<String>();
    item.weekday = jsonDoc["data"]["weekday"].as<String>();
    item.lunarYear = jsonDoc["data"]["lunarYear"].as<String>();
    item.lunar = jsonDoc["data"]["lunar"].as<String>();
    item.yearMonth = jsonDoc["data"]["year-month"].as<String>();
    item.date = jsonDoc["data"]["date"].as<String>();
    item.suit = jsonDoc["data"]["suit"].as<String>();
    item.avoid = jsonDoc["data"]["avoid"].as<String>();
    item.holiday = jsonDoc["data"]["holiday"].as<String>();
    item.desc = jsonDoc["data"]["desc"].as<String>();

    Serial.println("万年历获取成功！");
  }
  else {
    Serial.printf("万年历获取失败");
  }
  http.end();

  sprintf(url, "https://api.topthink.com/almanac/date?appCode=%s&date=%d-%d-%d",topthink_key, (timeinfo.tm_year + 1900),(timeinfo.tm_mon + 1),timeinfo.tm_mday);
  http.begin(url);
  httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();

    DynamicJsonDocument jsonDoc(1024);
    deserializeJson(jsonDoc, payload);
    // 提取数据到 DataItem 对象
    item.id = jsonDoc["data"]["id"].as<String>();
    item.yangli = jsonDoc["data"]["yangli"].as<String>();
    item.yinli = jsonDoc["data"]["yinli"].as<String>();
    item.wuxing = jsonDoc["data"]["wuxing"].as<String>();
    item.chongsha = jsonDoc["data"]["chongsha"].as<String>();
    item.baiji = jsonDoc["data"]["baiji"].as<String>();
    item.jishen = jsonDoc["data"]["jishen"].as<String>();
    item.yi = jsonDoc["data"]["yi"].as<String>();
    item.xiongshen = jsonDoc["data"]["xiongshen"].as<String>();
    item.ji = jsonDoc["data"]["ji"].as<String>();

    Serial.println("黄历获取成功！");

  }
  else {
    Serial.printf("黄历获取失败");
  }
  http.end();

  
}

