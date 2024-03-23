#include <HTTPClient.h>
#include "data.h"
#include "bitmap.h"

void text12(const char *str, int16_t x, int16_t y, uint16_t fg_color, uint16_t bg_color);
void text40(const char *str, int16_t x, int16_t y, uint16_t fg_color, uint16_t bg_color);

void tianqi_show() {
  u8g2Fonts.setFont(u8g2_font_fub42_tf);
  int16_t dd = (u8g2Fonts.getUTF8Width((item.temperature+ "°").c_str())); 
  u8g2Fonts.setForegroundColor(GxEPD_BLACK);
  u8g2Fonts.setBackgroundColor(GxEPD_WHITE);
  text40((item.temperature+ "°").c_str(), (81 - dd) / 2 + 11, 32,GxEPD_BLACK,GxEPD_WHITE);
  text12(item.weather.c_str(), 100, 46,GxEPD_BLACK,GxEPD_WHITE);
  text12(("风力" + item.windScale).c_str(), 100, 32,GxEPD_BLACK,GxEPD_WHITE);
  text12((item.low+ "°-"+item.high+ "°").c_str(), 100, 60,GxEPD_BLACK,GxEPD_WHITE);
  drawWeatherIcon();
}

//显示天气图标
void drawWeatherIcon(){
  const unsigned char *icon;
  unsigned char disp_mode=1;
  switch (item.codeNow.toInt()) {
      case 0: //晴（国内城市白天晴）
          icon = Bitmap_qt;
          disp_mode=2;
          break;
      case 1: //晴（国内城市夜晚晴）
          icon = Bitmap_qt_ws;
          disp_mode=2;
          break;
      case 2: //晴（国外城市白天晴）
          icon = Bitmap_qt;
          disp_mode=2;
          break;
      case 3: //晴（国外城市夜晚晴）
          icon = Bitmap_qt_ws;
          disp_mode=2;
          break;
      case 4: //多云
          icon = Bitmap_dy;
          disp_mode=2;
          break;
      case 5: //晴间多云
          icon = Bitmap_dy;
          disp_mode=2;
          break;
      case 6: //晴间多云
          icon = Bitmap_dy;
          disp_mode=2;
          break;
      case 7: //大部多云
          icon = Bitmap_dy;
          disp_mode=2;
          break;
      case 8: //大部多云
          icon = Bitmap_dy;
          disp_mode=2;
          break;
      case 9: //阴
          icon = Bitmap_yt;
          break;
      case 10: //阵雨
          icon = Bitmap_zheny;
          break;
      case 11: //雷阵雨
          icon = Bitmap_lzy;
          break;
      case 12: //雷阵雨伴有冰雹
          icon = Bitmap_lzybbb;
          break;
      case 13: //小雨
          icon = Bitmap_xy;
          break;
      case 14: //中雨
          icon = Bitmap_zhongy;
          break;
      case 15: //大雨
          icon = Bitmap_dayu;
          break;
      case 16: //暴雨
          icon = Bitmap_by;
          break;
      case 17: //大暴雨
          icon = Bitmap_dby;
          break;
      case 18: //特大暴雨
          icon = Bitmap_tdby;
          break;
      case 19: //冻雨
          icon = Bitmap_dongy;
          break;
      case 20: //雨夹雪
          icon = Bitmap_yjx;
          break;
      case 21: //阵雪
          icon = Bitmap_zhenx;
          break;
      case 22: //小雪
          icon = Bitmap_xx;
          break;
      case 23: //中雪
          icon = Bitmap_zhongx;
          break;
      case 24: //大雪
          icon = Bitmap_dx;
          break;
      case 25: //暴雪
          icon = Bitmap_bx;
          break;
      case 26: //浮尘
          disp_mode=0;
          break;
      case 27: //扬沙
          icon = Bitmap_ys;
          break;
      case 28: //沙尘暴
          icon = Bitmap_scb;
          break;
      case 29: //强沙尘暴
          icon = Bitmap_qt;
          break;
      case 30: //雾
          icon = Bitmap_w;
          break;
      case 31: //霾
          icon = Bitmap_m;
          break;
      case 32: //风
          icon = Bitmap_f;
          break;
      case 33: //大风
          disp_mode=0;
          break;
      case 34: //飓风
          icon = Bitmap_jf;
          break;
      case 35: //热带风暴
          icon = Bitmap_rdfb;
          break;
      case 36: //龙卷风
          icon = Bitmap_ljf;
          break;
      case 37: //冷
          disp_mode=0;
          break;
      case 38: //热
          disp_mode=0;
          break;
      case 99: //未知
          icon = Bitmap_wz;
          break;
      default:
          icon = Bitmap_wz;
          break;
  }
  if(disp_mode==1)//白低黑图
  {
    display.drawInvertedBitmap(145, 32, icon, 45, 45, GxEPD_BLACK);
  }
  else if(disp_mode==2)//白低红图
  {
    display.drawInvertedBitmap(145, 32, icon, 45, 45, GxEPD_RED);
  }
}

void tianqiDays_get() {
  HTTPClient http;  // 声明HTTPClient对象
  http.begin("https://api.seniverse.com/v3/weather/daily.json?key="+seniverse_key+"&location="+item.city+"&language=zh-Hans&unit=c&start=-1&days=5");//这里更换php文件夹中的天气.php实际地址，具体操作请仔细阅读README.md
  int httpCode = http.GET();

  // Check the response code
  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();

    // Parse the JSON response
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);

    // Extract the "daily" field from the JSON response
    JsonArray dailyArray = doc["results"][0]["daily"];
    JsonObject firstDay = dailyArray[0];
    String date = firstDay["date"];
    item.textDay = firstDay["text_day"].as<String>();
    item.codeDay = firstDay["code_day"].as<String>();
    item.textNight = firstDay["text_night"].as<String>();
    item.codeNight = firstDay["code_night"].as<String>();
    item.high = firstDay["high"].as<String>();
    item.low = firstDay["low"].as<String>();
    item.rainfall = firstDay["rainfall"].as<String>();
    item.precip = firstDay["precip"].as<String>();
    item.windDirection = firstDay["wind_direction"].as<String>();
    item.windDirectionDegree = firstDay["wind_direction_degree"].as<String>();
    item.windSpeed = firstDay["wind_speed"].as<String>();
    item.windScale = firstDay["wind_scale"].as<String>();
    item.humidity = firstDay["humidity"].as<String>();
    Serial.println("天气获取成功!");  

  } else {
    Serial.println("3日天气获取失败");
  }

  http.end();

}

void tianqiNow_get() {
  HTTPClient http;  // 声明HTTPClient对象
  http.begin("https://api.seniverse.com/v3/weather/now.json?key="+seniverse_key+"&location="+item.city+"&language=zh-Hans&unit=c");//这里更换php文件夹中的天气.php实际地址，具体操作请仔细阅读README.md
  int httpCode = http.GET();

  // Check the response code
  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();

    // Parse the JSON response
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);

    // Extract the "daily" field from the JSON response
    JsonObject dayweather = doc["results"][0]["now"];
    item.weather = dayweather["text"].as<String>();
    item.codeNow = dayweather["code"].as<String>();
    item.temperature = dayweather["temperature"].as<String>();

    Serial.println("天气获取成功!");  

  } else {
    Serial.println("实时天气获取失败");
    // item.codeNow="99";
  }

  http.end();
}


