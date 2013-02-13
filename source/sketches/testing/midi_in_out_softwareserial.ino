#include <SoftwareSerial.h>

// RX, TX for MIDI out
SoftwareSerial MIDI(10, 11); 

//button pin
const int switchPin = 6;
//rotary encoder pins
const int encAPin = 4;
const int encBPin = 5;

//for sending note-off once after button is released
boolean btnOff = false;

//old rotary encoder value
int encA = LOW;
//read rotary encoder value
int enc = HIGH;

void setup()  
{
  //printing baudrate
  Serial.begin(9600);
  //MIDI baudrate for software serial (pin 10 & 11)
  MIDI.begin(31250);
  //button and encoder pins as input
  pinMode(switchPin, INPUT);
  pinMode(encAPin, INPUT);
  pinMode(encBPin, INPUT);
  //activate pullup-resistors (read value is inverted, so LOW is active)
  digitalWrite(switchPin, HIGH);
  digitalWrite(encAPin, HIGH);
  digitalWrite(encBPin, HIGH);
}

void loop()
{
  //print incoming bytes on softwareserial, just for checking MIDI-in, worked
  if (MIDI.available())
    Serial.println(MIDI.read());
  
  //check if button is pressed
  if (digitalRead(switchPin) == LOW)
  {  
    if (!btnOff) {
      //send note on
      midiSignal(144,60,100);
      btnOff = true;
    }
  }  
  if (digitalRead(switchPin) == HIGH)
    {
    //send note off
    if (btnOff) {
        midiSignal(128,60,0);
        btnOff = false;
    }
  }
  
  //read encoder pin A
  enc = digitalRead(encAPin);
  //check if rotary encoder is turned
  if ((encA == HIGH) && (enc == LOW)) {
      //check direction of turning
      if (digitalRead(encBPin) == HIGH) {
         //send note on and note off directly, so signal is send on every turn 
         midiSignal(144,62,100);
         midiSignal(128,62,100);
       } else {
         //other direction, other note value
         midiSignal(144,61,100);
         midiSignal(128,61,100);
       }
   } 
   //save "old" encoder value
   encA = enc;
}

//send MIDI signal through softwareserial
void midiSignal(byte b1, byte b2, byte b3) {
  //debug printing
  Serial.print("send: ");
  Serial.print(b1);
  Serial.print(" | ");
  Serial.print(b2);
  Serial.print(" | ");
  Serial.print(b3);
  Serial.println("");
  MIDI.write(b1);
  MIDI.write(b2);
  MIDI.write(b2);
}
