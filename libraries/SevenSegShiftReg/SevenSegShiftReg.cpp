/************************************************************************************************
*
* Test wiring and display driver code for  2 RadioShack 276-0075 7 Segment LED Displays
* connected to two SN54HC595 8-bit shift registers
*
*
* Pinouts: (top left corner is pin 1,  going around in a U so that bottom right corner is pin 8, top right is pin 14)


Looking at chip right side up      .8.

1     14
2     13
X     12
4     X
X     X
6     9
7     8

*  1 - Anode for segment f
*  2 - Anode for segment g
*  3 - no pin
*  4 - Common cathode
*  5 - no pin
*  6 - Anode for segment e
*  7 - Anode for segment d
*  8 - Anode for segment c
*  9 - Anode for RH decimal point (unused here)
*  10 - no pin
*  11 - no pin
*  12 - Common cathode  (only one of pin 4 or 12 needs to be connected with 300 Ohm resistor in series
*  13 - Anode for segment b
*  14 - Anode for segment a
*
*
***************************************************************************************************/
#include <SevenSegShiftReg.h>
#include <avr/pgmspace.h>

// store the lookup table in program memory, must be declared outside the class
prog_uchar PROGMEM seg7LookupTable[] =
{ 
  0x3f,  // 0011 1111 a,b,c,d,e,f        - 0
  0x06,  // 0000 0110 b,c                - 1
  0x5b,  // 0101 1011 a,b,d,e,g          - 2
  0x4f,  // 0100 1111 a,b,c,d,g          - 3
  0x66,  // 0110 0110 b,c,f,g            - 4
  0x6d,  // 0110 1101 a,c,d,f,g          - 5
  0x7d,  // 0111 1101 a,c,d,e,f,g        - 6
  0x07,  // 0000 0111 a,b,c              - 7
  0x7f,  // 0111 1111 a,b,c,d,e,f,g      - 8
  0x6f,  // 0110 1111 a,b,c,d,f,g        - 9
  0x77,  // 0111 0111 a,b,c,e,f,g        - A
  0x7c,  // 0111 1100 c,d,e,f,g          - b
  0x39,  // 0011 1001 a,d,e,f            - C
  0x5e,  // 0101 1110 b,c,d,e,g          - d
  0x79,  // 0111 1001 a,d,e,f,g          - E
  0x71   // 0111 0001 a,e,f,g            - F

};

SevenSegShiftReg::SevenSegShiftReg(int dataPin, int latchPin, int clockPin)
{
		// remember which pins to use
		mDataPin = dataPin;
		mLatchPin = latchPin;
		mClockPin = clockPin;
		pinMode(dataPin, OUTPUT);       //Configure each IO Pin
		pinMode(latchPin, OUTPUT);
		pinMode(clockPin, OUTPUT);
		mThreePinInterface = true;
}

SevenSegShiftReg::SevenSegShiftReg(int dataPin, int clockPin)
{
	// latch pin needs to be connected to clock Pin per 595 datasheet
	mDataPin = dataPin;
	mClockPin = clockPin;
	pinMode(dataPin, OUTPUT);       //Configure each IO Pin
	pinMode(clockPin, OUTPUT);
	mThreePinInterface = false;
}

void SevenSegShiftReg::displayByte(byte digit)
{
	// get low and high nybbles of byte
	byte highNybble = (digit & 0xF0) >> 4;
	byte lowNybble = digit & 0x0F;
	
	// look up segment codes from progmem table
	byte lowByteOut = pgm_read_byte_near(&seg7LookupTable[lowNybble]);
	byte highByteOut;
	
	// save a table lookup if they are the same (flash is slow-ish)
	if(highNybble != lowNybble)
	{
		highByteOut = pgm_read_byte_near(&seg7LookupTable[highNybble]);
	}
	else
	{
		highByteOut = lowByteOut;
	}
	
	// pack into an unsigned int for output
	unsigned int output;
	output = highByteOut << 8;
	output = output | lowByteOut;
	
	byteOutSerial(output);
}

void SevenSegShiftReg::clearDisplay()
{
	byteOutSerial(0x0000);
}

void SevenSegShiftReg::byteOutSerial(unsigned int writeByte)
{
	if(mThreePinInterface)
	{
		digitalWrite(mLatchPin, LOW);          //Pull latch LOW to start sending data
	}
	shiftOut(mDataPin, mClockPin, MSBFIRST, highByte(writeByte));   //Send HO byte
	shiftOut(mDataPin, mClockPin, MSBFIRST, lowByte(writeByte));	// send LO byte
	if(mThreePinInterface)
	{
		digitalWrite(mLatchPin, HIGH);         //Pull latch HIGH to stop sending data
	}
	else
	{
		digitalWrite(mClockPin, HIGH);
		digitalWrite(mClockPin, LOW);
	}
	
}