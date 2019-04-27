

/*
  Getting distance from the RFD77402 Time of Flight Sensor
  By: Nathan Seidle
  SparkFun Electronics
  Date: June 6th, 2017
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting our work? Buy a board from SparkFun!

  Read the raw distance values from the vertical-cavity surface-emitting laser (VCSEL) sensor.

  Hardware Connections:
  Attach the Qwiic Shield to your Arduino/Photon/ESP32 or other
  Plug the sensor onto the shield (any port)
  Open the serial monitor at 9600 baud
*/

#include <SparkFun_RFD77402_Arduino_Library.h> //Use Library Manager or download here: https://github.com/sparkfun/SparkFun_RFD77402_Arduino_Library
#include <Wire.h>
RFD77402 myDistance; //Hook object to the library

void setup()
{
  Serial.begin(9600);
  while (!Serial);
  Serial.println("RFD77402 Read Example");
  // set pinmode
  if (myDistance.begin() == false)
  {
    Serial.println("Sensor failed to initialize. Check wiring.");
    while (1); //Freeze!
  }
  Serial.println("Sensor online!");
}

void loop()
{
  myDistance.takeMeasurement(); //Tell lower sensor to take measurement
  unsigned int distance_upper = 0; // placeholder number for var
  unsigned int distance_lower = myDistance.getDistance(); //Retrieve the distance value
  Serial.print(distance_lower); // distance in mm
  if (distance_lower<500) {
    // arbitrary number, will be changed w/measurements
    
    sigdown = 1;
    myDistance.takeMeasurement(); //Tell lower sensor to take measurement again
    distance_lower = myDistance.getDistance(); // gets distance
    if (distance_lower < 500){
      // again, arbitray number
      // being less than this number will trigger a proximal signal
      // if so, Upper sensor takes measurement
       // debating whether to make function for "I am here" bc used in more than one place
      if (distance_upper < 500){
        // Go to ready to grab
        // digitalWrite(pinnum, HIGH);
        myDistance.takeMeasurement(); //Tell lower sensor to take measurement again
        distance_lower = myDistance.getDistance();
        if (distance_lower < 500){
          //
          if (distance_upper < 500){
            // go to gentle reminder
          }
          else {
            
          }
        }
        
        
      }
      else{
        delay(10000); // arbitrary delay time, go back to top of loop
      }
    }
  }
  else{
    delay(10000); // delay 10 seconds, arbitrary number atm
}
}


