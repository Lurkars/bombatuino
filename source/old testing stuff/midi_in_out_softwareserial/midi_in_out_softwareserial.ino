#include <Wire.h>
#include <SoftwareSerial.h>

#define IOPOLA   0x02
#define GPPUA   0x12
#define BIT_IS_SET(i, bits)  (1 << i & bits)

SoftwareSerial MIDI(10,11);

boolean button[8];

void setup()  
{
  //printing baudrate
  Serial.begin(9600);
  MIDI.begin(31250);
  Wire.begin();
   Wire.beginTransmission(0x20);
  Wire.write(0x12); // set MCP23017 memory pointer to GPIOB address
  Wire.write(0xFF); //PULLUP
  Wire.endTransmission();
}

void loop()
{
  Wire.beginTransmission(0x20);
  Wire.write(0x12); // set MCP23017 memory pointer to GPIOB address
  Wire.endTransmission();
  Wire.requestFrom(0x20, 1); // request one byte of data from MCP20317
  int inputs = Wire.read();
  delayMicroseconds(10);
  //check if button is pressed
  
  int i;
  for(i=0;i<8;i++) {
    if (BIT_IS_SET(i,inputs)) {
      if(!button[i]) {
        button[i] = true;
        midiSignal(144,60+i,115);
      }
    } else {
      if(button[i]) {
        button[i] = false;
        midiSignal(128,60+i,0);
      }
    }
  }  
}

//send MIDI signal through softwareserial
void midiSignal(byte b1, byte b2, byte b3) {
  Serial.print(b1);
  Serial.print(" ");
  Serial.print(b2);
  Serial.print(" ");
  Serial.print(b3);
  Serial.print(" ");
  Serial.println();
  MIDI.write(b1);
  MIDI.write(b2);
  MIDI.write(b2);
}
