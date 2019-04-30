#include <Wire.h>
#include <lp55231.h>
#include "definitions.h"

BlynkTimer timer;

//int led_channel = 1;


void setup() {
// put your setup code here, to run once:

    Serial.begin(9600);
    Serial.println("-- Starting Setup() --");

    ledChip2.Begin();
    ledChip2.Enable();

    delay(500);

    timer.setInterval(LED_INTERVAL,thankYouFlash);
//    timer.setInterval(LED_INTERVAL,strongReminderLED);
//    timer.setInterval(LED_INTERVAL,startUpLED);
//    timer.setInterval(LED_INTERVAL,gentleReminderLED);
//    timer.setInterval(LED_INTERVAL,inUseLED);

    Serial.println("-- Setup() Complete --");
}


void ThankYouLED(void)
{
  static int counter = 0; 
  static int startup = 0;
  if(startup == 0)
  {
    clearLED();
    startup = 1;
  }
  switch(counter){ // this switch statement allows the same function to be called at a timer instance but have different results. 
    case 0: 
        ledChip2.SetChannelPWM(greenLED1,50);  // turn on
        ledChip2.SetChannelPWM(greenLED2,0);  // turn on
        ledChip2.SetChannelPWM(greenLED3,0);  // turn on
		ledChip.SetChannelPWM(greenLED1,50);  // turn on
        ledChip.SetChannelPWM(greenLED2,0);  // turn on
        ledChip.SetChannelPWM(greenLED3,0);  // turn on
      break;
    case 1: 
        ledChip.SetChannelPWM(greenLED1,0);  // turn off
        ledChip.SetChannelPWM(greenLED2,50);  // turn off
		ledChip2.SetChannelPWM(greenLED1,0);  // turn off
        ledChip2.SetChannelPWM(greenLED2,50);  // turn off
      break; 
    case 2:
        ledChip.SetChannelPWM(greenLED2,0);  // turn off
        ledChip.SetChannelPWM(greenLED3,50);  // turn off 
		ledChip2.SetChannelPWM(greenLED2,0);  // turn off
        ledChip2.SetChannelPWM(greenLED3,50);  // turn off 
      break;
  }
  counter++;
  counter = counter % 3;
}

void StrongReminderLED(void)
{
  static int counter = 0;
  static int startup = 0;
  if(startup == 0)
  {
    clearLED();
    startup = 1;
  } 
  switch(counter){// this switch statement allows the same function to be called at a timer instance but have different results. 
    case 0: 
        ledChip.SetChannelPWM(redLED1,50);  // turn on
        ledChip.SetChannelPWM(redLED2,50);  // turn on
        ledChip.SetChannelPWM(redLED3,50);  // turn on
		ledChip2.SetChannelPWM(redLED1,50);  // turn on
        ledChip2.SetChannelPWM(redLED2,50);  // turn on
        ledChip2.SetChannelPWM(redLED3,50);  // turn on
      break;
    case 1: 
        ledChip.SetChannelPWM(redLED1,0);  // turn off
        ledChip.SetChannelPWM(redLED2,0);  // turn off
        ledChip.SetChannelPWM(redLED3,0);  // turn on
		ledChip2.SetChannelPWM(redLED1,0);  // turn off
        ledChip2.SetChannelPWM(redLED2,0);  // turn off
        ledChip2.SetChannelPWM(redLED3,0);  // turn on
      break;
  }
  counter++;
  counter = counter % 2;
}

