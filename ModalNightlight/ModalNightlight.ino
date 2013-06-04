/*

Modal Nightlight Project
CEF - 05/19/2013
Dedicated to my beautiful and wonderful daughter Evangeline :-)

Synopsis: 

Use the Arduino analog output pins 9, 10 and 11 to control an RGB LED to create a nightlight
The nightlight has 6 modes: 
	1. Transition mode - color sweeps through the spectrum with a pleasing effect
	2. Red - only the RED LED is illuminated
	3. Green - ditto the GREEN LED
	4. Blue - ditto the BLUE LED
	5. Yellow - Red + Green LED  
	6. Off - all LED's switched off, but program remains running

TODO: 
 
 * change ints to bytes 
 * try to use timer0 instead of a software counter for the cycle count,
   it should already have been started by the runtime, check with serial output 
 
 * recode in ATMega328P assembler
 
*/

// operational parameter enums
const int FULLY_OFF = 255;   // RGB LED is common cathode
const int FULLY_ON 	= 0;      // so we need reverse logic

// led transition status
const int OFF 			= 0;
const int RAMPING_UP 	        = 1;
const int HOLDING 		= 2;
const int RAMPING_DOWN 	        = 3;

// lookup and output tables 
// steady state outputs
int outputValuesTable[6][3] = 
{ 
  { FULLY_OFF,FULLY_OFF,FULLY_OFF  },     // TRANSITION MODE, only these values will ever change
  { FULLY_ON, FULLY_OFF,FULLY_OFF  },     // RED
  { FULLY_OFF, FULLY_ON, FULLY_OFF  },    // GREEN
  { FULLY_OFF, FULLY_OFF, FULLY_ON  },    // BLUE
  { FULLY_ON, FULLY_ON, FULLY_OFF  },     // YELLOW
  { FULLY_OFF, FULLY_OFF, FULLY_OFF }     // OFF
};

// vars for transition mode
const int transitionStateTable[7][3] = 
{
  { RAMPING_UP, OFF, OFF  },             // to RED
  { HOLDING, OFF, RAMPING_UP  },         // to PURPLE
  { RAMPING_DOWN, OFF, HOLDING  },       // TO BLUE
  { OFF, RAMPING_UP, HOLDING  },         // TO AQUA
  { OFF, HOLDING, RAMPING_DOWN  },       // TO GREEN
  { RAMPING_UP, HOLDING, OFF  },         // TO YELLOW
  { RAMPING_DOWN, RAMPING_DOWN, OFF }    // TO OFF
};

//operation modes
const int TRANSITION_MODE  = 0; 
const int RED_MODE         = 1; 
const int GREEN_MODE       = 2;
const int BLUE_MODE        = 3;
const int YELLOW_MODE      = 4;
const int OFF_MODE         = 5;

// pin enums
const int redPin 	= 11;
const int greenPin 	= 10;
const int bluePin 	= 9;
const int buttonPin     = 12;
const int potentiometerPin = 14;
const int photoCellPin = 17;

// LED indexes
const int RED 	= 0;
const int GREEN = 1;
const int BLUE 	= 2;

// init values and states for transition mode
int currentMode = TRANSITION_MODE; // default
unsigned int transitionStateIndex = 0;
unsigned int cycleCount = 0;

// output counter
int counter = 0;
const int OUTPUTCOUNT = 8192;   // adjust to change cycling rate of transition mode

//switch debouncing
int buttonState = HIGH; // initial state of the button
unsigned int shiftReg = 0xFF;    // keypress forces LO bit to 0

// 7 segment output table
int segment_lookup[10] = 
{ 
  0x3f,  // 0011 1111 segs a,b,c,d,e,f   - 0
  0x06,  // 0000 0110 segs b,c           - 1
  0x5b,  // 0101 1011 a,b,d,e,g          - 2
  0x4f,  // 0100 1111 a,b,c,d,g          - 3
  0x66,  // 0110 0110 b,c,f,g            - 4
  0x6d,  // 0110 1101 a,c,d,f,g          - 5
  0x7d,  // 0111 1101 a,c,d,e,f,g        - 6
  0x07,  // 0000 0111 a,b,c              - 7
  0x7f,  // 0111 1111 a,b,c,d,e,f,g      - 8
  0x6f   // 0110 1111 a,b,c,d,f,g        - 9

};

unsigned int potReading;
unsigned int photoCellReading;

/********************************************************************************************************
 * Code
 *********************************************************************************************************/
