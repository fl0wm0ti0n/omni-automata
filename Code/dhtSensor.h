// home_dht.h

#ifndef _HOME_DHT_h
#define _HOME_DHT_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "sensor.h"
#include <DHT.h>
#include "logger.h"

class dhtSensor :public sensor
{
	float temp;
	float hum;
	float savetemp;
	float savehum;
	DHT dht = DHT(getPin(),DHT22);

public:
		dhtSensor(String n, int p);									// Constructor
		virtual ~dhtSensor();										// Destructor
		float getTempValue(logger &logging_one);					// Method: get Value
		float getHumValue(logger &logging_one);						// Method: get Value
		float getTempValueOnlyIfChanged(logger &logging_one);		// Method: get Value
		float getHumValueOnlyIfChanged(logger &logging_one);		// Method: get Value
};
#endif