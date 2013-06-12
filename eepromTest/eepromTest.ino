/* test the funtioning of the Microchip 24LC256 256kbit I2C serial EEPROM
 *
 *
 *
 **************************************************************************/
#include <Wire.h> // for the I2C library
#define PAGE_SIZE 64    // page size of this EEPROM
#define BUS_SIZE 8      // # of eeproms on the i2c bus
#define MAX_ADDRESS 0x7FFF // max address for this EEPROM

byte writeVal = 0xF0;

// device address matrix
byte eepromBus[BUS_SIZE] = 
{
  0x50, 
  0x51, 
  0x52, 
  0x53, 
  0x54, 
  0x55, 
  0x56, 
  0x57
};

void setup()
{
  Serial.begin(9600);

  Serial.print("Wire buffer size is ");
  Serial.print(BUFFER_LENGTH);
  Serial.println(" bytes ");
 
  
  // start the I2C serial bus as master
  Wire.begin();
  delay(5);  // give things time to settle on the bus

// test each eeprom
  for(int i = 0; i < BUS_SIZE; i++)
  {
     writeTest(i);
  }

  for(int i = 0; i < BUS_SIZE; i++)
  {
     verify(i);
  }
}

void loop()
{
}

void writeTest(int eeprom)
{
  byte data[64];
  for(int i = 0; i < PAGE_SIZE; i++)
  {
    data[i] = writeVal;
  }

  Serial.print("Writing 32k bytes to eeprom by pages ");
  Serial.println(eeprom);

  // write from 0x0000 to 0x7FFF
  for(unsigned int address = 0x000; address <= MAX_ADDRESS; address+= PAGE_SIZE)
  {
    Serial.print("Writing block ");
    Serial.print((address / PAGE_SIZE) + 1);
    Serial.println(" of 512");
    eepromWritePage(eeprom, address, data); 
    delay(5);
  } 
  Serial.println("Done");

}

void pageWriteTest(int eeprom)
{
  byte data[PAGE_SIZE];
  for(int i = 0; i < PAGE_SIZE; i++)
  {
    data[i] = i;
  }
  eepromWritePage(eeprom, 0x0000, data);
  
  delay(10);
  Serial.println("Page write finished, verifying...");
  
  bool result = true;
  for(unsigned int i = 0; i < PAGE_SIZE; i++)
  {
    byte data = eepromReadByte(eeprom, i);
    Serial.print("read ");
    Serial.print(data);
    Serial.print(" at ");
    Serial.println(i);
    if(data != (byte) i)
    {
      result = false;
      break;
    }
  }
  if(result)
  {
    Serial.println("Block test passed");
  }
  else
  {
    Serial.println("Block test failed");
  }
  
}

void verify(int eeprom)
{
  // verify starting from 0x0000 to 0x7FFF
  Serial.print("Verifying 32k bytes from eeprom ");
  Serial.println(eeprom);

  boolean pass = true;

  for(unsigned int address = 0; address <= MAX_ADDRESS; address++)
  {

    byte data = eepromReadByte(eeprom, address);

    if(data != writeVal)
    {
      pass = false;
      Serial.print("Test failed. Byte @ ");
      Serial.print(address);
      Serial.print(" was ");
      Serial.println(data);
      break;
    } 

  }
  if(pass)
  {
    Serial.print("Eeprom ");
    Serial.print(eeprom);
    Serial.println(" passed");
  }
}

void eepromWriteByte(int eeprom, unsigned int address, byte data)
{
  Wire.beginTransmission(eepromBus[eeprom]);
  Wire.write(highByte(address));
  Wire.write(lowByte(address)); 
  Wire.write(data);
  Wire.endTransmission();
}

byte eepromReadByte(int eeprom, unsigned int address)
{
  int eepromAddress = eepromBus[eeprom];
  Wire.beginTransmission(eepromBus[eeprom]);
  Wire.write(highByte(address));
  Wire.write(lowByte(address));
  Wire.endTransmission();
  Wire.requestFrom(eepromAddress, 1);
  while(!Wire.available()){}
  return Wire.read();
}  

// write a block at a time
void eepromWritePage(int eeprom, unsigned int startAddress, byte* data)
{
 
  Wire.beginTransmission(eepromBus[eeprom]);
  Wire.write(highByte(startAddress));
  Wire.write(lowByte(startAddress));
  for(int i = 0; i < PAGE_SIZE; i++)
  {
    Wire.write(data[i]);  
  }
  Wire.endTransmission();  

}


