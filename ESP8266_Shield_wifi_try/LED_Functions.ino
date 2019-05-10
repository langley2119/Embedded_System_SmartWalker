#include "definitions.h"

// DECLARE THE COUNTER OUTSIDE OF THE LED FUNCTIONS 

void ThankYouLED(int * counter)
{
  
  switch(*counter){ // this switch statement allows the same function to be called at a timer instance but have different results. 
    case 1: 
        ledChip.SetChannelPWM(greenLED1,50);  // turn on
        ledChip.SetChannelPWM(greenLED2,0);  // turn on
        ledChip.SetChannelPWM(greenLED3,0);  // turn on
        ledChip2.SetChannelPWM(greenLED1,0);  // turn on
        ledChip2.SetChannelPWM(greenLED2,0);  // turn on
        ledChip2.SetChannelPWM(greenLED3,50);  // turn on
      break;
    case 2: 
        ledChip.SetChannelPWM(greenLED1,0);  // turn off
        ledChip.SetChannelPWM(greenLED2,50);  // turn on
		    ledChip2.SetChannelPWM(greenLED3,0);  // turn off
        ledChip2.SetChannelPWM(greenLED2,50);  // turn on
      break; 
    case 3:
        ledChip.SetChannelPWM(greenLED2,0);  // turn off
        ledChip.SetChannelPWM(greenLED3,50);  // turn on 
		    ledChip2.SetChannelPWM(greenLED2,0);  // turn off
        ledChip2.SetChannelPWM(greenLED1,50);  // turn on 
        *counter = 0; // by setting it to 0 we get 1 the next time it comes around, to restart the cycle 
      break;
  }
  
}

void StrongReminderLED(int * counter)
{

  switch(*counter){// this switch statement allows the same function to be called at a timer instance but have different results. 
    case 1: 
        ledChip.SetChannelPWM(redLED1,50);  // turn on
        ledChip.SetChannelPWM(redLED2,50);  // turn on
        ledChip.SetChannelPWM(redLED3,50);  // turn on
		    ledChip2.SetChannelPWM(redLED1,50);  // turn on
        ledChip2.SetChannelPWM(redLED2,50);  // turn on
        ledChip2.SetChannelPWM(redLED3,50);  // turn on
      break;
    case 2: 
        ledChip.SetChannelPWM(redLED1,0);  // turn off
        ledChip.SetChannelPWM(redLED2,0);  // turn off
        ledChip.SetChannelPWM(redLED3,0);  // turn on
		    ledChip2.SetChannelPWM(redLED1,0);  // turn off
        ledChip2.SetChannelPWM(redLED2,0);  // turn off
        ledChip2.SetChannelPWM(redLED3,0);  // turn on
        *counter = 0; // by setting it to -1 we get 0 the next time it comes around 
      break;
  }

}

void StartUpLED(int * counter)
{
  // this routine only happens once, so we refrain from resetting the counter in the last step. 
  switch(*counter){ // this switch statement allows the same function to be called at a timer instance but have different results. 
    case 1: 
        ledChip.SetChannelPWM(blueLED1,50);  
        ledChip.SetChannelPWM(greenLED1,50);  
        ledChip.SetChannelPWM(redLED1,50);
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
        ledChip2.SetChannelPWM(blueLED3,50); 
        ledChip2.SetChannelPWM(greenLED3,50);  
        ledChip2.SetChannelPWM(redLED3,50);
      break;
    case 2:
        ledChip.SetChannelPWM(blueLED1,0); 
        ledChip.SetChannelPWM(greenLED1,0);  
        ledChip.SetChannelPWM(redLED1,0);  
        ledChip.SetChannelPWM(blueLED2,50); 
        ledChip.SetChannelPWM(greenLED2,50);  
        ledChip.SetChannelPWM(redLED2,50);  
		    ledChip2.SetChannelPWM(blueLED3,0); 
        ledChip2.SetChannelPWM(greenLED3,0);  
        ledChip2.SetChannelPWM(redLED3,0);  
        ledChip2.SetChannelPWM(blueLED2,50); 
        ledChip2.SetChannelPWM(greenLED2,50);  
        ledChip2.SetChannelPWM(redLED2,50);  
      break; 
    case 3:
        ledChip.SetChannelPWM(blueLED2,0); 
        ledChip.SetChannelPWM(greenLED2,0);  
        ledChip.SetChannelPWM(redLED2,0);  
        ledChip.SetChannelPWM(blueLED3,50); 
        ledChip.SetChannelPWM(greenLED3,50);  
        ledChip.SetChannelPWM(redLED3,50);
		    ledChip2.SetChannelPWM(blueLED2,0); 
        ledChip2.SetChannelPWM(greenLED2,0);  
        ledChip2.SetChannelPWM(redLED2,0);  
        ledChip2.SetChannelPWM(blueLED1,50); 
        ledChip2.SetChannelPWM(greenLED1,50);  
        ledChip2.SetChannelPWM(redLED1,50); 		
      break;
     case 4:
        ledChip.SetChannelPWM(blueLED1,50);  
        ledChip.SetChannelPWM(greenLED1,50);  
        ledChip.SetChannelPWM(redLED1,50);
        ledChip.SetChannelPWM(blueLED2,50); 
        ledChip.SetChannelPWM(greenLED2,50);  
        ledChip.SetChannelPWM(redLED2,50);  
		    ledChip2.SetChannelPWM(blueLED3,50);  
        ledChip2.SetChannelPWM(greenLED3,50);  
        ledChip2.SetChannelPWM(redLED3,50);
        ledChip2.SetChannelPWM(blueLED2,50); 
        ledChip2.SetChannelPWM(greenLED2,50);  
        ledChip2.SetChannelPWM(redLED2,50);
      break;
    case 10:
        ClearLED(); // keep the lights on for a bit before the setup sequence turns off
      break;
    default:
      break; 
  }

}

