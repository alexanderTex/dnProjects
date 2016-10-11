/*
  Blink
  The basic Energia example.
  Turns on an LED on for one second, then off for one second, repeatedly.
  Change the LED define to blink other LEDs.
  
  Hardware Required:
  * LaunchPad with an LED
  
  This example code is in the public domain.
*/

// most launchpads have a red LED
#define LEDR RED_LED
#define LEDG GREEN_LED
#define LEDY YELLOW_LED

//see pins_energia.h for more LED definitions
//#define LEDO GREEN_LED
  
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(LEDR, OUTPUT);     
  pinMode(LEDG, OUTPUT);    
  pinMode(LEDY, OUTPUT);     
}
void lightningUnit(int pin){
  digitalWrite(pin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(pin, LOW);    // turn the LED off by making the voltage LOW
  delay(100);               // wait for a second
  
}

// the loop routine runs over and over again forever:
void loop() {
  lightningUnit(LEDR);               // wait for a second
  lightningUnit(LEDG);
  lightningUnit(LEDY);
}
