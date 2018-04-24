#include <MIDI.h>

//Set pins on atMega328
static const unsigned flex1 = A0;
static const unsigned flex2 = A3;
static const unsigned flex3 = A2;
static const unsigned accX = A1;
static const unsigned accY = A4;
static const unsigned accZ = A5;

int bend1prev = 0;
int bend2prev = 0;
int bend3prev = 0;
int pitchPrev = 0;
int rollPrev = 0;
int zPrev = 0;

//define custom settings for MIDI comms
struct MySettings : public midi::DefaultSettings
{
   static const long  BaudRate = 115200; // Set to baud rate for bluetooth serial to hairless midi
};
MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial, midi1, MySettings);

void setup() {
  //Set up analog input pins
  pinMode(flex1, INPUT);
  pinMode(flex2, INPUT);
  pinMode(flex3, INPUT);
  pinMode(accX, INPUT);
  pinMode(accY, INPUT);
  pinMode(accZ, INPUT);

  //start MIDI communications via bluetooth module- bluetooth connection must already be set up
  midi1.begin(MIDI_CHANNEL_OMNI);
}

void loop() {
  //read and scale flex sensors and map to Midi notes
  //Must see a change in value of 5 to trigger
  int BEND1 = analogRead(flex1);
  int BEND2 = analogRead(flex2);
  int BEND3 = analogRead(flex3);
  int bend1 = getFlexVal(BEND1);
  int bend2 = getFlexVal(BEND2);
  int bend3 = getFlexVal(BEND3);

  
  if(abs(bend1prev - bend1) > 13){
  midi1.sendNoteOn(70, bend1, 1); //or this- sendControlChange(31, flex1val, 1); //Brightness - Flex1
  bend1prev = bend1;
  }
  if(abs(bend2prev - bend2) > 13){
  midi1.sendNoteOn(71, bend2, 2); 
  bend2prev = bend2;
  }
  if(abs(bend3prev - bend3) > 13){
  midi1.sendNoteOn(72, bend3, 3);
  bend3prev = bend3;
  }
  
  
  //read and scale x and y axis accel
  float acc_x = analogRead(accX);
  float acc_y = analogRead(accY);
  int roll = scaleVelocity(acc_x);
  int pitch = scaleVelocity(acc_y);

  //note on: 0xA0 0x49 0xpitch
  if(abs(pitchPrev - pitch) > 12){
  midi1.sendNoteOn(73, pitch, 4); 
  pitchPrev = pitch;
  }
  
  if(abs(rollPrev - roll) > 12){
  midi1.sendNoteOn(74, roll, 5); 
  rollPrev = roll;
  }

  /*//check if tapped
  bool tapped = tapCheck();
  //pause program and wait until tapped again
  if(tapped){
    tapped = false;
    while(!tapped){
      tapped = tapCheck();
      delay(1);
    }
    tapped = false;
    delay(1000);
  }*/
  
  delay(1);
}

  
//scale flex sensor inputs
int getFlexVal(int flexNum){
  int flexval = (float((float((flexNum)/float(1024))*127))-30)*8;
  flexval = abs(flexval-127);
  if(flexval>127){flexval=127;}
  else if(flexval<0){flexval=0;}
  return flexval;
}

//set threshold value for a tap to register
bool tapCheck(){
  float acc_z = analogRead(accZ);
  int z = scaleVelocity(acc_z);
  if(abs(zPrev - z) > 45){
    zPrev = z;
    return true;
  }
  zPrev = z;
  return false; 
}

//scale accelerometer inputs
int scaleVelocity(int accel){
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
