
#include "HammingCode.h"

unsigned long HammingCode::Encode12_8(byte data1, byte data2)
{
		byte parity1 = 0;
		byte parity2 = 0;
		
		unsigned int data1 = SetDataBits(data1);
		unsigned int data2 = SetDataBits(data2);
		data1 = SetParityBits(data1);
		data2 = SetParityBits(data2);
		
		// pack the two hamming code words into a long
		//	HO 4 bits of each int are don't care	
		unsigned long output = 0;
		output = data1 << 16;
		output += data2;
		return output;
		

}

boolean HammingCode::Decode12_8(long *codeword, byte *buffer)
{

}

unsigned int HammingCode::SetDataBits(byte data)
{
	int output = 0;
	if(bitRead(data, 7)
	{
		bitSet(output, 12);
	}
		
	if(bitRead(data, 6)
	{
		bitSet(output, 11);
	}
	
	if(bitRead(data, 5)
	{
		bitSet(output, 10);
	}
	
	if(bitRead(data, 4)
	{
		bitSet(output, 9);
	}
	
	if(bitRead(data, 3)
	{
		bitSet(output,7);
	}
	
	if(bitRead(data, 2)
	{
		bitSet(output, 6);
	}
	
	if(bitRead(data, 1)
	{
		bitSet(output, 5);
	}
	
	if(bitRead(data, 0)
	{
		bitSet(output, 3);
	}
	
	return output;
		
}

unsigned int HammingCode::SetParityBits(unsigned int data)
{
	
}




