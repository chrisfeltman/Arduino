#include <SevenSegShiftReg.h>
int dataPin = 2;        //Define which pins will be used for the Shift Register control
int latchPin = 3;
int clockPin = 4;

// set up the 16 bit shift register object
SevenSegShiftReg reg = SevenSegShiftReg(dataPin, latchPin, clockPin); 

void setup()
{
  pinMode(dataPin, OUTPUT);       //Configure each IO Pin
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void loop()
{
  for(int i = 0; i < 256; i++)
  {
    Serial.print("count is ");
    Serial.println(i);
    reg.displayByte(i);
    delay(200);
  }
}
