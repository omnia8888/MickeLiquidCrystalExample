// 
// 
// 

#include "MickeLiquidCrystal.h"


MickeLiquidCrystal::MickeLiquidCrystal(uint8_t rs_Pin, uint8_t enable_Pin,
	uint8_t d0_Pin, uint8_t d1_Pin, uint8_t d2_Pin, uint8_t d3_Pin)
	:LiquidCrystal(rs_Pin, enable_Pin, d0_Pin, d1_Pin, d2_Pin, d3_Pin)
{

}

void MickeLiquidCrystal::initLCDdisplay(uint8_t numOfCols, uint8_t numOfRows, int scrollSpeed)
{
	_numOfColumns = numOfCols;
	_numOfRows = numOfRows;
	_scrollSpeed = scrollSpeed;
	begin(numOfCols, numOfRows);
}

//Prints out a single line of text directly on display
void MickeLiquidCrystal::printDirect(String text, uint8_t row, bool clearAllRows, bool scrollText)
{
	//Check if all rows is to be cleared or only the row thats being printed
	//if (clearAllRows) 
	//{
	//	//Clearing the display
	//	clear();
	//}

	String textToDisplay = text;
	//Get first 16 chars from text
	uint8_t textLenght = text.length();


	//check if text is longer than the display can fit at one time and 
	//if its going to be scrolled
	if (textLenght > _numOfColumns && scrollText)
	{
		//Text is long and scroll text option is true
		//Print first part of Text starting from left.
		
		

		setCursor(0, row);
		print("Scroll!");

	}
	else
	{
		//Check if text is shorter then display length and
		// if it`s too short add blanks to remove old stuff that could remain.
		for (uint8_t i = textLenght; i < _numOfColumns; i++)
		{
			textToDisplay += " ";
		}
		//Print first part of Text starting from left.
		setCursor(0, row);
		print(textToDisplay);
	}




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