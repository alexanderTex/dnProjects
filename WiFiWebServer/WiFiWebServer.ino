/*
  WiFi Web Server

 A simple web server that shows the value of the analog input pins.
 using a WiFi shield.

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 Circuit:
 * WiFi shield attached
 * Analog inputs attached to pins A0 through A5 (optional)

 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe

 */

#include <SPI.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>


// your network name also called SSID
char ssid[] = "C624AI-2";
// your network password
char password[] = "1FEE98EC";
// your network key Index number (needed only for WEP)
int keyIndex = 0;

WiFiServer server(80);
long laenge, cm;

void setup() {
  Serial.begin(115200);      // initialize serial communication
  pinMode(RED_LED, OUTPUT);      // set the LED pin mode
  pinMode(GREEN_LED, OUTPUT);      // set the LED pin mode
  pinMode(YELLOW_LED, OUTPUT);      // set the LED pin mode


  
  pinMode(2,INPUT); //DistanceSensorEcho
  pinMode(3,OUTPUT);//DistanceSensorTrigger
  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to Network named: ");
  // print the network name (SSID);
  Serial.println(ssid); 
  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED) {
    // print dots while we wait to connect
    Serial.print(".");
    delay(300);
  }
  
  Serial.println("\nYou're connected to the network");
  Serial.println("Waiting for an ip address");
  
  while (WiFi.localIP() == INADDR_NONE) {
    // print dots while we wait for an ip addresss
    Serial.print(".");
    delay(300);
  }

  // you're connected now, so print out the status  
  printWifiStatus();
  
  Serial.println("Starting webserver on port 80");
  server.begin();                           // start the web server on port 80
  Serial.println("Webserver started!");

}

boolean endsWith(char* inString, char* compString){
  int compLength = strlen(compString);
  int strLength = strlen(inString);

  int i;
  for (i=0; i< compLength; i++){
    char a= inString[(strLength-1)-i];
    char b = compString[(compLength -1)-i];
    if(a != b) {
      return false;
    }
  }
  return true;
}

void loop() {
  digitalWrite(3, HIGH);
  delayMicroseconds(5);
  digitalWrite(3, LOW);

  laenge = pulseIn(2, HIGH);
  cm = (laenge*34)/2000;

  Serial.print(cm);
  Serial.println("cm");

 // delay(1000);
  
  
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    char buffer[150]={0};
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 1");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output the value of each analog input pin
          
        client.println("<html><head><title>Ultrasonic Device Super Hyper Distance Dingelidingong Server</title></head><body align=center>");
        client.println("<h1 align=center>Ultrasonic Device Super Hyper Distance Dingelidingong Server</h1>");
        client.print(cm);
        client.println(" cm");

        client.println("R LED <button onclick=\"location.href='/R'\">ON/OFF</button><br>");
        client.println("G LED <button onclick=\"location.href='/G'\">ON/OFF</button><br>");
        client.println("Y LED <button onclick=\"location.href='/Y'\">ON/OFF</button><br>");
            
            
            
          client.println("</body></html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
        if (endsWith(buffer, "GET /R")){
          if (RED_LED == HIGH) digitalWrite(RED_LED, LOW);
          else digitalWrite(RED_LED,HIGH);
        }
        if (endsWith(buffer, "GET /G")){
          if (GREEN_LED == HIGH) digitalWrite(GREEN_LED,LOW);
          else digitalWrite(GREEN_LED, HIGH);
        }
        if (endsWith(buffer, "GET /Y")){
          if (YELLOW_LED == HIGH) digitalWrite(YELLOW_LED,LOW);
          else digitalWrite(YELLOW_LED,HIGH);
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("Network Name: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

