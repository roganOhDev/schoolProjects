#include <AFMotor.h>
#include <SoftwareSerial.h> // 블루투스 통신을 위한 SoftwareSerial 라이브러리
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS A5 //숫자는 핀번호 의미 연결하고 바꾸기
#define BT_RXD A0
#define BT_TXD A1
SoftwareSerial BTSerial(BT_RXD,BT_TXD);
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors (&oneWire);


byte buffer[1024]; // 데이터 수신 버퍼
int bufferPosition; // 버퍼에 기록할 위치

int sp;
int speedlimit=300;
//int dcMotor = 12;
//int dcSpeed = 3;
// DC모터의 움직임을 제어하는 핀(12)과 속도를 제어하는 핀(3)

//int motorAngle = 0;
int motorSpeed = 0;
// 서보모터의 각도와, DC모터의 속도

void setup ()
{
 // servo.attach(5); // 5번핀에 연결된 서보모터
  pinMode(A4,OUTPUT);//d2에 led 연결

  BTSerial.begin(9600);
  Serial.begin(9600);//윗줄하고 순서가 바뀌었지만 이유는 모르겠음
 // bufferPosition = 0;
  sensors.begin();
  motor1.setSpeed(0);
  motor1.run(RELEASE);
  motor2.setSpeed(0);
  motor2.run(RELEASE);
}

void loop ()
{
    if(Serial.available())
  {
    
    BTSerial.write(Serial.read());
  }
  
  if (BTSerial.available())
  { // 블루투스 통신이 가능할 경우
    byte data = BTSerial.read();
    //buffer[bufferPosition++] = data; 
    // 블루투스에서 받아온 값을 byte data에 저장
    Serial.write(data);
    
    switch(data)
    { // 블루투스에서 받아온 값에 따라 맞는 동작을 함
      /*case 'q':  // q일경우 프로그레스바에 값을 속도로 
        speedSet();
        break;
        
      case 'w': // 스마트폰의 기울기(양수)에 따라 서보모터 각도 제어
        angleSet(0);
        break;
       
      case 'e':  // 스마트폰의 기울기(음수)에 따라 서보모터 각도 제어
        angleSet(1);
        break;
        */
      case 'j': // -60도 버튼을 눌렀을 경우, 속도 가장 느림
       {
        sp=50;
        Serial.write("dk");
        if(sp>=speedlimit)
        {
          motor1.run(BACKWARD);
          motor1.setSpeed(speedlimit);
          motor2.run(BACKWARD);
          motor2.setSpeed(speedlimit);
        }   
        else
        {
          motor1.run(BACKWARD);
          motor1.setSpeed(sp);
          motor2.run(BACKWARD);
          motor2.setSpeed(sp); 
        }
        break;
       }
      
      case 'i': // -30도 버튼을 눌렀을 경우, 속도 2번째
       {
        sp=100;
        if(sp>=speedlimit)
        {
          motor1.run(BACKWARD);
          motor1.setSpeed(speedlimit);
          motor2.run(BACKWARD);
          motor2.setSpeed(speedlimit);
        }
        else
        {
          motor1.run(BACKWARD);
          motor1.setSpeed(sp);
          motor2.run(BACKWARD);
          motor2.setSpeed(sp);
        }
        break;
       }
        
      case 'k': // 0도 버튼을 눌렀을 경우,속도 3번째
        {
          sp=150;
         if(sp>=speedlimit)
        {
          motor1.run(FORWARD);
          motor1.setSpeed(speedlimit);
          motor2.run(FORWARD);
          motor2.setSpeed(speedlimit);
        }
        else
        {
          motor1.run(FORWARD);
          motor1.setSpeed(sp);
          motor2.run(FORWARD);
          motor2.setSpeed(sp);
        }
         break;
        }
         
       case 'o': // 30도 버튼을 눌렀을 경우,속도 4번째
         {
          sp=200;
         if(sp>=speedlimit)
        {
          motor1.run(BACKWARD);
          motor1.setSpeed(speedlimit);
          motor2.run(BACKWARD);
          motor2.setSpeed(speedlimit);
        }
        else
        {
          motor1.run(FORWARD);
          motor1.setSpeed(sp);
          motor2.run(FORWARD);
          motor2.setSpeed(sp);
        }
         break;
         }
         
       case 'l': // 60도 버튼을 눌렀을 경우,속도 5번째
         {
          sp=250;
          if(sp>=speedlimit)
          {
           motor1.run(FORWARD);
           motor1.setSpeed(speedlimit);
           motor2.run(FORWARD);
           motor2.setSpeed(speedlimit);
          }
          else
          {
           motor1.run(FORWARD);
           motor1.setSpeed(sp);
           motor2.run(FORWARD);
           motor2.setSpeed(sp);
          }
         break;
         }
         
       case 'F': // Forward 토글버튼을 눌렀을 경우(토글버튼에 불이 켜졌을 경우) 모터를 정방향으로 돌림
         {
          sp=150;
          if(sp>=speedlimit)
          {
           motor1.run(FORWARD);
           motor1.setSpeed(speedlimit);
           motor2.run(FORWARD);
           motor2.setSpeed(speedlimit);
          }
          else
          {
           motor1.run(FORWARD);
           motor1.setSpeed(sp);
           motor2.run(FORWARD);
           motor2.setSpeed(sp);
          }
         break;
         }
         
       case 'f': // Forward 토글버튼을 눌렀을 경우(토글버튼에 불이 꺼졌을 경우) 모터를 멈춤
         {
          motor1.run(RELEASE);
          motor1.setSpeed(0);
          motor2.run(RELEASE);
          motor2.setSpeed(0);
          break;
         }

       case 'B': // Back 버튼을 눌렀을 경우(토글버튼에 불이 켜졌을 경우) 모터를 역방향으로 돌림
        {
          sp=150;
          if(sp>=speedlimit)
          {
           motor1.run(BACKWARD);
           motor1.setSpeed(speedlimit);
           motor2.run(BACKWARD);
           motor2.setSpeed(speedlimit);
          }
          else
          {
           motor1.run(BACKWARD);
           motor1.setSpeed(sp);
           motor2.run(BACKWARD);
           motor2.setSpeed(sp);
          }
         break;
        }
         
       case 'b': // Back 버튼을 눌렀을 경우(토글버튼에 불이 꺼졌을 경우) 모터를 멈춤
         {
          motor1.run(RELEASE);
          motor1.setSpeed(0);
          motor2.run(RELEASE);
          motor2.setSpeed(0);
         break;
         }
         
       case '\n': // 문장이 끝낫을 경우
         {
          bufferPosition = 0;
         break;
         }
    }
  }//if 문 끝


  sensors.requestTemperatures();
  Serial.print("Temperature is: ");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.println("Degree");
  delay(5000);//온도를 재어서 Serial 모니터에 표시하라
  if(sensors.getTempCByIndex(0)>=36.5)//만약 온도가 36.5도 보다 높으면->나중에 측정하고 바꾸기
  {
    while(sensors.getTempCByIndex(0)>=29)
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
  



