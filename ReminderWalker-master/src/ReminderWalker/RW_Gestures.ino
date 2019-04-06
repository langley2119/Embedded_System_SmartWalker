#define PRINT_GESTURES              ON
enum GESTURE_ACTIONS                { NO_GESTURE, STANDING_UP, SITTING_DOWN, APPROACHING_WALKER, LEAVING_WALKER };                  // Define basic movement gestures/actions
GESTURE_ACTIONS gesture_action      = NO_GESTURE;                                                                                   // Current gesture/action detected
enum CUING_ACTIONS                  { NO_CUE, SLOW_BLINK, FAST_BLINK, VAR_BLINK, BEEP, PLAY_WAV };                                  // Define basic movement gestures/actions
CUING_ACTIONS cuing_action          = NO_CUE;                                                                                       // Current gesture/action detected
String GESTURE_ACTION_STRINGS[]       = { "NO_GESTURE", "STANDING_UP", "SITTING_DOWN", "APPROACHING_WALKER", "LEAVING_WALKER" };     // Define the system's state machine states

#define     RFD77402_MOVE_THRESH            10  
#define     VL53L0X_MOVE_THRESH             10  
#define     TORSO_APPROACH_THRESH           10  
#define     LOWER_BODY_APPROACH_THRESH      10  
#define     TORSO_RECEDING_THRESH           -10  
#define     LOWER_BODY_RECEDING_THRESH      -10  
#define     APPROACHING_CUE_THRESH          2  
#define     LEAVING_CUE_ONE_THRESH          2  
#define     LEAVING_CUE_TWO_THRESH          7
int8_t      gesture_counter                 = 0;
int8_t      approaching_counter             = 0;
int8_t      leaving_counter                 = 0;

//---------------------------------------------------------------------------------------------------------------------------------------------------/  
/****************************************************************************************************************************************************/  
/************************************************************ Conditional Serial Printing ***********************************************************/  
/****************************************************************************************************************************************************/  
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
void torso_gesturing() 
{
    //RFD77402_movement_direction = move_dir(RFD77402_a1, RFD77402_a2, RFD77402_a3);  
    //RFD77402_movement_counter   += RFD77402_movement_direction;
    //VL53L0X_movement_direction  = move_dir(VL53L0X_a1, VL53L0X_a2, VL53L0X_a3);      
    //VL53L0X_movement_counter    += VL53L0X_movement_direction;
}
void lower_body_gesturing() 
{
    //RFD77402_movement_direction = move_dir(RFD77402_a1, RFD77402_a2, RFD77402_a3);  
    //RFD77402_movement_counter   += RFD77402_movement_direction;
    //VL53L0X_movement_direction  = move_dir(VL53L0X_a1, VL53L0X_a2, VL53L0X_a3);      
    //VL53L0X_movement_counter    += VL53L0X_movement_direction;
}
void gesture_state() 
{
    if( torso_movement_counter > TORSO_APPROACH_THRESH )
    {
        if( lower_body_movement_counter < LOWER_BODY_APPROACH_THRESH && lower_body_movement_counter > LOWER_BODY_RECEDING_THRESH)
            gesture_action  = STANDING_UP;
        else
        {
            gesture_action  = APPROACHING_WALKER;
            gesture_counter--;
            approaching_counter++;
            leaving_counter = 0;
        }
    }
    else if( torso_movement_counter < TORSO_RECEDING_THRESH )
    {
        if( lower_body_movement_counter < LOWER_BODY_APPROACH_THRESH && lower_body_movement_counter > LOWER_BODY_RECEDING_THRESH)
            gesture_action  = SITTING_DOWN;
        else
        {
            gesture_action  = LEAVING_WALKER;
            gesture_counter++;
            approaching_counter = 0;
            leaving_counter++;
        }
    }
    else
        gesture_action  = NO_GESTURE;
}
void gesture_response() 
{
    if( approaching_counter > APPROACHING_CUE_THRESH )
        cuing_action = VAR_BLINK;
    else if( leaving_counter > LEAVING_CUE_TWO_THRESH )
        cuing_action = PLAY_WAV;
    else if( leaving_counter > LEAVING_CUE_ONE_THRESH )
        cuing_action = BEEP;
    else
        cuing_action = NO_CUE;
}
void print_gesture_info() 
{
    #ifdef PRINT_GESTURES
        Serial.print("Gesture : ");
        if(gesture_action == NO_GESTURE)
            Serial.println(GESTURE_ACTION_STRINGS[0]);         
        else if(gesture_action == STANDING_UP)
            Serial.println(GESTURE_ACTION_STRINGS[1]);         
        else if(gesture_action == SITTING_DOWN)
            Serial.println(GESTURE_ACTION_STRINGS[2]);         
        else if(gesture_action == APPROACHING_WALKER)
            Serial.println(GESTURE_ACTION_STRINGS[3]);         
        else if(gesture_action == LEAVING_WALKER)
            Serial.println(GESTURE_ACTION_STRINGS[4]);         
    #endif
}
//enum GESTURE_ACTIONS                { NO_GESTURE, STANDING_UP, SITTING_DOWN, APPROACHING_WALKER, LEAVING_WALKER };                // Define basic movement gestures/actions
//GESTURE_ACTIONS gesture_action      = NO_GESTURE;                                                                                 // Current gesture/action detected
//enum CUING_ACTIONS                  { NO_CUE, SLOW_BLINK, FAST_BLINK, VAR_BLINK, BEEP, PLAY_WAV };                // Define basic movement gestures/actions
//CUING_ACTIONS cuing_action          = NO_CUE;                                                                                 // Current gesture/action detected
//#define PRINT_GESTURES      ON
//String GESTURE_ACTION_STRINGS[]       = { "NO_GESTURE", "STANDING_UP", "SITTING_DOWN", "APPROACHING_WALKER", "LEAVING_WALKER" };     // Define the system's state machine states


