
void setup()
{
    cli();
    TCCR2B = 0x00;        // Disable Timer2 while we set it up
    TCNT2  = 254;         // Reset Timer Count  (255-0) = execute ev 255-th T/C clock
    TIFR2  = 0x00;        // Timer2 INT Flag Reg: Clear Timer Overflow Flag
    TIMSK2 = 0x01;        // Timer2 INT Reg: Timer2 Overflow Interrupt Enable
    TCCR2A = 0x00;        // Timer2 Control Reg A: Wave Gen Mode normal
    TCCR2B = 0x06;        // Timer2 Control Reg B: Timer Prescaler set to 1
    pinMode(5, OUTPUT);
    
    sei();
}
void loop()
{}

ISR(TIMER2_OVF_vect) 
{
  static unsigned int pinstate = 0;
  byte sample = getNextSample();
  analogWrite(5, sample);
  TCNT2 = 254;
  TIFR2 = 0x00; // clear overflow flag
  
}
