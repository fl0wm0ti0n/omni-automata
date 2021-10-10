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

#include "ISensor.h"
#include "logger.h"
#include "stdint.h"

class Sensor : public ISensor
{

protected:

	sensor_type			type_;
	sensor_subtype		subtype_;
	char*				sensorname_;
	unsigned short		sensorvalue_;
	sensor_pins			sensor_pin_;
	//sensor_pin_values	sensor_pin_values_;
	int					id_;			// instance id
	static int			current_id;		// static for sensor id shared between all instances

public:
	Sensor(sensor_type t, sensor_subtype s, char n[], sensor_pins p);
	virtual ~Sensor();
			sensor_event	event_;
	virtual bool			readEvent()				override {return true;}
	virtual sensor_event	getEvent()				override {return event_;}
	virtual sensor_type		getType()				override {return type_;}
	virtual sensor_subtype	getSubtype()			override {return subtype_;}
	virtual char*			getName()				override {return sensorname_;}
	virtual sensor_pins		getPin()				override {return sensor_pin_;}
	virtual bool			setPin(sensor_pins p)	override
	{
		sensor_pin_ = p;
		if (sensor_pin_.eins.pin1)
		{
			pinMode(sensor_pin_.eins.pin1, INPUT_PULLUP);
			return true;
		}
		if (sensor_pin_.zwei.pin1 && sensor_pin_.zwei.pin2)
		{
			pinMode(sensor_pin_.zwei.pin1, INPUT_PULLUP);
			pinMode(sensor_pin_.zwei.pin2, INPUT_PULLUP);
			return true;
		}
		if (sensor_pin_.drei.pin1 && sensor_pin_.drei.pin2 && sensor_pin_.drei.pin3)
		{
			pinMode(sensor_pin_.drei.pin1, INPUT_PULLUP);
			pinMode(sensor_pin_.drei.pin2, INPUT_PULLUP);
			pinMode(sensor_pin_.drei.pin3, INPUT_PULLUP);
			return true;
		}
		return false;
	}
};

#endif