// Client Publisher

#include <WiFi.h>
#include <PubSubClient.h>
#include "OneMsTaskTimer.h"
#define topic11 "sensor/push/nibble"
/***   161107 It works!   ***/
int oldMillis = 0; int pause = 500; //loop pause
char deviceId[] = "000000000000";
char buf[100]; //sprintf buffer
uint32_t push1cnt = 0; uint8_t flag1 = 0;
//char ssid[] = "C624AI-2"; char password[] = "1FEE98EC";
char ssid[] = "C624AI"; char password[] = "C27A11D2";
//char server[] = "192.168.0.250";//"iot.eclipse.org";  // MQTTServer to use
char server[] = "192.168.0.101";//MyMAC
void callback(char* topic, byte* payload, unsigned int length);
void action1();
void printWifiStatus();
WiFiClient wifiClient; PubSubClient client(server, 1883, callback, wifiClient);
OneMsTaskTimer_t myTask1 ={50,  action1, 0, 0};  // PUSH1 handling ISR

void setup(){
  Serial.begin(115200);
  Serial.print("Attempting to connect to Network named: "); Serial.println(ssid); 
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED) { Serial.print("."); delay(300); }
  Serial.println("Waiting for an ip address");
  while (WiFi.localIP() == INADDR_NONE) { Serial.print("."); delay(300); }
  printWifiStatus();
  MACAddress mac; uint8_t macOctets[6]; 
  mac = WiFi.macAddress(macOctets);
  Serial.print("MAC Address: "); Serial.println(mac);  
  // Use MAC Address as deviceId
  sprintf(deviceId, "%02x%02x%02x%02x%02x%02x", macOctets[0], macOctets[1], 
                    macOctets[2], macOctets[3], macOctets[4], macOctets[5]);
  Serial.print("deviceId: "); Serial.println(deviceId);
  pinMode(PUSH2, INPUT);
  OneMsTaskTimer::add(&myTask1); // start the task with 50ms period: PUSH1 check
  OneMsTaskTimer::start();
}

void loop(){
  static int currentMillis = 0;
  currentMillis = millis();
  if(currentMillis > oldMillis + pause){ 
    oldMillis = currentMillis;
    if (client.connected()) {
      if(flag1){
        flag1 = 0;
        Serial.print("Publishing "); 
        sprintf(buf, "%s", "Wir sind Helden");
        //sprintf(buf, "%d", push1cnt);
        Serial.println(buf);
        if(client.publish(topic11, buf)) {
          Serial.println("Publish success");
        } else {
          Serial.println("Publish failed");
        }
      }
    } else {   // connect to the broker
      Serial.println("Disconnected. Reconnecting....");  
      if(!client.connect(deviceId)){   
        Serial.println("Connection failed");
      } else {
        Serial.println("Connection success");
      }      
    }
  } 
}

// interrupt handler passed to OneMsTaskTimer
void action1(){
  uint8_t currentstate;
  static uint8_t oldstate = 0;
  currentstate = digitalRead(PUSH2);  
  if(oldstate != currentstate){
    oldstate = currentstate;
    if(currentstate == 1) {
      push1cnt++;
      flag1 = 1;
    }
  }
}

void printWifiStatus() {
  Serial.print("SSID: "); Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP(); Serial.print("IP Address: "); Serial.println(ip);
  long rssi = WiFi.RSSI(); 
  Serial.print("signal strength (RSSI):"); Serial.print(rssi); Serial.println(" dBm");
}

void callback(char* topic, byte* payload, unsigned int length) { } //not used now


