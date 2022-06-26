#include <Servo.h>
Servo servo;
#include "DHT.h"
#define dataPin 2 // Определяет номер вывода, к которому подключен датчик
DHT dht(dataPin, DHT22);          // Создает объект DHT

void setup() {
  // put your setup code here, to run once:
  servo.attach(11);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  int t = dht.readTemperature(); // Получить значение температуры 
  Serial.println(t);
  if(Serial.available()>0)
  {
    String str=Serial.readString();
    if(str.toInt()!=t and str.toInt()!=0)
    {
      int grad=90;
      if(str.toInt()>t)
        grad=map(str.toInt(), 10, 40, 90, 180);
      else grad=map(str.toInt(), 10, 40, 0, 90);
      //Serial.println(grad);
      while(Serial.available()==0)
      {
        for(int i=0;i<=180;i+=grad)
          {
            servo.write(i);
            delay(1000);
          }
        for(int i=180;i>=0;i-=grad)
          {
            servo.write(i);
            delay(1000);
          }
      }
    } else delay(2000);
  } else delay(2000);
}
