/**
设置4个传感器，任意触发一个传感器可编程LED灯带就会点亮。
*/
#include <Adafruit_NeoPixel.h>

#define LED_PIN    6 // LED灯带数据引脚连接到Arduino的D6
#define NUM_LEDS   30 // 根据你的LED灯带实际数量调整
#define SENSOR1_PIN 2 // 第一个传感器连接到Arduino的D2
#define SENSOR2_PIN 3 // 第二个传感器连接到Arduino的D3
#define SENSOR3_PIN 7 // 第3个传感器连接到Arduino的D7
#define SENSOR4_PIN 8 // 第4个传感器连接到Arduino的D8
//#define RELAY_PIN  4  // 继电器控制引脚连接到Arduino的D4

// 传感器检测参数
#define SENSOR_CHECK_INTERVAL 5000  // 每5秒检测一次传感器状态
#define SENSOR_TIMEOUT 1000         // 传感器响应超时时间(ms)

/**
  The purpose of this project is to realize the function of automatically lighting up the programmable LED belt when any obstacle avoidance sensor is triggered.
  本项目旨在实现当任意避障传感器被触发时，可编程LED灯带自动亮起的功能。
 **/

//LED灯带定义
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// unsigned long previousTriggerTime = 0;  // 上次触发时间
// const long lightDuration = 3000;       // 点亮持续时间(ms)
// unsigned long lastSensorCheck = 0;     // 上次传感器检测时间

// 传感器状态结构体
// struct Sensor {
//   int pin;
//   bool isActive;    // 传感器是否有效
//   bool lastState;   // 上次检测状态
//   unsigned long lastResponseTime; // 最后响应时间
// };

// Sensor sensors[4] = {
//   {SENSOR1_PIN, true, HIGH, 0},
//   {SENSOR2_PIN, true, HIGH, 0},
//   {SENSOR3_PIN, true, HIGH, 0},
//   {SENSOR4_PIN, true, HIGH, 0}
// };

//
unsigned long previousMillis = 0; // 上次点亮时间
const long interval = 3000; // 亮灯后，移除障碍物，延迟时间3秒后关灯

void setup() {
  // 初始化串口用于调试
  //Serial.begin(9600);

  // 初始化传感器引脚
  // for(int i=0; i<4; i++) {
  //   pinMode(sensors[i].pin, INPUT_PULLUP);
  // }

  // 传感器 初始化
  /*pinMode(SENSOR1_PIN, INPUT); // 设置第一个传感器引脚为输入模式
  pinMode(SENSOR2_PIN, INPUT); // 设置第二个传感器引脚为输入模式
  pinMode(SENSOR3_PIN, INPUT);
  pinMode(SENSOR4_PIN, INPUT);*/
  pinMode(SENSOR1_PIN, INPUT_PULLUP); // 设置第一个传感器引脚为输入模式，使用内部上拉电阻
  pinMode(SENSOR2_PIN, INPUT_PULLUP); // 设置第二个传感器引脚为输入模式，使用内部上拉电阻
  pinMode(SENSOR3_PIN, INPUT_PULLUP); // 设置第三个传感器引脚为输入模式，使用内部上拉电阻
  pinMode(SENSOR4_PIN, INPUT_PULLUP); // 设置第四个传感器引脚为输入模式，使用内部上拉电阻

  //没有单独给LED灯配置电源，此继电器可以去掉
  //pinMode(RELAY_PIN, OUTPUT); // 设置继电器控制引脚为输出模式
  //digitalWrite(RELAY_PIN, LOW); // 默认关闭继电器

  //LED灯带初始化
  strip.begin(); // 初始化NeoPixel strip
  strip.show(); // 初始化所有像素为'off'

  //Serial.println("System initialized");
}

