// @file      Sensor.h
// @author    flow@p0cki.net
// @date      01.2017
// @brief     baseclass of all sensors

#ifndef _SENSOR_h
#define _SENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "logger.h"

enum sensor_type
{
	undefined_sens = 0,
	digitalIn_sens = 1,
	analogIn_sens = 2,
	I2C_sens = 3,
	DHT_sens = 4,
	gas_sens = 5,
	ada_sens = 6
};

class Sensor
{

private:
	sensor_type sensortype_;
	char* sensorname_;
	unsigned short sensorvalue_;
	unsigned short sensorpin_;

public:
	Sensor(sensor_type t, char n[], unsigned short p);
	virtual ~Sensor();

	virtual sensor_type getType()
	{return sensortype_;}

	virtual char* getName()
	{return sensorname_;}

	virtual bool setPin(unsigned short p)
	{
		sensorpin_ = p;
		pinMode(sensorpin_, INPUT_PULLUP);
		return true;
	}

	virtual unsigned short getPin()
	{return sensorpin_;}
	
	virtual bool getValue()
	{
		if (sensorvalue_ >= 1)
		{
			return true;
		}
		return false;
	}
};

#endif