// 
// 
// 

#include "MickeLiquidCrystal.h"


MickeLiquidCrystal::MickeLiquidCrystal(uint8_t rs, uint8_t enable,
	uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3)
	:LiquidCrystal(rs, enable, d0, d1, d2, d3)
{

}

void MickeLiquidCrystal::initLCDdisplay(uint8_t columns, uint8_t rows, int scrollSpeed)
{
	_numOfColumns = columns;
	_numOfRows = rows;
	_scrollSpeed = scrollSpeed;
	begin(columns, rows);
}

void MickeLiquidCrystal::printDirect(int rowNo, String text)
{
	//Clear Row
	setCursor(0, rowNo);
	print("                ");
	//Print Text
	setCursor(0, rowNo);
	print(text);
}

void MickeLiquidCrystal::rowText(uint8_t rowNo, String rowText)
{
	_rowData[rowNo].rowText = rowText;
	_rowData[rowNo].update = true;
	
}

void MickeLiquidCrystal::rowText(uint8_t rowNo, String rowText, bool scroll, bool continueScroll)
{
	_rowData[rowNo].rowText = rowText;
	_rowData[rowNo].update = true;
	
}

void MickeLiquidCrystal::UpdateDisplay()
{
	//String sDebug = "UpdateTimer: ";
	//sDebug += _updateTimer; // + "currMillis:" + millis();
	//Serial.println(sDebug);
	//
	//sDebug = "Current millis: ";
	//sDebug += millis(); // + "currMillis:" + millis();
	//Serial.println(sDebug);

	//sDebug = "Scroll Speed: ";
	//sDebug += _scrollSpeed; // + "currMillis:" + millis();
	//Serial.println(sDebug);
	//Serial.println();
	//delay(300);

	//Check update timer
	if (_updateTimer > millis() && _updateTimer > 0)
	{
		//Time is not reached, do nothing
		//Serial.println("Time not reached");
		return;
	}

	//Loop throu all rows on display
	for (uint8_t rowNo = 0; rowNo < _numOfRows; rowNo++)
	{
		//Serial.println("Looping rows");
		//Check if row update status or if no text is found
		if (_rowData[rowNo].update == false)
		{
			//No update needed move to next row
			continue;
		}

		setCursor(0, rowNo);
		uint8_t textLen = _rowData[rowNo].rowText.length();
		//Check if text is to long for display
		if (textLen > _numOfColumns)
		{
			//Scroll the long text
			uint8_t currStartPos;
			uint8_t currEndPos;

			//for (uint8_t i = 0; i < currTextLen - (_numOfColumns -1); i++)
			//{
			//Set the start position of the text string to be displayed
			currStartPos = _rowData[rowNo].textStartPos;
			
			//Serial.println(currStartPos);
			//delay(500);
			
			//Set the end position of the text string so it not is larger then display
			if ((textLen - currStartPos) > _numOfColumns)
			{
				currEndPos = currStartPos + (_numOfColumns - 1);
			}
			else
			{
				currEndPos = textLen;

			}
			setCursor(0, rowNo);
			print(_rowData[rowNo].rowText.substring(currStartPos, currEndPos));

			//Scroll text left
			if (currStartPos + _numOfColumns > textLen - 1)
			{
				//All text is displayed
				_rowData[rowNo].update = false;
			}
			else
			{
				_rowData[rowNo].textStartPos = currStartPos + 1;
			}

		}
		else
		{
			//Its a short text set cursor to begining
			setCursor(0, rowNo);
			print(_rowData[rowNo].rowText);

		}
	}
	//Set new value for update timer
	_updateTimer = millis() + _scrollSpeed;
}


void MickeLiquidCrystal::printHej()
{
	print(_rowData[0].rowText);
}