#include <INPUT_4051.h>



INPUT_4051 input_4051(A1,10,9,8,printValue);

void setup() {
  Serial.begin(9600);
  input_4051.setPinCount(2);
}

void loop() {
  input_4051.loop();
} 

void printValue(int pin, int value) {
    Serial.print("pin");
    Serial.print(pin);
    Serial.print(" : ");
    Serial.print(value/8);
    Serial.println();
}
