int dataPin = 2;        //Define which pins will be used for the Shift Register control
int latchPin = 3;
int clockPin = 4;


const int delayTime = 200;

void setup()
{
  pinMode(dataPin, OUTPUT);       //Configure each IO Pin
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  randomSeed(analogRead(A5));
}

void loop()
{
  knightRider();
}

void counter()
{
  for ( byte c = 0; c < 256; c++)
   {
     ByteOutSerial(c);   
   }
  
  
}

void randPattern()
{
   ByteOutSerial(random(0, 256)); 
}

void knightRider()
{
  while(true)
  {
    int outputval = 1;
    for(int i = 0; i < 8; i++)
    {
      
      ByteOutSerial(outputval);
     outputval *= 2; 
    }

    for(int i = 0; i < 8; i++)
    {
      outputval /= 2;
      ByteOutSerial(outputval);
    }

  }
  
  
}

void ByteOutSerial(byte writeByte)
{
  digitalWrite(latchPin, LOW);          //Pull latch LOW to start sending data
  shiftOut(dataPin, clockPin, MSBFIRST, writeByte);         //Send the data
  digitalWrite(latchPin, HIGH);         //Pull latch HIGH to stop sending data
  delay(delayTime);


}

