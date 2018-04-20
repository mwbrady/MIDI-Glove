#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

//Set pins on atMega328
static const unsigned flex1 = A0;
static const unsigned flex2 = A3;
static const unsigned flex3 = A2;
static const unsigned accX = A1;
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

  int bend1prev = 0;
  int bend2prev = 0;
  int bend3prev = 0; 
  int rollPrev = 0;
  int pitchPrev = 0;
}

void loop() {

  int bend1 = getFlexVal(1);
  int bend2 = getFlexVal(2);
  int bend3 = getFlexVal(3);

  if((bend1prev - bend1) > 10){
  MIDI.sendNoteOn(72, bend1, 1); //or this- sendControlChange(31, flex1val, 1); //Brightness - Flex1
  }
  if((bend2prev - bend2) > 10){
  MIDI.sendNoteOn(72, bend1, 2); 
  }
  if((bend3prev - bend3) > 10){
  MIDI.sendNoteOn(72, bend3, 3);
  }
  bend1prev = bend1;
  bend2prev = bend2;
  bend3prev = bend3;
  
  float acc_x = analogRead(accX);
  float acc_y = analogRead(accY);
  float acc_z = analogRead(accZ);
  int roll = scaleVelocity(acc_x);
  int pitch = scaleVelocity(acc_y);
  bool z_tap = tapCheck(acc_z);

  if((pitchPrev - pitch) > 8){
  MIDI.sendNoteOn(72, pitch, 4); 
  }
  if((rollPrev - roll) > 8){
  MIDI.sendNoteOn(72, roll, 5); 
  }
  pitchPrev = pitch;
  rollPrev = roll;
  delay(1);
}

  
//scale flex sensor inputs
int getFlexVal(int flexNum){
  int flexval = (float((float((analogRead(flexNum))/float(1024))*127))-30)*8;
  flexval = abs(flexval-127);
  if(flexval>127){flexval=127;}
  else if(flexval<0){flexval=0;}
  return flexval;
}

//set threshold value for a tap to register
bool tapCheck(float acc_z){
  if(acc_z > 50)
    return true;
}

//scale accelerometer inputs
void scaleVelocity(int accel){
  int velocity = float((float((accel-285))/float((430-285))))*127;
  velocity = velocity + 30;
  if (velocity < 0){
    velocity = 0;
  }
  else if (velocity > 127){
    velocity = 127;
  }
  return velocity;
} 

 // MIDI.sendControlChange(32, 0.5, 1); //Decay - Flex2
 // MIDI.sendControlChange(34, 0.5, 1); //Feedback - Flex3
 // MIDI.sendControlChange(35, 0.5, 1); //Level - Acc1
 // MIDI.sendControlChange(33, 0.5, 1); //Delay - Acc2
