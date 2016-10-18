// Blink without Delay - Interrupt

// constants won't change. Used here to
// set pin numbers:
 // the number of the LED pin
const int ledPin =  10;


// Variables will change:
int ledState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated

// Variables will change:
int ledState1 = LOW;             // ledState used to set the LED
long previousMillis1 = 0;        // will store last time LED was updated

// Variables will change:
int ledState2 = LOW;             // ledState used to set the LED
long previousMillis2 = 0;        // will store last time LED was updated

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 1000;           // interval at which to blink (milliseconds)

long interval1 = 333;           // interval at which to blink (milliseconds)

long interval2 = 142;           // interval at which to blink (milliseconds)

void setup() {
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(29, OUTPUT);

  Serial.begin(8600);
}



void loop()
{
  // check to see if it's time to blink the LED; that is, if the
  // difference between the current time and last time you blinked
  // the LED is bigger than the interval at which you want to
  // blink the LED.

  // millis() - zaehlt die Zeit von aktivierung des Bords mittels
  // internem Taktgeber
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }

  if(currentMillis - previousMillis1 > interval1) {
    // save the last time you blinked the LED
    previousMillis1 = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState1 == LOW)
      ledState1 = HIGH;
    else
      ledState1 = LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(9, ledState1);
  }

  if(currentMillis - previousMillis2 > interval2) {
    // save the last time you blinked the LED
    previousMillis2 = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState2 == LOW)
      ledState2 = HIGH;
    else
      ledState2 = LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(29, ledState2);
  }
}
