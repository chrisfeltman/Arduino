/*
  Counter
  Makes the LED count up repeatedly from one to ten.
 
 */
 
#define BLINK_DELAY 250
#define LOOP_DELAY 1000
#define MAXCOUNT 20

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:

const int led = 13;
int counter = 1;  // keep track of current count

//prototypes
void blinkLed();

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT); 
  Serial.begin(9600);  
}

// the loop routine runs over and over again forever:
void loop() {
  
  Serial.print("Count is now ");
  Serial.println(counter);
  for(int i = 0; i < counter; i++)
  {
    blinkLed();
  }
  
  counter++;
  if(counter > MAXCOUNT)
  {
    Serial.println("Resetting counter...");
    counter = 1;
  }
  delay(LOOP_DELAY);
    
}

void blinkLed()
{
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(BLINK_DELAY);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(BLINK_DELAY);  
}
  
