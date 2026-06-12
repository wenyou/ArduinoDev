int pushButton = 2;//D2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);//串口通讯初始化，每秒9600位

  //设置按键引脚为输入
  pinMode(pushButton, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //读取输入引脚
  int buttonState = digitalRead(pushButton);

  //显示按键转态
  Serial.println(buttonState);

  delay(500);//短暂停止
}
