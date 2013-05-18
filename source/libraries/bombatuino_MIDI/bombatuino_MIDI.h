/**
 * @file bombatuino_MIDI.h
 * 
 * @author Lukas Haubaum (lukas@haubaum.de)
 * 
 * @date February, 2013
 * 
 * @brief arduino library for sending MIDI messages over serial
 * 
 * library is just for sending MIDI messages over normal Serial (TX), not for receiving.
 * 	
 * */

//uncomment for debugging
//#define DEBUG

#ifndef bombatuino_MIDI_h
#define bombatuino_MIDI_h

#define MIDI_NOTE_OFF 0x80
#define MIDI_NOTE_ON 0x90
#define MIDI_POLYPHONIC_KEY_PRESSURE 0xA0
#define MIDI_CONTROL_CHANGE 0xB0
#define MIDI_PROGRAMM_CHANGE 0xC0
#define MIDI_CHANNEL_PRESSURE 0xD0
#define MIDI_PITCH_WHEEL_CHANGE 0xE0

#define MIDI_DEFAULT_CHANNEL 0x00
#define MIDI_MAX_STATUS 0xE0
#define MIDI_MAX_CHANNEL 0x0F
#define MIDI_MAX_DATA 0x7F
#define MIDI_NULL_CHANNEL -1

class MIDI {
	public:		
		/**
		 * initalize the class, should be called in setup() function
		 * 
		 * !IMPORTANT sets Serial baud rate to the default MIDI baud rate, so do not change baud rate manually
		 * 
		 * @param optional: default MIDI channel
		 */
		void begin(int channel = MIDI_DEFAULT_CHANNEL);	
		/**
		 * send MIDI message over Serial
		 * 
		 * @param status byte
		 * @param first data byte
		 * @param second data byte
		 * @param optional: MIDI channel
		 * 
		 * @return false, if an error occurs
		 */	
		bool message(int status, int data, int data2, int channel = MIDI_NULL_CHANNEL);		
		/**
		 * send Note off MIDI message
		 * 
		 * @param note number
		 * @param optional: velocity
		 * @param optional: MIDI channel
		 * 
		 * @return false, if an error occurs
		 */	
		bool noteOff(int note, int velocity = MIDI_MAX_DATA, int channel = MIDI_NULL_CHANNEL);
		/**
		 * send Note on MIDI message
		 * 
		 * @param note number
		 * @param velocity
		 * @param optional: MIDI channel
		 * 
		 * @return false, if an error occurs
		 */	
		bool noteOn(int note, int velocity, int channel = MIDI_NULL_CHANNEL);	
		/**
		 * send polyphinic key pressure MIDI message
		 * 
		 * @param note number
		 * @param velocity
		 * @param optional: MIDI channel
		 * 
		 * @return false, if an error occurs
		 */	
		bool polyphonicKeyPressure(int note, int velocity, int channel = MIDI_NULL_CHANNEL);
		/**
		 * send control change MIDI message
		 * 
		 * @param controller number
		 * @param value
		 * @param optional: MIDI channel
		 */	
		bool controlChange(int controller, int value, int channel = MIDI_NULL_CHANNEL);
		/**
		 * send program change MIDI message
		 * 
		 * @param programm number
		 * @param optional: MIDI channel
		 * 
		 * @return false, if an error occurs
		 */	
		bool programChange(int programm, int channel = MIDI_NULL_CHANNEL);
		/**
		 * send channel pressure MIDI message
		 * 
		 * @param pressure value
		 * @param optional: MIDI channel
		 * 
		 * @return false, if an error occurs
		 */	
		bool channelPressure(int pressure, int channel = MIDI_NULL_CHANNEL);
		/**
		 * send pitch wheel change MIDI message
		 * 
		 * @param last significant bits
		 * @param most significant bits
		 * @param optional: MIDI channel
		 * 
		 * @return false, if an error occurs
		 */	
		bool pitchWheelChange(int last, int most, int channel = MIDI_NULL_CHANNEL);
	private:
		int _channel; /**> the default MIDI channel */
};


#endif
