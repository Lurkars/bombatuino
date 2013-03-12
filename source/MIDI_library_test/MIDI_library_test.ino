
#include <bombatuino_MIDI.h>

MIDI Midi;

void setup() {
    Midi.begin();
}

void loop() {
    Midi.noteOn(0x3C,0x64);
}
