
/* LCD display segments
 a - pin 0
 b - pin 1
 c - pin 2
 d - pin 3
 e - pin 4
 f - pin 5
 g - pin 6
 */

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



void setup()
{

  for(int i = 0; i < 7; i++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);

  }

}

void loop()
{
  for(int i = 0; i<10; i++)
  {
    display_digit(i);
    delay(1000);
  }
}


void display_digit(int digit)
{
  int bitPattern = segment_lookup[digit];
  for(int i = 0; i < 8; i++)
  {
    int output = bitRead(bitPattern,i);
    digitalWrite(i, output);
  }
}


