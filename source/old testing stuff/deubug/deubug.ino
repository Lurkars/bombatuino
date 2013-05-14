#include <Wire.h>

#include <bombatuino_INPUT_MCP23017.h>
#include <bombatuino_INPUT_74HC4051.h>
#include <bombatuino_ROTARY_ENCODER.h>

INPUT_MCP23017 input_MCP23017_0;
INPUT_MCP23017 input_MCP23017_1;
INPUT_MCP23017 input_MCP23017_3;
INPUT_MCP23017 input_MCP23017_4;

INPUT_74HC4051 input_4051_A0;
INPUT_74HC4051 input_4051_A1;
INPUT_74HC4051 input_4051_A2;


ROTARY_ENCODER re_jogwheel(jogwheel);
//ROTARY_ENCODER re_JogWheel1(rotaryLeftJogWheel1,rotaryRightJogWheel1);
//ROTARY_ENCODER re_JogWheel2(rotaryLeftJogWheel2,rotaryRightJogWheel2);
//ROTARY_ENCODER re_Browse(rotaryLeftBrowse,rotaryRightBrowse);

void setup() {
  Serial.begin(9600);
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
    Serial.print("id ");
    Serial.print(pin);
    Serial.print(" pin ");
    Serial.print(pin);
    Serial.print(" : ");
    Serial.print(value);
    Serial.println();
}

void digitalCallback(int id, int pin, int value) {
    if (id == 1 && pin == 6)
      re_jogwheel.setPinA(value);
    if (id == 1 && pin == 7)
      re_jogwheel.setPinB(value);
    
    /*
    if (id == 3 && pin == 9)
      re_JogWheel2.setPinA(value);
    if (id == 3 && pin == 10)
      re_JogWheel2.setPinB(value);
    if (id == 3 && pin == 6)
      re_Browse.setPinA(value);
    if (id == 3 && pin == 5)
      re_Browse.setPinB(value);
    */
    if ((id == 3 && pin != 5 && pin != 6 && pin!= 9 && pin != 10) || (id == 1 && pin != 6 && pin !=7) || (id == 0) || (id == 4)) {
      Serial.print("id ");
      Serial.print(pin);
      Serial.print(" pin ");
      Serial.print(pin);
      Serial.print(" : ");
      Serial.print(value);
      Serial.println();
    }
}

void jogwheel(int c) {
   Serial.println(c); 
}

//JogWheel1
void rotaryLeftJogWheel1() {
      Serial.println("wheel1 left");
}

void rotaryRightJogWheel1() {
      Serial.println("wheel1 right");
}


//JogWheel2
void rotaryLeftJogWheel2() {
      Serial.println("wheel2 left");
}

void rotaryRightJogWheel2() {
      Serial.println("wheel2 right");
}


//Browse
void rotaryLeftBrowse() {
      Serial.println("wheel3 left");
}

void rotaryRightBrowse() {
      Serial.println("wheel3 right");
}
