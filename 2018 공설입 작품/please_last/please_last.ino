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
int speedlimit =300;
int motorspeed=0;

char data;

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

void loop() {
  if(BTSerial.available()){ Serial.write(BTSerial.read()); }
  if(Serial.available()){ BTSerial.write(Serial.read()); }
  if(BTSerial.available())
  {
   data=BTSerial.read();
   switch(data)
   {
    case'I':
    {
     do0();
    }
    case'J' :
    {
      do1();
    }
    case'L' :
    {
      do2();
    }
    case'M':
    {
      do3();
    }
   }
  }
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
