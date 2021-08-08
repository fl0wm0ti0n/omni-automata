// Motionsensor.h

#ifndef _HOME_MOTION_h
#define _HOME_MOTION_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Sensor.h"
#include "logger.h"

class MotionSensor :public Sensor
{
private:
	byte motion_state_ = 0;
	bool motion_value_ = false;

public:
	MotionSensor(char n[], int p);		// Constructor
	virtual ~MotionSensor();				// Destructor

	virtual bool getValue();		// Method: get motion Value
	bool true_if_status_changed();
};

#endif