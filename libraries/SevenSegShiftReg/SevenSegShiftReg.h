#include <Arduino.h>


#ifndef _SevenSegShiftReg
#define _SevenSegShiftReg

class SevenSegShiftReg
{
	private:
		int mDataPin;
		int mLatchPin; 
		int mClockPin;
		bool mThreePinInterface;
		void byteOutSerial(unsigned int writeByte);
	public:
		SevenSegShiftReg(int dataPin, int latchPin, int clockPin);
		SevenSegShiftReg(int dataPin, int clockPin);
		void displayByte(byte digit);
		void clearDisplay();
};
#endif		