void GentleReminderLED(int * counter)
{
  switch(*counter){ // this switch statement allows the same function to be called at a timer instance but have different results. 
    case 1: 
        ledChip.SetChannelPWM(greenLED1,50);  // turn on
        ledChip.SetChannelPWM(redLED1,50);  // turn on
        ledChip.SetChannelPWM(greenLED3,0);  // turn on
        ledChip.SetChannelPWM(redLED3,0);  // turn on
		    ledChip2.SetChannelPWM(greenLED3,50);  // turn on
        ledChip2.SetChannelPWM(redLED3,50);  // turn on
        ledChip2.SetChannelPWM(greenLED1,0);  // turn on
        ledChip2.SetChannelPWM(redLED1,0);  // turn on
        
      break;
    case 2: 
        ledChip.SetChannelPWM(greenLED2,50);  // turn on
        ledChip.SetChannelPWM(redLED2,50);  // turn on
        ledChip.SetChannelPWM(greenLED1,0);  // turn on
        ledChip.SetChannelPWM(redLED1,0);  // turn on
		    ledChip2.SetChannelPWM(greenLED2,50);  // turn on
        ledChip2.SetChannelPWM(redLED2,50);  // turn on
        ledChip2.SetChannelPWM(greenLED3,0);  // turn on
        ledChip2.SetChannelPWM(redLED3,0);  // turn on
      break; 
    case 3:
        ledChip.SetChannelPWM(greenLED3,50);  // turn on
        ledChip.SetChannelPWM(redLED3,50);  // turn on
        ledChip.SetChannelPWM(greenLED2,0);  // turn on
        ledChip.SetChannelPWM(redLED2,0);  // turn on
		    ledChip2.SetChannelPWM(greenLED1,50);  // turn on
        ledChip2.SetChannelPWM(redLED1,50);  // turn on
        ledChip2.SetChannelPWM(greenLED2,0);  // turn on
        ledChip2.SetChannelPWM(redLED2,0);  // turn on
        *counter = 0;
      break;
  }

}

void InUseLED(int * counter)
{
 
  int slow_counter = *counter/5 + 1; // slow down the counter to change functionality every 5th counter cycle. 
  switch(slow_counter){// this switch statement allows the same function to be called at a timer instance but have different results. 
    case 1: 
      ledChip.SetChannelPWM(redLED2,20);  // turn on
      ledChip.SetChannelPWM(greenLED2,20);  // turn on
      ledChip.SetChannelPWM(blueLED2,20);  // turn on
	    ledChip2.SetChannelPWM(redLED2,20);  // turn on
      ledChip2.SetChannelPWM(greenLED2,20);  // turn on
      ledChip2.SetChannelPWM(blueLED2,20);  // turn on
      break;
    case 2: 
      ledChip.SetChannelPWM(redLED2,0);  // turn off
      ledChip.SetChannelPWM(greenLED2,0);  // turn off
      ledChip.SetChannelPWM(blueLED2,0);  // turn on
	    ledChip2.SetChannelPWM(redLED2,0);  // turn off
      ledChip2.SetChannelPWM(greenLED2,0);  // turn off
      ledChip2.SetChannelPWM(blueLED2,0);  // turn on
      break;
  }
  // resets counter after every 10 cycles. 
  *counter = *counter % 10;
}

void ClearLED(void)
{
  //delay(10);
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
