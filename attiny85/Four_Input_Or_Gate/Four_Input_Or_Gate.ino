#define Q 0
#define I0 1
#define I1 2
#define I2 3
#define I3 4

void setup()
{
  pinMode(Q, OUTPUT);
  pinMode(I0, INPUT_PULLUP);
  pinMode(I1, INPUT_PULLUP);
  pinMode(I2, INPUT_PULLUP);
  pinMode(I3, INPUT_PULLUP);
}

void loop()
{
  digitalWrite(Q, digitalRead(I0) | digitalRead(I1) | digitalRead(I2) | digitalRead(I3));
  
}

