#include <MIDI.h> //Not sure if going to use this but added it here anyways

/*SETS DEFAULT SERIAL OUTPUT
MIDI_CREATE_DEFAULT_INSTANCE(); //https://github.com/FortySevenEffects/arduino_midi_library/blob/master/src/midi_Defs.h Do we need to create a different instance since we are not using a board
*/

//Set pins on atMega328
static const unsigned flex1 = 23;
static const unsigned flex2 = 24;
static const unsigned flex3 = 25;
static const unsigned accX = 26;
static const unsigned accY = 27;
static const unsigned accZ = 28;

//Set analog sensor threshold values to trigger a MIDI event; TO BE FILLED IN UPON TESTING
static const unsigned flex1_t = 0000000000;
static const unsigned flex2_t = 0000000000;
static const unsigned flex3_t = 0000000000;
static const unsigned accX_t = 0000000000;
static const unsigned accY_t = 0000000000;
static const unsigned accZ_t = 0000000000;

void setup() {
  Serial.begin(115200); //Set Serial Baud rate

  //Set up analog input pins
  pinMode(flex1, INPUT);
  pinMode(flex2, INPUT);
  pinMode(flex3, INPUT);
  pinMode(accX, INPUT);
  pinMode(accY, INPUT);
  pinMode(accZ, INPUT);

  int useAccel = 0; //Default is to not use accelerometer. When double-tapped, this changes to 1 and volume changes can ocurr with accelerometer

//  MIDI.begin(1); // MAKE SURE TO SET OUR KEYBOARD TO CHANNEL 1; this launches MIDI and listens to channel 1

}

void loop() {
  
  //read sensor values constantly
  int flex1val = analogRead(flex1);
  int flex2val = analogRead(flex2);
  int flex3val = analogRead(flex3);
  int accXval = analogRead(accX);
  int accYval = analogRead(accY);
  int accZval = analogRead(accZ);

  print sensor vallue to Serial Monitor, TO BE USED FOR DEBUGGING TO FIND THRESHOLD VALUES
  Serial.println(flex1val);
  delay(2000); */


//Send Midi Program change serially
  if(flex1val > flex1_t){
    programChange(0xC0, 0x00); //change MIDI channel 1 to standard instrument
  }

  else if(flex2val > flex2_t){
    programChange(0xC0, 0x01); //change MIDI channel 1 to sound 2 in standard soundbank
  }

  else if(flex3val > flex3_t){
    programChange(0xC0, 0x02); //Change MIDI channel 1 to sound 3 in standard soundbank
  } 

  else if (useAccel == 1);{
    scaleVelocity(accX, accY, accZ);
  }
  
  else if(ACCEL IS TAPPED, NEED TO FIGURE OUT HOW IT SENSES THIS)
  {
    if(useAccel == 0){
      useAccel = 1; 
    }
    else{
      useAccel = 0;
    }
  }
  
}
*/

/*0xB0 <- B = controller change, 0 = channel 1, only use if need to change sound banks
http://www.music-software-development.com/midi-tutorial.html info about sound banks, if needed, for now, ignore
*/
void programChange(int chan, int sound){
  Serial.write(chan);
  Serial.write(sound);
}

void volumeChange(int chan, int controller, int vel){
  Serial.write(chan);
  Serial.write(controller);
  Serial.write(vel);
}

void scaleVelocity(int analogVal){
  //INSERT VOLUME CHANGE ALGORITHM HERE, we should discuss how we wanna do this
  volumeChange(0xB0, 0x07, velocity);
}
}

