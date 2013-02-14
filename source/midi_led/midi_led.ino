/*
 MIDI note player
 
 This sketch shows how to use the serial transmit pin (pin 1) to send MIDI note data.
 If this circuit is connected to a MIDI synth, it will play 
 the notes F#-0 (0x1E) to F#-5 (0x5A) in sequence.

 
 The circuit:
 * digital in 1 connected to MIDI jack pin 5
 * MIDI jack pin 2 connected to ground
 * MIDI jack pin 4 connected to +5V through 220-ohm resistor
 Attach a MIDI cable to the jack, then to a MIDI synth, and play music.

 created 13 Jun 2006
 modified 13 Aug 2012
 by Tom Igoe 

 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/Midi
 
 */

void setup() {
  //  Set MIDI baud rate:
  Serial.begin(9600);
  pinMode(2, INPUT);
  digitalWrite(2, HIGH);
  pinMode(3, OUTPUT); 
}

void loop() {
  button();
}

void button() {
  int sensorVal = digitalRead(2);
  if (sensorVal == HIGH) {
    digitalWrite(3, LOW);
  } 
  else {
    digitalWrite(3, HIGH);
  }
}
