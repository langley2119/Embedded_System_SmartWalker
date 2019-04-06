// Serial Printing
#define PRINT_BUFF_PTRS     ON
#define PRINT_RAW_DATA      ON
#define PRINT_AVG_DATA      ON
#define PRINT_MOVEMENT      ON
#define PRINT_GESTURES      ON
String          serial_string;
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
/****************************************************************************************************************************************************/  
/************************************************************ Conditional Serial Printing ***********************************************************/  
/****************************************************************************************************************************************************/  
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
template<typename T> size_t printListMem(T output)
{
    Serial.print(output);
    return Serial.print(", ");
}
template<typename T> size_t printIf(T output)
{
    if(SERIAL_PRINTING)
        return Serial.print(output);
    return 0;
}
template<typename T> size_t printlnIf(T output)
{
    if(SERIAL_PRINTING)
        return Serial.println(output);
    return 0;
}
int seconds() {return millis() / MS_PER_S;}
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
/****************************************************************************************************************************************************/  
/******************************************************** Serial Monitor: Sensor Data/Status ********************************************************/  
/****************************************************************************************************************************************************/  
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
void print_OpenPIR()
{
    if ( (last_print + PIR_PRINT_TIME) < millis() )
    {
        Serial.println("<******** OpenPIR: ********>");
        last_print = millis();        
        PIR_digitalOutput   = digitalRead(PIR_DOUT_PIN);
        Serial.print(PIR_VMAX * PIR_digitalOutput);                // Print 5 x digital pin to maintain scale with AOUT. 
        Serial.print(',');    // Print a comma
        Serial.print(PIR_DOUT_MAX);    // Print the upper limit
        Serial.print(',');    // Print a comma
        Serial.print(PIR_DOUT_MIN);    // Print the lower limit
        Serial.print(',');    // Print a comma
        Serial.print(PIR_voltage); // Print voltage
        Serial.println();
    }
}
void print_HCSR04()
{
    Serial.println("<******** HC-SR04: ********>");
    serial_string = "The hit time was " + String(HCSR04_hitTime) + " microseconds\n";
    if((HCSR04_hitTime == 0) && (HCSR04_sensor.getTimeout() == HCSR04_TIMEOUT)) 
    {
        HCSR04_sensor.setTimeout(HCSR04_DEBUG_TIMEOUT);
        serial_string += "[!] Timeout increased from " + String(HCSR04_TIMEOUT) + " to " + String(HCSR04_DEBUG_TIMEOUT) + "\n";
        serial_string += "[!] If the hit time is still 0 after this message, please check your wiring!\n";
    }
    Serial.print(serial_string);
}
void print_info()
{
    if(SERIAL_PRINTING)
    {
        Serial.print("Time since last motion = ");  // Print voltage
        Serial.println(last_motion);                // Print voltage
        #ifdef OPENPIR_SENSOR
            print_OpenPIR();
        #endif
        #ifdef VL53L0X_SENSOR
            print_VL53L0X();
        #endif
        #ifdef RFD77402_SENSOR
            print_RFD77402();
        #endif
        #ifdef HCSR04_SENSOR
            print_HCSR04();
        #endif
//        if(OPENPIR_SENSOR == ON)
//            print_HCSR04();
//        if(VL53L0X_SENSOR == ON)
//            print_VL53L0X();
//        if(RFD77402_SENSOR == ON)
//            print_RFD77402();
//        if(HCSR04_SENSOR == ON)
//            print_HCSR04();
    }
}

