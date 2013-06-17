#include<VirtualWire.h>
#include<avr/sleep.h>
#include <avr/wdt.h>
#define LED 0
#define PTT 3


void setup()
{
    //setPowerSave();
    //setup_watchdog(8);
    pinMode(PTT, OUTPUT);
    pinMode(LED, OUTPUT);
    vw_setup(2000);	 // Bits per sec
    vw_set_tx_pin(1);
    //set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    //sleep_enable();  
}

byte count = 0;
void loop()
{
      
    char msg[7] = {'h','e','l','l','o',' ', '#'};
    msg[6] = count++;
    

    digitalWrite(0, HIGH); // Flash a light to show transmitting
    digitalWrite(PTT, HIGH); // turn on the transmitter
    delay(5); // this delay may not be necessary
    
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx(); // Wait until the whole message is gone
    
 
    digitalWrite(0, LOW);
    digitalWrite(PTT, LOW);  /// xmitter off 
    delay(5000);
    //sleep_mode(); 
}


void setPowerSave()
{
  ADCSRA &= ~(1<<ADEN); //Disable ADC
  ACSR = (1<<ACD); //Disable the analog comparator
  DIDR0 = 0x3F; //Disable digital input buffers on all ADC0-ADC5 pins.
}

// 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms
// 6=1 sec,7=2 sec, 8=4 sec, 9= 8sec
void setup_watchdog(int ii) {
   byte bb;
  int ww;
  if (ii > 9 ) ii=9;
  bb=ii & 7;
  if (ii > 7) bb|= (1<<5);
  bb|= (1<<WDCE);
  ww=bb;

  MCUSR &= ~(1<<WDRF);
  // start timed sequence
  WDTCR |= (1<<WDCE) | (1<<WDE);
  // set new watchdog timeout value
  WDTCR = bb;
  WDTCR |= _BV(WDIE);// timer goes off every 8 seconds
 
  sei(); //Enable interrupts
}

ISR(PCINT0_vect)
{
  //This vector is only here to wake unit up from sleep mode
}

