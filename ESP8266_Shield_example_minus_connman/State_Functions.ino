#include "definitions.h" 

//enum State{waiting, iAmHere, gentleReminder, strongReminder, thankYou, inUse}; 

void StateMachine()
{ 
  static int counter = 0; 
  static unsigned long time_elapsed = 0; 
  counter = counter + 1;
  time_elapsed = counter * STATE_MACH_INTERVAL;  


  if(next_state != current_state) {
    //DEBUG.println("State change! Counter Reset"); 
    DEBUG.print("Current State: "); DEBUG.println(next_state); 
    counter = 0; 
  }


  current_state = next_state; 
  
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



enum State WaitingState(unsigned long time_elapsed, int * counter) {
    if(LowerSensorTakeMeasurement() == 1){
      // DEBUG.println("going to I AM Here"); 
      return iAmHere;
    }
    if(time_elapsed >= 2000L) { // every two seconds
      //DEBUG.println(time_elapsed);
      if(UpperSensorTakeMeasurement() > 0) {
        // detected motion, go to i am here
        //DEBUG.println("going to I AM Here");
        return iAmHere; 
      } 
      *counter = 0; // reset the counter in order to continue to monitor. 
    }
    
    return waiting; 
}

enum State IAmHereState(unsigned long time_elapsed, int * counter) {
    if(time_elapsed % 500 == 0) { // every second FIXME: make more frequent in release
      if(UpperSensorTakeMeasurement() == 2){
        // moving to gentle reminder state
        //DEBUG.println("Moving to gentle reminder");
        return gentleReminder; 
      }
    }
    if(time_elapsed >= 10000) { // every ten seconds
      if(LowerSensorTakeMeasurement() == 0) { // no further signal detected 
        //DEBUG.println("Going back to waiting"); 
        return waiting; 
      }  
    }
    return iAmHere;
}

enum State GentleReminderState(unsigned long time_elapsed, int * counter) {
    // do gentle reminder things
    if(time_elapsed % 500 == 0) { // every half second
      if(UpperSensorTakeMeasurement() == 0){
        // no signal 
        //DEBUG.println("Moving to strong reminder"); 
        return strongReminder; 
      }
    }
    if(time_elapsed >= 1000L * 5 && time_elapsed % 1000 == 0) { // after five seconds, every second
      if(LowerSensorTakeMeasurement() == 0){ // nobody home
        //DEBUG.println("Going to waiting"); 
        return waiting; 
      }
    }

    if(time_elapsed >= 1000L * 15) { // after 15 seconds, it doesn't matter, we're going to waiting
      return waiting; 
    }
    // if none of these things happen, we stay at the same state. 
    return gentleReminder; 
}

enum State StrongReminderState(unsigned long time_elapsed, int * counter) {
    // do strong reminder things 
    if(time_elapsed >= 1000L * 15){ // be loud for 15 seconds, then timeout
      // timeout feature to go back to waiting 
      return waiting; 
    }
    return strongReminder;
}

enum State ThankYouState(unsigned long time_elapsed, int * counter) {
    // always gone to when the walker is grabbed. 
    //DEBUG.println("THANK YOU!!!");
    if(time_elapsed >= 6500L) { // the amount of time 
        // after this, the LED sequence should be done 
        if(CARD_OK == 1) // that means the card is ok to use and we can successfully print
        {
          printDateAndTime(); 
        }
        //DEBUG.println("Going to In Use"); 
        return inUse; 
      }
    return thankYou;  
}

enum State InUseState(unsigned long time_elapsed, int * counter) {
    while(digitalRead(LEFT_HANDLE_BUTTON)==1 || digitalRead(RIGHT_HANDLE_BUTTON) == 1) 
    {
      // if the person is using the buttons, then we are absolutely in use and don't need to check the other criterion. 
      return inUse;  
    }
    
    if(time_elapsed >= 1000L) { // every second
      if(UpperSensorTakeMeasurement() == 0){
        // no signal 
        //DEBUG.println("Moving back to Waiting"); 
        //EnableButtonInterrupts(); 
        *counter = 0; 
        return waiting; 
      }
      *counter = 0; 
    }
    return inUse; 
}

/*********** REDIRECTION FUNCTIONS ***********/
void GoToThankYouLeft(){
  DEBUG.println("Redirect Left");
  //DisableButtonInterrupts(); 
  //delayMicroseconds(1000);
  next_state = thankYou;   
}

void GoToThankYouRight() {
  DEBUG.println("Redirect Right");
  //delayMicroseconds(1000); 
  next_state = thankYou;   
}
