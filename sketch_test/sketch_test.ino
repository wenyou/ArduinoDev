#include <Adafruit_NeoPixel.h>
#define LED_PIN    6 // 数据引脚连接到Arduino的D6
#define NUM_LEDS   30 // 假设有8个LED，根据实际情况调整
#define SENSOR_PIN 2 // 传感器连接到Arduino的D2

//传感器配置
int sensorPin1 = 2;//红外传感器1接D2
int sensorPin2 = 3;//红外传感器2接D3

//继电器配置
int relayPin = 4;//继电器控制引脚接D4

// 当前显示的颜色索引
int colorIndex = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

//初始化设置（启动设置）
void setup() {
  // put your setup code here, to run once:
  pinMode(SENSOR_PIN, INPUT);
  //pinMode(sensorPin2, INPUT);
  strip.begin(); // 初始化NeoPixel strip
  strip.show(); // 初始化所有像素为'off'

  //pinMode(relayPin, OUTPUT);

  //继电器初始断开（根据模块逻辑调整）
  //digitalWrite(relayPin, HIGH);

  //digitalWrite(5,LOW);
}

int i = 0;
int pin5 = 5;
//循环运行
void loop() {
   if (digitalRead(SENSOR_PIN) == LOW) { // 当传感器检测到物体时
   //循环遍历所有LED
    for(int i=0; i<NUM_LEDS; i++) {
      //strip.setPixelColor(i, strip.Color(255,0,0)); // 设置颜色为红色
      switch (i % 3) {
        case 1:
          strip.setPixelColor(i, strip.Color(0,0,255)); // 设置颜色为绿色
          break;
        case 2:
          strip.setPixelColor(i, strip.Color(0,255,0)); // 设置颜色为蓝色
          break;
        case 0:
          strip.setPixelColor(i, strip.Color(255,0,0)); // 设置颜色为红色
          break;
        }
      
    }
    strip.show();

    // 跑马灯效果
    for(int i=0; i<NUM_LEDS; i++) {
      // 根据当前颜色索引设置颜色
      switch(colorIndex % 3) {
        case 0:
          strip.setPixelColor(i, strip.Color(255, 0, 0)); // 红色
          break;
        case 1:
          strip.setPixelColor(i, strip.Color(0, 255, 0)); // 绿色
          break;
        case 2:
          strip.setPixelColor(i, strip.Color(0, 0, 255)); // 蓝色
          break;
      }
      strip.show();
      delay(100); // 延迟一段时间以便观察颜色变化
    }
    colorIndex++; // 更新颜色索引
    // end 跑马灯效果
  } else {
    strip.clear(); // 清除所有像素
    strip.show();
    colorIndex = 0; // 重置颜色索引
  }


  // if(i < 10) {
  //     digitalWrite(pin5,HIGH);
  //     delay(500);
  //     digitalWrite(pin5,LOW);
  //     delay(500);
  // }
  // i++;

  // put your main code here, to run repeatedly:
  // 无障碍=HIGH，有障碍=LOW
  //int sensor1 = digitalRead(sensorPin1);
  //int sensor2 = digitalRead(sensorPin2);

  //任意传感器触发
  /*if(sensor1 == LOW || sensor2 == LOW) {
    //继电器吸合（点亮LED）
    digitalWrite(relayPin, LOW);

    //保持3秒
    delay(3000); 

    //关闭继电器
    digitalWrite(relayPin, HIGH);
  }*/
  // int i = 0;
  // while(i < 100) {
  //   if(i / 2 == 0) {
  //     digitalWrite(5,HIGH);
      
  //   } else {
  //     digitalWrite(5,LOW);
  //   }
    
  //   i++;
  // }
  
  
}
