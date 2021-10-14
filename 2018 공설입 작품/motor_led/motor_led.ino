#include <AFMotor.h>
#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS A5
#define BT_RXD A0
#define BT_TXD A1
SoftwareSerial BTSerial(BT_RXD,BT_TXD);
AF_DCMotor motorR(1);
AF_DCMotor motorL(2);//이게 아니면 둘이 바꾸기

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors (&oneWire);

int sp;
int degreelimit=30;
int speedlimit =180;
int motorspeed=0;
char bt_cmd;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  pinMode(A4,OUTPUT);
  sensors.begin();
  motorR.setSpeed(255);//코코아팹 한번 보기
  motorR.run(RELEASE);
  motorL.setSpeed(255);
  motorL.run(RELEASE);
}

void FOWARD()
{
  sp=100;
  if(sp>=speedlimit)
  {
    motorR.setSpeed(speedlimit);
    motorR.run(FORWARD);
    motorL.setSpeed(speedlimit);
    motorL.run(FORWARD);
  }
  else
  {
    motorR.setSpeed(sp);
    motorR.run(FORWARD);
    motorL.setSpeed(sp);
    motorL.run(FORWARD);
  }

}
void STOP()
{
  motorR.run(RELEASE);
  motorL.run(RELEASE);
}
void do0()
{
  sp=60;
  
  if(sp>=speedlimit)
  {
    motorR.setSpeed(speedlimit);
    motorR.run(FORWARD);
    motorL.setSpeed(speedlimit);
    motorL.run(FORWARD);
  }
  else
  {
    motorR.setSpeed(sp);
    motorR.run(FORWARD);
    motorL.setSpeed(sp);
    motorL.run(FORWARD);
  }
}

void do1()
{
  sp=120;
  if(sp>=speedlimit)
  {
    motorR.setSpeed(speedlimit);
    motorR.run(FORWARD);
    motorL.setSpeed(speedlimit);
    motorL.run(FORWARD);
  }
  else
  {
    motorR.setSpeed(sp);
    motorR.run(FORWARD);
    motorL.setSpeed(sp);
    motorL.run(FORWARD);
  }
}

void do2()
{
  sp=180;
  if(sp>=speedlimit)
  {
    motorR.setSpeed(speedlimit);
    motorR.run(FORWARD);
    motorL.setSpeed(speedlimit);
    motorL.run(FORWARD);
  }
  else
  {
    motorR.setSpeed(sp);
    motorR.run(FORWARD);
    motorL.setSpeed(sp);
    motorL.run(FORWARD);
  }
}
void do3()
{
  sp=255;
  if(sp>=speedlimit)
  {
    motorR.setSpeed(speedlimit);
    motorR.run(FORWARD);
    motorL.setSpeed(speedlimit);
    motorL.run(FORWARD);
  }
  else
  {
    motorR.setSpeed(sp);
    motorR.run(FORWARD);
    motorL.setSpeed(sp);
    motorL.run(FORWARD);
  }
}

void loop() 
{
  if(BTSerial.available())
  {
    bt_cmd=BTSerial.read();
    Serial.write(bt_cmd);
    if(bt_cmd=='F'){FOWARD();}
    else if(bt_cmd=='S'){STOP();}
    else if(bt_cmd=='I'){do0();}
    else if(bt_cmd=='J'){do1();}
    else if(bt_cmd=='L'){do2();}
    else if(bt_cmd=='M'){do3();}
   }
  if(Serial.available()){ BTSerial.write(Serial.read()); }
  
  sensors.requestTemperatures();
  Serial.print("Temperature is: ");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.println("Degree");
  delay(50);//온도를 재어서 Serial 모니터에 표시하라
  if(sensors.getTempCByIndex(0)>=degreelimit)//만약 온도가 36.5도 보다 높으면->나중에 측정하고 바꾸기
  {
    while(sensors.getTempCByIndex(0)>=degreelimit)
    {
    digitalWrite(A4,HIGH);
    delay(500);
    digitalWrite(A4,LOW);
    delay(500);
    }
    if(sensors.getTempCByIndex(0)<29)
      digitalWrite(A4,LOW);
  }
}

