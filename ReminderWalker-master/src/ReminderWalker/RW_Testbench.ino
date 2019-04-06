//---------------------------------------------------------------------------------------------------------------------------------------------------/  
/****************************************************************************************************************************************************/  
/********************************************************************* VL53L0X **********************************************************************/  
/****************************************************************************************************************************************************/  
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
void RGBLCDshield_testing() 
{
    RGBLCDshield.setCursor(0, 1);       // set the cursor to column 0, line 1 (note: line 1 is the second row, since counting begins with 0):   
    RGBLCDshield.print(seconds());      // print the number of seconds since reset:    
    RGBLCDshield_buttonPressed = RGBLCDshield.readButtons();
    
    if (RGBLCDshield_buttonPressed) 
    {
        RGBLCDshield.clear();
        RGBLCDshield.setCursor(0,0);
        if (RGBLCDshield_buttonPressed & BUTTON_UP) 
        {
            RGBLCDshield.print("UP ");
            RGBLCDshield.setBacklight(RED);
        }
        if (RGBLCDshield_buttonPressed & BUTTON_DOWN) 
        {
            RGBLCDshield.print("DOWN ");
            RGBLCDshield.setBacklight(YELLOW);
        }
        if (RGBLCDshield_buttonPressed & BUTTON_LEFT) 
        {
            RGBLCDshield.print("LEFT ");
            RGBLCDshield.setBacklight(GREEN);
        }
        if (RGBLCDshield_buttonPressed & BUTTON_RIGHT) 
        {
            RGBLCDshield.print("RIGHT ");
            RGBLCDshield.setBacklight(TEAL);
        }
        if (RGBLCDshield_buttonPressed & BUTTON_SELECT) 
        {
            RGBLCDshield.print("SELECT ");
            RGBLCDshield.setBacklight(VIOLET);
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
/****************************************************************************************************************************************************/  
/********************************************************************* VL53L0X **********************************************************************/  
/****************************************************************************************************************************************************/  
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
void Adafruit_VL53L0X_testing()
{   
    Adafruit_VL53L0X_sensor.rangingTest(&Adafruit_VL53L0X_measure, TEST_ADAFRUIT_VL53L0X);             // pass in 'true' to get debug data printout! 
    if(SERIAL_PRINTING)
    {
        Serial.print("Reading a measurement... ");
        if (Adafruit_VL53L0X_measure.RangeStatus != 4)                       // phase failures have incorrect data        
        {
            Serial.print("Distance (mm): "); 
            Serial.println(Adafruit_VL53L0X_measure.RangeMilliMeter);
        }
        else 
            Serial.println(" out of range ");
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
/****************************************************************************************************************************************************/  
/******************************************************************* Test Routine *******************************************************************/  
/****************************************************************************************************************************************************/  
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
void testing_routines()
{   
    if(TEST_MODE) 
    {
        if(TEST_RGBLCD_SHIELD)
        {
            RGBLCDshield_testing();
        }
        if(TEST_ADAFRUIT_VL53L0X)
        {
            Adafruit_VL53L0X_testing();
        }
    }
}

