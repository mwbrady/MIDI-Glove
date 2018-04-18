#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

//Set pins on atMega328
static const unsigned flex1 = A0;
static const unsigned flex2 = A1;
static const unsigned flex3 = A2;
static const unsigned accX = A3;
static const unsigned accY = A4;
static const unsigned accZ = A5;

//Set analog sensor threshold values to trigger a MIDI event; TO BE FILLED IN UPON TESTING
static const unsigned flex1_t = 0;
static const unsigned flex2_t = 0;
static const unsigned flex3_t = 0;
static const unsigned accX_t = 0;
static const unsigned accY_t = 0;
static const unsigned accZ_t = 0;

void setup() {

MIDI.begin(MIDI_CHANNEL_OMNI);
Serial.begin(115200);

  //Set up analog input pins
  pinMode(flex1, INPUT);
  pinMode(flex2, INPUT);
  pinMode(flex3, INPUT);
  pinMode(accX, INPUT);
  pinMode(accY, INPUT);
  pinMode(accZ, INPUT);

  int useAccel = 0; //Default is to not use accelerometer. When double-tapped, this changes to 1 and volume changes can ocurr with accelerometer

}

void loop() {
  
  //read sensor values constantly
  int flex1val = analogRead(flex1);
  int flex2val = analogRead(flex2);
  int flex3val = analogRead(flex3);
  int accXval = analogRead(accX);
  int accYval = analogRead(accY);
  int accZval = analogRead(accZ);

  //print sensor vallue to Serial Monitor, TO BE USED FOR DEBUGGING TO FIND THRESHOLD VALUES
  Serial.println(flex1val);
  delay(2000); */
/*
  if(flex1val > flex1_t){
    MIDI.sendProgramChange(0x00, 0); //change MIDI channel 1 to standard instrument
  }

  else if(flex2val > flex2_t){
    MIDI.sendProgramChange(0x01, 0); //change MIDI channel 1 to sound 2 in standard soundbank
  }

  else if(flex3val > flex3_t){
    MIDI.sendProgramChange(0x02, 0); //Change MIDI channel 1 to sound 3 in standard soundbank
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


void scaleVelocity(int x, int y, int z){
  //INSERT VOLUME CHANGE ALGORITHM HERE, we should discuss how we wanna do this
  int velocity = 0;//CHANGE THIS BASED ON ALGORITHM
  MIDI.sendControlChange(0x07, velocity, 0); //cc#=7, cc_value= velocity, channel = 1
} */
}

