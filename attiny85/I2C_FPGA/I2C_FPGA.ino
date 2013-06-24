#define Q0 0
#define I0 1
#define Q1 2
#define I1 3


void setup()
{
  pinMode(Q0, OUTPUT);
  pinMode(I0, INPUT_PULLUP);
  pinMode(Q1, OUTPUT);
  pinMode(I1, INPUT_PULLUP);
  
}

void loop()
{
  digitalWrite(Q0, !digitalRead(I0));
  digitalWrite(Q1, !digitalRead(I1));
  
}

.

