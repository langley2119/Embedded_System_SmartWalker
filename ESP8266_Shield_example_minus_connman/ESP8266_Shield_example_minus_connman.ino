/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  This example shows how to use ESP8266 Shield (with AT commands)
  to connect your project to Blynk.

  WARNING!
    It's very tricky to get it working. Please read this article:
    http://help.blynk.cc/hardware-and-libraries/arduino/esp8266-with-at-firmware

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/
#include "definitions.h" 

// define pinouts, define interrupts



// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "a2f791ce584c4b91a59bdc40e6e9b4d9";

// including the timer necessary instead of delays (so that blink can still run compatibly) 
BlynkTimer timer; 

// adding the wifi Manager
//WifiManager wifiManager; 

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "iPhone";
char pass[] = "morecoffee";


ESP8266 wifi(&EspSerial);

void setup()
{
  // Debug console
  Serial.begin(9600);

  delay(10);

  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  // setting up function calls via the timer 
  // first argument is the duration between events in milliseconds 
  // up to 16 timers per timer object. 
  // max data sending rate of 10 values per second
  timer.setInterval(STATE_MACH_INTERVAL,StateMachine); 
//  timer.setInterval(LED_INTERVAL,LEDMain); // can be on a separate time from the state machine if flashes must occur slower or faster 

  // WIFI Manager Attempts 
  // one-time thing: 
  //wifiManager.resetSettings(); 
  // setting up the auto connnect using WiFiManager Library
  //wifiManager.setConfigPortalTimeout(180); // waits 3 minutes and then will shut off. 
  //wifiManager.autoConnect("RemindME Walker","remindme"); 

// SetupLEDs(); 
  SetupRTCandSD();   
  SetupSensors(); 
  SetupButtonInterrupts(); 
  //Blynk.begin(auth, wifi, ssid, pass);
//  SetupLEDDriveCurrents(); 
  DEBUG.println("Setup Complete!"); 
}

void loop()
{
  //Blynk.run();
  timer.run(); 
  if (rtc.updateTime() == false) //Updates the time variables from RTC
  {
    Serial.print("RTC failed to update");
  }
  // periodically checking 
  // currently disabled to prevent the SD card from preventing other operation of the device.
   
  // FIXME: maybe add a parameter that enables easier checking and initialization if possible
  /*if (!digitalRead(cardDetect))
  {
    initializeCard();
  }*/
  
}
