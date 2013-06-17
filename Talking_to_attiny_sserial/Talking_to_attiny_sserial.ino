#include <SoftwareSerial.h>
const int SSTX = 2;
const int SSRX = 3;

SoftwareSerial mySerial = SoftwareSerial(SSRX, SSTX);

char buffer[4];

void setup()
{
  Serial.begin(115200);
  mySerial.begin(57600);
}

void loop()
{

  mySerial.write('0');
  delay(1);
  printResponse();
  
  delay(1000);
  mySerial.write('1');
  delay(1);
  printResponse();
  delay(1000);
 
}

void printResponse()
{
  int len = mySerial.available();
  if(len == 0)
  {  
    Serial.println("got no answer"); 
  }
  else
  {
    Serial.print("got an answer, ");
    Serial.print(len);
    Serial.println(" chars waiting");
    
    while(mySerial.available())
    {
      Serial.write(mySerial.read());
    }
   
  }
  
}



