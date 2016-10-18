long laenge, cm;

void setup() {
  Serial.begin(9600);
  pinMode(2,INPUT);
  pinMode(3,OUTPUT);
}

void loop() {

  digitalWrite(3, HIGH);
  delayMicroseconds(5);
  digitalWrite(3, LOW);

  laenge = pulseIn(2, HIGH);
  cm = (laenge*34)/2000;

  Serial.print(cm);
  Serial.println("cm");

  delay(1000);
  
}
