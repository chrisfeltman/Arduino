// which analog pin to connect
#define THERMISTORPIN A1
// resistance at 25 degrees C
#define THERMISTORNOMINAL 50000
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25
// how many samples to take and average, more takes longer
// but is more 'smooth'
#define NUMSAMPLES 5
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 4300
// the value of the 'other' resistor
#define SERIESRESISTOR 46600

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
  int sample1;
  int sample2;
  int sample3;
  int sample4;
  int sample5;
};

SEND_DATA_STRUCT samples;  

void setup() {
  Serial.begin(115200);
  Serial.println("Waiting for samples...");
  //mySerial.begin(9600);
  ET.begin(details(samples));
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);	 // Bits per sec
  vw_set_rx_pin(2);
  vw_rx_start();       // Start the receiver PLL running

}
void loop() 
{
 
  if(ET.receiveData())
  {
    printCalculation();
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
  
 
  average /= NUMSAMPLES;
  Serial.print("Average analog reading ");
  Serial.println(average);
  // convert the value to resistance
  average = 1024 / average - 1;
  average = SERIESRESISTOR / average;
  //average = average / SERIESRESISTOR;
  Serial.print("Thermistor resistance ");
  Serial.println(average);
  float steinhart;
  steinhart = average / THERMISTORNOMINAL; // (R/Ro)
  steinhart = log(steinhart); // ln(R/Ro)
  steinhart /= BCOEFFICIENT; // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart; // Invert
  steinhart -= 273.15; // convert to C
  float tempf = (steinhart * 9 / 5) + 32 + calibration;
  Serial.print("Temperature ");
  Serial.print(tempf);
  Serial.println(" *F");
  Serial.println();
}
