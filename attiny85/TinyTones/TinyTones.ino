#define speakerPin 0
#define EN 250  // eighth note
#define QN 500  // quarter note
#define QNp 750 // quarter note + tied 8th
#define HN 1000 // half note
#define WN 2000 // whole note

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
  loveMeTender();
  twinkleTwinkle();


}

void playNote(int note, int duration)
{
  tone(speakerPin, note);
  delay(duration);
  noTone(speakerPin);
  delay(10);
}

void twinkleTwinkle()
{
  playNote(C1, QN);
  playNote(C1, QN);
  playNote(G, QN);
  playNote(G,QN);
  playNote(A, QN);
  playNote(A, QN);
  playNote(G, HN);

  playNote(F, QN);
  playNote(F, QN);
  playNote(E, QN);
  playNote(E, QN);
  playNote(D, QN);
  playNote(D, QN);
  playNote(C1, HN);

  playNote(G, QN);
  playNote(G, QN);
  playNote(F, QN);
  playNote(F, QN);
  playNote(E, QN);
  playNote(E, QN);
  playNote(D, HN);

  playNote(G, QN);
  playNote(G, QN);
  playNote(F, QN);
  playNote(F, QN);
  playNote(E, QN);
  playNote(E, QN);
  playNote(D, HN);

  playNote(C1, QN);
  playNote(C1, QN);
  playNote(G, QN);
  playNote(G,QN);
  playNote(A, QN);
  playNote(A, QN);
  playNote(G, HN);

  playNote(F, QN);
  playNote(F, QN);
  playNote(E, QN);
  playNote(E, QN);
  playNote(D, QN);
  playNote(D, QN);
  playNote(C1, HN);

  noTone(speakerPin);
  delay(500); 

}

void loveMeTender()
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
  playNote(D, QNp);
  playNote(E, EN);
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
  playNote(D, QNp);
  playNote(E, EN);
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
  playNote(F,QNp);
  playNote(G, EN);
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
  playNote(A,QNp);
  playNote(G,EN);
  playNote(F, WN);


  noTone(speakerPin);
  delay(500); 

}


