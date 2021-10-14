#include <SoftwareSerial.h> // 블루투스 통신을 위한 SoftwareSerial 라이브러리
#include <Servo.h> // 서보모터를 제어하기 위한 라이브러리
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 5//숫자는 핀번호 의미 연결하고 바꾸기
#define BT_RXD 6
#define BT_TXD 7

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors (&oneWire);

SoftwareSerial BTSerial(BT_RXD, BT_TXD); // SoftwareSerial(RX, TX)
byte buffer[1024]; // 데이터 수신 버퍼
int bufferPosition; // 버퍼에 기록할 위치

Servo servo;

int dcMotor = 12;
int dcSpeed = 3;
// DC모터의 움직임을 제어하는 핀(12)과 속도를 제어하는 핀(3)

//int motorAngle = 0;
int motorSpeed = 0;
// 서보모터의 각도와, DC모터의 속도

void setup ()
{
 // servo.attach(5); // 5번핀에 연결된 서보모터
  pinMode(dcMotor, OUTPUT);
  pinMode(2,OUTPUT);//d2에 led 연결

  BTSerial.begin(9600);
  Serial.begin(9600);//윗줄하고 순서가 바뀌었지만 이유는 모르겠음
  bufferPosition = 0;
  sensors.begin();

}

void loop ()
{
  if (BTSerial.available())
  { // 블루투스 통신이 가능할 경우
    byte data = BTSerial.read();
    buffer[bufferPosition++] = data; 
    // 블루투스에서 받아온 값을 byte data에 저장
    Serial.println(data);
    
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
        speedSet(-60);
        break;
      
      case 'i': // -30도 버튼을 눌렀을 경우, 속도 2번째
        speedSet(-30);
        break;
        
      case 'k': // 0도 버튼을 눌렀을 경우,속도 3번째
         speedSet(0);
         break;
         
       case 'o': // 30도 버튼을 눌렀을 경우,속도 4번째
         speedSet(30);
         break;
         
       case 'l': // 60도 버튼을 눌렀을 경우,속도 5번째
         speedSet(60);
         break;
         
       case 'F': // Forward 토글버튼을 눌렀을 경우(토글버튼에 불이 켜졌을 경우) 모터를 정방향으로 돌림
         motorDirection(0, motorSpeed);
         break;
         
       case 'f': // Forward 토글버튼을 눌렀을 경우(토글버튼에 불이 꺼졌을 경우) 모터를 멈춤
         motorDirection(0, 0);
         break;

       case 'B': // Back 버튼을 눌렀을 경우(토글버튼에 불이 켜졌을 경우) 모터를 역방향으로 돌림
         motorDirection(1, motorSpeed);
         break;
         
       case 'b': // Back 버튼을 눌렀을 경우(토글버튼에 불이 꺼졌을 경우) 모터를 멈춤
         motorDirection(1, 0);
         break;
         
       case '\n': // 문장이 끝낫을 경우
         bufferPosition = 0;
         break;
    }
  }//if 문 끝

  sensors.requestTemperatures();
  Serial.print("Temperature is: ");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.println("Degree");
  delay(500);//온도를 재어서 Serial 모니터에 표시하라
  if(sensors.getTempCByIndex(0)>=36.5)//만약 온도가 36.5도 보다 높으면->나중에 측정하고 바꾸기
  {
    while(1)
    {
    digitalWrite(2,HIGH);
    delay(500);
    digitalWrite(2,LOW);
    delay(500);
    if(sensors.getTempCByIndex(0)<36.5)
      {
        digitalWrite(2,LOW);
        break;
      }
    }
  }
  else
  {
    digitalWrite(2,LOW);
  }
}

void speedSet(int angle) 
{ // 프로그레스바에 맞는 값을 읽어 모터의 속도를 조절하는 함수
  if (angle == 60 )
  {
     motorSpeed = (buffer[0]-48)*256 + (buffer[1]-48)*64 + (buffer[2]-48)*16+(buffer[3]-48)*4+(buffer[4]);
  }
  else if (angle==30)
  {
    motorSpeed = (buffer[0]-48)*64 + (buffer[1]-48)*16+(buffer[2]-48)*4+(buffer[3]-48);
  } 
  else if (angle==0)
  {
    motorSpeed = (buffer[0] - 48)*16+(buffer[2]-48)*4+(buffer[3]-48);
  }
  else if(angle ==-30)
  {
    motorSpeed = (buffer[0]-48)*4+(buffer[1]);
  }
  else if(angle == -60)
  {
    motorSpeed = (buffer[0]-48) ;
  }
  analogWrite(dcSpeed, motorSpeed);
}
/*
void angleSet(boolean flag)
{ // 스마트폰에 기울기를 읽어 서보모터의 각도를 조절하는 함수
  if(buffer[0] != 10)
  {
    if (bufferPosition == 4)
    {
       motorAngle = (buffer[0]-48)*100 + (buffer[1]-48)*10 + (buffer[2]-48);
    }
    else if (bufferPosition == 3)
    {
      motorAngle = (buffer[0]-48)*10 + (buffer[1]-48);
    }
    else if (bufferPosition == 2) 
    {
      motorAngle = buffer[0] - 48;
    }

    if(flag){ // flag가 0이면 왼쪽(기울기가 양수), flag가 1이면 오른쪽(기울기가 음수)
      motorAngle *= -1;
    }
  
   Serial.print("motorAngle = ");
   Serial.println(motorAngle);
   
   motorAngle = map(motorAngle, 150, -150, 30, 150); // 서보모터의 각도로 범위를 재지정 해줌
   servo.write(motorAngle);
  }
}

void angleWrite(int angle){ // 서보모터의 각도 조절
  servo.write(angle); 
}
*/
void motorDirection(boolean dir, int speedVal) { // Dc모터의 방향 및 속도 제어
  motorSpeed = speedVal;
  
  if (dir == 0) {
    digitalWrite(dcMotor, HIGH);
  } else {
    digitalWrite(dcMotor, LOW);
  }

  analogWrite(dcSpeed, motorSpeed);
}
