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
  // counting 00 to FF
  for(int i = 0; i < 256; i++)
  {
    reg.displayByte(i);
    delay(200);
  }
  
  // blank display
  reg.clearDisplay();
  delay(500);
  
  // blink display
  showBlink(0x00, 5);
  showBlink(0x11, 5);
  showBlink(0x22, 5);
  showBlink(0x33, 5);
  showBlink(0x44, 5);
  showBlink(0x55, 5);
  showBlink(0x66, 5);
  showBlink(0x77, 5);
  showBlink(0x88, 5);
  showBlink(0x99, 5);
  showBlink(0xaa, 5);
  showBlink(0xbb, 5);
  showBlink(0xcc, 5);
  showBlink(0xdd, 5);
  showBlink(0xee, 5);
  showBlink(0xff, 5);
  
  
}

void showBlink(byte value, int timesToBlink)
{
    for(int i = 0; i < timesToBlink; i++)
    {
      reg.displayByte(value);
      delay(200);
      reg.clearDisplay();
      delay(200);  
    }
}
