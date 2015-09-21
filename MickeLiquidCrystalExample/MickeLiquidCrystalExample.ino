/*
 Name:		MickeLiquidCrystalExample.ino
 Created:	9/21/2015 11:21:49 AM
 Author:	Micke
*/

#include "MickeLiquidCrystal.h"

//LCD Pin Config from default Lawicel connection scheme not from Aurdoino example
const uint8_t pin_Rs = 7;
const uint8_t pin_Enable = 8;
const uint8_t pin_d0 = 9;
const uint8_t pin_d1 = 10;
const uint8_t pin_d2 = 11;
const uint8_t pin_d3 = 12;

//Display config info for current display
const uint8_t displayColumns = 16;
const uint8_t displayRows = 2;
const uint8_t displayScrollSpeed = 300;

MickeLiquidCrystal mLCD(pin_Rs, pin_Enable, pin_d0, pin_d1, pin_d2, pin_d3);

// the setup function runs once when you press reset or power the board
void setup() {
	mLCD.initLCDdisplay(displayColumns, displayRows,displayScrollSpeed);
	
	mLCD.printDirect("Hejsan Hejsan Hejsan Hejsan");
	mLCD.printDirect("Micke",1);

}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
