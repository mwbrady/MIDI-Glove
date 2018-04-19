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
  Serial.begin(9600);

  //Set up analog input pins
  pinMode(flex1, INPUT);
  pinMode(flex2, INPUT);
  pinMode(flex3, INPUT);
  pinMode(accX, INPUT);
  pinMode(accY, INPUT);
  pinMode(accZ, INPUT);

  //int useAccel = 0; //Default is to not use accelerometer. When double-tapped, this changes to 1 and volume changes can ocurr with accelerometer
}

void loop() {

  float flex_const = (3.3/1024);
  
  //read sensor values constantly
  //float flex1val = analogRead(flex1);//*3.3/1024;
  int flex1val = (analogRead(flex1)*flex_const-1.43)*(127/(2.31-1.43));
  if(flex1val>127){flex1val=127;}
  else if(flex1val<0){flex1val=0;}

  float acc_x = analogRead(A0);
  Serial.print("X = ");
  Serial.println(acc_x);
  float acc_y = analogRead(A1);
  float acc_z = analogRead(A2);
 
 scaleVelocity(acc_x, acc_y, acc_z);
/*
  int flex2val = floor(analogRead(flex2)*flex_const);
  int flex3val = floor(analogRead(flex3)*flex_const);
  
  int accXval = analogRead(accX)*127/(1.95-1.63);
  int accYval = analogRead(accY)*127/(1.93-1.29);
  int accZval = analogRead(accZ)*127/(1.92-1.29);

  MIDI.sendControlChange(31, flex1val, 1); //Brightness - Flex1
  MIDI.sendControlChange(32, 0.5, 1); //Decay - Flex2
  MIDI.sendControlChange(34, 0.5, 1); //Feedback - Flex3
  MIDI.sendControlChange(35, 0.5, 1); //Level - Acc1
  MIDI.sendControlChange(33, 0.5, 1); //Delay - Acc2
*/
  /*print sensor vallue to Serial Monitor, TO BE USED FOR DEBUGGING TO FIND THRESHOLD VALUES
  Serial.print("X= ");
  Serial.println(x);
  Serial.print("Y= ");
  Serial.println(y);
  Serial.print("Z= ");
  Serial.println(z);
  delay(1000);
  */
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
}
void scaleVelocity(int x, int y, int z){
  int velocity = float((float((x-285))/float((430-285))))*127;
  Serial.print("Velocity =");
  Serial.println(velocity);
  delay(1000);
  if (velocity < 0){
  velocity = 0;
  }
  else if (velocity > 127){
  velocity = 127;
  }
  MIDI.sendControlChange(0x07, velocity, 0); //cc#=7, cc_value= velocity, channel = 1
} 
