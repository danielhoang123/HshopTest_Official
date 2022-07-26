# DFRobot_SpeechSynthesis
- [English Version](./README.md)

让声音为你的项目增添一抹特色！连接上语音合成模块，再添加几行简单的代码就可以让您的项目开口说话。无论是中文还是英文对于语音合成模块来说都是so easy，播报当前时间，播报环境数据统统不在话下，与语音识别模块结合还可实现语音对话！该模块采用I2C和UART两种通讯方式，Gravity接口，兼容绝大部分主控。模块上已经自带了一个喇叭，所以您无需再额外的添加喇叭。
   

![正反面svg效果图](./resources/images/dfr0760.png)

## 产品链接（https://www.dfrobot.com.cn/goods-3014.html）
    DFR0760：中英文语音合成模块

## 目录

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## 概述

   1. Speech Synthesis <br>


## 库安装

使用此库前，请首先下载库文件，将其粘贴到\Arduino\libraries目录中，然后打开examples文件
夹并在该文件夹中运行演示。

## 方法

```C++
    
    
 /**
   *  @brief 语音合成函数
   *  @param word 要合成的内容，可以是中文，英文，数字等
   */
  void speak(String word);

  /**
   *  @brief 设置语音的音量大小
   *  @param voc,音量数值(0-9)
   */
  void setVoice(uint8_t voc);

  /**
   *  @brief 设置语音的播放速度
   *  @param speed,速度数值(0-9)
   */
  void setSpeed(uint8_t speed);

  /**
   *  @brief 设置音调
   *  @param tone,音调数值(0-9)
  */
  void setTone(uint8_t tone);

  /**
   *  @brief 设置英文发音
   *  @param pron(ALPHABET:以字母单个发音,WORD:以单词发音)
   */
  void setEnglishPron(eENpron_t pron);

  /**
   *  @brief 恢复默认设置
   */
  void reset();
```

## 兼容性

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino Uno        |      √       |              |             | 
FireBeetle-ESP8266        |      √       |              |             | 
FireBeetle-ESP32        |      √       |              |             | 
Arduino MEGA2560        |      √       |              |             | 
Arduino Leonardo|      √       |              |             | 
Micro:bit        |      √       |              |             | 
FireBeetle-M0        |      √       |              |             | 
Raspberry Pi      |      √       |              |             | 

## 历史

- 2021/08/12 - 1.0.0 版本


## 创作者

Written by fengli(li.feng@dfrobot.com), 2020.8.12 (Welcome to our [website](https://www.dfrobot.com/))





