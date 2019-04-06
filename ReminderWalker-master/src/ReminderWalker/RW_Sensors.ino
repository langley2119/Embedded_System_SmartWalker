#define     RFD77402_INBUFFERSIZE       20  
#define     RFD77402_MIDBUFFERSIZE      30  
#define     RFD77402_OUTBUFFERSIZE      20  
#define     RFD77402_MIDBUFFER_OLAP     10  
#define     RFD77402_OUTBUFFER_OLAP     10  
//                                              20            +          30            +           20           -            10           -         10                  =       50
#define     RFD77402_BUFFERSIZE         RFD77402_INBUFFERSIZE + RFD77402_MIDBUFFERSIZE + RFD77402_OUTBUFFERSIZE - RFD77402_MIDBUFFER_OLAP - RFD77402_OUTBUFFER_OLAP   
#define     RFD77402_BUFFERSIZE_SQD     pow(RFD77402_BUFFERSIZE,2)

int8_t      RFD77402_P1in       = 0;
int8_t      RFD77402_P1out      = RFD77402_P1in + RFD77402_INBUFFERSIZE - 1;                                             // 0 + 20       = 20 - 1 = 19
int8_t      RFD77402_P2in       = RFD77402_P1in + RFD77402_INBUFFERSIZE - RFD77402_MIDBUFFER_OLAP;                       // 0 + 20 - 10  = 10
int8_t      RFD77402_P2out      = RFD77402_P2in + RFD77402_MIDBUFFERSIZE - 1;                                            // 10 + 30 - 1  = 40 - 1 = 39
int8_t      RFD77402_P3in       = RFD77402_BUFFERSIZE - RFD77402_OUTBUFFERSIZE;                                          // 50 - 20      = 30
int8_t      RFD77402_P3out      = RFD77402_P3in + RFD77402_OUTBUFFERSIZE - 1;                                            // 30 + 20 - 1  = 50 - 1 = 49
int8_t      RFD77402_p_LUT      [RFD77402_BUFFERSIZE];
//***********************************************
unsigned int RFD77402_buffer     [RFD77402_BUFFERSIZE];
unsigned int       RFD77402_s1         = 0;
unsigned int       RFD77402_s2         = 0;
unsigned int       RFD77402_s3         = 0;
//***********************************************
//float       RFD77402_s1         = 0;
//float       RFD77402_s2         = 0;
//float       RFD77402_s3         = 0;
//***********************************************
float       RFD77402_a1         = 0;
float       RFD77402_a2         = 0;
float       RFD77402_a3         = 0;
float       RFD77402_varsum     = 0;
float       RFD77402_var        = 0;

#define     VL53L0X_BUFFERSIZE      10  
#define     VL53L0X_INBUFFERSIZE       20  
#define     VL53L0X_MIDBUFFERSIZE      30  
#define     VL53L0X_OUTBUFFERSIZE      20  
#define     VL53L0X_MIDBUFFER_OLAP     10  
#define     VL53L0X_OUTBUFFER_OLAP     10  
//                                              20            +          30            +           20           -            10           -         10                  =       50
#define     VL53L0X_BUFFERSIZE         VL53L0X_INBUFFERSIZE + VL53L0X_MIDBUFFERSIZE + VL53L0X_OUTBUFFERSIZE - VL53L0X_MIDBUFFER_OLAP - VL53L0X_OUTBUFFER_OLAP   
#define     VL53L0X_BUFFERSIZE_SQD     pow(VL53L0X_BUFFERSIZE,2)

