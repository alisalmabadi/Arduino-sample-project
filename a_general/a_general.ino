#include <Wire.h>
#include <LiquidCrystal.h>

// Setting the LCD shields pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// The LCD screen
//LCDKeypad lcd;


#define DAYS 0
#define HOURS 1
#define MINUTES 2
#define SECONDS 3

// The time model

byte dd = 0;
byte hh = 0;
byte mm = 0;
byte ss = 0;

unsigned int settime = 0;

/****/
String menuItems[] = {"Select Modes", "Setting", "Home"};
String modeItems[] = {"Herbs", "Veggies", "24h ON", "24h OFF", "Back"};
String settItems[] = {"Light : ","t : ","Back"};

bool Light = true;
bool Clock = false;
int button  = 0;
bool KeyPress = false;
int activeMenu = 0;

// state = 0 : Home Screen
// state = 1 : Menu
// state = 2 : select modes
// state = 3 : setting
byte state = 0;
byte Mode = 0;
byte pointerLoc[4];
byte pageLoc[4];


// Navigation button variables
int readKey;
int savedDistance = 0;

// Menu control variables
byte MenuItemNum = sizeof(menuItems) / sizeof(String);
byte ModeItemNum = sizeof(modeItems) / sizeof(String);
byte SettItemNum = sizeof(settItems) / sizeof(String);

// Creates 3 custom characters for the menu display
byte downArrow[8] = {
  B00100, //   *
  B00100, //   *
  B00100, //   *
  B00100, //   *
  B00100, //   *
  B10101, // * * *
  B01110, //  ***
  B00100  //   *
};

byte upArrow[8] = {
  B00100, //   *
  B01110, //  ***
  B10101, // * * *
  B00100, //   *
  B00100, //   *
  B00100, //   *
  B00100, //   *
  B00100  //   *
};

byte menuCursor[8] = {
  B01000, //  *
  B00100, //   *
  B00010, //    *
  B00001, //     *
  B00010, //    *
  B00100, //   *
  B01000, //  *
  B00000  //
};
