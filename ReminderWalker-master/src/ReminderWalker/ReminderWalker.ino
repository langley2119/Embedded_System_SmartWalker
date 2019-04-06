//---------------------------------------------------------------------------------------------------------------------------------------------------/  
/****************************************************************************************************************************************************/  
/********************************************************************* Arduino **********************************************************************/  
/****************************************************************************************************************************************************/  
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
#include <Wire.h>  
#include <string.h>  
#include <stdio.h>  
//#include <vector.h>
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
/****************************************************************************************************************************************************/  
/******************************************************** System Component/Sensor Libraries *********************************************************/  
/****************************************************************************************************************************************************/  
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <WiFiEspServer.h>
#include <WiFiEspUdp.h>
//#include <WiFi.h>
//#include <WiFiClient.h>
//#include <WiFiServer.h>
//#include <WiFiUdp.h>
//#include <ConnectThings_ESP8266.h>
//#include <WiFiManager.h>
//#include <WireWrapper.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>                      // Adafruit_RGBLCDShield
#include <ST_HW_HC_SR04.h>
#include <VL53L0X.h>
#include <Adafruit_VL53L0X.h>
#include <SparkFun_RFD77402_Arduino_Library.h>              // https://github.com/sparkfun/SparkFun_RFD77402_Arduino_Library
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
/****************************************************************************************************************************************************/  
/*********************************************************** Aliases/Constants Definitions **********************************************************/  
/****************************************************************************************************************************************************/  
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
#define BAUD_RATE       115200
#define MS_PER_S        1000
#define ON              true
#define OFF             false
#define RED             0x1
#define GREEN           0x2
#define YELLOW          0x3
#define BLUE            0x4
#define VIOLET          0x5
#define TEAL            0x6
#define WHITE           0x7
#define RECEDING        -1
#define APPROACHING     1
#define STATIONARY      0
/****************************************************************************************************************************************************/  
/*************************** Component/Sensor IO Configurations: Signal Parameter Definitions & Operation Settings/Options **************************/ 
/****************************************************************************************************************************************************/  
//--------------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------- Adafruit_RGBLCDShield --------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------------------------------------//
#define RGBLCD_ROWS                 2
#define RGBLCD_COLUMNS              16
#define RGBLCD_DEFAULT_BACKLIGHT    WHITE
//--------------------------------------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------- HC-SR04 --------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------------------------------------//
#define HCSR04_TIMEOUT              5000                    // Default timeout = 5000
#define HCSR04_DEBUG_TIMEOUT        23200                   // Extended timeout = 23200
//--------------------------------------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------- VL53L0X --------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------------------------------------//
#define VL53L0X_TIMEOUT             500
//#define VL53L0X_LONG_RANGE
//#define VL53L0X_HIGH_SPEED
//#define VL53L0X_HIGH_ACCURACY
//--------------------------------------------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------- OpenPIR --------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------------------------------------//
#define PIR_VMAX                    5.0                     // Maximum PIR voltage
#define PIR_AOUT_BITS               10                      // PIR analog output bit precision
#define PIR_AOUT_MAX                (2^PIR_AOUT_BITS)       // PIR max analog output 
#define PIR_DOUT_MIN                1.7                     // PIR min digital output 
#define PIR_DOUT_MAX                2.5                     // PIR max digital output 
//-------------------------------------------------------------------- RFD77402 --------------------------------------------------------------------//
#define RFD77402_SPEED              I2C_SPEED_STANDARD      // I2C_SPEED_FAST or I2C_SPEED_STANDARD _NORMAL
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
/****************************************************************************************************************************************************/  
/************************************************************ Arduino IO Pin Assignments ************************************************************/  
/****************************************************************************************************************************************************/  
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
#define HCSR04_TRIGGER_PIN          13
#define HCSR04_ECHO_PIN             12  
#define VL53L0X_SCL_PIN             21
#define VL53L0X_SDA_PIN             20  
#define PIR_AOUT_PIN                A0                      // PIR analog output on A0
#define PIR_DOUT_PIN                2                       // PIR digital output on D2
#define PIR_LED_PIN                 13                      // LED to illuminate on motion
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
/****************************************************************************************************************************************************/  
/****************************************************************** I2C Addressing ******************************************************************/  
/****************************************************************************************************************************************************/  
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
#define VL53L0X_ADDR                0x29
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
/****************************************************************************************************************************************************/  
/********************************************************************* Control **********************************************************************/  
/****************************************************************************************************************************************************/  
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
// Execution Options/Controls
#define OPENPIR_SENSOR              ON
#define VL53L0X_SENSOR              OFF
#define ST_VL53L0X_SENSOR           OFF
#define ADAFRUIT_VL53L0X_SENSOR     OFF
#define RFD77402_SENSOR             ON
//#define HCSR04_SENSOR             OFF

