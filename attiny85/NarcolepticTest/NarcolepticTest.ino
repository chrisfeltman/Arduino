
#include <SoftwareSerial.h>
#include <Narcoleptic.h>

int led = 0;
int tx = 1;
int rx = 2;

SoftwareSerial tinySerial(2,1);
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  pinMode(tx, OUTPUT);
  pinMode(rx, INPUT);
  tinySerial.begin(9600);
  //pinMode(3,INPUT); 
 //analogReference(DEFAULT); 
}

// the loop routine runs over and over again forever:
void loop() {
  int theDelay = analogRead(A2);
  
  tinySerial.println(theDelay);
  //blinkit(1);
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  Narcoleptic.delay(theDelay); 
  digitalWrite(led,LOW);
  Narcoleptic.delay(theDelay);
}



