#include <Wire.h>

#include <bombatuino_INPUT_MCP23017.h>
#include <bombatuino_INPUT_74HC4051.h>
#include <bombatuino_ROTARY_ENCODER.h>
#include <bombatuino_MIDI.h>

INPUT_MCP23017 input_MCP23017;
INPUT_74HC4051 input_4051;
ROTARY_ENCODER rot(incement,decrement);
MIDI Midi;

void setup() {
  //Serial.begin(9600);
  Midi.begin();
  input_MCP23017.begin(0,sendNote);
  input_4051.begin(A0,11,12,13,sendCC);
}

void loop() {
  input_MCP23017.loop();  
  input_4051.loop();
}

void sendNote(int id, int pin, int value) {
   if (pin == 15) {
      rot.setPinB(value); 
   } else
      if (pin == 14) {
      rot.setPinA(value); 
   } else {
     if (value == HIGH) {
		 Midi.noteOn(id*16+pin,MIDI_MAX_DATA);
	 }
	 else {
		 //Midi.noteOff(id*16+pin);
	 }
   }
}

void sendCC(int id, int pin, int value) {
	Midi.controlChange(id*8+pin,value/8);
}

void incement() {
	Midi.noteOn(16+14,MIDI_MAX_DATA);
	//Midi.noteOff(16+14);
}

void decrement() {
	Midi.noteOn(16+15,MIDI_MAX_DATA);
	//Midi.noteOff(16+15); 
}
