#include <avr/interrupt.h>

//operation modes
const int TRANSITION_MODE  = 0; 
const int RED_MODE         = 1; 
const int GREEN_MODE       = 2;
const int BLUE_MODE        = 3;
const int YELLOW_MODE      = 4;
const int OFF_MODE         = 5;

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
const int OFF = 0;
const int RAMPING_UP = 1;
const int HOLDING = 2;
const int RAMPING_DOWN = 3;

int currentMode = TRANSITION_MODE; // default

// init values and states for transition mode

// pin indexes
const int RED = 0;
const int GREEN = 1;
const int BLUE = 2;

// vars for transition mode
int transitionStateTable[7][3];
unsigned int transitionStateIndex = 0;
unsigned int cycleCount = 0;
int outputValues[3] = {FULLY_OFF, FULLY_OFF, FULLY_OFF};

// output counter
int counter = 0;
const int OUTPUTCOUNT = 8192;

//switch debouncing
// volatile to force the compiler to not optimize with these vars
volatile int buttonState = HIGH; // initial state of the button
volatile unsigned int shiftReg = 0xFF;    // keypress forces LO bit to 0

void setup()
{
  initTransitionStateTable(); 
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
}

void loop()
{ 
  checkForModeChange(); 
  
  counter++;
  if(counter == OUTPUTCOUNT)   // output to pins each time the counter expires 
  {
    doOutput();
    counter = 0;
  }
}

void initTransitionStateTable()
{
  // to RED
  transitionStateTable[0][RED] = RAMPING_UP;
  transitionStateTable[0][GREEN] = OFF;
  transitionStateTable[0][BLUE] = OFF;
  
  //to PURPLE
  transitionStateTable[1][RED] = HOLDING;
  transitionStateTable[1][GREEN] = OFF;
  transitionStateTable[1][BLUE] = RAMPING_UP; 
  
  //to BLUE
  transitionStateTable[2][RED] = RAMPING_DOWN;
  transitionStateTable[2][GREEN] = OFF;
  transitionStateTable[2][BLUE] = HOLDING;
  
  //to AQUA
  transitionStateTable[3][RED] = OFF;
  transitionStateTable[3][GREEN] = RAMPING_UP;
  transitionStateTable[3][BLUE] = HOLDING;

  //to GREEN
  transitionStateTable[4][RED] = OFF;
  transitionStateTable[4][GREEN] = HOLDING;
  transitionStateTable[4][BLUE] = RAMPING_DOWN;
  
  //to YELLOW
  transitionStateTable[5][RED] = RAMPING_UP;
  transitionStateTable[5][GREEN] = HOLDING;
  transitionStateTable[5][BLUE] = OFF;
  
  // to DARK
  transitionStateTable[6][RED] = RAMPING_DOWN;
  transitionStateTable[6][GREEN] = RAMPING_DOWN;
  transitionStateTable[6][BLUE] = OFF;   
    
}

void checkForModeChange()
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

void sendDebugInfo()
{
  Serial.print("state ");
  Serial.print(transitionStateIndex);
  Serial.print(" cycle ");
  Serial.print(cycleCount);
  Serial.print(" red ");
  Serial.print(outputValues[RED]);
  Serial.print(" green ");
  Serial.print(outputValues[GREEN]);
  Serial.print(" blue ");
  Serial.println(outputValues[BLUE]);  
    
}

void sampleSwitch()
{
  int currentState = digitalRead(buttonPin);
  shiftReg = shiftReg << 1;                 // shift left 1 bit       
  shiftReg += (currentState & 0x01);        // set LO bit to current switch pin reading

}


void initTransitionMode()
{  
  transitionStateIndex = 0;
  cycleCount = 0;
  outputValues[RED] = FULLY_OFF;
  outputValues[GREEN] = FULLY_OFF;
  outputValues[BLUE] = FULLY_OFF;
  analogWrite(redPin, FULLY_OFF);
  analogWrite(greenPin, FULLY_OFF);
  analogWrite(bluePin, FULLY_OFF);
  
}
void doNextTransitionStep()
{

  for(int i = 0; i < 3; i++)
  {
      int state = transitionStateTable[transitionStateIndex][i];
           
      switch(state)
      {
        case RAMPING_UP:
          outputValues[i] = FULLY_OFF - cycleCount;
          break;
        case RAMPING_DOWN:
          outputValues[i] = cycleCount;  
          break;
          /*
        case HOLDING:
          outputValues[i] = FULLY_ON;
          break;
        case OFF: 
         outputValues[i] = FULLY_OFF; 
         break; 
        */ 
      }     
  }
 
  // output calculated values;
  analogWrite(redPin, outputValues[RED]);
  analogWrite(greenPin, outputValues[GREEN]);
  analogWrite(bluePin, outputValues[BLUE]);
 
  cycleCount++;
  
  // advance state every 255 cycles
  if(cycleCount == 256)
  {
    cycleCount = 0;
    transitionStateIndex++;
    transitionStateIndex = transitionStateIndex % 7;  // cycle 0-6
  }
  
}

void doRed()
{
  analogWrite(redPin, FULLY_ON);
  analogWrite(greenPin, FULLY_OFF);
  analogWrite(bluePin, FULLY_OFF);
}

void doGreen()
{
  analogWrite(redPin, FULLY_OFF);
  analogWrite(greenPin, FULLY_ON);
  analogWrite(bluePin, FULLY_OFF);
}

void doBlue()
{
  analogWrite(redPin, FULLY_OFF);
  analogWrite(greenPin, FULLY_OFF);
  analogWrite(bluePin, FULLY_ON);
}

void doYellow()
{
  analogWrite(redPin, FULLY_ON);
  analogWrite(greenPin, FULLY_ON);
  analogWrite(bluePin, FULLY_OFF);
}

void doOff()
{
  analogWrite(redPin, FULLY_OFF);
  analogWrite(greenPin, FULLY_OFF);
  analogWrite(bluePin, FULLY_OFF);
}

void nextMode()
{

   if(currentMode == OFF_MODE)
   {
     currentMode = 0;
   }
   else
   {
     currentMode++;
   }
   
   // need to reset vars or we will pick up where we left off  
   if(currentMode == TRANSITION_MODE)
   {
     initTransitionMode();
   } 
}


void doOutput()   // later we'll use function pointer table, KISS for now
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
    case OFF_MODE: 
      doOff();
      break;
  }

}