int8_t      VL53L0X_P1in       = 0;
int8_t      VL53L0X_P1out      = VL53L0X_P1in + VL53L0X_INBUFFERSIZE - 1;                                             // 0 + 20       = 20 - 1 = 19
int8_t      VL53L0X_P2in       = VL53L0X_P1in + VL53L0X_INBUFFERSIZE - VL53L0X_MIDBUFFER_OLAP;                       // 0 + 20 - 10  = 10
int8_t      VL53L0X_P2out      = VL53L0X_P2in + VL53L0X_MIDBUFFERSIZE - 1;                                            // 10 + 30 - 1  = 40 - 1 = 39
int8_t      VL53L0X_P3in       = VL53L0X_BUFFERSIZE - VL53L0X_OUTBUFFERSIZE;                                          // 50 - 20      = 30
int8_t      VL53L0X_P3out      = VL53L0X_P3in + VL53L0X_OUTBUFFERSIZE - 1;                                            // 30 + 20 - 1  = 50 - 1 = 49
int8_t      VL53L0X_p_LUT      [VL53L0X_BUFFERSIZE];
//***********************************************
uint16_t    VL53L0X_buffer     [VL53L0X_BUFFERSIZE];
uint16_t       VL53L0X_s1         = 0;
uint16_t       VL53L0X_s2         = 0;
uint16_t       VL53L0X_s3         = 0;
//***********************************************
//float       VL53L0X_s1         = 0;
//float       VL53L0X_s2         = 0;
//float       VL53L0X_s3         = 0;
//***********************************************
float       VL53L0X_a1         = 0;
float       VL53L0X_a2         = 0;
float       VL53L0X_a3         = 0;
float       VL53L0X_varsum     = 0;
float       VL53L0X_var        = 0;

#define     RFD77402_DIST_DIFF_THRESH       200  
#define     VL53L0X_DIST_DIFF_THRESH        200     
float       out_data;
//float     var_diffsum                     = 0;
//float     var_diffsum_factor              = 0;
float       varsum                          = 0;
float       var_diffsum_factor              = 0;

