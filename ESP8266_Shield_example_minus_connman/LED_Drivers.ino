/******************************************************************************
simple-two-chips.ino
simple demo of using two LP5s5231s in parallel to control 18 LEDs.
Byron Jacquot @ SparkFun Electronics
October 21, 2016
https://github.com/sparkfun/SparkFun_LP55231_Arduino_Library

Demonstration of two LP55231s on an I2C bus.

Two Lp55231 objects are declared, at unique I2C addresses.  The program then
writes different values to each chip, resulting an a chase pattern in which one
chip appears to be a step behind the other.

Resources:
Written using SparkFun Pro Micro controller, with two LP55231 breakout boards.

Hardware Configuration:
The second Lp55231 board is configured for address 0x33, by changing
 Address Jumper A0.  The first board has
the I2C pullup resistors disconnected.

Development environment specifics:
Written using Arduino 1.6.5


This code is released under the [MIT License](http://opensource.org/licenses/MIT).

Please review the LICENSE.md file included with this example. If you have any questions
or concerns with licensing, please contact techsupport@sparkfun.com.

Distributed as-is; no warranty is given.
******************************************************************************/
#include "definitions.h"

// don't need the enable 
//static const int32_t enable_pin = 10; // Apparently active high?

// A quick example demonstrating two LP55231's on the same I2C bus.
//
// One of them will need to be reconfigured to address 0x33, by changing
// Address Jumper A0.
//
// to interface them, two Lp55231 objects are declared, each with their own address.
//
// It will simply chase among the LED outputs.  The second chip will be one LED
// ahead of the other, and the chip are set to opposite ends of the range of
// output current, making the first chip brighter than the second..

// not used with this timer
//static uint32_t next;


// NOTE Must call Setup LED Drive currents to complete. 
// rather than keeping it one function I made it two and have other setups acting as the delay(1000) to reduce setup time
void SetupLEDs ()
{
  //Serial.begin(9600);

  //delay(2000);
  //Serial.println("### Setup entry");

  // the enable pin doesn't acutally make any difference. 
  //pinMode(enable_pin, OUTPUT);
  //digitalWrite(enable_pin, LOW);
  //digitalWrite(enable_pin, HIGH);

  ledChip.Begin();
  ledChip.Enable();

  ledChip2.Begin();
  ledChip2.Enable();

  
  //delay(1000);
}

void SetupLEDDriveCurrents() {
  for(uint8_t i = 0; i < 9; i++)
  {
    ledChip.SetDriveCurrent(i, 0x80);
    ledChip2.SetDriveCurrent(i, 0x80);
  }
  
  Serial.println("LED Setup Complete");

}

void LEDMain() {
    // based off the state, do various LED functions
    
    // The LED main function has one master counter that goes to all of the sub functions.
    // The sub functions have LED cycles they do based on the counter value, and can reset the counter to 0 if necessary
    static int counter = 0; 
    // we want the LED sequence to start fresh (counter = 0) each time the state is switched to it. 
    // an easy way to do this is to have a static state, previous state, that we can check the current state against. 
    // If they don't match, then we know that we should reset the counter to 0
    static enum State previous_state = waiting;  // initialized to the idle state of the system. 
    if(current_state != previous_state){
      //DEBUG.println("LED detected a change in state"); 
      ClearLED(); 
      counter = 1; 
      previous_state = current_state; // only changing here since we don't need to assign it otherwise
    }

    //DEBUG.println(counter);
    
    switch(current_state) {
    case waiting: 
        
      break; 
    case iAmHere: 
        StartUpLED(&counter);
      break; 
    case gentleReminder: 
        GentleReminderLED(&counter); 
      break;
    case strongReminder:
        StrongReminderLED(&counter); 
      break; 
    case thankYou: 
        ThankYouLED(&counter); 
      break;
    case inUse:
        InUseLED(&counter); 
      break;
    default: 
        DEBUG.println("Error occured in the LED diagram."); 
      break;     
  }

  // update the counter
  counter++; 
   
  
}


void Flash(int led_channel) {
  // can be up to 9 different channels. 
  // if channel 
  static int counter = 0; 
  switch(counter){ // this switch statement allows the same function to be called at a timer instance but have different results. 
    case 0: 
        ledChip.SetChannelPWM(led_channel,0xff);  // turn on
        ledChip2.SetChannelPWM(led_channel,0xff);  // turn on
      break;
    case 1: 
        ledChip.SetChannelPWM(led_channel,0);  // turn off
        ledChip2.SetChannelPWM(led_channel,0);  // turn on
      break; 
  }
  counter ++; 
  counter = counter%2; // right now only goes between 0 and 1. 
}


/* Example code from the fader example that I might want to use later 


#include <Wire.h>
#include <lp55231.h>

Lp55231 ledChip;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  delay(5000);
  Serial.println("-- Starting Setup() --");

  ledChip.Begin();
  ledChip.Enable();

  ledChip.AssignChannelToMasterFader(0, 0);
  ledChip.AssignChannelToMasterFader(1, 0);
  ledChip.AssignChannelToMasterFader(6, 0);

  ledChip.SetLogBrightness(0, true);
  ledChip.SetLogBrightness(1, true);
  ledChip.SetLogBrightness(6, true);

  ledChip.SetDriveCurrent(0, 0xff);
  ledChip.SetDriveCurrent(1, 0xff);
  ledChip.SetDriveCurrent(6, 0xff);

  // can adjust color here easily
  ledChip.SetChannelPWM(0,0x00); // og 80
  ledChip.SetChannelPWM(1,0xff); // og 40
  ledChip.SetChannelPWM(6,0xd0); // og ff

  delay(500);

  Serial.println("-- Setup() Complete --");

}

void loop() {
  // put your main code here, to run repeatedly:

  // current will track the LED we're turning on
  // previous will keep track of the last one we turned on to turn it off again

  static uint8_t current = 0, previous = 0;
  static uint32_t next = millis()+1000;

  if(millis() >= next)
  {
    next += 50;

    Serial.print("Illuminating: ");
    Serial.println(current);

    ledChip.SetMasterFader(0, current);

    current++;
  }
}


*/
