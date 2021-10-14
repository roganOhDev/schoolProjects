#include <SoftwareSerial.h>
#define BT_RXD 10
#define BT_TXD 11
SoftwareSerial BTSerial(BT_RXD,BT_TXD);
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  BTSerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(BTSerial.available())
  {
    Serial.write(BTSerial.read());
  }
  if(Serial.available())
  {
    BTSerial.write(Serial.read());
  }
}
