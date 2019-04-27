/*Ellie Langley, Jackson Farley, Erik Leinen
 * ELC 4438
 * Spring 2019
 * Final Project Code
 * Interrupts for mega pins - 2,3,18,19,20,21
 * */
int interruptButton = 18; // for the pushbutton interrupt
volatile int flag = 0;

#include <SparkFun_RFD77402_Arduino_Library.h> //Use Library Manager or download here: https://github.com/sparkfun/SparkFun_RFD77402_Arduino_Library
#include <Wire.h>
RFD77402 myDistance_lower; //Hook object to the library
RFD77402 myDistance_upper; // hook object to library for upper sensor

void setup() {
  // put your setup code here, to run once:
  pinMode(interruptButton, INPUT); // need to configure for button interrupt
  attachInterrupt(digitalPinToInterrupt(interruptButton), thank_you, RISING);
  Serial.begin(9600);
  while (!Serial);
  Serial.println("RFD77402 Read Example");
  // set pinmode
  if (myDistance_lower.begin() == false)
  {
    Serial.println("Sensor failed to initialize. Check wiring.");
    while (1); //Freeze!
  }
  Serial.println("Sensor online!");
  if (myDistance_upper.begin() == false){
    Serial.println("Sensor failed to initialize. Check wiring.");
    while (1); //Freeze!
  }
}



void loop() {

int x = 0;
int timeout = 0;
unsigned int distance_upper = 0;
unsigned int distance_lower = 0;
  switch (flag){
    case 1: // I am here state
    // digitalwrite
    //delay
    //digitalwrite for led flash
    myDistance_lower.takeMeasurement(); //Tell lower sensor to take measurement
    distance_lower = myDistance_lower.getDistance(); //Retrieve the distance value
    if (distance_lower<500){
      myDistance_upper.takeMeasurement();
      distance_upper = myDistance_upper.getDistance();
      // take upper sensor measurement
      if(distance_upper < 500){
        flag = 2; // ready to grab state
      }
      else{
        delay(1000); // wait short time
      }
    }
    else{
      flag = 0;
    }
    case 2: // ready to grab state
    // digitalwrite LEDs would like to know which gpio pin
     myDistance_lower.takeMeasurement(); //Tell lower sensor to take measurement
     distance_lower = myDistance_lower.getDistance(); //Retrieve the distance value
     if (distance_lower < 500){
      
      myDistance_upper.takeMeasurement();
      distance_upper = myDistance_upper.getDistance();
      
      if(distance_upper < 500){
        flag = 3; // if proximal for both cases, go to gentle reminder
      }
      else if (x = 0){ // placeholder value
        // if any signal
        flag = 9;
      }
      else{
        flag = 1; 
      }
     }

     case 3: // gentle reminder code
     // digitalWrite LED value HIGH
     // speaker reminder
     myDistance_lower.takeMeasurement(); //Tell lower sensor to take measurement
     distance_lower = myDistance_lower.getDistance();
     if (distance_lower < 500){
      
     // take upper sensor measurement
       myDistance_upper.takeMeasurement();
       distance_upper = myDistance_upper.getDistance();
       
      if (distance_upper < 500){
        delay(1000); // wait a short amount of time
      }
      else{
        flag = 4; // go to strong reminder
        // start timer for strong reminder here?
      }
     }
     else{
      flag = 4;
      // start timer for strong reminder here?
     }

    case 4: // strong reminder code
    //led flashing
    // harsh speaker reminder
    // timeout happened?
    if (timeout == 1){ // if timeout has happened
      flag = 0; // go back to waiting
    }
    else{
      flag = 4;
    }
    
    case 5:
    //get time stamp
    // log to open log
    // log to wifi
    flag = 6;

    case 6: // in use 
     
    default: // default is waiting i think
    myDistance_lower.takeMeasurement(); //Tell lower sensor to take measurement
    distance_lower = myDistance_lower.getDistance(); //Retrieve the distance value
    if (distance_lower<500){
      myDistance_upper.takeMeasurement();
      distance_upper = myDistance_upper.getDistance();
      // upper sensor take meas
      if(distance_upper <500){
        flag = 1;
      }
      else{
        delay(10000);
        flag  = 0;
      }
    }

  }
    
  // put your main code here, to run repeatedly:

}
void thank_you(){
  // interrrupt handler for the push button. Do we need to clear 
  // the interrupt flag?
  // led wind down sequence
  // speaker thanks thee
  flag = 5; // to finish rest of code
  
}


