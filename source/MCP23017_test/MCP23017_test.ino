#include <Wire.h>

#define MCP23017_ADDRESS 0x20

// registers (from https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library/blob/master/Adafruit_MCP23017.h)
#define MCP23017_IODIRA 0x00
#define MCP23017_IPOLA 0x02
#define MCP23017_GPINTENA 0x04
#define MCP23017_DEFVALA 0x06
#define MCP23017_INTCONA 0x08
#define MCP23017_IOCONA 0x0A
#define MCP23017_GPPUA 0x0C
#define MCP23017_INTFA 0x0E
#define MCP23017_INTCAPA 0x10
#define MCP23017_GPIOA 0x12
#define MCP23017_OLATA 0x14

#define MCP23017_IODIRB 0x01
#define MCP23017_IPOLB 0x03
#define MCP23017_GPINTENB 0x05
#define MCP23017_DEFVALB 0x07
#define MCP23017_INTCONB 0x09
#define MCP23017_IOCONB 0x0B
#define MCP23017_GPPUB 0x0D
#define MCP23017_INTFB 0x0F
#define MCP23017_INTCAPB 0x11
#define MCP23017_GPIOB 0x13
#define MCP23017_OLATB 0x15

int _addr = 0;
int _value[16];

void setup() {
  Serial.begin(9600);
	Wire.begin();
	
	// set defaults!
	Wire.beginTransmission(MCP23017_ADDRESS | _addr);
	Wire.write((byte)MCP23017_IODIRA);
	Wire.write(0xFF);  // all inputs on port A
	Wire.endTransmission();

	Wire.beginTransmission(MCP23017_ADDRESS | _addr);
	Wire.write(MCP23017_IODIRB);
	Wire.write(0xFF);  // all inputs on port B
	Wire.endTransmission();
	
	
	Wire.beginTransmission(MCP23017_ADDRESS | _addr);
	Wire.write(MCP23017_GPPUA); 
	Wire.write(0xFF);	// all pullup resistors on port A
	Wire.endTransmission();
	
	Wire.beginTransmission(MCP23017_ADDRESS | _addr);
	Wire.write(MCP23017_GPPUB); 
	Wire.write(0xFF);	// all pullup resistors on port B
	Wire.endTransmission();
}

void loop() {
   	uint8_t pin,bank;
	int value;
	//read bank A
	Wire.beginTransmission(MCP23017_ADDRESS | _addr);
	Wire.write(MCP23017_GPIOA);
	Wire.endTransmission();
    Wire.requestFrom(MCP23017_ADDRESS | _addr, 1);
	bank = Wire.read();
	for (pin=0; pin<8; pin++) {
		value = (bank >> pin) & 0x1;
		if (_value[pin] != value) {
			_value[pin] = value;
		printValue(_addr,pin,value);
		}
	}  	
	//read bank B
	Wire.beginTransmission(MCP23017_ADDRESS | _addr);
	Wire.write(MCP23017_GPIOB);
	Wire.endTransmission();
    Wire.requestFrom(MCP23017_ADDRESS | _addr, 1);
	bank = Wire.read();
	for (pin=8; pin<16; pin++) {
		value = (bank >> (pin-8)) & 0x1;
		if (_value[pin] != value) {
			_value[pin] = value;
		printValue(_addr,pin,value);
		}		
	}
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
