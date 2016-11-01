#include "OneMsTaskTimer.h"

class Flasher {
  bool state;
  int ledPin;
  long previousMillis;
  int ledState;
  long onTime;
  long offTime;

  OneMsTaskTimer_t my_task;

  public :
  Flasher(long onTime, long offTime, int l){
    onTime=onTime;
    offTime=offTime;
    ledPin =l;
    state = false;
    ledState = LOW;
    pinMode(ledPin, OUTPUT); 

    my_task = {offTime, TurnLedOn, 0, 0};
    OneMsTaskTimer::add(&my_task);
    OneMsTaskTimer::start();
  }
  void update(){


    // if the LED is off turn it on and vice-versa:
    if (state )
    {
      state = false;
      ledState = LOW;  
    }
    else
    {
      state = true;
      ledState = HIGH; 
    }
      
    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);    
  }

  void TurnLedOff()
  {
    digitalWrite(ledPin, LOW);   
    my_task = {offTime, Flasher::TurnLedOn, 0, 0};
  }

  void TurnLedOn()
  {
    digitalWrite(ledPin, HIGH);   
    my_task = {onTime, Flasher::TurnLedOff, 0, 0};
  }  
  
};

Flasher f1(100, 1000, 29);
//Flasher f2(9);
//Flasher f3(10);




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
/*  unsigned long currentMillis = millis();
  f1.update(currentMillis);
  f2.update(currentMillis);
  f3.update(currentMillis);*/
}

