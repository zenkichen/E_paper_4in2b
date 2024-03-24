# E_paper_4in2b
ESP32驱动的三色墨水屏程序，天气日历

![实物图](https://github.com/zenkichen/E_paper_4in2b/blob/main/image/e-paper.jpg)
# 项目简介
硬件是采用微雪的官方[ESP32墨水屏驱动板](https://www.waveshare.net/shop/e-Paper-ESP32-Driver-Board.htm)进行开发的。墨水屏是自己闲鱼买的电子价签拆下来的，不知道是什么型号。
## 软件开发
要感谢yanyuandi[https://github.com/yanyuandi/7.5inch_Multifunctional_E-Paper](https://github.com/yanyuandi/7.5inch_Multifunctional_E-Paper),本项目代码是在他的基础上修改出来的。但是去掉了与php服务器相关的内容，因此不能支持待办事项功能。
## 相关类库: 
在本软件开发中，主要用到了如下第三方库

Adafruit GFX: 由著名的电子硬件社区Adafruit提供的一套图形图像引擎。做各种需要显示输出的Arduino应用一般都少不了它了。

GxEPD2:基于Adafruit_GFX库来驱动各种电子墨水屏。

U8g2 for Adafruit GFX：一套基于U8g2字体引擎来通过Adafruit GFX来显示文字的第三方库。

ArduinoJSON:要处理JSON字符串现在少不了它了。
## 墨水屏显示整个逻辑介绍
第一次上电或者更换无线网络环境后，开机后会首先显示配网界面
配网成功后等待片刻，会进入整个界面，所有数据分别获取然后统一刷新
整个墨水屏会1个小时全刷一次（由于没有局刷，所以目前是整个刷新）
万年历及黄历部分采用了顶想云API，由于其免费版每天只能获取50次，因此这部分数据每天只在凌晨1点多获取一次。
一言api每次刷新都会改变内容
# 关于网页数据获取的API
使用前修改data.h里相关的API的Key部分，如下

String seniverse_key="you_api";//知心天气API Key

char topthink_key[]="you_api";//顶想云API Key

