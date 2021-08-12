
// @file           Sensor.cpp
// @author         flow@p0cki.at
// @date           01.2017
// @brief          baseclass of all sensors

#include "Sensor.h"

Sensor::Sensor(sensor_type t, sensor_subtype s, char n[], unsigned short p)
	:sensortype_(t), sensorsubtype_(s), sensorname_(n), sensorvalue_(0), sensorpin_(p), id_(current_id++)
{
	Sensor::setPin(sensorpin_);
}

Sensor::~Sensor()
= default;
