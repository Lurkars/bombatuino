#include <Wire.h>

//helper to check MCP23017 input
#define BIT_IS_SET(i, bits)  (1 << i & bits)

//array for the 8 inputs of bank A of MCP23017
boolean button[8];

void setup() {
	//set MIDI baudrate
	Serial.begin(31250);
	//start I2C
	Wire.begin();
}

void loop() {
	//0x20 address of MCP23017 (A0,A1,A2 to ground)
	Wire.beginTransmission(0x20);
	Wire.write(0x12); // set MCP23017 memory pointer to GPIOA address
	Wire.endTransmission();
	Wire.requestFrom(0x20, 1); // request one byte of data from MCP20317
	int inputs = Wire.read();
	delayMicroseconds(10);
	int i;
	for(i=0;i<8;i++) {
		//checkk for every input if its set
		if (BIT_IS_SET(i,inputs)) {
			//only send Note-on, when button was not pressed before
			if(!button[i]) {
				button[i] = true;
				midiSignal(144,60+i,115);
			}
		} else {
		//if not pressed, only send Note-off when button was pressed before
			if(button[i]) {
				button[i] = false;
				midiSignal(128,60+i,0);
			}
		}
	}  
}

//send MIDI signal
void midiSignal(byte b1, byte b2, byte b3) {
	Serial.write(b1);
	Serial.write(b2);
	Serial.write(b2);
}
