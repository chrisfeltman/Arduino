#include <avr/interrupt.h>

// timer interrupt count
const int INTERRUPT_COUNT = 3200;
//operation modes
const int TRANSITION_MODE  = 0; 
const int RED_MODE         = 1; 
const int GREEN_MODE       = 2;
const int BLUE_MODE        = 3;
const int YELLOW_MODE      = 4;   

// pin enums
const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;
const int buttonPin = 4;
const int LED = 13;

// operational parameter enums

const int FULLY_OFF = 255;
const int FULLY_ON = 0;

// led transition status
const int RAMPING_UP = 0;
const int RAMPING_DOWN = 1;
const int OFF = 2;

unsigned int currentMode = TRANSITION_MODE; // default

// init values and states for transition mode
int currentRed = FULLY_OFF;
int currentGreen = FULLY_OFF;
int currentBlue = FULLY_OFF;

int redState = RAMPING_UP;
int greenState = OFF;
int blueState = OFF;

//switch debouncing
// volatile to force the compiler to not optimize with these vars
volatile int buttonState = HIGH; // state of the button
volatile unsigned int shiftReg = 0xFF;    // keypress forces LO bit to 0

void setup()
{
  
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT); 
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH); // turn on internal pull up resistor
  
  analogWrite(redPin, FULLY_OFF);
  analogWrite(greenPin, FULLY_OFF);
  analogWrite(bluePin, FULLY_OFF);
  
  // set up timer interrupt

    // initialize Timer1
    cli();          // disable global interrupts 
    TCCR1A = 0;     // set entire TCCR1A register to 0
    TCCR1B = 0;     // same for TCCR1B
 
    // set compare match register to desired timer count:
    OCR1A = INTERRUPT_COUNT;
    // turn on CTC mode:
    TCCR1B |= (1 << WGM12);
    // Set CS10 and CS12 bits for 1024 prescaler:
    TCCR1B |= (1 << CS10);
    TCCR1B |= (1 << CS12);
    // enable timer compare interrupt:
    TIMSK1 |= (1 << OCIE1A);
    sei();          // enable global interrupts
}

void loop()
{
  
  // debounce switch and check for button state change
  sampleSwitch();
    
  if(shiftReg == 0 && buttonState == HIGH)
  {
    buttonState = LOW;
    nextMode();
  }
  if(shiftReg == 0xFF && buttonState == LOW)
  {
    buttonState = HIGH;
  }   
  
}

void sampleSwitch()
{
  int currentState = digitalRead(buttonPin);
  shiftReg = shiftReg << 1;                 // shift left 1 bit       
  shiftReg += (currentState & 0x01);        // set LO bit to current switch pin reading

}


void doNextTransitionStep()
{
  Serial.println("In doNextTransitionStep");
  currentRed = FULLY_OFF;
  currentGreen = FULLY_OFF;
  currentBlue = FULLY_OFF;
  analogWrite(redPin, currentRed);
  analogWrite(greenPin, currentGreen);
  analogWrite(bluePin, currentBlue);
  
  // logic to ramp LED colors up and down cyclically goes here

}

void doRed()
{
  Serial.println("In doRed");
  analogWrite(redPin, FULLY_ON);
  analogWrite(greenPin, FULLY_OFF);
  analogWrite(bluePin, FULLY_OFF);
}

void doGreen()
{
  Serial.println("In doGreen");
  analogWrite(redPin, FULLY_OFF);
  analogWrite(greenPin, FULLY_ON);
  analogWrite(bluePin, FULLY_OFF);
}

void doBlue()
{
  Serial.println("In doBlue");
  analogWrite(redPin, FULLY_OFF);
  analogWrite(greenPin, FULLY_OFF);
  analogWrite(bluePin, FULLY_ON);
}

void doYellow()
{
  Serial.println("In doYellow");
  analogWrite(redPin, FULLY_ON);
  analogWrite(greenPin, FULLY_ON);
  analogWrite(bluePin, FULLY_OFF);
}

void nextMode()
{
  // disable interrupts while we are changing mode to prevent a bad mode value 
  // from being seen if INT occurs between increment and modulo
   cli();  
   currentMode++;
   currentMode %= 5;
   sei();
  
}


void timerInterrupt()   // later we'll use function pointer table, KISS for now
{

   switch(currentMode)
  {
    case TRANSITION_MODE:
      doNextTransitionStep();
      break;
    case RED_MODE:
      doRed();
      break;
    case GREEN_MODE: 
      doGreen();
      break;
    case BLUE_MODE: 
      doBlue();
      break;
    case YELLOW_MODE: 
      doYellow();
      break;
  }
  // auoto cycle for test
  //nextMode();
  
}

//  timer interrupt handler
ISR(TIMER1_COMPA_vect)
{
  timerInterrupt();     
}