bool    TEST_MODE                   = true;
bool    SLEEP_MODE                  = true;      
bool    SERIAL_PRINTING             = true;
bool    TEST_ADAFRUIT_VL53L0X       = false;
bool    TEST_RGBLCD_SHIELD          = false;

// Timing Constants/Counters
#define INACTIVE_TIME_THRESH        30                      // Rate of serial printouts
#define REFRESH_TIME                20  
#define LOOP_DELAY                  100                     // VL53L0X = 100, OpenPIR Delay 1500ms (1.5s)
#define PIR_PRINT_TIME              100                     // Rate of serial printouts
long            loop_start          = 0;
unsigned long   last_print          = 0;                    // Keep track of last serial out
long            last_motion         = 0;
  
// State Control/Transition Conditions
enum SYSTEM_STATES                  { SLEEP, STANDBY, LOW_POWER, AWAKE };               // Define the system's state machine states
enum EXECUTION_MODES                { TESTING, EVALUATION, OPERATION};                  // Define the system's state machine states
String SYSTEM_STATE_STRINGS[]       = { "SLEEP", "STANDBY", "LOW_POWER", "AWAKE" };     // Define the system's state machine states
String EXEC_MODE_STRINGS[]          = { "TESTING", "EVALUATION", "OPERATION"};          // Define the system's state machine states
SYSTEM_STATES   system_state        = SYSTEM_STATES(0);
EXECUTION_MODES execution_mode      = EXECUTION_MODES(0);
String          sys_state_string    = SYSTEM_STATE_STRINGS[0];
String          exec_mode_string    = EXEC_MODE_STRINGS[0];
bool            sleep               = false;    
bool            wake_up             = false;      


// Sensor Objects
Adafruit_RGBLCDShield   RGBLCDshield            = Adafruit_RGBLCDShield();
Adafruit_VL53L0X        Adafruit_VL53L0X_sensor = Adafruit_VL53L0X();
VL53L0X                 VL53L0X_sensor;
ST_HW_HC_SR04           HCSR04_sensor(HCSR04_TRIGGER_PIN, HCSR04_ECHO_PIN, HCSR04_TIMEOUT);     // Using constructor with timeout value 
RFD77402                RFD77402_sensor;                                                        // Hook object to the library

// Sensor Measurement/Status Variables
unsigned int                        PIR_analogOutput;               // Read in analog value    
float                               PIR_digitalOutput;              // Read in digital value    
int                                 PIR_motionStatus;               // PIR detected motion status from DOUT, active HIGH signal upon motion detection
float                               PIR_voltage;                    // Convert 10-bit analog value to a voltage (Assume high voltage is 5.0V.)    
VL53L0X_RangingMeasurementData_t    Adafruit_VL53L0X_measure;
uint16_t                            VL53L0X_range;
unsigned int                        RFD77402_distance;
unsigned int                        RFD77402_confidence;
byte                                RFD77402_pixels;
int                                 HCSR04_hitTime;                 // In microseconds 

// Sensor Data Buffering
#define     HCSR04_BUFFERSIZE       10  
float       HCSR04_buffer           [HCSR04_BUFFERSIZE];  
int         HCSR04_buffer_pos       = 0;  

