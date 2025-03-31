#include <Adafruit_NeoPixel.h>

#define LED_PIN    6 // LED灯带数据引脚连接到Arduino的D6
#define NUM_LEDS   30 // 根据你的LED灯带实际数量调整
#define SENSOR1_PIN 2 // 第一个传感器连接到Arduino的D2
#define SENSOR2_PIN 3 // 第二个传感器连接到Arduino的D3
#define RELAY_PIN  4  // 继电器控制引脚连接到Arduino的D4

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

unsigned long previousMillis = 0; // 上次点亮时间
const long interval = 3000; // 延迟时间5秒

void setup() {
  // put your setup code here, to run once:
  pinMode(SENSOR1_PIN, INPUT); // 设置第一个传感器引脚为输入模式
  pinMode(SENSOR2_PIN, INPUT); // 设置第二个传感器引脚为输入模式
  pinMode(RELAY_PIN, OUTPUT); // 设置继电器控制引脚为输出模式
  digitalWrite(RELAY_PIN, LOW); // 默认关闭继电器
  strip.begin(); // 初始化NeoPixel strip
  strip.show(); // 初始化所有像素为'off'
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();
  if (digitalRead(SENSOR1_PIN) == LOW || digitalRead(SENSOR2_PIN) == LOW) { // 当任一传感器检测到物体时
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
  }/* else {
    //障碍物移开立马熄灭LED（关闭电源）
    digitalWrite(RELAY_PIN, LOW); // 关闭继电器，断开LED供电
    strip.clear(); // 清除所有像素
    strip.show();
  }*/

  // 如果障碍物移开后三秒才熄灭LED（关闭电源），则使用下面的代码，注销上面的 else 部分代码。
  // 如果超过10秒且传感器不再被触发，则关闭LED
  if ((currentMillis - previousMillis >= interval) && (digitalRead(SENSOR1_PIN) != LOW && digitalRead(SENSOR2_PIN) != LOW)) {
    digitalWrite(RELAY_PIN, LOW); // 关闭继电器，断开LED供电
    strip.clear(); // 清除所有像素
    strip.show();
  }
}

