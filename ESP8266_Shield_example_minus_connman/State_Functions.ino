#include "definitions.h" 

//enum State{waiting, iAmHere, gentleReminder, strongReminder, thankYou, inUse}; 

void StateMachine()
{ 
  static int counter = 0; 
  static unsigned long time_elapsed = 0; 
  counter = counter + 1;
  time_elapsed = counter * STATE_MACH_INTERVAL;  

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
    if(time_elapsed >= 1000L) { // every second
      //DEBUG.println(time_elapsed);
      if(LowerSensorTakeMeasurement() == 1) {
        // detected motion, go to i am here
        DEBUG.println("going to I AM Here");
        *counter = 0; 
        return iAmHere; 
      } 
      *counter = 0; 
    }
    
    return waiting; 
}

enum State IAmHereState(unsigned long time_elapsed, int * counter) {
    if(time_elapsed >= 1000L) { // every second FIXME: make more frequent in release
      if(UpperSensorTakeMeasurement() == 2){
        // moving to gentle reminder state
        DEBUG.println("Moving to gentle reminder");
        *counter = 0; 
        return gentleReminder; 
      }
      *counter = 0; 
    }
    return iAmHere;
}

enum State GentleReminderState(unsigned long time_elapsed, int * counter) {
    // do gentle reminder things
    if(time_elapsed >= 1000L) { // every second
      if(UpperSensorTakeMeasurement() == 0){
        // no signal 
        DEBUG.println("Moving to strong reminder"); 
        *counter = 0; 
        return strongReminder; 
      }
      *counter = 0; 
    }
    return gentleReminder; 
}

enum State StrongReminderState(unsigned long time_elapsed, int * counter) {
    // do strong reminder things 
    if(time_elapsed >= 1000L * 15){ // be loud for 15 seconds, then timeout
      // timeout feature to go back to waiting 
      *counter = 0; 
    }
    return strongReminder;
}

enum State ThankYouState(unsigned long time_elapsed, int * counter) {
    // always gone to when the walker is grabbed. 
    DEBUG.println("THANK YOU!!!");
    
    printDateAndTime(); 
    
    return inUse;  
}

enum State InUseState(unsigned long time_elapsed, int * counter) {

    return inUse; 
}

/*********** REDIRECTION FUNCTIONS ***********/
void GoToThankYou(){
  DEBUG.println("Redirecting to Thank you");
  next_state = thankYou;   
}
