#include "data.h"

#define MAX_W 400
#define MAX_H 300

void text12(const char *str, int16_t x, int16_t y, uint16_t fg_color, uint16_t bg_color);

void yiyan_show() {
  //一言 的位置格式
  display.fillRect(0, MAX_H-50, MAX_W, 25, GxEPD_WHITE);
  display.fillRoundRect(2, MAX_H-20-24, 31, 16, 2, GxEPD_RED);
  text12("一言", 5, MAX_H-18-24, GxEPD_WHITE, GxEPD_RED);
  display.drawFastHLine(0, MAX_H-50, MAX_W, GxEPD_BLACK);
  
  u8g2Fonts.setFont(u8g2_font_wqy16_t_gb2312);
  int16_t dd = (u8g2Fonts.getUTF8Width(item.yiyan.c_str()));  
  u8g2Fonts.setForegroundColor(GxEPD_BLACK);
  u8g2Fonts.setBackgroundColor(GxEPD_WHITE);    
  text12(item.yiyan.c_str(), 40, MAX_H-18-24,GxEPD_BLACK,GxEPD_WHITE);  
}

void yiyan_get() {

  HTTPClient http;  // 声明HTTPClient对象 
  http.begin("https://v1.hitokoto.cn/");//这里更换php文件夹中的一言.php实际地址，具体操作请仔细阅读README.md
  int httpCode = http.GET();
  if (httpCode != 200) {
    Serial.println(HTTPClient::errorToString(httpCode));
    http.end();
    Serial.println("一言获取失败");
    return;
  }
 
  String jsoninput = http.getString();
  StaticJsonDocument<100> filter;
  filter["hitokoto"] = true;
  filter["from_who"] = true;

  StaticJsonDocument<500> doc;

  DeserializationError error = deserializeJson(doc, jsoninput, DeserializationOption::Filter(filter));

  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }
  http.end();

  String hitokoto = doc["hitokoto"]; // "眼睛为她下着雨，心却为她打着伞，这就是爱情。 "
  String who = doc["from_who"]; // "d"
  if (who == "null") {
  who = "--佚名";
  }
  item.yiyan = hitokoto + "  " + who;

  Serial.println("一言获取成功!");  

}
