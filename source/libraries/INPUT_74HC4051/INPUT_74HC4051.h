/*
  INPUT_4051.h - Library for reading inputs from 4051 multiplexer
*/
#ifndef INPUT_74HC4051_h
#define INPUT_74HC4051_h

#define INPUT_74HC4051_TOLERANCE 1

#if !defined(CallbackFunction)
typedef void (*CallbackFunction)(int,int,int);
#endif

class INPUT_74HC4051
{
	public:
		void begin(uint8_t analog, uint8_t s0, uint8_t s1, uint8_t s2,CallbackFunction cbF);
		void loop(void);
		int getSpecificValue(uint8_t pin);
	private:
		uint8_t _analog;
		uint8_t _s0;
		uint8_t _s1;
		uint8_t _s2;
		int _value[8];
		CallbackFunction _callbackFunction;
};


#endif
