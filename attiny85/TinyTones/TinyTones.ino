#define speakerPin 0
#define QN 500
#define HN 1000
#define WN 2000

const int C1 = 261;
const int D  = 294;
const int E  = 329;
const int F  = 349;
const int G  = 392;
const int A = 440;
const int Bflat = 466;
const int B  = 493;
const int C2 = 523;

void setup()
{
  
}
void loop()
{
 
  
  // love me tender
  playNote(C1, QN);
  playNote(F, QN);
  playNote(E, QN);
  playNote(F, QN);
  playNote(G, QN);
  playNote(D, QN);
  playNote(G, HN);
  playNote(F, QN);
  playNote(E, QN);
  playNote(D, QN);
  playNote(E, QN);
  playNote(F, WN);
  
  playNote(C1, QN);
  playNote(F, QN);
  playNote(E, QN);
  playNote(F, QN);
  playNote(G, QN);
  playNote(D, QN);
  playNote(G, HN);
  playNote(F, QN);
  playNote(E, QN);
  playNote(D, QN);
  playNote(E, QN);
  playNote(F, WN);
  
  playNote(A, QN);
  playNote(A, QN);
  playNote(A, QN);
  playNote(A, QN);
  playNote(A, QN);
  playNote(A, QN);
  playNote(A, HN);
  playNote(A,QN);
  playNote(G,QN);
  playNote(F,QN);
  playNote(G, QN);
  playNote(A,WN);
  
  playNote(A,QN);
  playNote(A,QN);
  playNote(Bflat, QN);
  playNote(A,QN);
  playNote(G, QN);
  playNote(D,QN);
  playNote(G, HN);
  playNote(F,QN);
  playNote(E,QN);
  playNote(D,QN);
  playNote(E,QN);
  playNote(F, WN);
  
   
  noTone(speakerPin);
  delay(500);
}

void playNote(int note, int duration)
{
  tone(speakerPin, note);
  delay(duration);
  noTone(speakerPin);
  delay(10);
}