int8_t      RFD77402_movement_direction     = STATIONARY;
int8_t      VL53L0X_movement_direction      = STATIONARY;
int8_t      RFD77402_movement_counter       = 0;
int8_t      VL53L0X_movement_counter        = 0;
int8_t*     torsa_movement_direction        = &RFD77402_movement_direction;
int8_t*     torso_movement_counter          = &RFD77402_movement_counter;
int8_t*     lower_body_movement_direction   = &VL53L0X_movement_direction;
int8_t*     lower_body_movement_counter     = &VL53L0X_movement_counter;

//---------------------------------------------------------------------------------------------------------------------------------------------------/  
/****************************************************************************************************************************************************/  
/*********************************************************************** Main ***********************************************************************/  
/****************************************************************************************************************************************************/  
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
void setup()  
{  
    init_system();
    setup_system();
}  
void loop()  
{  
    loop_start = millis();      
    system_state_machine();
    print_info();
    delay(LOOP_DELAY);  
}  
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
/****************************************************************************************************************************************************/  
/*********************************************** System Configuration/Initialization Setup Functions ************************************************/  
/****************************************************************************************************************************************************/  
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
void init_system()
{
    Serial.begin (BAUD_RATE);  
    Wire.begin ();   
    while (! Serial) delay(1);              // wait until serial port opens for native USB devices   
}
void setup_system()
{
    setup_RGBLCDshield();
    #ifdef OPENPIR_SENSOR
        setup_OpenPIR();
    #endif
    #ifdef VL53L0X_SENSOR
        setup_VL53L0X();
    #endif
    #ifdef RFD77402_SENSOR
        setup_RFD77402();
    #endif
//    if( OPENPIR_SENSOR == ON)
//    {
//        setup_OpenPIR();
//    }   
//    if( VL53L0X_SENSOR == ON)
//    {
//        setup_VL53L0X();
//    }
//    if( RFD77402_SENSOR == ON)
//    {
//        setup_RFD77402();
//    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
/****************************************************************************************************************************************************/  
/*********************************************** System State Machine Transitions/Operation Functions ***********************************************/  
/****************************************************************************************************************************************************/  
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
void set_system_state()
{
    // { SLEEP, STANDBY, LOW_POWER, AWAKE }
    if (SLEEP_MODE == ON && last_motion > INACTIVE_TIME_THRESH)
    {
        sleep = true; 
        system_state = SLEEP;       
    }
    if (sleep && PIR_motionStatus == HIGH)
    {
        sleep = false;     
        wake_up = true;   
        system_state = AWAKE;  
    }
}
void sleep_state()
{
    printlnIf("Sleep State");
//    if(OPENPIR_SENSOR == ON)
//    {
//        acquire_OpenPIR_data();
//    }
    #ifdef OPENPIR_SENSOR
        acquire_OpenPIR_data();
    #endif
}
void awake_state()
{
    printlnIf("Awake State");
//    if(OPENPIR_SENSOR == ON)
//    {
//        acquire_OpenPIR_data();
//    }
//    if(VL53L0X_SENSOR == ON)
//    {
//        acquire_VL53L0X_data();
//    }
//    if(RFD77402_SENSOR == ON)
//    {
//        acquire_RFD77402_data();
//    }
//    if(HCSR04_SENSOR == ON)
//    {
//        acquire_HCSR04_data();
//    }
    #ifdef OPENPIR_SENSOR
        acquire_OpenPIR_data();
    #endif
    #ifdef VL53L0X_SENSOR
        acquire_VL53L0X_data();
    #endif
    #ifdef RFD77402_SENSOR
        acquire_RFD77402_data();
    #endif
    #ifdef HCSR04_SENSOR
        acquire_HCSR04_data();
    #endif
    gesture_state();
}
void system_state_machine()
{
    if(system_state == SLEEP)
        sleep_state();
    else if(system_state == AWAKE)
        awake_state();
    else if(system_state == STANDBY);
    else if(system_state == LOW_POWER);
    set_system_state();
    set_RFD77402_state();    
}

