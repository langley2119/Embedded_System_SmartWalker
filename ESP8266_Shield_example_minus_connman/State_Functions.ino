//enum State{waiting, iAmHere, gentleReminder, strongReminder, thankYou, inUse}; 

enum State WaitingState(unsigned long time_elapsed, int * counter) {
    if(time_elapsed > 1000L) { // every second
      if(LowerSensorTakeMeasurement() == 1) {
        // detected motion, go to i am here
        DEBUG.println("going to I AM Here");
        return iAmHere; 
      } 
      *counter = 0; 
    }
    
    return waiting; 
}

enum State IAmHereState(unsigned long time_elapsed, int * counter) {
    if(time_elapsed > 1000L) { // every second
      if(UpperSensorTakeMeasurement == 2){
        
      }
      *counter = 0; 
    }
    return iAmHere;
}

enum State GentleReminderState(unsigned long time_elapsed, int * counter) {

    return gentleReminder; 
}

enum State StrongReminderState(unsigned long time_elapsed, int * counter) {

    return strongReminder;
}

enum State ThankYouState(unsigned long time_elapsed, int * counter) {
  
    return thankYou;  
}

enum State InUseState(unsigned long time_elapsed, int * counter) {

    return inUse; 
}