void setup()
{
      Serial.begin(9600);
      /*
      // pins 0-6 are hooked up to 7 segment LED
        for(int i = 0; i < 7; i++)
        {
          pinMode(i, OUTPUT);
          digitalWrite(i, LOW);

        }
        */
	// set up LED pins
	pinMode(redPin, OUTPUT);
	pinMode(greenPin, OUTPUT);
	pinMode(bluePin, OUTPUT); 
        pinMode(potentiometerPin, INPUT);
        pinMode(photoCellPin, INPUT);
        digitalWrite(photoCellPin, HIGH);

	// set up switch pin
	pinMode(buttonPin, INPUT);     // pin 4 is switch input
	digitalWrite(buttonPin, HIGH); // turn on internal pull up resistor

        potReading = analogRead(potentiometerPin) / 4;
        photoCellReading = analogRead(photoCellPin);

	// LEDS to OFF
	writeToLeds();
        //displayDigit(currentMode + 1);                
        
}

void loop()
{ 
	checkForModeChange(); 
	counter++;

	if(counter == OUTPUTCOUNT)   // output to pins each time the counter expires 
	{
                potReading = analogRead(potentiometerPin) / 4;
                photoCellReading = analogRead(photoCellPin);
                if(photoCellReading > 200)
                {
		  doOutput();
                }
                else
                {
                  analogWrite(redPin, FULLY_OFF);
                  analogWrite(greenPin, FULLY_OFF);
                  analogWrite(bluePin, FULLY_OFF);
                }
                
		counter = 0;
	}
        //Serial.println(TCNT0);
       
}

void doOutput()   
{
	if(currentMode == TRANSITION_MODE)
	{  
		doNextTransitionStep();
	}
	writeToLeds();

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
	
	if(shiftReg == 0xFFFF && buttonState == LOW)
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

void initTransitionMode()
{  
	transitionStateIndex = 0;
	cycleCount = 0;
	outputValuesTable[TRANSITION_MODE][RED] = FULLY_OFF;
	outputValuesTable[TRANSITION_MODE][GREEN] = FULLY_OFF;
	outputValuesTable[TRANSITION_MODE][BLUE] = FULLY_OFF;

	writeToLeds();

}

void doNextTransitionStep()
{

	for(int i = 0; i < 3; i++)   // update the RGB values for the next output step
	{
		int colorState = transitionStateTable[transitionStateIndex][i];   

		switch(colorState)
		{
			case RAMPING_UP:
			  outputValuesTable[TRANSITION_MODE][i] = FULLY_OFF - cycleCount;
			  break;
			  
			case RAMPING_DOWN:
			  outputValuesTable[TRANSITION_MODE][i] = cycleCount;  
			  break;
			  
			default:       // if its anything else, leave it alone
			  break;
		}
    
	}

	cycleCount++;

	 // if we change this to use an internal hardware counter, 
	 // timer overflow interrupt could advance the transitionStateIndex
	 
	if(cycleCount == 256)   // advance state every 255 cycles
	{
		cycleCount = 0;
		transitionStateIndex++;
		transitionStateIndex = transitionStateIndex % 7;  // cycle 0-6
	}
}

void writeToLeds()
{
        float scaleFactor = (255 - potReading) / 255.0;
        byte redVal =  outputValuesTable[currentMode][RED];
        byte greenVal = outputValuesTable[currentMode][GREEN];
        byte blueVal = outputValuesTable[currentMode][BLUE];
        
        redVal = (byte)redVal  + ((255 - redVal) * scaleFactor);
        greenVal = (byte)greenVal + ((255 - greenVal) * scaleFactor);
        blueVal = (byte)blueVal  + ((255 - blueVal) * scaleFactor);
        //greenVal = greenVal < 255 ? greenVal + scaleFactor : greenVal;
        //blueVal = blueVal < 255 ?  blueVal + scaleFactor : blueVal;
        Serial.print("PhotoCell ");
        Serial.print(photoCellReading);
        Serial.print(" Red: ");
        Serial.print(redVal);
        Serial.print(" Green: "); 
        Serial.print(greenVal);
        Serial.print(" Blue: ");
        Serial.println(blueVal);
	analogWrite(redPin, redVal );
	analogWrite(greenPin,greenVal);
	analogWrite(bluePin, blueVal ) ;
}

void nextMode()
{
	if(currentMode == OFF_MODE)
	{
		initTransitionMode();
		currentMode = TRANSITION_MODE; 
	}
	else
	{
		currentMode++;
	}

        //blankDisplay();              // to avoid conflict with LED pins 0,1  
        //displayDigit(currentMode + 1);

}