void StartUpLED(void)
{
  static int counter = 0; 
  static int startup = 0;
  if(startup == 0)
  {
    clearLED();
    startup = 1;
  } 
  switch(counter){ // this switch statement allows the same function to be called at a timer instance but have different results. 
    case 0: 
        ledChip.SetChannelPWM(blueLED1,50);  
        ledChip.SetChannelPWM(greenLED1,50);  
        ledChip.SetChannelPWM(redLED1,50);
        ledChip.SetChannelPWM(blueLED2,0); 
        ledChip.SetChannelPWM(greenLED2,0);  
        ledChip.SetChannelPWM(redLED2,0);  
        ledChip.SetChannelPWM(blueLED3,0); 
        ledChip.SetChannelPWM(greenLED3,0);  
        ledChip.SetChannelPWM(redLED3,0);   
		ledChip2.SetChannelPWM(blueLED1,50);  
        ledChip2.SetChannelPWM(greenLED1,50);  
        ledChip2.SetChannelPWM(redLED1,50);
        ledChip2.SetChannelPWM(blueLED2,0); 
        ledChip2.SetChannelPWM(greenLED2,0);  
        ledChip2.SetChannelPWM(redLED2,0);  
        ledChip2.SetChannelPWM(blueLED3,0); 
        ledChip2.SetChannelPWM(greenLED3,0);  
        ledChip2.SetChannelPWM(redLED3,0);
      break;
    case 1:
        ledChip.SetChannelPWM(blueLED1,0); 
        ledChip.SetChannelPWM(greenLED1,0);  
        ledChip.SetChannelPWM(redLED1,0);  
        ledChip.SetChannelPWM(blueLED2,50); 
        ledChip.SetChannelPWM(greenLED2,50);  
        ledChip.SetChannelPWM(redLED2,50);  
		ledChip2.SetChannelPWM(blueLED1,0); 
        ledChip2.SetChannelPWM(greenLED1,0);  
        ledChip2.SetChannelPWM(redLED1,0);  
        ledChip2.SetChannelPWM(blueLED2,50); 
        ledChip2.SetChannelPWM(greenLED2,50);  
        ledChip2.SetChannelPWM(redLED2,50);  
      break; 
    case 2:
        ledChip.SetChannelPWM(blueLED2,0); 
        ledChip.SetChannelPWM(greenLED2,0);  
        ledChip.SetChannelPWM(redLED2,0);  
        ledChip.SetChannelPWM(blueLED3,50); 
        ledChip.SetChannelPWM(greenLED3,50);  
        ledChip.SetChannelPWM(redLED3,50);
		ledChip2.SetChannelPWM(blueLED2,0); 
        ledChip2.SetChannelPWM(greenLED2,0);  
        ledChip2.SetChannelPWM(redLED2,0);  
        ledChip2.SetChannelPWM(blueLED3,50); 
        ledChip2.SetChannelPWM(greenLED3,50);  
        ledChip2.SetChannelPWM(redLED3,50); 		
      break;
     case 3:
        ledChip.SetChannelPWM(blueLED1,50);  
        ledChip.SetChannelPWM(greenLED1,50);  
        ledChip.SetChannelPWM(redLED1,50);
        ledChip.SetChannelPWM(blueLED2,50); 
        ledChip.SetChannelPWM(greenLED2,50);  
        ledChip.SetChannelPWM(redLED2,50);  
		ledChip2.SetChannelPWM(blueLED1,50);  
        ledChip2.SetChannelPWM(greenLED1,50);  
        ledChip2.SetChannelPWM(redLED1,50);
        ledChip2.SetChannelPWM(blueLED2,50); 
        ledChip2.SetChannelPWM(greenLED2,50);  
        ledChip2.SetChannelPWM(redLED2,50);
      break;
    default:
        clearLED();
      break;
  }
  counter++;
}

