#include <Wire.h>

#include <bombatuino_INPUT_MCP23017.h>
#include <bombatuino_INPUT_74HC4051.h>
#include <bombatuino_MIDI.h>
#include <bombatuino_ROTARY_ENCODER.h>

MIDI Midi;

INPUT_MCP23017 input_MCP23017_0;
INPUT_MCP23017 input_MCP23017_1;
INPUT_MCP23017 input_MCP23017_3;
INPUT_MCP23017 input_MCP23017_4;

INPUT_74HC4051 input_4051_A0;
INPUT_74HC4051 input_4051_A1;
INPUT_74HC4051 input_4051_A2;

ROTARY_ENCODER rotary_encoder_jogwheel_left(rotary_encoder_jogwheel_left_inc, rotary_encoder_jogwheel_left_dec);
ROTARY_ENCODER rotary_encoder_jogwheel_right(rotary_encoder_jogwheel_right_inc, rotary_encoder_jogwheel_right_dec);
ROTARY_ENCODER rotary_encoder_browse(rotary_encoder_browse_inc,rotary_encoder_browse_dec);


void setup() {
  Serial.begin(9600);
  input_MCP23017_0.begin(0,digitalCallback);
  input_MCP23017_1.begin(1,digitalCallback1);
  input_MCP23017_3.begin(3,digitalCallback3);
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
    Serial.print("id ");
    Serial.print(id);
    Serial.print(" pin ");
    Serial.print(pin);
    Serial.print(" : ");
    Serial.print(value);
    Serial.println(); 
}


void digitalCallback(int id, int pin, int value) {
    Serial.print("id ");
    Serial.print(id);
    Serial.print(" pin ");
    Serial.print(pin);
    Serial.print(" : ");
    Serial.print(value);
    Serial.println(); 
}


void digitalCallback1(int id, int pin, int value) {
    if (pin == 6)
      rotary_encoder_jogwheel_left.setPinA(value);
    if (pin == 7)
      rotary_encoder_jogwheel_left.setPinB(value);
    if (pin != 6 && pin !=7) {
          Serial.print("id ");
          Serial.print(id);
          Serial.print(" pin ");
          Serial.print(pin);
          Serial.print(" : ");
          Serial.print(value);
          Serial.println(); 
    }
}

void digitalCallback3(int id, int pin, int value) {
    if (pin == 9)
      rotary_encoder_jogwheel_right.setPinA(value);
    if (pin == 10)
      rotary_encoder_jogwheel_right.setPinB(value);
    if (pin == 6)
      rotary_encoder_browse.setPinA(value);
    if (pin == 5)
      rotary_encoder_browse.setPinB(value);
    if (pin!= 9 && pin != 10 && pin != 6 && pin != 5){
          Serial.print("id ");
          Serial.print(id);
          Serial.print(" pin ");
          Serial.print(pin);
          Serial.print(" : ");
          Serial.print(value);
          Serial.println(); 
    }
}

//left jogwheel
void rotary_encoder_jogwheel_left_inc() {
    Serial.println("jogwheel_left_inc");
}

void rotary_encoder_jogwheel_left_dec() {
    Serial.println("jogwheel_left_dec");
}

//right jogwheel
void rotary_encoder_jogwheel_right_inc() {
    Serial.println("jogwheel_right_inc");
}

void rotary_encoder_jogwheel_right_dec() {
    Serial.println("jogwheel_right_dec");
}

//Browse
void rotary_encoder_browse_inc() {
    Serial.println("browse inc"); 
}

void rotary_encoder_browse_dec() {
    Serial.println("browse dec"); 
}
