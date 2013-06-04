/************************************************************************************************
*
* Test wiring and display driver code for RadioShack 276-0075 7 Segment LED Display
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

 Arduino pins for LCD display segments:
 a - pin 0
 b - pin 1
 c - pin 2
 d - pin 3
 e - pin 4
 f - pin 5
 g - pin 6

Note: serial port uses pin 0 an 1 so the display will glitch during upload and any serial communications
sending serial with the display connected like this requires special handling to avoid garbage

you have to do:
 Serial.begin(9600);
 delay(1);
 // send your data
Serial.end();

I want to find a way to use a transistor to disconnect the display by disconnecting the common cathode while sending data




 ***************************************************************************************************/

byte segment_lookup[16] = 
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

void setup()
{

  //configure pins 0-7 as outputs
  for(byte i = 0; i < 7; i++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);

  }

}

void loop()
{
  // count endlessly from 0-F
  for(byte i = 0; i< 0x10                                                                                                                                                                                                                                                                                        ; i++)
  {
    display_digit(i);
    delay(300);
  }
}


void display_digit(byte digit)
{
  // get approprite bit pattern from lookup
  byte bitPattern = segment_lookup[digit];
  
  //output bit pattern to pins 0-7
  for(byte i = 0; i < 8; i++)
  {
    byte output = bitRead(bitPattern,i);   // read bit corresponding to pin
    digitalWrite(i, output);              // set pin i to whatever bitPattern[i] is
  }
}


