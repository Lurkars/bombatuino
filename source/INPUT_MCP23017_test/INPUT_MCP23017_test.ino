#include <Wire.h>

#include <bombatuino_INPUT_MCP23017.h>
#include <bombatuino_INPUT_74HC4051.h>
#include <bombatuino_ROTARY_ENCODER.h>

INPUT_MCP23017 input_MCP23017;
INPUT_74HC4051 input_4051;

void setup() {
  Serial.begin(9600);
  input_MCP23017.begin(0,printData);
  input_4051.begin(A3,10,11,12,printData);
}

void loop() {
  input_MCP23017.loop();  
  input_4051.loop();
}

void printData(int id, int pin, int value) {
    Serial.print("id");
    Serial.print(id);
    Serial.print(" - ");
    Serial.print("pin");
    Serial.print(pin);
    Serial.print(" : ");
    Serial.print(value);
    Serial.println();
}
