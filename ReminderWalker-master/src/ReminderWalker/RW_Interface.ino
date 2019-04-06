// RGB LCD Shield Interfacing/IO
//uint8_t       RGBLCDshield_menuLevels[2][3]   =
//                                                {
//                                                    {1,2,3},
//                                                    {2,3,4}
//                                                };
uint8_t         RGBLCDshield_menuLevels[][6]   =
                                                {
                                                    {3},
                                                    {2,3,4},{2,3,4},
                                                    {1,2},
                                                    {2,3,4,5,6,7}
                                                };
uint8_t         RGBLCDshield_menuLevelsB[][3][6]   =
                                                {
                                                    {{3}},
                                                    {{2,3,4},{2,3,4}},
                                                    {{1,2},
                                                    {2,3,4,5,6,7}}
                                                };
int8_t         RGBLCDshield_menuLevelsC[][4][3][7]   =
                                                {
                                                    {3},
                                                    {
                                                        {3}, 
                                                        {
                                                            {-1}, 
                                                            {1,3}
                                                        },
                                                        {
                                                            {-2},
                                                            {3,2,3,4},
                                                            {3, 2,3,4}
                                                        },
                                                        {
                                                            {-2},
                                                            {2, 1,2},
                                                            {6, 2,3,4,5,6,7}
                                                        }
                                                    },
                                                    {
                                                        {3}, 
                                                        {
                                                            {-1}, 
                                                            {1,3}
                                                        },
                                                        {
                                                            {-2},
                                                            {3,2,3,4},
                                                            {3, 2,3,4}
                                                        },
                                                        {
                                                            {-2},
                                                            {2, 1,2},
                                                            {6, 2,3,4,5,6,7}
                                                        }
                                                    },
                                                    {
                                                        {3}, 
                                                        {
                                                            {-1}, 
                                                            {1,3}
                                                        },
                                                        {
                                                            {-2},
                                                            {3,2,3,4},
                                                            {3, 2,3,4}
                                                        },
                                                        {
                                                            {-2},
                                                            {2, 1,2},
                                                            {6, 2,3,4,5,6,7}
                                                        }
                                                    }
                                                };
uint8_t         RGBLCDshield_menuPath[]         = {0, 0, 0, 0};
uint8_t         RGBLCDshield_menuLevel          = 0;
uint8_t         RGBLCDshield_menuParent         = 0;
uint8_t         RGBLCDshield_menuPosition       = 0;
uint8_t         RGBLCDshield_menuPositions      = RGBLCDshield_menuLevels[RGBLCDshield_menuLevel][RGBLCDshield_menuParent];
uint8_t         RGBLCDshield_submenuPositions   = RGBLCDshield_menuLevels[RGBLCDshield_menuLevel + 1][RGBLCDshield_menuPosition];
uint8_t         RGBLCDshield_buttonPressed;
String          RGBLCDshield_string;
String          RGBLCDshield_menuState;
String          RGBLCDshield_menuSelection;
String          RGBLCDshield_menuCategory;
String          RGBLCDshield_menuOption;
String          RGBLCDshield_menuOptions[]      = {"Mode Selection", "B", "C"};

