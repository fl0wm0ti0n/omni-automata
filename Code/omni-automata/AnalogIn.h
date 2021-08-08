// analogIn.h

#ifndef _HOME_AIN_h
#define _HOME_AIN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Sensor.h"

class AnalogIn final : public Sensor
{
	private:
		unsigned short analog_value_;
		unsigned short	pin_num_;
		logger* logger_g_;

	public:
		AnalogIn(char n[], unsigned short p);			// Constructor
		~AnalogIn();									// Destructor

		unsigned short getAnalogValue();				// Method: get Value
};

#endif