void GentleReminderLED(void)
{
  static int counter = 0; 
  static int startup = 0;
  if(startup == 0)
  {
    clearLED();
    startup = 1;
  }
  switch(counter){ // this switch statement allows the same function to be called at a timer instance but have different results. 
    case 0: 
        ledChip.SetChannelPWM(greenLED1,50);  // turn on
        ledChip.SetChannelPWM(redLED1,50);  // turn on
        ledChip.SetChannelPWM(greenLED3,0);  // turn on
        ledChip.SetChannelPWM(redLED3,0);  // turn on
		ledChip2.SetChannelPWM(greenLED1,50);  // turn on
        ledChip2.SetChannelPWM(redLED1,50);  // turn on
        ledChip2.SetChannelPWM(greenLED3,0);  // turn on
        ledChip2.SetChannelPWM(redLED3,0);  // turn on
        
      break;
    case 1: 
        ledChip.SetChannelPWM(greenLED2,50);  // turn on
        ledChip.SetChannelPWM(redLED2,50);  // turn on
        ledChip.SetChannelPWM(greenLED1,0);  // turn on
        ledChip.SetChannelPWM(redLED1,0);  // turn on
		ledChip2.SetChannelPWM(greenLED2,50);  // turn on
        ledChip2.SetChannelPWM(redLED2,50);  // turn on
        ledChip2.SetChannelPWM(greenLED1,0);  // turn on
        ledChip2.SetChannelPWM(redLED1,0);  // turn on
      break; 
    case 2:
        ledChip.SetChannelPWM(greenLED3,50);  // turn on
        ledChip.SetChannelPWM(redLED3,50);  // turn on
        ledChip.SetChannelPWM(greenLED2,0);  // turn on
        ledChip.SetChannelPWM(redLED2,0);  // turn on
		ledChip2.SetChannelPWM(greenLED3,50);  // turn on
        ledChip2.SetChannelPWM(redLED3,50);  // turn on
        ledChip2.SetChannelPWM(greenLED2,0);  // turn on
        ledChip2.SetChannelPWM(redLED2,0);  // turn on
      break;
  }
  counter++;
  counter = counter % 3;
}

void InUseLED(void)
{
  static int counter = 0;
  static int startup = 0;
  if(startup == 0)
  {
    clearLED();
    startup = 1;
  } 
  switch(counter){// this switch statement allows the same function to be called at a timer instance but have different results. 
    case 0: 
      ledChip.SetChannelPWM(redLED2,20);  // turn on
      ledChip.SetChannelPWM(greenLED2,20);  // turn on
      ledChip.SetChannelPWM(blueLED2,20);  // turn on
	  ledChip2.SetChannelPWM(redLED2,20);  // turn on
      ledChip2.SetChannelPWM(greenLED2,20);  // turn on
      ledChip2.SetChannelPWM(blueLED2,20);  // turn on
      break;
    case 1: 
      ledChip.SetChannelPWM(redLED2,0);  // turn off
      ledChip.SetChannelPWM(greenLED2,0);  // turn off
      ledChip.SetChannelPWM(blueLED2,0);  // turn on
	  ledChip2.SetChannelPWM(redLED2,0);  // turn off
      ledChip2.SetChannelPWM(greenLED2,0);  // turn off
      ledChip2.SetChannelPWM(blueLED2,0);  // turn on
      break;
  }
  counter++;
  counter = counter % 2;
}

void ClearLED(void)
{
  ledChip.SetChannelPWM(blueLED1,0);  
  ledChip.SetChannelPWM(greenLED1,0);  
  ledChip.SetChannelPWM(redLED1,0);
  ledChip.SetChannelPWM(blueLED2,0); 
  ledChip.SetChannelPWM(greenLED2,0);  
  ledChip.SetChannelPWM(redLED2,0);  
  ledChip.SetChannelPWM(blueLED3,0); 
  ledChip.SetChannelPWM(greenLED3,0);  
  ledChip.SetChannelPWM(redLED3,0);
  ledChip2.SetChannelPWM(blueLED1,0);  
  ledChip2.SetChannelPWM(greenLED1,0);  
  ledChip2.SetChannelPWM(redLED1,0);
  ledChip2.SetChannelPWM(blueLED2,0); 
  ledChip2.SetChannelPWM(greenLED2,0);  
  ledChip2.SetChannelPWM(redLED2,0);  
  ledChip2.SetChannelPWM(blueLED3,0); 
  ledChip2.SetChannelPWM(greenLED3,0);  
  ledChip2.SetChannelPWM(redLED3,0);
}
