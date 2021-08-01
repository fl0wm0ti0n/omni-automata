// Motionsensor_one.h

#ifndef _HOME_MOTION_h
#define _HOME_MOTION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "sensor.h"
#include "logger.h"

class motionSensor :public sensor
{
private:
	byte iMotionState = 0;
	bool iMotionValue = false;

public:
	motionSensor(char n[], int p);		// Constructor
	virtual ~motionSensor();				// Destructor

	virtual bool getValue();		// Method: get motion Value
	bool trueIfStatusChanged();
};

#endif