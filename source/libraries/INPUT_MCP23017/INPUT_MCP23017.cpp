#include <Wire.h>

#include "Arduino.h"
#include "INPUT_MCP23017.h"

void INPUT_MCP23017::begin(uint8_t addr,CallbackFunction cbF) {
	Wire.begin();
	
	if (addr > 7)
		_addr = 7;
	else _addr =  addr;
	
	_callbackFunction = cbF;
		
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

	Wire.beginTransmission(MCP23017_ADDRESS | _addr);
	Wire.write((byte)MCP23017_IPOLA);
	Wire.write(0xFF);  // inverse all inputs
	Wire.endTransmission();

	Wire.beginTransmission(MCP23017_ADDRESS | _addr);
	Wire.write(MCP23017_IPOLB);
	Wire.write(0xFF);    // inverse all inputs
	Wire.endTransmission();

	//init start values
	uint8_t pin,bank;
	//read bank A
	Wire.beginTransmission(MCP23017_ADDRESS | _addr);
	Wire.write(MCP23017_GPIOA);
	Wire.endTransmission();
    Wire.requestFrom(MCP23017_ADDRESS | _addr, 1);
	bank = Wire.read();
	for (pin=0; pin<8; pin++) 
		_value[pin] = (bank >> pin) & 0x1;
	//read bank B
	Wire.beginTransmission(MCP23017_ADDRESS | _addr);
	Wire.write(MCP23017_GPIOB);
	Wire.endTransmission();
    Wire.requestFrom(MCP23017_ADDRESS | _addr, 1);
	bank = Wire.read();
	for (pin=8; pin<16; pin++) 
		_value[pin] = (bank >> (pin-8)) & 0x1;	 	
}

void INPUT_MCP23017::loop() {
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
		(*_callbackFunction)(_addr,pin,value);
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
		(*_callbackFunction)(_addr,pin,value);
		}		
	} 
}

int INPUT_MCP23017::getSpecificValue(uint8_t pin) {
	if (pin > 16)
		return LOW;
	Wire.beginTransmission(MCP23017_ADDRESS | _addr);	
	uint8_t p = pin;
	if (pin > 8) {
		Wire.write(MCP23017_GPIOB);
		p -= 8;
	} else 
		Wire.write(MCP23017_GPIOA);
	Wire.endTransmission();
	uint8_t	bank = Wire.read();
	int value = (bank >> p) & 0x1;
	_value[pin] = value;
	return value;
}


