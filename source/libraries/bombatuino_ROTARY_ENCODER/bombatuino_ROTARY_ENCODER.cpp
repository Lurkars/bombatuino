#include "Arduino.h"
#include "bombatuino_ROTARY_ENCODER.h"

ROTARY_ENCODER::ROTARY_ENCODER(XcrementFunction incrementFunction, XcrementFunction decrementFunction) {
	_increment = incrementFunction;
	_decrement = decrementFunction;
	_pinA = LOW;
	_pinB = LOW;
	_oldA = LOW;
}

void ROTARY_ENCODER::setPinA(int value) {
	_pinA = value;
	onPinChange();
}

void ROTARY_ENCODER::setPinB(int value) {
	_pinB = value;
	onPinChange();
}

void ROTARY_ENCODER::onPinChange() {
	if ((_oldA == LOW) && (_pinA == HIGH)) {
		if (_pinB == LOW) {
			(*_increment)();
		}
		else {
			(*_decrement)();
		}
	}
	_oldA = _pinA;
}
