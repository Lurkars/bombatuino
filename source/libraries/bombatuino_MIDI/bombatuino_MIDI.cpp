#include "Arduino.h"
#include "bombatuino_MIDI.h"

void MIDI::begin(int channel) {
	Serial.begin(31250);
	//if given channel is not valid, set default channel to 1
	if (channel > MIDI_MAX_CHANNEL)
		channel = MIDI_DEFAULT_CHANNEL;
	_channel = channel;
}

bool MIDI::message(int status, int data, int data2, int channel) {
	//check if status byte is valid
	if (status > MIDI_MAX_STATUS) return false;
	//check if first data byte is valid
	if (data > MIDI_MAX_DATA) return false;
	//check if second data byte is valid
	if (data2 > MIDI_MAX_DATA) return false;	
	//if no specific channel given, use default channel
	if (channel == MIDI_NULL_CHANNEL) channel = _channel;
	//check if channel is valid
	if (channel > MIDI_MAX_CHANNEL) return false;
	//write bytes to serial
	Serial.write(status+channel);
	Serial.write(data);
	//check if second data byte should be send
	if (status != MIDI_PROGRAMM_CHANGE && status != MIDI_CHANNEL_PRESSURE)
		Serial.write(data2);
	return true;
}

bool MIDI::noteOff(int note, int velocity, int channel) {
	return message(MIDI_NOTE_OFF,note,velocity,channel);
}

bool MIDI::noteOn(int note, int velocity, int channel) {
	return message(MIDI_NOTE_ON,note,velocity,channel);
}

bool MIDI::polyphonicKeyPressure(int note, int velocity, int channel) {
	return message(MIDI_POLYPHONIC_KEY_PRESSURE,note,velocity,channel);
}

bool MIDI::controlChange(int controller, int value, int channel) {
	return message(MIDI_CONTROL_CHANGE,controller,value,channel);
}

bool MIDI::programChange(int programm, int channel) {
	return message(MIDI_PROGRAMM_CHANGE,programm,0,channel);
}

bool MIDI::channelPressure(int pressure, int channel) {
	return message(MIDI_CHANNEL_PRESSURE,pressure,0,channel);
}

bool MIDI::pitchWheelChange(int last, int most, int channel) {
	return message(MIDI_PITCH_WHEEL_CHANGE,last,most,channel);
}

