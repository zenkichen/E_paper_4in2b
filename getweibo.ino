#include <vector>

// 定义 WeiboItem 结构体
struct WeiboItem {
  String word;
  String label_name;
};

// 定义全局的向量，用于存储 WeiboItem 数据
std::vector<WeiboItem> data_items;

void text12(const char *str, int16_t x, int16_t y, uint16_t fg_color, uint16_t bg_color);

void weibo_show(){
  int8_t i = 0;
  uint16_t x = 0;
  uint16_t y = 0;
  for (const auto& item : data_items) {
      x = 207;
      y = 88 + i * (12 + 9);

    String data_item_word = item.word;
    String word_with_index = String(i + 1) + "." + data_item_word;  // Combine the index and word with the prefix, as a UTF-8-encoded string
    const char *data_item_word1 = word_with_index.c_str();
    if (data_item_word != 0) {
      display.fillRect(x, y-5, 180, 19 + 9, GxEPD_WHITE);
      text12(data_item_word1, x, y,GxEPD_BLACK,GxEPD_WHITE);  // Insert the UTF-8 string into the buffer using buf_ins_text16hei()
      //display.drawFastHLine(x, y + 24, 232, GxEPD_BLACK);
    }
    String label_name = item.label_name;
    const char *data_item_label_name = label_name.c_str();

    std::string data_item_label_name1 = data_item_label_name;
    if (!data_item_label_name1.empty()) {
     int16_t aa = (u8g2Fonts.getUTF8Width(data_item_word1));
     display.fillRoundRect(x + aa + 2, y - 1, 14, 14, 2, GxEPD_RED);
     text12(data_item_label_name, x + aa + 3, y,GxEPD_WHITE,GxEPD_RED);
   }
    i++;
    if(i>=8)
    {
      return;
    }
  }
}
void weibo_get() {
  HTTPClient http;
  http.begin("https://weibo.com/ajax/side/hotSearch");
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();

    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);

    if (doc.containsKey("data")) {
      JsonArray realtime = doc["data"]["realtime"];
      int numResults = realtime.size();

      DynamicJsonDocument outputDoc(1024);
      outputDoc["code"] = 200;
      JsonArray data = outputDoc.createNestedArray("data");

      for (int i = 0; i < numResults; i++) {
        JsonObject resultObj = realtime[i];
        JsonObject outputObj = data.createNestedObject();
        // outputObj["word"] = resultObj["word"].as<String>();
        // outputObj["label_name"] = resultObj["label_name"].as<String>();
        WeiboItem item;
        item.word = resultObj["word"].as<String>().substring(0, 36);
        item.label_name = resultObj["label_name"].as<String>();
        data_items.push_back(item);    
      }
      Serial.println("微博获取成功！");

      // String output;
      // serializeJson(outputDoc, output);
      // Serial.println(output);
    }
  }
  else {
    Serial.printf("HTTP request failed with error code %d\n", httpCode);
  }
  http.end();
}
