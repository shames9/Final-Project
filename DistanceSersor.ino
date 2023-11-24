#include <Servo.h>

#define PIN_TRIG 12
#define PIN_ECHO 11
#define SERVO_PIN 10

Servo myservo;
float cm;
float temp;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  myservo.attach(SERVO_PIN);
  myservo.write(90); // 设置舵机初始角度为90度
}

void gradualMove(int currentPos, int newPos) {
  int stepDelay = 35; // 控制舵机移动速度的延迟时间，数值越大移动越慢
  if (currentPos < newPos) {
    for (int pos = currentPos; pos <= newPos; pos++) {
      myservo.write(pos);
      delay(stepDelay);
    }
  } else {
    for (int pos = currentPos; pos >= newPos; pos--) {
      myservo.write(pos);
      delay(stepDelay);
    }
  }
}

void loop() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  temp = float(pulseIn(PIN_ECHO, HIGH));
  cm = (temp * 17) / 1000;

  Serial.print("Echo = ");
  Serial.print(temp);
  Serial.print(",  Distance = ");
  Serial.print(cm);
  Serial.println("cm");

  int currentPos = myservo.read();
  if (cm < 30) {
    gradualMove(currentPos, 0); // 0度为舵机的顺时针方向
  } else {
    gradualMove(currentPos, 270); // 270度为舵机的初始位置
  }

  delay(100);
}
