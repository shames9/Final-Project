#include <Wire.h>
#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
const int ledPin = 10; // 连接LED的数字引脚

int previousGreenValue = 0; // 声明并初始化 previousGreenValue
int threshold = 10; // 声明并初始化 threshold

void setup(void) {
  Serial.begin(9600);

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  pinMode(ledPin, OUTPUT); // 设置LED引脚为输出
  digitalWrite(ledPin, LOW); // 初始状态下熄灭LED
}

void loop(void) {
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);

  // 打印RGB通道值
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  
  // 检测绿色通道值的变化
  if (abs(g - previousGreenValue) > threshold) {
    if (g > previousGreenValue) {
      // 绿色通道值增加，点亮LED
      digitalWrite(ledPin, HIGH); // 将LED引脚设置为高电平，点亮LED
    } else {
      // 绿色通道值减小，熄灭LED
      digitalWrite(ledPin, LOW); // 将LED引脚设置为低电平，熄灭LED
    }
    previousGreenValue = g;
  }
  
  // 其他代码（显示颜色温度、光照度等）可以继续放在这里
  
  Serial.println(" "); // 打印一行后换行
  
  delay(100); // 控制循环的执行速率，避免频繁切换LED状态
}
