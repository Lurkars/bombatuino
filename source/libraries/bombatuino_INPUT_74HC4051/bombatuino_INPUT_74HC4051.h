/**
 * @file bombatuino_INPUT_74HC4051.h
 * 
 * @author Lukas Haubaum (lukas@haubaum.de)
 * 
 * @date February, 2013
 * 
 * @brief arduino library for reading inputs from 74HC4051 multiplexer
 * 
 * library is for specialiced use: all I/O ports are used as analog inputs, values are stored and a callback function is called, when a value changes
 * 	
 * */
#ifndef bombatuino_INPUT_74HC4051_h
#define bombatuino_INPUT_74HC4051_h

#if !defined(CallbackFunction)
/**
 * callback function
 * 
 * @param address
 * @param pin
 * @param value
 */
typedef void (*CallbackFunction)(int,int,int);
#endif

class INPUT_74HC4051
{
	public:		
		/**
		 * initalize the class, should be called in setup() function
		 * 
		 * @param analog input pin on arduino, connected Z pin here
		 * @param digital output pin for S0
		 * @param digital output pin for S0
		 * @param digital output pin for S0
		 * @param callback function
		 */
		void begin(uint8_t analog, uint8_t s0, uint8_t s1, uint8_t s2,CallbackFunction cbF);		
		/**
		 * read values and call callback function on change, should be called in loop()
		 */
		void loop(void);		
		/**
		 * get value of specific pin (0-7)
		 * 
		 * @param pin
		 * @return value of pin
		 */
		int getSpecificValue(uint8_t pin);
	private:
		uint8_t _analog; /**< analog input pin on arduino, connected Z pin here */ 
		uint8_t _s0; /**< digital output pin for S0 */ 
		uint8_t _s1; /**< digital output pin for S0 */ 
		uint8_t _s2; /**< digital output pin for S0 */ 
		int _value[8]; /**< read values */ 
		CallbackFunction _callbackFunction; /**< callback function */ 
};


#endif
