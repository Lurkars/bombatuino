#include "Arduino.h"
#include "INPUT_74HC4051.h"

void INPUT_74HC4051::begin(uint8_t analog, uint8_t s0, uint8_t s1, uint8_t s2,CallbackFunction cbF) {
	_analog = analog;
	
	_s0 = s0;
	_s1 = s1;
	_s2 = s2;
	
	pinMode(_analog,INPUT);
	
	pinMode(_s0,OUTPUT);
	pinMode(_s1,OUTPUT);
	pinMode(_s2,OUTPUT);
	
	_callbackFunction = cbF;
	
	//init start values
	uint8_t pin,r0,r1,r2;
	for (pin=0; pin<8; pin++) {
		r0 = bitRead(pin,0);     
		r1 = bitRead(pin,1);
		r2 = bitRead(pin,2);   
		digitalWrite(_s0, r0);
		digitalWrite(_s1, r1);
		digitalWrite(_s2, r2);
		//delayMicroseconds(10);
		_value[pin] = analogRead(_analog);
	}  	
}

void INPUT_74HC4051::loop() {
	uint8_t pin,r0,r1,r2;
	int value;
	for (pin=0; pin<8; pin++) {
		r0 = bitRead(pin,0);     
		r1 = bitRead(pin,1);
		r2 = bitRead(pin,2);   
		digitalWrite(_s0, r0);
		digitalWrite(_s1, r1);
		digitalWrite(_s2, r2);
		//delayMicroseconds(10);
		value = analogRead(_analog);
		if (_value[pin] < value - INPUT_74HC4051_TOLERANCE || _value[pin] > value + INPUT_74HC4051_TOLERANCE) {
			_value[pin] = value;
			(*_callbackFunction)(_analog,pin,value);
		}
	}  	
}

int INPUT_74HC4051::getSpecificValue(uint8_t pin) {
	if (pin >= 8)
		return -1;
	uint8_t r0,r1,r2;
	r0 = bitRead(pin,0);     
	r1 = bitRead(pin,1);
	r2 = bitRead(pin,2);   
	digitalWrite(_s0, r0);
	digitalWrite(_s1, r1);
	digitalWrite(_s2, r2);
	//delayMicroseconds(10);
	int value = analogRead(_analog);
	_value[pin] = value;
	return value;
}

