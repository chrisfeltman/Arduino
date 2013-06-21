//#include<VirtualWire.h>
#include<SoftwareSerial.h>
//#include<Narcoleptic.h>
#include <SoftEasyTransfer.h>
#define LED 0
#define PTT 3



SoftwareSerial mySerial(5,2);
SoftEasyTransfer ET;

struct SEND_DATA_STRUCT
{
  int sample1;
  int sample2;
  int sample3;
  int sample4;
  int sample5;
};

SEND_DATA_STRUCT samples;  
  
  
void setup()
{
  //adcOff();
  //setup_watchdog();
  pinMode(PTT, OUTPUT);
  pinMode(LED, OUTPUT);
  //vw_setup(2000);	 // Bits per sec
  //vw_set_tx_pin(1);
  //DIDR0 = 0x00; //enable digital input buffers on all ADC0-ADC5 pins.
  mySerial.begin(9600);
  ET.begin(details(samples), &mySerial);


}


void loop()
{
  //adcOn();
  sendSample();

  //adcOff();
  //Narcoleptic.delay(8000);
  delay(500);

}

void sendSample()
{
   
  int thermistorReading;
  
  samples.sample1 = analogRead(A2);
  delay(10);
  samples.sample2 = analogRead(A2);
  delay(10);
  samples.sample3 = analogRead(A2);
  delay(10);
  samples.sample4 = analogRead(A2);
  delay(10);
  samples.sample5 = analogRead(A2);
  delay(10);
 
  ET.sendData();
  digitalWrite(LED, HIGH); // Flash a light to show transmitting
  digitalWrite(PTT, HIGH); // turn on the transmitter


  //vw_send((uint8_t *)msg, 8);
  //vw_wait_tx(); // Wait until the whole message is gone

  digitalWrite(PTT, LOW);  /// xmitter off 
  delay(500);
  digitalWrite(LED, LOW);  // LED off
}


void adcOff()
{


  ADCSRA &= ~(1<<ADEN); //Disable ADC
  ACSR = (1<<ACD); //Disable the analog comparator
  DIDR0 = 0x3F; //Disable digital input buffers on all ADC0-ADC5 pins.

}

void adcOn()
{
  ADCSRA &= (1<<ADEN); //Enable ADC
  ACSR = (0<<ACD); //Enable the analog comparator
  DIDR0 = 0x00; // Enable digital input buffers on all ADC0-ADC5 pins.

}




