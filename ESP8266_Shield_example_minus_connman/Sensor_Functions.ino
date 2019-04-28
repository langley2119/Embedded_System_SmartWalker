#include <SparkFun_RFD77402_Arduino_Library.h> //Use Library Manager or download here: https://github.com/sparkfun/SparkFun_RFD77402_Arduino_Library
#include <Wire.h>
#define PIR_DOUT 5  // PIR digital output on D2

RFD77402 myDistance_upper; // hook object to library for upper sensor

int SetupSensors() {
  //int interruptButtonLeft = 2; // for the pushbutton interrupt
  //int interruptButtonRight = 3;

  // for lowerSensor 
  pinMode(PIR_DOUT,INPUT); 
  


  if (myDistance_upper.begin() == false){
    Serial.println("Upper RF Sensor failed to initialize. Check wiring.");
    while(1); // freezes 
  }

  DEBUG.println("Sensors Up!"); 
  return 0; 
}


int LowerSensorTakeMeasurement() {
  int motion_sense; 
  motion_sense = digitalRead(PIR_DOUT); 
  // maybe have some sort of filtering/window in this part of the function. Hold off for the moment 
  return motion_sense; 
  // return decision 
}

int UpperSensorTakeMeasurement() {
  // using RFD77402
  int distance; 
  myDistance_upper.takeMeasurement(); 
  distance = myDistance_upper.getDistance(); 
  // distance returned on a scale of 0 to 2047
  if(distance < 1000) {
    return 2;   
  }
  else if(distance < 2000) {
    return 1; 
  }
  else {
    return 0; 
    // no signal detected, or the signal is sufficiently far away
  }
  
  
  

}
