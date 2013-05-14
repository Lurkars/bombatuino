#include <Wire.h>

#include <bombatuino_INPUT_MCP23017.h>
#include <bombatuino_INPUT_74HC4051.h>
#include <bombatuino_ROTARY_ENCODER.h>
#include <bombatuino_MIDI.h>


MIDI Midi;

INPUT_MCP23017 input_MCP23017_0;
INPUT_MCP23017 input_MCP23017_1;
INPUT_MCP23017 input_MCP23017_3;
INPUT_MCP23017 input_MCP23017_4;

INPUT_74HC4051 input_4051_A0;
INPUT_74HC4051 input_4051_A1;
INPUT_74HC4051 input_4051_A2;

ROTARY_ENCODER re_JogWheel1(rotaryLeftJogWheel1,rotaryRightJogWheel1);
ROTARY_ENCODER re_JogWheel2(rotaryLeftJogWheel2,rotaryRightJogWheel2);
ROTARY_ENCODER re_Browse(rotaryLeftBrowse,rotaryRightBrowse);

void setup() {
  Midi.begin();
  input_MCP23017_0.begin(0,digitalCallback);
  input_MCP23017_1.begin(1,digitalCallback);
  input_MCP23017_3.begin(3,digitalCallback);
  input_MCP23017_4.begin(4,digitalCallback);
  
  input_4051_A0.begin(A0,8,9,10,analogCallback);
  input_4051_A1.begin(A1,8,9,10,analogCallback);
  input_4051_A2.begin(A2,8,9,10,analogCallback);
}

void loop() {
  input_MCP23017_0.loop(); 
  input_MCP23017_1.loop(); 
  input_MCP23017_3.loop(); 
  input_MCP23017_4.loop(); 
  input_4051_A0.loop();
  input_4051_A1.loop();
  input_4051_A2.loop();
}

void analogCallback(int id, int pin, int value) {
  Midi.controlChange((id-A0) * 8 + pin,value);
}

void digitalCallback(int id, int pin, int value) {
    if (id == 1 && pin == 6)
      re_JogWheel1.setPinA(value);
    if (id == 1 && pin == 7)
      re_JogWheel1.setPinB(value);
    if (id == 3 && pin == 9)
      re_JogWheel2.setPinA(value);
    if (id == 3 && pin == 10)
      re_JogWheel2.setPinB(value);
    if (id == 3 && pin == 6)
      re_Browse.setPinA(value);
    if (id == 3 && pin == 5)
      re_Browse.setPinB(value);
    if ((id == 3 && pin != 5 && pin != 6 && pin!= 9 && pin != 10) || (id == 1 && pin != 6 && pin !=7) || (id == 0) || (id == 4)) {
      if (value == HIGH)
        Midi.noteOn(id * 16 + pin, MIDI_MAX_DATA);
      else Midi.noteOff(id * 16 + pin);
    }
}

//JogWheel1
void rotaryLeftJogWheel1() {
   Midi.noteOn(1 * 16 + 6, MIDI_MAX_DATA);
   Midi.noteOff(1 * 16 + 6);
}

void rotaryRightJogWheel1() {
   Midi.noteOn(1 * 16 + 7, MIDI_MAX_DATA);
   Midi.noteOff(1 * 16 + 7);
}


//JogWheel2
void rotaryLeftJogWheel2() {
   Midi.noteOn(3 * 16 + 9, MIDI_MAX_DATA);
   Midi.noteOff(3 * 16 + 9);
}

void rotaryRightJogWheel2() {
   Midi.noteOn(3 * 16 + 10, MIDI_MAX_DATA);
   Midi.noteOff(3 * 16 + 10);
}


//Browse
void rotaryLeftBrowse() {
   Midi.noteOn(3 * 16 + 6, MIDI_MAX_DATA);
   Midi.noteOff(3 * 16 + 6);
}

void rotaryRightBrowse() {
   Midi.noteOn(3 * 16 + 5, MIDI_MAX_DATA);
   Midi.noteOff(3 * 16 + 5);
}
