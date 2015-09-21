// MickeLiquidCrystal.h

#ifndef _MICKELIQUIDCRYSTAL_h
#define _MICKELIQUIDCRYSTAL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

#include "LiquidCrystal.h"

const uint8_t displayRowMax = 2; //Maxumum of rows that can be handled by display library
const uint8_t printDirectMaxLenght = 25; //Defines the maximum amount of display rows the library can handel

#define MAX_PRINT_DIRECT_CHARS 25 //Maxum of displayed chars scrolled of total text

class MickeLiquidCrystal : private LiquidCrystal

{
public:
	//MickeLiquidCrystal dispaycontrol object.
	MickeLiquidCrystal(uint8_t rs_Pin, uint8_t enable_Pin,
		uint8_t d0_Pin, uint8_t d1_Pin, uint8_t d2_Pin, uint8_t d3_Pin);

	void initLCDdisplay(uint8_t numOfCols, uint8_t numOfRows, int scrollSpeed =300);

	void printHej();

	void printDirect(String text, uint8_t rowNo = 0, bool clearAllRows=true, bool scrollText=true);

	void rowText(uint8_t rowNo, String rowText);
	void rowText(uint8_t rowNo, String rowText, bool scroll,bool continueScroll=true);
	

	void UpdateDisplay();

private:
	
	int _scrollSpeed;
	long _updateTimer = 0;
	uint8_t _numOfColumns;
	uint8_t _numOfRows;

	struct rowDataValues
	{
		String rowText = "";
		uint8_t textStartPos = 0;
		bool scrollText = false;
		bool continueScrolling = false;
		bool update = false;
	};
	
	rowDataValues _rowData[displayRowMax];



};




