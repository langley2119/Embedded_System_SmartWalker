#ifndef SMART_WALKER_DEF_H
#define SMART_WALKER_DEF_H




/************* FILE Inclusions ***************/
//#include <queue.h>
//#include <ESP8266WiFi.h>

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

// LEDS

#include <lp55231.h>


// for the wifi manager
//#include <WiFiManager.h> // Wifi configuration manager used thanks to tazpu
//#include <DNSServer.h>
//#include <ESP8266WebServer.h>

// used in SD_SAVE_FILE
#include <SPI.h>
#include <SD.h>
#include <SparkFun_RV1805.h>

// used in Sensor_Functions
#include <SparkFun_RFD77402_Arduino_Library.h> //Use Library Manager or download here: https://github.com/sparkfun/SparkFun_RFD77402_Arduino_Library
#include <Wire.h>

/************ COMMUNICATIONS ***********/
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#define DEBUG Serial 

// FOR ESP WIFI
// Hardware Serial on Mega, Leonardo, Micro...
#define EspSerial Serial1

// or Software Serial on Uno, Nano...
//#include <SoftwareSerial.h>
//SoftwareSerial EspSerial(10, 11); // RX, TX


/************* PINOUT ***************/

// used in Sensor Functions
#define LEFT_HANDLE_BUTTON 2
#define RIGHT_HANDLE_BUTTON 3

// plug the pir sensor in to D6 and the 3.3 v and GND pins on the top of the wifi shield
#define PIR_DOUT 6  // PIR digital output on D2

// used In SD_SAVE_FILE
const uint8_t chipSelect = 8;
const uint8_t cardDetect = 9; 

// FOR the button triggers
/*
  Buttons are hooked up to D2 and D3, but when plugging in the button leads to and from use
  MEGA_A0 From BTN1
  MEGA_A1 From BTN2
  MEGA_A2 To BTN1
  MEGA_A3 To BTN2


*/


// FOR SD CARD
/*
* MEGA_P51 -> SD_DI
* MEGA_P50 -> SD_DO
* MEGA_P52 -> SD_SCK
*/


/************ MODULES AND CLASSS DEFINITIONS **********/

// module stuff
RV1805 rtc;
File fd;

// LEDS
static Lp55231 ledChip(0x32);
static Lp55231 ledChip2(0x33);

RFD77402 myDistance_upper; // hook object to library for upper sensor

/******************** CONSTANTS *******************/ 
// used in SD_SAVE_FILE
#define str_len 3

// Timing 
#define STATE_MACH_INTERVAL 100L
#define LED_INTERVAL 500L


// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600


 

/****************** GLOBALS **********************/ 
enum State{waiting, iAmHere, gentleReminder, strongReminder, thankYou, inUse}; 
enum State current_state;
enum State volatile next_state; // so that it can be changed in the interrupt callbacks

bool CARD_OK = 1; 
bool WIFI_ENABLED = 0;

/***************** LED CHANNELS ******************/ 
int greenLED1 = 0;
int blueLED1 = 1;
int greenLED2 = 2;
int blueLED2 = 3;
int greenLED3 = 4;
int blueLED3 = 5;
int redLED1 = 6;
int redLED2 = 7;
int redLED3 = 8;



#endif // SMART_WALKER_DEF_H
