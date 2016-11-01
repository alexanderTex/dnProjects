class Flasher {
  long onTime;
  long offTime;
  bool state;
  int ledPin;
  long previousMillis;
  int ledState;

  public :
  Flasher(int onT, int offT, int l){
    onTime = onT;
    offTime = offT;
    ledPin =l;
    state = false;
    previousMillis=0;
    ledState = LOW;
    pinMode(ledPin, OUTPUT); 
  }
  void update( unsigned long cm){


    // if the LED is off turn it on and vice-versa:
    if (state && cm - previousMillis > onTime)
    {
      state = false;
      ledState = LOW;
      previousMillis = cm;  
    }
    else if(!state && cm - previousMillis > offTime)
    {
      state = true;
      ledState = HIGH;
      previousMillis = cm;  
    }
      
    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);    
  }
};

Flasher f1(100, 1000, 29);
Flasher f2(100, 333, 9);
Flasher f3(100, 142, 10);

void setup() {
  // set the digital pin as output:
     

  Serial.begin(8600);
}



void loop()
{
  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the 
  // difference between the current time and last time you blinked 
  // the LED is bigger than the interval at which you want to 
  // blink the LED.
  unsigned long currentMillis = millis();
  f1.update(currentMillis);
  f2.update(currentMillis);
  f3.update(currentMillis);
}

