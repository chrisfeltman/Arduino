/*******************************************************************************************
* Send Thermistor readings wirelessly via 433 Mhz cheapo transmitter
* CEF 6-24-2013
* Revisions:
* 0.11 - added 2N222 to act as PTT for transmitter (it doesn't have one built in)
* 0.12 - added power down ADC for extra power savings
* 
* TODO - add voltage monitor reading for 9V battery to data packet
********************************************************************************************/

#include<VirtualWire.h>
#include<Narcoleptic.h>
#include <EasyTransferVirtualWire.h>

// pins used
#define LED 0
#define PTT 2
#define THERM A3

#define SENDINTERVAL 4    // how many 8 second sleep cycles to wait before transmitting
#define REPEATMESSAGE 3   // how many times to transmit the packet for redundancy

EasyTransferVirtualWire ET;

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

  pinMode(PTT, OUTPUT);
  pinMode(LED, OUTPUT);

  vw_setup(2000);	 // Bits per sec
  vw_set_tx_pin(1);
  vw_set_ptt_pin(PTT);

  ET.begin(details(samples));
}

void loop()
{
  static byte wakeCount = 0;

  if (wakeCount % SENDINTERVAL == 0)
  {
    transmitSampleSet();
  }
  wakeCount++;
  Narcoleptic.delay(8000);  // put the cpu to sleep for 8 secs

}

void transmitSampleSet()
{
  adcOn();
  for(byte i = 0; i < REPEATMESSAGE; i++)
  {
    sendSample();
  }
  adcOff();

}

void sendSample()
{

  samples.sample1 = analogRead(THERM);
  delay(10);
  
  samples.sample2 = analogRead(THERM);
  delay(10);
  
  samples.sample3 = analogRead(THERM);
  delay(10);
  
  samples.sample4 = analogRead(THERM);
  delay(10);
  
  samples.sample5 = analogRead(THERM);

  digitalWrite(LED, HIGH); // Flash a light to show transmitting
  ET.sendData();
  delay(500);
  digitalWrite(LED, LOW);  // LED off
}

void adcOn()
{
  bitSet(ADCSRA,ADEN);  // set enable bit in ADC Control Reg
  delay(10);             // give ADC time to stabilize
}

void adcOff()
{
  bitClear(ADCSRA, ADEN);  // clear enable bit in ADC Control Reg
}
