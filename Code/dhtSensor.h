// DhtSensor.h

#ifndef _DHTSENSOR_h
#define _DHTSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Sensor.h"
#include <DHT.h>
#include "logger.h"

class DhtSensor :public Sensor
{
	float temp_;
	float hum_;
	float savetemp_;
	float savehum_;
	DHT dht_ = DHT(getPin(),DHT22);
	logger* logger_g_;

public:
		DhtSensor(char n[], int p);				// Constructor
		virtual ~DhtSensor();					// Destructor
		float getTempValue();					// Method: get Value
		float getHumValue();					// Method: get Value
		float getTempValueOnlyIfChanged();		// Method: get Value
		float getHumValueOnlyIfChanged();		// Method: get Value
};
#endif