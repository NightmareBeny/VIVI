#include "DHT.h"
#define dataPin 8 // Определяет номер вывода, к которому подключен датчик
DHT dht(dataPin, DHT22);          // Создает объект DHT
int moto3=3;
int moto4=4;

void setup() {
  // put your setup code here, to run once:
  pinMode(moto3, OUTPUT);
  pinMode(moto4, OUTPUT);
  dht.begin();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int t=dht.readTemperature();
  Serial.println(t);
  if(Serial.available()>0)
  {
    String str=Serial.readString();
    if(str.toInt()!=t and str.toInt()!=0)
    {
      if(str.toInt()<t)
      {
        while(Serial.available()==0)
        {
          //по часовой
          analogWrite(moto3, 150);
          digitalWrite(moto4, LOW);
          //delay(5000);
          //отдыхаем
          //analogWrite(moto3, 0);
          //digitalWrite(moto4, LOW);
          //delay(1000);
        }
      } else if (str.toInt()>t)
      { 
        while(Serial.available()==0)
        {
          //против часовой
          analogWrite(moto3, 150);
          digitalWrite(moto4, HIGH);
          /*delay(5000);
          //отдыхаем
          analogWrite(moto3, 0);
          digitalWrite(moto4, LOW);
          delay(1000);*/
         }
      }
    } 
    while(Serial.available()==0)
        {
          //против часовой
          analogWrite(moto3, 0);
          digitalWrite(moto4, LOW);
        }
  } delay(2000);
}
