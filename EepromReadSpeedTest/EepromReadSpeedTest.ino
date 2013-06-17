#include <Wire.h>

void setup()
{
  Serial.begin(115200);
  int bytesRead = 0;
  Wire.begin();
  delay(5);
  
  Wire.beginTransmission(0x50);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.endTransmission();
  
  Wire.requestFrom(0x50,64);
  unsigned long starttime = micros();
  while(Wire.available())
  {  
     Wire.read();
     bytesRead++;
  }
  unsigned long stoptime = micros();
  Serial.print("Read ");
  Serial.print(bytesRead);
  Serial.print(" bytes in ");
  Serial.print(stoptime - starttime);
  Serial.println(" microseconds"); 

}

void loop()
{
  tone(5, 131);
  delay(500);
  tone(5, 147);
  delay(500);
  tone(5,165);
  delay(500);
  tone(5,175);
  delay(500);
  tone(5,196);
  delay(500);
  tone(5,220);
  delay(500);
  tone(5,247);
  delay(500);
  tone(5,262);
  delay(500);
}
