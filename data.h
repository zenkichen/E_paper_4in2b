#ifndef _DATA_H_
#define _DATA_H_
#include <Time.h>

String seniverse_key="S2TNa6gPEQwUNnc-9";//知心天气API Key
char topthink_key[]="9af58a92-ce57-4e76-aadf-fa7a49a7290d";//顶想云API Key

// 定义 DataItem 结构体
struct DataItem {
  String yiyan;//一言

  String animalsYear;//"龙",
  String weekday ;//"星期六",
  String lunarYear;//"甲辰年",
  String lunar;//"二月十四",
  String yearMonth;//"2024-3",
  String date;//"2024-3-23",
  String suit;//"结婚.出行.搬家.签订合同.交易.开业.动土.安床.祭祀.修造.入殓.移柩.成人礼.收养子女.破土",
  String avoid;//"安葬.作灶.开光.斋醮",
  String holiday;
  String desc;
  String id;
  String yangli;

  String yinli;
  String wuxing;
  String chongsha;
  String baiji;
  String jishen;
  String yi;
  String xiongshen;
  String ji;

  String publicIP;//公网IP
  String city;//"南京",
  String region;//"JS",
  String regionName;//"江苏省",
  String lat;//32.0607,
  String lon;//118.763,
  String isp;//"Chinanet",
  
  String weather;//天气现象文字
  String codeNow;//天气现象代码
  String temperature;//温度，单位为c摄氏度或f华氏度
  String textDay;//白天天气现象文字
  String codeDay;//白天天气现象代码
  String textNight;//晚间天气现象文字
  String codeNight;//晚间天气现象代码
  String high;//当天最高温度
  String low;//当天最低温度
  String rainfall;//降水量，单位mm
  String precip;//降水概率，范围0~1，单位百分比（目前仅支持国外城市）
  String windDirection;//风向文字
  String windDirectionDegree;//风向角度，范围0~360
  String windSpeed;//风速，单位km/h（当unit=c时）、mph（当unit=f时）
  String windScale;//风力等级
  String humidity;//相对湿度，0~100，单位为百分比
};

DataItem item;
struct tm timeinfo;

#endif