//---------------------------------------------------------------------------------------------------------------------------------------------------/  
/****************************************************************************************************************************************************/  
/************************************************************* RGB LCD Shield Functions *************************************************************/  
/****************************************************************************************************************************************************/  
//---------------------------------------------------------------------------------------------------------------------------------------------------/  
void setup_RGBLCDshield() 
{
    RGBLCDshield.begin(RGBLCD_COLUMNS, RGBLCD_ROWS);                         // set up the LCD's number of columns and rows
    
    // Print a message to the LCD. We track how long it takes since this library has been optimized a bit and we're proud of it :)
    int time = millis();
    RGBLCDshield.print("Hello, world!");
    time = millis() - time;
    Serial.print("Took "); Serial.print(time); Serial.println(" ms");
    RGBLCDshield.setBacklight(RGBLCD_DEFAULT_BACKLIGHT);
}
uint8_t LCDshield_num_sublevels(uint8_t path[4], uint8_t new_level) 
{
    uint8_t num_sublevels = RGBLCDshield_menuLevelsC[path[0]][path[1]][path[2]][path[3]];
    return num_sublevels;
    //return RGBLCDshield_menuLevelsC[path[0]][path[1]][path[2]][path[3]];
}
void process_LCDshield_IO() 
{
//uint8_t         RGBLCDshield_buttonPressed;
//uint8_t         RGBLCDshield_menuLevel          = 0;
//uint8_t         RGBLCDshield_menuPosition       = 0;
//uint8_t         RGBLCDshield_menuPositions      = RGBLCDshield_menuLevels[RGBLCDshield_menuLevel][RGBLCDshield_menuParent];
//uint8_t         RGBLCDshield_submenuPositions      = RGBLCDshield_menuLevels[RGBLCDshield_menuLevel][RGBLCDshield_menuParent];
//String          RGBLCDshield_string;
//String          RGBLCDshield_menuState;
//String          RGBLCDshield_menuSelection;
//String          RGBLCDshield_menuCategory;
//String          RGBLCDshield_menuOption;
//String          RGBLCDshield_menuOptions[]      = {"Mode Selection", "B", "C"};
//int             RGBLCDshield_menuLevels[][6]   =
//{
//    {3},
//    {2,3,4},
//    {1,2},
//    {2,3,4,5,6,7}
//};
//uint8_t         RGBLCDshield_menuPath[]         = {0, 0, 0, 0};
    RGBLCDshield.setCursor(0, 1);       // set the cursor to column 0, line 1 (note: line 1 is the second row, since counting begins with 0):   
    RGBLCDshield.print(seconds());      // print the number of seconds since reset:    
    RGBLCDshield_buttonPressed = RGBLCDshield.readButtons();
    
    if (RGBLCDshield_buttonPressed) 
    {
        RGBLCDshield.clear();
        RGBLCDshield.setCursor(0,0);
        if (RGBLCDshield_buttonPressed & BUTTON_UP) 
        {
            if(RGBLCDshield_menuPosition > 0)
            {
                RGBLCDshield_menuPosition--;
                RGBLCDshield_submenuPositions   = RGBLCDshield_menuLevels[RGBLCDshield_menuLevel][RGBLCDshield_menuPosition];
            }
            RGBLCDshield.print("UP ");
            RGBLCDshield.setBacklight(RED);
        }
        if (RGBLCDshield_buttonPressed & BUTTON_DOWN) 
        {
            if(RGBLCDshield_menuPosition < RGBLCDshield_menuPositions)
            {
                RGBLCDshield_menuPosition++;
                RGBLCDshield_submenuPositions   = RGBLCDshield_menuLevels[RGBLCDshield_menuLevel][RGBLCDshield_menuPosition];
            }
            RGBLCDshield.print("DOWN ");
            RGBLCDshield.setBacklight(YELLOW);
        }
        if (RGBLCDshield_buttonPressed & BUTTON_LEFT) 
        {
            if( RGBLCDshield_menuLevel > 0 )
            {
                RGBLCDshield_menuLevel--;
                RGBLCDshield_menuParent         = RGBLCDshield_menuPath[RGBLCDshield_menuLevel];
                RGBLCDshield_menuPosition       = RGBLCDshield_menuParent;
                RGBLCDshield_submenuPositions   = RGBLCDshield_menuPositions;
                RGBLCDshield_menuPositions      = RGBLCDshield_menuLevels[RGBLCDshield_menuLevel][RGBLCDshield_menuPosition];
            }
            RGBLCDshield.print("LEFT ");
            RGBLCDshield.setBacklight(GREEN);
        }
        if (RGBLCDshield_buttonPressed & BUTTON_RIGHT) 
        {//RGBLCDshield_menuPositions      = RGBLCDshield_menuLevels[RGBLCDshield_menuLevel][RGBLCDshield_menuPosition];
            if( RGBLCDshield_submenuPositions > 0 )
            {
                RGBLCDshield_menuPath[RGBLCDshield_menuLevel] = RGBLCDshield_menuPosition;
                RGBLCDshield_menuLevel++;
                RGBLCDshield_menuParent = RGBLCDshield_menuPosition;
                RGBLCDshield_menuPosition = 0;
                RGBLCDshield_submenuPositions   = RGBLCDshield_menuLevels[RGBLCDshield_menuLevel][RGBLCDshield_menuPosition];
                RGBLCDshield_menuPositions      = RGBLCDshield_submenuPositions;
            }
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