//---------------------------------------------------------------------------------------------------------------------------------------------------/  
/****************************************************************************************************************************************************/  
/********************************************************************** OpenPIR *********************************************************************/  
/****************************************************************************************************************************************************/  
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
void setup_OpenPIR()
{
    pinMode(PIR_AOUT_PIN, INPUT);
    pinMode(PIR_DOUT_PIN, INPUT);
    pinMode(PIR_LED_PIN, OUTPUT);               // Configure the motion indicator LED pin as an output
    digitalWrite(PIR_LED_PIN, LOW);             // Turn the LED off
}
void acquire_OpenPIR_data()
{
    PIR_motionStatus    = digitalRead(PIR_DOUT_PIN);                                // The OpenPIR's digital output is active high    
    if (PIR_motionStatus == HIGH)                                                   // If motion is detected, turn the onboard LED on:
    {
        last_motion = 0;
        //sleep = false;
        PIR_analogOutput    = analogRead(PIR_AOUT_PIN);                             // Read in analog value    
        PIR_voltage         = (float) PIR_analogOutput / PIR_AOUT_MAX * PIR_VMAX;   // Convert 10-bit analog value to a voltage, high = 5.0V          
        digitalWrite(PIR_LED_PIN, HIGH);
    }
    else// Otherwise turn the LED off:
    {
        last_motion++;
        digitalWrite(PIR_LED_PIN, LOW);   
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
/****************************************************************************************************************************************************/  
/********************************************************************* VL53L0X **********************************************************************/  
/****************************************************************************************************************************************************/  
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
void setup_VL53L0X()
{
    //    pinMode(VL53L0X_SCL_PIN, INPUT);
    //    pinMode(VL53L0X_SDA_PIN, INPUT);
    Serial.println("Initializing Adafruit VL53L0X");
    if (!Adafruit_VL53L0X_sensor.begin()) 
    {
        Serial.println(F("Failed to initialize VL53L0X"));
        while(1);
    }
    // power 
    Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
       
//    // Start continuous back-to-back mode (take readings as fast as possible).  To use continuous timed mode
//    // instead, provide a desired inter-measurement period in ms (e.g. sensor.startContinuous(100)).
//    VL53L0X_sensor.init();
//    VL53L0X_sensor.setTimeout(VL53L0X_TIMEOUT);
//    VL53L0X_sensor.startContinuous();
    
    // Fill data FIFO pointer lookup table
    VL53L0X_p_LUT[0] = VL53L0X_BUFFERSIZE - 1;
    for( int i = 1; i < VL53L0X_BUFFERSIZE; i++)
        VL53L0X_p_LUT[i] = i - 1;
}
void acquire_VL53L0X_data()
{
    //VL53L0X_range = VL53L0X_sensor.readRangeContinuousMillimeters();
    //VL53L0X_buff[VL53L0X_BUFFSIZE];  
    Adafruit_VL53L0X_sensor.rangingTest(&Adafruit_VL53L0X_measure, TEST_ADAFRUIT_VL53L0X);             // pass in 'true' to get debug data printout! 
    if (Adafruit_VL53L0X_measure.RangeStatus != 4)                       // phase failures have incorrect data        
        VL53L0X_range = Adafruit_VL53L0X_measure.RangeMilliMeter;
    
    VL53L0X_shift_data          (VL53L0X_range);
    VL53L0X_movement_direction  = move_dir(VL53L0X_a1, VL53L0X_a2, VL53L0X_a3);      
    VL53L0X_movement_counter    += VL53L0X_movement_direction;
}
//***********************************************
//void VL53L0X_shift_data(float in_data)  
//***********************************************
void VL53L0X_shift_data(uint16_t in_data)  
//***********************************************
{  
    out_data                        = VL53L0X_buffer[VL53L0X_P3out];
    //if(VL53L0X_a1 - in_data < 3 * VL53L0X_var)
    //if(abs(VL53L0X_a1 - in_data) < VL53L0X_DIST_DIFF_THRESH)
    //{
        VL53L0X_s1                      = VL53L0X_s1 + in_data                      - VL53L0X_buffer[VL53L0X_P1out];
        VL53L0X_s2                      = VL53L0X_s2 + VL53L0X_buffer[VL53L0X_P2in] - VL53L0X_buffer[VL53L0X_P2out];
        VL53L0X_s3                      = VL53L0X_s3 + VL53L0X_buffer[VL53L0X_P3in] - out_data;
        VL53L0X_buffer[VL53L0X_P3out]   = in_data;  
        
        VL53L0X_P1in                = VL53L0X_p_LUT[VL53L0X_P1in];
        VL53L0X_P1out               = VL53L0X_p_LUT[VL53L0X_P1out];
        VL53L0X_P2in                = VL53L0X_p_LUT[VL53L0X_P2in];
        VL53L0X_P2out               = VL53L0X_p_LUT[VL53L0X_P2out];
        VL53L0X_P3in                = VL53L0X_p_LUT[VL53L0X_P3in];
        VL53L0X_P3out               = VL53L0X_p_LUT[VL53L0X_P3out];
        
        //VL53L0X_P1in               = (VL53L0X_P1in    + VL53L0X_BUFFERSIZE - 1) % VL53L0X_BUFFERSIZE;
        //VL53L0X_P1out              = (VL53L0X_P1out   + VL53L0X_BUFFERSIZE - 1) % VL53L0X_BUFFERSIZE;
        //VL53L0X_P2in               = (VL53L0X_P2in    + VL53L0X_BUFFERSIZE - 1) % VL53L0X_BUFFERSIZE;
        //VL53L0X_P2out              = (VL53L0X_P2out   + VL53L0X_BUFFERSIZE - 1) % VL53L0X_BUFFERSIZE;
        //VL53L0X_P3in               = (VL53L0X_P3in    + VL53L0X_BUFFERSIZE - 1) % VL53L0X_BUFFERSIZE;
        //VL53L0X_P3out              = (VL53L0X_P3out   + VL53L0X_BUFFERSIZE - 1) % VL53L0X_BUFFERSIZE;
        //VL53L0X_data_calcs(in_data);
    //}
}
//***********************************************
//void VL53L0X_data_calcs(float in_data)  
//***********************************************
void VL53L0X_data_calcs(uint16_t in_data)  
//***********************************************
{  
    //***********************************************
    VL53L0X_a1                 = static_cast<float>(VL53L0X_s1 / VL53L0X_INBUFFERSIZE);
    VL53L0X_a2                 = static_cast<float>(VL53L0X_s2 / VL53L0X_INBUFFERSIZE);
    VL53L0X_a3                 = static_cast<float>(VL53L0X_s3 / VL53L0X_INBUFFERSIZE);
    //***********************************************
    //VL53L0X_a1                 = VL53L0X_s1 / VL53L0X_INBUFFERSIZE;
    //VL53L0X_a2                 = VL53L0X_s2 / VL53L0X_MIDBUFFERSIZE;
    //VL53L0X_a3                 = VL53L0X_s3 / VL53L0X_OUTBUFFERSIZE;
    //***********************************************
    VL53L0X_varsum             += ( pow(in_data,2) - pow(out_data,2) )/ VL53L0X_BUFFERSIZE;
    VL53L0X_var                = VL53L0X_varsum - pow(VL53L0X_a2,2);
    //VL53L0X_var                = position_var(in_data, out_data, VL53L0X_varsum, float VL53L0X_a2);
    
    //var_diffsum = 0;
    //var_diffsum_factor = (out_data - in_data)/ VL53L0X_BUFFERSIZE_SQD;
    //VL53L0X_var += VL53L0X_BUFFERSIZE * ((pow(in_data,2) - (pow(out_data,2));
    //for(i = 0; i < VL53L0X_BUFFERSIZE; i++)
    //    var_diffsum += VL53L0X_buffer[i] * (out_data - in_data);
    //VL53L0X_var += var_diffsum / VL53L0X_BUFFERSIZE_SQD;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
/****************************************************************************************************************************************************/  
/********************************************************************* RFD77402 *********************************************************************/  
/****************************************************************************************************************************************************/  
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
void setup_RFD77402()
{
    if (RFD77402_sensor.begin(Wire, RFD77402_SPEED) == false)
    {
        Serial.println("RFD77402 failed to initialize. Check wiring.");
        while (1); //Freeze!
    }
    Serial.println("RFD77402 initialized");
    
    // Fill data FIFO pointer lookup table
    RFD77402_p_LUT[0] = RFD77402_BUFFERSIZE - 1;
    for( int i = 1; i < RFD77402_BUFFERSIZE; i++)
        RFD77402_p_LUT[i] = i - 1;

}
void set_RFD77402_state()
{   
    if (sleep)
    {
        //RFD77402_sensor.goToStandbyMode();                        // Low power standby mode
        RFD77402_sensor.goToOffMode();                              // Turn off MCPU
    }
    if (wake_up)
    {
        RFD77402_sensor.goToOnMode();                               // Wake MCPU to ON Mode
        //RFD77402_sensor.getMeasurement();                         // Once sensor is configured, issue to take measurement
    }
}
void acquire_RFD77402_data()
{
    RFD77402_sensor.takeMeasurement();                              //Tell sensor to take measurement
    RFD77402_distance = RFD77402_sensor.getDistance();              //Retrieve the distance value
    //RFD77402_pixels = RFD77402_sensor.getValidPixels();
    //RFD77402_confidence = RFD77402_sensor.getConfidenceValue();
      
    //getPeak/setPeak(byte) - Gets/sets the vertical-cavity surface-emitting laser (VCSEL) peak
    //getThreshold/setThreshold(byte) - Gets/sets the VCSEL threshold
    //getFrequency/setFrequency(byte) - Gets/sets the modulation frequency
    //RFD77402_buff[RFD77402_BUFFSIZE];  

    RFD77402_shift_data(RFD77402_distance);
    RFD77402_movement_direction = move_dir(RFD77402_a1, RFD77402_a2, RFD77402_a3);  
    RFD77402_movement_counter   += RFD77402_movement_direction;
}
//***********************************************
//void RFD77402_shift_data(float in_data)  
//***********************************************
void RFD77402_shift_data(unsigned int in_data)  
//***********************************************
{  
    out_data = RFD77402_buffer[RFD77402_P3out];
    //if(RFD77402_a1 - in_data < 3 * VL53L0X_var)
    //if(abs(RFD77402_a1 - in_data) < RFD77402_DIST_DIFF_THRESH)
    //{
        RFD77402_s1                 = RFD77402_s1 + in_data                         - RFD77402_buffer[RFD77402_P1out];
        RFD77402_s2                 = RFD77402_s2 + RFD77402_buffer[RFD77402_P2in]  - RFD77402_buffer[RFD77402_P2out];
        RFD77402_s3                 = RFD77402_s3 + RFD77402_buffer[RFD77402_P3in]  - out_data;
        RFD77402_buffer[RFD77402_P3out]      = in_data;  
             
        RFD77402_P1in               = RFD77402_p_LUT[RFD77402_P1in];
        RFD77402_P1out              = RFD77402_p_LUT[RFD77402_P1out];
        RFD77402_P2in               = RFD77402_p_LUT[RFD77402_P2in];
        RFD77402_P2out              = RFD77402_p_LUT[RFD77402_P2out];
        RFD77402_P3in               = RFD77402_p_LUT[RFD77402_P3in];
        RFD77402_P3out              = RFD77402_p_LUT[RFD77402_P3out];
        
        //RFD77402_P1in               = (RFD77402_P1in    + RFD77402_BUFFERSIZE - 1) % RFD77402_BUFFERSIZE;
        //RFD77402_P1out              = (RFD77402_P1out   + RFD77402_BUFFERSIZE - 1) % RFD77402_BUFFERSIZE;
        //RFD77402_P2in               = (RFD77402_P2in    + RFD77402_BUFFERSIZE - 1) % RFD77402_BUFFERSIZE;
        //RFD77402_P2out              = (RFD77402_P2out   + RFD77402_BUFFERSIZE - 1) % RFD77402_BUFFERSIZE;
        //RFD77402_P3in               = (RFD77402_P3in    + RFD77402_BUFFERSIZE - 1) % RFD77402_BUFFERSIZE;
        //RFD77402_P3out              = (RFD77402_P3out   + RFD77402_BUFFERSIZE - 1) % RFD77402_BUFFERSIZE;
        //RFD77402_data_calcs(in_data);
    //}
}
//***********************************************
//void RFD77402_data_calcs(float in_data)  
//***********************************************
void RFD77402_data_calcs(unsigned int in_data)  
//***********************************************
{  
    //***********************************************
    RFD77402_a1                 = static_cast<float>(RFD77402_s1 / RFD77402_INBUFFERSIZE);
    RFD77402_a2                 = static_cast<float>(RFD77402_s2 / RFD77402_MIDBUFFERSIZE);
    RFD77402_a3                 = static_cast<float>(RFD77402_s3 / RFD77402_OUTBUFFERSIZE);
    RFD77402_varsum             += static_cast<float>(( pow(in_data,2) - pow(out_data,2) )/ RFD77402_BUFFERSIZE);
    RFD77402_var                = static_cast<float>(RFD77402_varsum - pow(RFD77402_a2,2));
    //***********************************************
    //RFD77402_a1                 = RFD77402_s1 / RFD77402_INBUFFERSIZE;
    //RFD77402_a2                 = RFD77402_s2 / RFD77402_MIDBUFFERSIZE;
    //RFD77402_a3                 = RFD77402_s3 / RFD77402_OUTBUFFERSIZE;
    //RFD77402_varsum             += ( pow(in_data,2) - pow(out_data,2) )/ RFD77402_BUFFERSIZE;
    //RFD77402_var                = RFD77402_varsum - pow(RFD77402_a2,2);
    //***********************************************
    //RFD77402_var                = position_var(in_data, out_data, RFD77402_varsum, float RFD77402_a2);
    
    //var_diffsum = 0;
    //var_diffsum_factor = (out_data - in_data)/ RFD77402_BUFFERSIZE_SQD;
    //RFD77402_var += RFD77402_BUFFERSIZE * ((pow(in_data,2) - (pow(out_data,2));
    //for(i = 0; i < RFD77402_BUFFERSIZE; i++)
    //    var_diffsum += RFD77402_buffer[i] * (out_data - in_data);
    //RFD77402_var += var_diffsum / RFD77402_BUFFERSIZE_SQD;
}
int8_t move_dir(float avgpos1, float avgpos2, float avgpos3)  
{  
    if( avgpos1 > avgpos2 && avgpos2 > avgpos3)
        return RECEDING;
    if( avgpos1 > avgpos2 && avgpos2 > avgpos3)
        return APPROACHING;
    else
        return STATIONARY;
}  
//***********************************************
//float position_var(float new_data, float old_data, float& varsum, float avgpos)  
//***********************************************
float position_var(unsigned int new_data, unsigned int old_data, float& varsum, float avgpos)  
{  
    //***********************************************
    varsum      += static_cast<float>(( pow(new_data,2) - pow(old_data,2) ) / RFD77402_BUFFERSIZE);
    //***********************************************
    //varsum      += ( pow(new_data,2) - pow(old_data,2) ) / RFD77402_BUFFERSIZE;
    //***********************************************
    return      varsum - pow(avgpos,2);
}  
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
/****************************************************************************************************************************************************/  
/********************************************************************** HC-SR04 *********************************************************************/  
/****************************************************************************************************************************************************/  
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
void acquire_HCSR04_data()
{
      HCSR04_hitTime = HCSR04_sensor.getHitTime();                        // In microseconds
      //HC_SR04_buff[HCSR04_BUFFSIZE];    
}
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
/****************************************************************************************************************************************************/  
/***************************************************************** Print Sensor Info ****************************************************************/  
/****************************************************************************************************************************************************/  
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
void print_VL53L0X()
{
    Serial.println("<******** VL53L0X: ********>");
    #ifdef PRINT_BUFF_PTRS
        Serial.println("Ptrs = ");
        Serial.println(VL53L0X_P1in);         
        Serial.println(VL53L0X_P1out);       
        Serial.println(VL53L0X_P2in);       
        Serial.println(VL53L0X_P2out);    
        Serial.println(VL53L0X_P3in);
        Serial.println(VL53L0X_P3out);    
    #endif
    #ifdef PRINT_RAW_DATA
        Serial.print("D = ");
        Serial.print(VL53L0X_range);
        Serial.println("mm");
        if (VL53L0X_sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
    #endif
    #ifdef PRINT_AVG_DATA
        Serial.print("D_avgs = ");
        //printListMem(VL53L0X_a1);         
        //printListMem(VL53L0X_a2);         
        //printListMem(VL53L0X_a3);         
        Serial.print(VL53L0X_a1);         
        Serial.print(", ");
        Serial.print(VL53L0X_a2);         
        Serial.print(", ");
        Serial.println(VL53L0X_a3);         
    #endif    
    #ifdef PRINT_MOVEMENT
        Serial.print("Dir/Cnt :");
        Serial.println(VL53L0X_movement_direction);         
        Serial.print(", ");
        Serial.println(VL53L0X_movement_counter);         
    #endif
}
void print_RFD77402()
{
    Serial.println("<******** RFD77402: ********>");
    #ifdef PRINT_BUFF_PTRS
        Serial.println("Ptrs = ");
        Serial.println(RFD77402_P1in);         
        Serial.println(RFD77402_P1out);       
        Serial.println(RFD77402_P2in);       
        Serial.println(RFD77402_P2out);    
        Serial.println(RFD77402_P3in);
        Serial.println(RFD77402_P3out);    
    #endif
    #ifdef PRINT_RAW_DATA
        Serial.print("D = ");
        Serial.print(RFD77402_distance);
        Serial.println("mm");
    #endif
    #ifdef PRINT_AVG_DATA
        Serial.print("D_avgs = ");
        //printListMem(RFD77402_a1);         
        //printListMem(RFD77402_a2);         
        //printListMem(RFD77402_a3);         
        Serial.print(RFD77402_a1);         
        Serial.print(", ");
        Serial.print(RFD77402_a2);         
        Serial.print(", ");
        Serial.println(RFD77402_a3);         
    #endif    
    #ifdef PRINT_MOVEMENT
        Serial.print("Dir/Cnt :");
        Serial.println(RFD77402_movement_direction);         
        Serial.print(", ");
        Serial.println(RFD77402_movement_counter);         
    #endif
}

