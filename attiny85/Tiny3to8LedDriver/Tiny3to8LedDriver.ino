
#define A 0
#define B 1
#define C 2

void setup()
{
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);

}  
void loop()
{
  nightRider();
  nightRider();
  povTwoOn();
  povTwoOn();
  povTwoOn();
  povTwoOn();

}

void Output(byte data)
{
  for(byte j = 0; j < 3; j++)
  {
    digitalWrite(j, bitRead(data, j));
  }

}

void povTwoOn()
{
  int count = 50;
  // two outer
  povDisplayTwo(0,7, count);
 
  povDisplayTwo(1,6, count);
 
  povDisplayTwo(2,5, count);
 
  povDisplayTwo(3,4, count);
 
  povDisplayTwo(4,3, count);

  povDisplayTwo(5,2, count);
 
  povDisplayTwo(6,1, count);
 
  povDisplayTwo(7,0, count);



}

void povDisplayTwo(byte first, byte second, int times)
{
  for(int i = 0; i < times; i++)
  {
    Output(first);
    delay(1);
    Output(second);
    delay(1);
    
  }


}
void nightRider()
{
  for(int i = 0; i < 8; i++)
  {
    Output(i);
    delay(100);
  } 


  for(int j = 7; j >= 0; j--)
  {
    Output(j);
    delay(100); 
  }



}


