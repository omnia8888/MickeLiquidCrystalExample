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

#define MAX_TEXT_LENGHT 25
#define MAX_NUM_OF_ROWS 16

class MickeLiquidCrystal : private LiquidCrystal
{
public:
	MickeLiquidCrystal(uint8_t rs, uint8_t enable,
		uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);

	void initLCDdisplay(uint8_t columns, uint8_t rows, int scrollSpeed=300);

	void printHej();

	void printDirect(int rowNo, String text);

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
	
	rowDataValues _rowData[MAX_NUM_OF_ROWS];



};




