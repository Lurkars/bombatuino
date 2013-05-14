void setup() {
   Serial.begin(9600);
}

void loop() {
  int val = analogRead(5);     
  Serial.println(val);
  delay(100);  // we have to make a delay to avoid overloading the serial port
}
