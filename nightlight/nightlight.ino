/* RGB

Output various colors to the analog outputs with smooth transition between colors

*/

#include <avr/interrupt.h>

const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;
const int buttonPin = 2;
const int LED = 13;

const int DELAYTIME = 10;
const int HOLDTIME = 1000;
const int FULLY_OFF = 255;
const int FULLY_ON = 0;




void setup()
{
  
  Serial.begin(9600);
  
  // set up button pin and ISR
  pinMode(buttonPin, INPUT); 
  digitalWrite(buttonPin, HIGH); // turn on internal pullup
  attachInterrupt(0, buttonPressed, FALLING);
  /*
  sei();
  EIMSK |= (1 << INT0);     // Enable external interrupt INT0
  EICRA |= (1 << ISC01);    // Trigger INT0 on falling edge
  */
  // configure analog outputs for LED
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT); 
  pinMode(LED, OUTPUT);
  
  // init LED to all colors off state
  //LED is shared anode, so pins are pull up for off and down for on
  analogWrite(redPin, FULLY_OFF);
  analogWrite(greenPin, FULLY_OFF);
  analogWrite(bluePin, FULLY_OFF);
  
  
  
}


 
void loop()
{
  
  rampUp(redPin);
  delay(HOLDTIME);
  rampUp(bluePin);
  delay(HOLDTIME);
  rampDown(redPin);
  delay(HOLDTIME);
  rampUp(greenPin);
  delay(HOLDTIME);
  rampDown(bluePin);
  delay(HOLDTIME);
  rampUp(redPin);
  delay(HOLDTIME);
  rampDown(greenPin);
  delay(HOLDTIME);
  rampDown(redPin);
  delay(HOLDTIME);  
}
 
void rampUp(int pin)
{
  for(int i = FULLY_OFF; i > FULLY_ON; i--)
  {
    analogWrite(pin, i);
    delay(DELAYTIME);
  }     
}

void rampDown(int pin)
{
  for(int i = FULLY_ON; i < FULLY_OFF; i++)
  {
    analogWrite(pin, i);
    delay(DELAYTIME);
  }  
  
}

//ISR
//ISR(EXT_INT0_vect)
void buttonPressed()
{
  for(int i = 0; i < 1000; i++)
  if(digitalRead(buttonPin) == LOW)
  {
    Serial.println("Button pressed");
    digitalWrite(13, !digitalRead(13));
  }
  
}



