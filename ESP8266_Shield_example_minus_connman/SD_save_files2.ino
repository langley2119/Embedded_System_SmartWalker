#include "definitions.h"


const uint8_t BUFFER_SIZE = 20;
char fileName[15] = "19Week00.txt"; // SD library only supports up to 8.3 names
char buff[BUFFER_SIZE+2] = "";  // Added two to allow a 2 char peek for EOF state
uint8_t index = 0;


enum states: uint8_t { NORMAL, E, EO };
uint8_t state = NORMAL;

bool alreadyBegan = false;  // SD.begin() misbehaves if not first call

String currentMonth;
String currentDay;
String currentYear;
String currentCentury;

int month;
int day; 
int year;
int century;

  String monthName;
  String dayName;
  String firstDay;

  char curMon[str_len];
  char curDay[str_len];
  char curYear[str_len];
  char curCent[str_len];

  int dayOfWeek;
  int firstOfYear;
  int leapYear;
  int addyear;
  int firstYear;
  int addmonth;
  int dayOfYear;
  int weekNumber;

  int previousWeek;
  int currentWeek;
  int previousDay = 10; // this is not a real day (1-6). Guarantees that 

void SetupRTCandSD()
{

  //Wire.begin();
  
  //Serial.begin(57600); // hopefully this doesn't wreak havok. 


  if (rtc.begin() == false) 
  {
    Serial.println("Something went wrong with the RTC, check wiring");
  }
  //String currentDate = rtc.stringDateUSA(); //Get the current date in mm/dd/yyyy format (we're weird)
  //String currentTime = rtc.stringTime(); //Get the time
  //calculateDayOfYear(month,day,year,century);
  //calculateWeekday(dayOfWeek,firstOfYear);
  
  DEBUG.println("RTC online!");
  while (!Serial);  // Wait for serial port to connect (ATmega32U4 type PCBAs)

  // Note: To satisfy the AVR SPI gods the SD library takes care of setting
  // SS_PIN as an output. We don't need to.
  //pinMode(chipSelect, OUTPUT); 
  pinMode(cardDetect, INPUT);

  initializeCard();
}

/* Not necessary as acting as a supporting fle 

void loop() 
{
  if (rtc.updateTime() == false) //Updates the time variables from RTC
  {
    Serial.print("RTC failed to update");
  }

//  String currentDate = rtc.stringDateUSA(); //Get the current date in mm/dd/yyyy format (we're weird)
//  String currentTime = rtc.stringTime(); //Get the time
//  Serial.print(currentDate);
//  Serial.print(" ");
//  Serial.println(currentTime);
//  calculateWeekday;
  
  if (!digitalRead(cardDetect))
  {
    initializeCard();
  }

  if (Serial.available() > 0)
  {
    readByte();
//    printDateAndTime();    
  }

//  delay(1000);
}

*/

int initializeCard(void)
{
  static int tries = 1; 
  Serial.print(F("Initializing SD card..."));
  //CARD_OK = 0; 
  // Is there even a card?
  if (!digitalRead(cardDetect))
  {
    Serial.println(F("No card detected. Waiting for card."));
    if(!digitalRead(cardDetect) && tries <= 10)
    {
      CARD_OK = 0; 
      tries++; 
    }
    else if(tries <= 10) 
    { // this means that a card was read since this condition has not been satisfied
      tries = 1; 
      CARD_OK = 1; 
    }
    else {
      // proceed with no card by setting global CARD_OK to 0, aka it's not ok use; 
      CARD_OK = 0; 
    }
    delay(250); // 'Debounce insertion'
  }

  // Card seems to exist.  begin() returns failure
  // even if it worked if it's not the first call.
  if (!SD.begin(chipSelect) && !alreadyBegan)  // begin uses half-speed...
  {
    Serial.println(F("Initialization failed!"));
    if(tries <= 10){
      initializeCard(); // Possible infinite retry loop is as valid as anything
      tries++; 
      return -1; 
    }
    else {
      Serial.println(F("Giving up on using SD")); 
      CARD_OK = 0; 
      return -1; 
    }
  }
  else
  {
    alreadyBegan = true;
    tries = 1; // success! reset tries
    CARD_OK = 1; 
  }
  Serial.println(F("Initialization done."));
    
  Serial.print(fileName);
  if (SD.exists(fileName))
  {
    Serial.println(F(" exists."));
  }
  else
  {
    Serial.println(F(" doesn't exist. Creating."));
  }

  Serial.print("Opening file: ");
  Serial.println(fileName);

  Serial.println(F("Enter text to be written to file. 'EOF' will terminate writing."));

  return 0; 
}

