
// @file           Doggle.h
// @author         flow@p0cki.at
// @date           12.2016
// @brief          flip a Value

#ifndef _DOGGLE_h
#define _DOGGLE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Doggle
{
private:
	static int flip_;
	static int flop_;
	bool return_value_;

public:
	Doggle();						// Constructor
	virtual ~Doggle();				// Destructor

	int flip(int iValue);				// Method: get on or off					
};
#endif

