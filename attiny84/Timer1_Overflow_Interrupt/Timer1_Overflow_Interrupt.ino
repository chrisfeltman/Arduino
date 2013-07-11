//#include<UserTimer.h>

#define TIMER_PERIOD 3036
#define LED 4

volatile unsigned int interruptCount = 0;

void setup() {
  pinMode(LED, OUTPUT);

  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;

  TCNT1 = TIMER_PERIOD;      // preload timer for 0.125 hz
  TCCR1B |= (1 << CS12);    // 1024 prescaler 
  TCCR1B |= (1 << CS10);    // 1024 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt

  GIMSK |= (1 << PCIE0);  // enable pin change interrupt 0
  PCMSK0 |= (1 << PCINT6); // enable interrupt for pin 6 change

  interrupts();             //
  Serial.begin(9600);

}

void loop() 
{

  Serial.print("Interrupt count: "); 
  Serial.println(interruptCount);
  delay(500);


}

ISR(TIM1_OVF_vect)
{
  interruptCount++;
  TCNT1 = TIMER_PERIOD;            // preload timer 65536-16MHz/256/2Hz
  digitalWrite(LED, !digitalRead(LED));
}

ISR(PCINT0_vect)
{
  Serial.print("Pin change on PCINT6 to ");
  Serial.println(digitalRead(LED) ? "on" : "off");  

}