void eof(void)
{
  printDateAndTime();

  // Re-open the file for reading:
  fd = SD.open(fileName);
  if (fd)
  {
    Serial.println("");
    Serial.print(fileName);
    Serial.println(":");

    while (fd.available())
    {
      Serial.write(fd.read());
    }
  }
  else
  {
    Serial.print("Error opening ");
    Serial.println(fileName);
  }
  fd.close();
}

void printDateAndTime(void)
{
  if(CARD_OK == 1)
  {
  String currentDate = rtc.stringDateUSA(); //Get the current date in mm/dd/yyyy format (we're weird)
  //String currentDate = rtc.stringDate()); //Get the current date in dd/mm/yyyy format
  String currentTime = rtc.stringTime(); //Get the time
  //currentDate.toCharArray(curDate,str_len);

  previousDay = day;
  
  currentMonth = currentDate.substring(0,2);
  currentDay = currentDate.substring(3,5);
  currentCentury = currentDate.substring(6,8);
  currentYear = currentDate.substring(8,10);
  
  currentMonth.toCharArray(curMon,str_len);
  currentDay.toCharArray(curDay,str_len);
  currentYear.toCharArray(curYear,str_len);
  currentCentury.toCharArray(curCent,str_len);

  month = atoi(curMon);
  day = atoi(curDay);
  year = atoi(curYear);
  century = atoi(curCent);

//  Use these to test random dates for debugging
//  month = 04;
//  day = 27;
//  century = 20;
//  year = 19;

  calculateDayOfYear(month,day,year,century);
  
  calculateWeekday(dayOfWeek,firstOfYear);

  previousWeek = currentWeek;
  currentWeek = weekNumber;
  if(currentWeek != previousWeek)
  {
    sprintf(fileName, "%dweek%d.txt", year, weekNumber);
  }

  // DEBUG Step 
  DEBUG.println("printing to "); DEBUG.println(fileName); 
  
  fd = SD.open(fileName, FILE_WRITE);
  if (fd) 
  {
    if(previousDay != day)
    {
      fd.print(dayName);
      fd.println(":");
    }
    fd.print(F("  The chair was used on "));
    fd.print(currentDate);
    fd.print(F(" at "));
    fd.println(currentTime);
    fd.println();
    fd.flush();
    index = 0;
    fd.close();
  }

  }
  else{
    DEBUG.println("Card not detected, skipping PrintDateAndTime call."); 
  }
}

void readByte(void)
{
  byte byteRead = Serial.read();
  Serial.write(byteRead); // Echo
  buff[index++] = byteRead;

  // Must be 'EOF' to not get confused with words such as 'takeoff' or 'writeoff'
  if (byteRead == 'E' && state == NORMAL)
  {
    state = E;
  }
  else if (byteRead == 'O' && state == E)
  {
    state = EO;
  }
  else if (byteRead == 'F' && state == EO)
  {
    eof();
    state = NORMAL;
  }
}

void calculateDate(String currentDate, String currentTime)
{
  //String currentDate = rtc.stringDateUSA(); //Get the current date in mm/dd/yyyy format (we're weird)
  //String currentDate = rtc.stringDate()); //Get the current date in dd/mm/yyyy format
  //String currentTime = rtc.stringTime(); //Get the time
  
}

void calculateDayOfYear(int month,int day, int year, int century)
{
   if(month > 2)
  {
    addmonth = month - 2;
    addyear = year;
  }
  else
  {
    addmonth = month + 10;
    addyear = year - 1;
  }

  firstYear = year - 1;
  leapYear = year % 4;

  firstOfYear = (1 + ((13 * 11 - 1) / 5) + firstYear + (firstYear / 4) + (century / 4) - 2 * century) % 7;
  dayOfWeek = (day + ((13 * addmonth - 1) / 5) + addyear + (addyear / 4) + (century / 4) - 2 * century) % 7;
  

  switch(month)
  {
    case 1:
    {
      monthName = "January";
      dayOfYear = day;
      break;
    }
    case 2:
    {
      monthName = "February";
      dayOfYear = 31 + day;
      break;
    }
    case 3:
    {
      monthName = "March";
      dayOfYear = 59 + day;
      break;
    }
    case 4:
    {
      monthName = "April";
      dayOfYear = 90 + day;
      break;
    }
    case 5:
    {
      monthName = "May";
      dayOfYear = 120 + day;
      break;
    }
    case 6:
    {
      monthName = "June";
      dayOfYear = 151 + day;
      break;
    }
    case 7:
    {
      monthName = "July";
      dayOfYear = 181 + day;
      break;
    }
    case 8:
    {
      monthName = "August";
      dayOfYear = 212 + day;
      break;
    }
    case 9:
    {
      monthName = "September";
      dayOfYear = 243 + day;
      break;
    }
    case 10:
    {
      monthName = "October";
      dayOfYear = 273 + day;
      break;
    }
    case 11:
    {
      monthName = "November";
      dayOfYear = 304 + day;
      break;
    }
    case 12:
    {
      monthName = "December";
      dayOfYear = 334 + day;
      break;
    }
    default:
    {
      monthName = "Something";
      dayOfYear = 366;
      break;
    }
  }

  if(leapYear == 0)
  {
    dayOfYear += 1;
  }
}

