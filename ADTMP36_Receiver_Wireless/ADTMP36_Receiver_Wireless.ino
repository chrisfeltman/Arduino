// which analog pin to connect
#define TEMPSENSOR A1
// reference ADC reading at 25 degrees C
#define BASELINE_MV_AT_25 750
#define BASELINE_TEMP 25
#define MILLIVOLTS_PER_DEGC 10
#define MILLIVOLT_CORRECTION 13.0

// how many samples to take and average, more takes longer
// but is more 'smooth'
#define NUMSAMPLES 5

#define LED 13

//#include <SoftwareSerial.h>
//#include <SoftEasyTransfer.h>
#include <VirtualWire.h>
#include <EasyTransferVirtualWire.h>

const float calibration = -2.15;

//SoftwareSerial mySerial(3,4);
//SoftEasyTransfer ET;
EasyTransferVirtualWire ET;

struct SEND_DATA_STRUCT
{
  int batteryVoltage;
  int sample1;
  int sample2;
  int sample3;
  int sample4;
  int sample5;
};

SEND_DATA_STRUCT samples;  

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  delay(5);
  Serial.println("Waiting for samples...");

  ET.begin(details(samples));

  vw_setup(2000);	 // Bits per sec
  vw_set_rx_pin(2);
  vw_rx_start();       // Start the receiver PLL running

}
void loop() 
{
 
  if(ET.receiveData())
  {
    digitalWrite(LED, HIGH);
    printCalculation();
    digitalWrite(LED, LOW);
  }  
}

void printCalculation()
{
 uint8_t i;
  float average;
  // take N samples in a row, with a slight delay
  
  // average all the samples out
  average = 0;
  
  Serial.print("first sample was ");
  Serial.println(samples.sample1);
  average += samples.sample1;
  Serial.print("second sample was ");
  Serial.println(samples.sample2);
  average += samples.sample2;
  Serial.print("third sample was ");
  Serial.println(samples.sample3);
  average += samples.sample3;
  Serial.print("fourth sample was ");
  Serial.println(samples.sample4);
  average += samples.sample4;
  Serial.print("fifth sample was "); 
  Serial.println(samples.sample5); 
  average += samples.sample5;
  
  Serial.print("Battery voltage is ");
  Serial.println(samples.batteryVoltage);
 
  average /= NUMSAMPLES;
  Serial.print("Average analog reading ");
  Serial.println(average);
  
  float averageMillis = round((1100.0 / 1024.0 * average) - MILLIVOLT_CORRECTION);
  Serial.print("Average millivolt reading ");
  Serial.println(averageMillis);
  
  float tempC = (averageMillis - 500) / 10;
  Serial.print("Temperature ");
  Serial.print(tempC);
  Serial.println(" *C");
 
  float tempf = (tempC * 9 / 5) + 32;
  Serial.print("Temperature ");
  Serial.print(tempf);
  Serial.println(" *F");
  Serial.println();
}
