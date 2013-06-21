byte memory[0x0A00];
void setup()
{
  Serial.begin(115200);
  Serial.println("Starting memory test.");
  Serial.println("Testing 2560 KB..");

 
}
void loop()
{
   byte readVal;
  byte* address = 0;


  for(unsigned int i = 0; i < 0x0A00; i++)
  {
    memory[i] = 0x00;
    readVal = memory[i];
    if(readVal != 0x00)
    {
      memError(readVal, 0x00, i);
    }
   
  }
  
  while(true)
  {
    Serial.println("idling ...");
    delay(1000);
  }
}

void memError(byte gotValue, byte expectedValue, unsigned int address)
{
  Serial.print("Memory test failed at address ");
  Serial.print(address, HEX);
  Serial.print(" expected ");
  Serial.print(expectedValue, HEX);
  Serial.print(" got ");
  Serial.println(gotValue, HEX);
}

