#include<VirtualWire.h>
//#include<SoftwareSerial.h>
#include<Narcoleptic.h>
//#include <SoftEasyTransfer.h>
#include <EasyTransferVirtualWire.h>
#define LED 0
//#define PTT 3
#define THERM A3

//SoftwareSerial mySerial(5,2);
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
  //adcOff();
  //setup_watchdog();
  //pinMode(PTT, OUTPUT);
  pinMode(LED, OUTPUT);
 
  vw_setup(2000);	 // Bits per sec
  vw_set_tx_pin(1);
  //vw_set_ptt_pin(PTT);
 
  ET.begin(details(samples));


}


void loop()
{
  //adcOn();
  sendSample();

  //adcOff();
  Narcoleptic.delay(8000);
  //delay(500);

}

void sendSample()
{
   
  int thermistorReading;
  
  samples.sample1 = analogRead(THERM);
  //samples.sample1 = 550;
  delay(10);
  samples.sample2 = analogRead(THERM);
  //samples.sample2 = 550;
  delay(10);
  samples.sample3 = analogRead(THERM);
  //samples.sample3 = 550;
  delay(10);
  samples.sample4 = analogRead(THERM);
  //samples.sample4 = 550;
  delay(10);
  samples.sample5 = analogRead(THERM);
  //samples.sample5 = 550;
  delay(10);
 
  
  digitalWrite(LED, HIGH); // Flash a light to show transmitting
  //digitalWrite(PTT, HIGH); // turn on the transmitter
  ET.sendData();
  delay(500);
  //digitalWrite(PTT, LOW);  /// xmitter off  
  digitalWrite(LED, LOW);  // LED off
}






