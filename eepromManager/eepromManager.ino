/***************************************************************************
 * EEPROM Manager
 *
 *
 **************************************************************************/
#include <Wire.h> // for the I2C library
#define PAGE_SIZE 64    // page size of this EEPROM
#define BUS_SIZE 8      // # of eeproms on the i2c bus
#define MAX_ADDRESS 0x7FFF // max address for this EEPROM
#define LINELENGTH 16


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
  
  // start serial port services
  Serial.begin(115200);
  Serial.flush();
  Serial.println("");
  Serial.println("Arduino EEPROM Manager");
  Serial.println("Copyright CF Industries 2013");
  Serial.println("Starting I2C Interface...");
  
   // start the I2C serial bus as master
  Wire.begin();
  Serial.println("Arduino is master");
  Serial.print("I2C bus speed: ");
  long freq = F_CPU / (16 + (2 * TWBR)) / 1000;
  Serial.print(freq);
  Serial.println("kHz");
  Serial.print("I2C buffer size is ");
  Serial.print(BUFFER_LENGTH);
  Serial.println(" bytes ");
  Serial.println("");
  
  Serial.println("Scanning I2C bus...");
  
  scanBus();
    
}

void loop()
{
  Serial.println("Send Command: D to dump, L to load, R to reset");
  while(!Serial.available()){}
  char command = Serial.read();
  if (command == 'D' || command == 'd')
  {
    dump();
  }
  else if(command == 'L' || command == 'l')
  {
    load();
  }
  else if(command =='R' || command == 'r')
  {
    asm("JMP 0");
  }
  else
  {
    Serial.print("Command ");
    Serial.print(command);
    Serial.println(" not understood."); 
  }
}

void scanBus()
{
  int nDevices = 0;
  for(int i = 0; i < BUS_SIZE; i++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(eepromBus[i]);
    int error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("EEPROM ");
      Serial.print(i + 1);
      Serial.print(" found at address 0x");
      Serial.print(eepromBus[i],HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print("Unknow error at address 0x");
      Serial.println(eepromBus[i],HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No EEPROMS found");
  else
    Serial.println("done.");
}

void dump()
{
  Serial.println("Select an eeprom to dump (1-8)");
  while(!Serial.available()){}
  int eeprom = Serial.parseInt();
  if(eeprom > 0 && eeprom < 9)
  {
     Serial.print("Dumping EEPROM ");
    Serial.println(eeprom);
    dumpEeprom(eepromBus[eeprom - 1]);
  }
  else
  {
    Serial.println("Invalid EEPROM index specified");
  }
  
  
}

void load()
{
  Serial.println("Load not yet implemented");
}



void dumpEeprom(byte eeprom)
{
 
  // read from 0x0000 to 0x7FFF
  for(unsigned int address = 0x000; address <= MAX_ADDRESS; address+= PAGE_SIZE)
  {
      dumpBlock(eeprom, address);
    
  }  
}


void dumpBlock(byte eeprom, unsigned int address)
{
  
  unsigned int currAddress = address;
  
  Wire.beginTransmission(eeprom);
  Wire.write(highByte(address));
  Wire.write(lowByte(address));
  Wire.endTransmission();
  
  int linecount = 0;
  Wire.requestFrom((uint8_t)eeprom, (uint8_t)PAGE_SIZE);
  while(Wire.available())
  {
    if(linecount == 0)
    {
      Serial.print(formatHexAddress(currAddress));
      Serial.print("\t");
    }
     linecount++;
     byte datum = Wire.read();
     Serial.print(formatHexByte(datum));
     
     
     if(linecount < LINELENGTH)
     {
       Serial.print("\t");
     }
     else
     {
       Serial.println("");
       linecount = 0;
       currAddress += LINELENGTH;
     }  
     
  } 
}

String formatHexByte(byte value)
{
  String base = "0x"; 
  String hexdata = String(value, HEX); 
  if(hexdata.length() < 2)
  {
    base += "0";
  }
  base += hexdata;
  return base;
  
}

String formatHexAddress(unsigned int address)
{
   String base = String("0x");
   
   String hexaddr = String(address, HEX);
   for(int i = 0; i < (4 - hexaddr.length()); i++)
   {
      base += "0";
   } 
   base += hexaddr;
   return base;
  
}

