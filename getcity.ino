
#include <ArduinoJson.h>
#include "data.h"

void text12(const char *str, int16_t x, int16_t y, uint16_t fg_color, uint16_t bg_color);
// 定义存储 IP 地址的字符串变量
void externIP_get(){
  int httpCode;
  HTTPClient http;
  String url = "https://www.ipplus360.com/getIP";
  http.begin(url);
  httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK) {
    String response = http.getString();
    // Parse JSON response
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, response);
    // Extract city name and its pinyin
    item.publicIP = doc["data"].as<String>();
  } else {
    Serial.println("获取用户端IP失败");
  }
  http.end();
}
void city_get() {
  externIP_get();
  int httpCode;
  HTTPClient http;

  if (WiFi.status() == WL_CONNECTED) {
    String url = "http://ip-api.com/json/"+item.publicIP+"?lang=zh-CN";
    http.begin(url);

    httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
      String response = http.getString();
      // Parse JSON response
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, response);
      item.city = doc["city"].as<String>();
      // Print results
      Serial.print("City:");
      Serial.println(item.city);
    } else {
      Serial.println("获取城市信息失败");
      item.city = "获取失败";
    }
    http.end();
  }
  else {
    Serial.printf("HTTP request failed with error code %d\n", httpCode);
  }
  http.end();
}

void city_show() {
  u8g2Fonts.setFont(u8g2_font_wqy12_t_gb2312);
  int16_t dd = (u8g2Fonts.getUTF8Width(item.city.c_str())); 
  text12(item.city.c_str(), 24, MAX_H-18, GxEPD_WHITE, GxEPD_BLACK);
}
