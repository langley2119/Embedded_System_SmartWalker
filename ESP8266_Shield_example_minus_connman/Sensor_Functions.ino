#include "definitions.h" 

int SetupButtonInterrupts(){
  pinMode(LEFT_HANDLE_BUTTON, INPUT); // need to configure for button interrupt
  pinMode(RIGHT_HANDLE_BUTTON, INPUT); 
  attachInterrupt(digitalPinToInterrupt(LEFT_HANDLE_BUTTON), GoToThankYou, RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_HANDLE_BUTTON), GoToThankYou, RISING);
  return 0; 
}

int EnableButtonInterrupts(){
  attachInterrupt(digitalPinToInterrupt(LEFT_HANDLE_BUTTON), GoToThankYou, RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_HANDLE_BUTTON), GoToThankYou, RISING);
}

int DisableButtonInterrupts(){
  detachInterrupt(digitalPinToInterrupt(LEFT_HANDLE_BUTTON)); 
  detachInterrupt(digitalPinToInterrupt(RIGHT_HANDLE_BUTTON));
}


int SetupSensors() {

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
  //DEBUG.println(distance); 
  // distance returned on a scale of 0 to 2047
  if(distance < 1000) {
    return 2;   
  }
  else if(distance < 1750) {
    return 1; 
  }
  else {
    return 0; 
    // no signal detected, or the signal is sufficiently far away
  }
    

}
