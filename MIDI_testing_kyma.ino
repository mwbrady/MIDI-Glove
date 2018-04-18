#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() 
{
    MIDI.begin(MIDI_CHANNEL_OMNI);
    Serial.begin(115200);
}

void loop() 
{
  for (int i = 10; i < 80; i++) 
  {
    MIDI.sendControlChange(31, i, 1); //Brightness
    delay(100);
    MIDI.sendControlChange(32, i, 1); //Decay
    delay(100);
    MIDI.sendControlChange(33, i, 1); //Delay
    delay(100);
    MIDI.sendControlChange(34, i, 1); //Feedback
    delay(100);
    MIDI.sendControlChange(35, i, 1); //Level
    delay(100);
  }

}
