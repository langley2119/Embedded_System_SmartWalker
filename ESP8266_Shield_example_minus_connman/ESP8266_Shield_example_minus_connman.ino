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

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#define DEBUG Serial 

#define STATE_MACH_INTERVAL 100L

//#include <queue.h>
//#include <ESP8266WiFi.h>

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

// define pinouts, define interrupts

// for the wifi manager


//#include <WiFiManager.h> // Wifi configuration manager used thanks to tazpu
//#include <DNSServer.h>
//#include <ESP8266WebServer.h>


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "a2f791ce584c4b91a59bdc40e6e9b4d9";

// including the timer necessary instead of delays (so that blink can still run compatibly) 
BlynkTimer StateTimer; 

// adding the wifi Manager
//WifiManager wifiManager; 

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "iPhone";
char pass[] = "morecoffee";

// Hardware Serial on Mega, Leonardo, Micro...
#define EspSerial Serial1

// or Software Serial on Uno, Nano...
//#include <SoftwareSerial.h>
//SoftwareSerial EspSerial(10, 11); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);

enum State{waiting, iAmHere, gentleReminder, strongReminder, thankYou, inUse}; 
enum State current_state;
enum State next_state; 
// globals for the stae



void StateMachine()
{ 
  static int counter = 0; 
  static unsigned long time_elapsed = 0; 
  counter = counter + 1;
  time_elapsed = counter * STATE_MACH_INTERVAL;  

  switch(current_state) {
    case waiting: 
        next_state = WaitingState(time_elapsed,&counter); 
      break; 
    case iAmHere: 
        next_state = IAmHereState(time_elapsed,&counter); 
      break; 
    case gentleReminder: 
        next_state = GentleReminderState(time_elapsed,&counter); 
      break;
    case strongReminder:
        next_state = StrongReminderState(time_elapsed,&counter); 
      break; 
    case thankYou: 
        next_state = ThankYouState(time_elapsed,&counter); 
      break;
    case inUse:
        next_state = InUseState(time_elapsed,&counter);
      break;
    default: 
        DEBUG.println("Error occured in the state diagram."); 
      break;     
  }

   
  //Blynk.virtualWrite(V5, (millis()/1000) % 10); 
}


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
  StateTimer.setInterval(STATE_MACH_INTERVAL,StateMachine); 

  // WIFI Manager Attempts 
  // one-time thing: 
  //wifiManager.resetSettings(); 
  // setting up the auto connnect using WiFiManager Library
  //wifiManager.setConfigPortalTimeout(180); // waits 3 minutes and then will shut off. 
  //wifiManager.autoConnect("RemindME Walker","remindme"); 
  
  SetupSensors(); 
  //Blynk.begin(auth, wifi, ssid, pass);

}

void loop()
{
  //Blynk.run();
  StateTimer.run(); 
}