void calculateWeekday(int dayOfWeek, int firstOfYear)
{
  weekNumber = (dayOfYear / 7) + 1;

  switch(dayOfWeek)
  {
    case 0:
    {
      dayName = "Sunday";
      break;
    }
    case 1:
    {
      dayName = "Monday";
      break;
    }
    case 2:
    {
      dayName = "Tuesday";
      break;
    }
    case 3:
    {
      dayName = "Wednesday";
      break;
    }
    case 4:
    {
      dayName = "Thursday";
      break;
    }
    case 5:
    {
      dayName = "Friday";
      break;
    }
    case 6:
    {
      dayName = "Saturday";
      break;
    }
  }

  

  switch(firstOfYear)
  {
    case 0:
    {
      firstDay = "Sunday";
      break;
    }
    case 1:
    {
      firstDay = "Monday";
      break;
    }
    case 2:
    {
      firstDay = "Tuesday";
      break;
    }
    case 3:
    {
      firstDay = "Wednesday";
      break;
    }
    case 4:
    {
      firstDay = "Thursday";
      break;
    }
    case 5:
    {
      firstDay = "Friday";
      break;
    }
    case 6:
    {
      firstDay = "Saturday";
      break;
    }
  }
}

void printDateAndTimeVerbose(void)
{
  String currentDate = rtc.stringDateUSA(); //Get the current date in mm/dd/yyyy format (we're weird)
  //String currentDate = rtc.stringDate()); //Get the current date in dd/mm/yyyy format
  String currentTime = rtc.stringTime(); //Get the time
  //currentDate.toCharArray(curDate,str_len);

  previousDay = day;
  
  currentMonth = currentDate.substring(0,2);
  currentDay = currentDate.substring(3,5);
  currentCentury = currentDate.substring(6,8);
  currentYear = currentDate.substring(8,10);
  
  currentMonth.toCharArray(curMon,str_len);
  currentDay.toCharArray(curDay,str_len);
  currentYear.toCharArray(curYear,str_len);
  currentCentury.toCharArray(curCent,str_len);

  month = atoi(curMon);
  day = atoi(curDay);
  year = atoi(curYear);
  century = atoi(curCent);

//  Use these to test random dates for debugging
//  month = 04;
//  day = 27;
//  century = 20;
//  year = 19;

  calculateDayOfYear(month,day,year,century);
  
  calculateWeekday(dayOfWeek,firstOfYear);

  previousWeek = currentWeek;
  currentWeek = weekNumber;
  if(currentWeek != previousWeek)
  {
    sprintf(fileName, "%dweek%d.txt", year, weekNumber);
  }

  
  fd = SD.open(fileName, FILE_WRITE);
  if (fd) 
  {
    if(previousDay != day)
    {
      fd.print(dayName);
      fd.println(":");
    }
    fd.print(F("  The chair was used on "));
    fd.print(currentDate);
    fd.print(F(" at "));
    fd.println(currentTime);
// this is what is added in the verbose
    fd.print(F("Month: "));
    //fd.print(currentMonth);
    //fd.print(month);
    fd.print(monthName);
    fd.print(F("  Day: "));
    //fd.print(currentDay);
    fd.print(day);
    fd.print(F("  Year: "));
    //fd.println(currentYear);
    fd.print(century);
    fd.println(year);
    fd.print(F("The day of week is: "));
    fd.print(dayName);
    fd.print(F(" The first day of the year was a: "));
    //fd.print(firstOfYear);
    fd.print(firstDay);
    if(leapYear == 0)
    {
      fd.println(F(" It is a leap year"));
    }
    else
    {
      fd.println(F(" It is not a leap year"));
    }
    fd.print(F("Day of Year: "));
    fd.print(dayOfYear);
    fd.print(F(" Week of Year: "));
    fd.println(weekNumber);
    fd.println();
    fd.flush();
    index = 0;
    fd.close();
  }
}
