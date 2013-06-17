#include<SoftwareSerial.h>

const int led = 0;
const int SSTX = 1;
const int SSRX = 2;
char commandBuffer[32];
SoftwareSerial mySerial = SoftwareSerial(SSRX,SSTX);

void setup()
{
  mySerial.begin(57600);
  pinMode(led, OUTPUT);

}

// the loop routine runs over and over again forever:
void loop() {

  if(mySerial.available())
  {
    char command = mySerial.read();
    mySerial.println("OK");
    digitalWrite(led, !digitalRead(led));
    
  } 

}

void blinkit(int times)
{


  for(int i = 0; i < times; i++)
  {    
    digitalWrite(led, !digitalRead(led));   // turn the LED on (HIGH is the voltage level)
    delay(250);               // wait for a second
    digitalWrite(led, !digitalRead(led));    // turn the LED off by making the voltage LOW
    delay(250);  
  }

}




