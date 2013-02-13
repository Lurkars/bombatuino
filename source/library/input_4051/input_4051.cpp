/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "input_4051.h"

const int tolerance = 4;

input_4051::input_4051(int analogPin, int s0Pin, int s1Pin, int s2Pin, void (*valueChangeCallback(int,int)))
{
	_analog = analogPin;
	_s0 = s0Pin;
	_s1 = s1Pin;
	_s2 = s2Pin;
	pinMode(_analog,INPUT);
	pinMode(_s0,OUTPUT);
	pinMode(_s1,OUTPUT);
	pinMode(_s2,OUTPUT);
	_valueChangeCallback = valueChangeCallback;
	_value = {-1,-1,-1,-1,-1,-1,-1,-1};
}

void input_4051::loop()
{
	for (count=0; count<=7; count++) {
		r0 = bitRead(count,0);     
		r1 = bitRead(count,1);
		r2 = bitRead(count,2);   
		digitalWrite(_s0, r0);
		digitalWrite(_s1, r1);
		digitalWrite(_s2, r2);
		int read = analogRead(_analog);
		if (value[count] < read - tolerance || value[count] > read + tolerance) {
			value[count] = read;
			_valueChangeCallback(count, read);
		}
	}  	
}

