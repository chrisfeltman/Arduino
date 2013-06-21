
#include<SoftwareSerial.h>

SoftwareSerial mySerial(3,4);
void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("Starting passthrough ...");
}
void loop()
{
  static byte count = 0;
 
    while(mySerial.available())
    {
      Serial.write(mySerial.read());
    }
  
  //Serial.println(count++);
  //delay(500);
}
