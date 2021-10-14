#include <SoftwareSerial.h>
#define BT_RXD A2
#define BT_TXD A3
SoftwareSerial BTSerial(BT_RXD,BT_TXD);
char bt_cmd;
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
    bt_cmd=BTSerial.read();
    Serial.write(bt_cmd);
    if(bt_cmd=='F')
    {
      Serial.write("foward");
    }
  }
  if(Serial.available())
  {
    BTSerial.write(Serial.read());
  }
}
