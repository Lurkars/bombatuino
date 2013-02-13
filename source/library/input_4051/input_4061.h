/*
  input_4051.h - Library for reading inputs from 4051 multiplexer
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef input_4051_h
#define input_4051_h

#include "Arduino.h"


class input_4051
{
	public:
		Morse(int analogPin, int s0Pin, int s1Pin, int s2Pin, void (*valueChangeCallback(int,int)));
		void loop(void);
		int getSpecificValue(int pin);
	private:
		int _analog;
		int _s0;
		int _s1;
		int _s2;
		void (*_valueChangeCallback(int,int);
		int _value[8];
};


#endif
