#include <TinyWireS.h>
#include<TinyDebugSerial.h>
#define I2C_SLAVE_ADDRESS 0x4

void setup()
{
  Serial.begin(9600);
  TinyWireS.begin(I2C_SLAVE_ADDRESS);
}

void loop()
{
}


