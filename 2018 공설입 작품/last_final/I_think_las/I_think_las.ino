#include <AFMotor.h>
#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS A5
#define BT_RXD A1
#define BT_TXD A2
SoftwareSerial BTSerial(BT_RXD,BT_TXD);
AF_DCMotor motorR(1);
AF_DCMotor motorL(2);//이게 아니면 둘이 바꾸기

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors (&oneWire);

int sp=0;
int degreelimit=10;
int speedlimit =300;
int motorspeed=0;
char bt_cmd;
int way;
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
  way=1;
}
void BACK()
{
  way=0;
}
void STOP()
{
  sp=0;
  motorR.run(RELEASE);
  motorL.run(RELEASE);
}
void EXCEL()
{
  sp=sp+1;
  if(sp<0){sp=0;}
  if(sp>4){sp=4;}
  if(way==1)
  {
    if(sp*60+15>=speedlimit)
    {
    motorR.setSpeed(speedlimit);
    motorR.run(FORWARD);
    motorL.setSpeed(speedlimit);
    motorL.run(FORWARD); 
    }
    else
    {
      motorR.setSpeed(sp*60+15);
      motorR.run(FORWARD);
      motorL.setSpeed(sp*60+15);
      motorL.run(FORWARD);
    }
  }
  else if(way==0)
  {
    if(sp*60+15>=speedlimit)
    {
      motorR.setSpeed(speedlimit);
      motorR.run(BACKWARD);
      motorL.setSpeed(speedlimit);
      motorL.setSpeed(BACKWARD);
    }
    else 
    {
      motorR.setSpeed(sp*60+15);
      motorR.run(BACKWARD);
      motorL.setSpeed(sp*60+15);
      motorL.run(BACKWARD);
    }
  }
}
void doBRAKE()
{
  sp=sp-1;
  if(sp<0){sp=0;}
  if(sp>4){sp=4;}
  if(way==1)
  {
    if(sp*60+15>=speedlimit)
    {
      motorR.setSpeed(speedlimit);
      motorR.run(FORWARD);
      motorL.setSpeed(speedlimit);
      motorL.run(FORWARD); 
    }
    else
    {
      motorR.setSpeed(sp*60+15);
      motorR.run(FORWARD);
      motorL.setSpeed(sp*60+15);
      motorL.run(FORWARD);
    }
  }
  else if(way==0)
  {
    if(sp*60+15>=speedlimit)
    {
      motorR.setSpeed(speedlimit);
      motorR.run(BACKWARD);
      motorL.setSpeed(speedlimit);
      motorL.setSpeed(BACKWARD);
    }
    else 
    {
      motorR.setSpeed(sp*60+15);
      motorR.run(BACKWARD);
      motorL.setSpeed(sp*60+15);
      motorL.run(BACKWARD);
    }
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
    else if(bt_cmd=='B'){BACK();}
    else if(bt_cmd=='E'){EXCEL();}
    else if(bt_cmd=='b'){doBRAKE();}
   }
  if(Serial.available()){ BTSerial.write(Serial.read()); }
  
  sensors.requestTemperatures();
 // Serial.print("Temperature is: ");
  //Serial.print(sensors.getTempCByIndex(0));
 // Serial.println("Degree");
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
    if(sensors.getTempCByIndex(0)<degreelimit)
      digitalWrite(A4,LOW);
  }
}
