#include "definitions.h" 

/*******Sensor notes********/
/*
  The PIR sensor is highly adjustable on the back. It will also, if the LED is enabled, blink upon startup and take a moment to initialize before use. 





*/

// REMOVED these in favor of polling, since they can only be used with the state machine anyways
/*
int SetupButtonInterrupts(){
  pinMode(LEFT_HANDLE_BUTTON, INPUT); // need to configure for button interrupt
  pinMode(RIGHT_HANDLE_BUTTON, INPUT); 
  attachInterrupt(digitalPinToInterrupt(LEFT_HANDLE_BUTTON), GoToThankYouLeft, RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_HANDLE_BUTTON), GoToThankYouRight, RISING);
  return 0; 
}
*/
/*
int EnableButtonInterrupts(){
  attachInterrupt(digitalPinToInterrupt(LEFT_HANDLE_BUTTON), GoToThankYouLeft, RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_HANDLE_BUTTON), GoToThankYouRight, RISING);
}

int DisableButtonInterrupts(){
  detachInterrupt(digitalPinToInterrupt(LEFT_HANDLE_BUTTON)); 
  detachInterrupt(digitalPinToInterrupt(RIGHT_HANDLE_BUTTON));
}
*/

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
  // DEBUG.println(distance); 
  // distance returned on a scale of 0 to 2047
  if(distance < 650) { // empirically determined that it's a proximal signal. 
    return 2;   
  }
  else if(distance < 1250) { // this is what we are considering someone close by 
    return 1; 
  }
  else {
    return 0; 
    // no signal detected, or the signal is sufficiently far away
  }
    
  
}