void loop() {
  unsigned long currentMillis = millis();

  bool sensorTriggered = false;//传感器是否被触发，false未触发
  int activeSensors = 0;//有效传感器数量

   // 检查各传感器状态，并计数有效传感器数量，防止传感器故障或断电
  int sensors[] = {SENSOR1_PIN, SENSOR2_PIN, SENSOR3_PIN, SENSOR4_PIN};
  for (int i = 0; i < 4; i++) {
    if (digitalRead(sensors[i]) == LOW) {
      sensorTriggered = true;
      //Serial.print("sensorTriggered true:");
      //Serial.println(i+1);
    }
    if (digitalRead(sensors[i]) != HIGH) { //如果不是高电平，则认为传感器是有效的（即连接或触发）
      activeSensors++;
    }
    //Serial.print(i+1);
    //Serial.print(" status:");
    //Serial.println(digitalRead(sensors[i]));
    
    /*if (digitalRead(sensors[i]) != LOW) { // 计算未触发的传感器数量，即认为是有效的
      activeSensors++;
    }*/
  }
  //Serial.print("activeSensors:");
  //Serial.println(activeSensors);
  //delay(2000);

   //如果有任意一个传感器被触发并且至少有一个传感器是有效的&& activeSensors > 0
  if (sensorTriggered) {
    //digitalWrite(RELAY_PIN, HIGH); // 打开继电器，给LED供电
    for(int i=0; i<NUM_LEDS; i++) {
      switch (i % 3) {
        case 0:
          strip.setPixelColor(i, strip.Color(255,0,0)); // 红色
          //strip.setPixelColor(i, strip.Color(100,200,0));
          break;
        case 1:
          strip.setPixelColor(i, strip.Color(255,200,0)); // 橙色
          break;
        case 2:
          strip.setPixelColor(i, strip.Color(255,0,255)); // 紫色
          break;
      }
    }
    strip.show();
    previousMillis = currentMillis; // 更新上次点亮时间为当前时间
  } else if ((currentMillis - previousMillis >= interval) && !sensorTriggered) {
    //digitalWrite(RELAY_PIN, LOW); // 关闭继电器，断开LED供电
    strip.clear(); // 清除所有像素
    strip.show();
  }

  /*
  // 定期检查传感器状态
  if(currentMillis - lastSensorCheck >= SENSOR_CHECK_INTERVAL) {
    checkSensors();
    lastSensorCheck = currentMillis;
  }

  // 检测传感器触发
  bool anyTriggered = false;
  int activeCount = 0;

  for(int i=0; i<4; i++) {
    if(sensors[i].isActive) {
      activeCount++;
      if(digitalRead(sensors[i].pin) == LOW) {
        anyTriggered = true;
        sensors[i].lastResponseTime = currentMillis;
      }
    }
  }

  // 如果有有效传感器被触发
  if(anyTriggered && activeCount > 0) {
    //digitalWrite(RELAY_PIN, HIGH);
    setRainbowPattern();
    strip.show();
    previousTriggerTime = currentMillis;
  } 
  // 如果超过点亮时间且没有新触发
  else if(currentMillis - previousTriggerTime >= lightDuration) {
    //digitalWrite(RELAY_PIN, LOW);
    strip.clear();
    strip.show();
  }*/

  /*if (digitalRead(SENSOR1_PIN) == LOW || digitalRead(SENSOR2_PIN) == LOW || digitalRead(SENSOR3_PIN) == LOW || digitalRead(SENSOR4_PIN) == LOW) { // 当任一传感器检测到物体时
    digitalWrite(RELAY_PIN, HIGH); // 打开继电器，给LED供电
    for(int i=0; i<NUM_LEDS; i++) {
      strip.setPixelColor(i, strip.Color(255,0,0)); // 设置颜色为红色
      switch (i % 3) {
        case 1:
            strip.setPixelColor(i, strip.Color(255,200,0)); // 设置颜色为红色
        break;
        case 2:
            strip.setPixelColor(i, strip.Color(255,0,255)); // 设置颜色为红色 
        break;
        case 0:
          strip.setPixelColor(i, strip.Color(100,200,0)); // 设置颜色为红色
        break;
      }
    }
    strip.show();
    previousMillis = currentMillis; // 更新上次点亮时间为当前时间
  }*//* else {
    //障碍物移开立马熄灭LED（关闭电源）
    digitalWrite(RELAY_PIN, LOW); // 关闭继电器，断开LED供电
    strip.clear(); // 清除所有像素
    strip.show();
  }*/

  // 如果障碍物移开后三秒才熄灭LED（关闭电源），则使用下面的代码，注销上面的 else 部分代码。
  // 如果超过10秒且传感器不再被触发，则关闭LED
  /*if ((currentMillis - previousMillis >= interval) && (digitalRead(SENSOR1_PIN) != LOW && digitalRead(SENSOR2_PIN) != LOW && digitalRead(SENSOR3_PIN) != LOW && digitalRead(SENSOR4_PIN) != LOW)) {
    digitalWrite(RELAY_PIN, LOW); // 关闭继电器，断开LED供电
    strip.clear(); // 清除所有像素
    strip.show();
  }*/
}

// 检查传感器状态
/*void checkSensors() {
  Serial.println("Checking sensors...");
  
  for(int i=0; i<4; i++) {
    bool currentState = digitalRead(sensors[i].pin);
    Serial.print(i+1);
    Serial.print(" status:");
    Serial.println(currentState);
    
    // 如果状态发生变化，说明传感器正常 currentState != sensors[i].lastState
    if(currentState != sensors[i].lastState) {
      sensors[i].isActive = true;
      sensors[i].lastState = currentState;
      sensors[i].lastResponseTime = millis();
      //Serial.print("Sensor ");
      //Serial.print(i+1);
      //Serial.println(" is active");
    } 
    // 如果长时间无响应，标记为失效
    else if(millis() - sensors[i].lastResponseTime > SENSOR_TIMEOUT) {
        sensors[i].isActive = false;
        Serial.print("Sensor ");
        Serial.print(i+1);
        Serial.println(" is inactive!");
    }
  }
}*/

// 设置彩虹灯效
/*void setRainbowPattern() {
  for(int i=0; i<NUM_LEDS; i++) {
    switch(i % 3) {
      case 0: strip.setPixelColor(i, strip.Color(255,0,0)); break;    // 红
      case 1: strip.setPixelColor(i, strip.Color(255,200,0)); break;  // 橙
      case 2: strip.setPixelColor(i, strip.Color(255,0,255)); break; // 紫
    }
  }
}*/
