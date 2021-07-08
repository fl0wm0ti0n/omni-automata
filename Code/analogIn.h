// analogIn.h

#ifndef _HOME_AIN_h
#define _HOME_AIN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "sensor.h"

class analogIn : public sensor
{
	private:
		int iAnalogValue;
		int	iPinNum;

	public:
		analogIn(String n, int p);			// Constructor
		virtual ~analogIn();				// Destructor

		int getValue();						// Method: get Value
		int setPin(int iPin);				// Method: set Pin
};

#endif