#ifndef _HOME_DOUT_h
#define _HOME_DOUT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Actor.h"
#include "logger.h"

class DigitalOut:public Actor
{
	logger* logger_g_;
	
public:
	 DigitalOut(char n[], int p);
	 virtual ~DigitalOut();
	 virtual bool setValue(int v);
	 bool doggle();
};

#endif

