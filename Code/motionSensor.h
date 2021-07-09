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
	int iMotionState = 0;
	bool iMotionValue = false;

public:
	motionSensor(String n, int p);		// Constructor
	virtual ~motionSensor();				// Destructor

	virtual bool getValue(logger &logging_one);		// Method: get motion Value
	bool trueIfStatusChanged(logger& log);
};

#endif