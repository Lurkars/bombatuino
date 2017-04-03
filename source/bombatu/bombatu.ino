#include <Wire.h>

#include <bombatuino_INPUT_MCP23017.h>
#include <bombatuino_INPUT_74HC4051.h>
#include <bombatuino_MIDI.h>
#include <bombatuino_ROTARY_ENCODER.h>

MIDI Midi;

//MCP23017 I2C addresses 0,1,3 and 4 (2 is unused yet)
INPUT_MCP23017 input_MCP23017_0;
INPUT_MCP23017 input_MCP23017_1;
INPUT_MCP23017 input_MCP23017_3;
INPUT_MCP23017 input_MCP23017_4;

//three 74HC4051 on analog pins A0,A1,A2; select on digital pins 8,9,10
INPUT_74HC4051 input_4051_A0;
INPUT_74HC4051 input_4051_A1;
INPUT_74HC4051 input_4051_A2;


//left jogwheel, sends CC message on controller id 0x7A with value 65 (increment)
void rotary_encoder_jogwheel_left_inc() {
  Midi.controlChange(MIDI_MAX_DATA-5,65);
}

//left jogwheel, sends CC message on controller id 0x7A with value 63 (decrement)
void rotary_encoder_jogwheel_left_dec() {
  Midi.controlChange(MIDI_MAX_DATA-5,63);
}

//right jogwheel, sends CC message on controller id 0x79 with value 65 (increment)
void rotary_encoder_jogwheel_right_inc() {
  Midi.controlChange(MIDI_MAX_DATA-6,65);
}

//right jogwheel, sends CC message on controller id 0x79 with value 63 (decrement)
void rotary_encoder_jogwheel_right_dec() {
  Midi.controlChange(MIDI_MAX_DATA-6,63);
}

//browse, sends note-on/off signal with note 0x36 [equals to default digital callback note] (increment)
void rotary_encoder_browse_inc() {
  Midi.noteOn(3 * 16 + 6, MIDI_MAX_DATA);
  Midi.noteOff(3 * 16 + 6);
}

//browse, sends note-on/off signal with note 0x35 [equals to default digital callback note] (decrement)
void rotary_encoder_browse_dec() {
  Midi.noteOn(3 * 16 + 5, MIDI_MAX_DATA);
  Midi.noteOff(3 * 16 + 5);
}

//three rotary encoders connected to input_MCP23017_1 and input_MCP23017_3
ROTARY_ENCODER rotary_encoder_jogwheel_left(rotary_encoder_jogwheel_left_inc, rotary_encoder_jogwheel_left_dec); //input_MCP23017_1 pins 6 and 7
ROTARY_ENCODER rotary_encoder_jogwheel_right(rotary_encoder_jogwheel_right_inc, rotary_encoder_jogwheel_right_dec); //input_MCP23017_3 pins 9 and 1
ROTARY_ENCODER rotary_encoder_browse(rotary_encoder_browse_inc,rotary_encoder_browse_dec); //input_MCP23017_3 pins 5 and 6


void setup() {
	//initialize MIDI
	Midi.begin();
	//initialize MCP23017s
	input_MCP23017_0.begin(0,digitalCallback);
	input_MCP23017_1.begin(1,digitalCallback1);
	input_MCP23017_3.begin(3,digitalCallback3);
	input_MCP23017_4.begin(4,digitalCallback);
	//initialize 74HC4051s
	input_4051_A0.begin(A0,8,9,10,analogCallback);
	input_4051_A1.begin(A1,8,9,10,analogCallback);
	input_4051_A2.begin(A2,8,9,10,analogCallback);
}

void loop() {
	//loop MCP23017s for callbacks
	input_MCP23017_0.loop(); 
	input_MCP23017_1.loop(); 
	input_MCP23017_3.loop(); 
	input_MCP23017_4.loop();
	//loop 74HC4051s for callback
	input_4051_A0.loop();
	input_4051_A1.loop();
	input_4051_A2.loop();
}


//callback for analog, sends CC message with unique controller id
void analogCallback(int id, int pin, int value) {
	Midi.controlChange((id-A0) * 8 + pin,value);
}

//default callback for buttons, sends note-on/off message with unique note value
void digitalCallback(int id, int pin, int value) {
	if (value == HIGH)
		Midi.noteOn(id * 16 + pin, MIDI_MAX_DATA);
	else Midi.noteOff(id * 16 + pin);
}

//callback for input_MCP23017_1, checks for rotary_encoder_jogwheel_left, otherwise default callback
void digitalCallback1(int id, int pin, int value) {
	if (pin == 6)
		rotary_encoder_jogwheel_left.setPinA(value);
	if (pin == 7)
		rotary_encoder_jogwheel_left.setPinB(value);
	if (pin != 6 && pin !=7)
		digitalCallback(id,pin,value);
}

//callback for input_MCP23017_3, checks for rotary_encoder_jogwheel_right and rotary_encoder_browse, otherwise default callback
void digitalCallback3(int id, int pin, int value) {
	if (pin == 9)
		rotary_encoder_jogwheel_right.setPinA(value);
	if (pin == 10)
		rotary_encoder_jogwheel_right.setPinB(value);
	if (pin == 6)
		rotary_encoder_browse.setPinA(value);
	if (pin == 5)
		rotary_encoder_browse.setPinB(value);
	if (pin!= 9 && pin != 10 && pin != 6 && pin != 5)
		digitalCallback(id,pin,value);
}
