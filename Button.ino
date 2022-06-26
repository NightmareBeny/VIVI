int ledPin=11;
int button=13;
int ledLevel=0; //для PWM
bool lastButton=LOW;
bool currentButton=LOW;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin,OUTPUT); //Pin11 выдаёт PWM сигнал
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  currentButton=fixButton(lastButton);
  if(!lastButton && currentButton)
       ledLevel+=70;
  lastButton=currentButton;
  if(ledLevel>255) ledLevel=0;
  analogWrite(ledPin,ledLevel);
  Serial.println(ledLevel);
}

bool fixButton(bool lastButton) //функция, убирающая дребезг кнопки
{
  bool currentButton=digitalRead(button);
  if(lastButton!=currentButton)
  {
    delay(5);
    currentButton=digitalRead(button);
  }
  return currentButton;
}
