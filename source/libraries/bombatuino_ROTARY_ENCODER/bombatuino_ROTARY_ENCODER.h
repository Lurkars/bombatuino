/**
 * @file bombatuino_ROTARY_ENCODER.h
 * 
 * @author Lukas Haubaum (lukas@haubaum.de)
 * 
 * @date February, 2013
 * 
 * @brief arduino library for handling a rotary encoder
 * 
 * library is for specialiced use: increment- and decrement-functions are called on change of pin A. 
 * 	
 * */
#ifndef bombatuino_ROTARY_ENCODER_h
#define bombatuino_ROTARY_ENCODER_h

#if !defined(XcrementFunction)
/**
 * callback function
 * 
 * @param address
 * @param pin
 * @param value
 */
typedef void (*XcrementFunction)(void);
#endif

class ROTARY_ENCODER
{
	public:		
		/**
		 * constructor
		 * 
		 * @param increment function
		 * @param decrement function
		 */
		ROTARY_ENCODER(XcrementFunction incrementFunction, XcrementFunction decrementFunction);		
		/**
		 * set the value of pin B
		 * 
		 * @param value of B-pin
		 */
		void setPinB(int value);
		/**
		 * set the value of pin A
		 * 
		 * @param value of A-pin
		 */
		void setPinA(int value);
	private:
		int _pinA;
		int _pinB;
		int _oldA;
		XcrementFunction _increment; /**< increment function */ 
		XcrementFunction _decrement; /**< decrement function */ 
		void onPinChange();
};

#endif
