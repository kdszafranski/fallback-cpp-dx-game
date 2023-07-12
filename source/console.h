#pragma once

#include "constants.h"
#include "textDX.h"

class Console
{
private:
	TextDX dxLogFont;
	std::string logText;
	
public:
	// Constructor
	Console();
	// Destructor
	virtual ~Console();
	// set up DX
	void initialize(Graphics* graphics);


	// reset text
	void resetLog();
	// sets the next log output message
	void setLogText(int number);
	void setLogText(const std::string &message);
	// set and immediately display
	void renderLog(const std::string &message);
	// displays message to the screen
	void renderLog(); 


	// housekeeping
	void onLostDevice();
	void onResetDevice();

};