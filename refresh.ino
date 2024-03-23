
void data_get(){
  city_get();
  yiyan_get();
  weibo_get();
  time_get();
  tianqiDays_get();
  tianqiNow_get();
}

void refresh_all(){
  // 获取常更新数据
  if(timeinfo.tm_hour==1){
    city_get();
    time_get();
  }
  weibo_get();
  yiyan_get();
  tianqiDays_get();
  tianqiNow_get();

//   todo_get(millis());
  display.setFullWindow();
  display.firstPage(); 
  display.fillScreen(GxEPD_WHITE);
  do {
  displaymain();
  time_show();
  weibo_show();
  // todo_show();
  city_show();
  tianqi_show();
  yiyan_show();
  } while (display.nextPage());
  display.powerOff();
}


