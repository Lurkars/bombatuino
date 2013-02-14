#include <Wire.h>

#include <INPUT_MCP23017.h>
#include <INPUT_74HC4051.h>

INPUT_MCP23017 input_MCP23017;
INPUT_74HC4051 input_4051;

void setup() {
  Serial.begin(9600);
  input_MCP23017.begin(0,printValue);
  input_4051.begin(A0,11,12,13,printValue);
}

void loop() {
  input_MCP23017.loop();  
  input_4051.loop();
}

void printValue(int id, int pin, int value) {
   Serial.print("id: ");
   Serial.print(id);
   Serial.print(" pin: ");
   Serial.print(pin);
   Serial.print(" value: ");
   Serial.print(value);
   Serial.println();
}
