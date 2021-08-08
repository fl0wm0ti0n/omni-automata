
// @file           Sensor.cpp
// @author         flow@p0cki.at
// @date           01.2017
// @brief          baseclass of all sensors

#include "Sensor.h"

Sensor::Sensor(sensor_type t, char n[], unsigned short p)
	:sensortype_(t), sensorname_(n), sensorvalue_(0), sensorpin_(p)
{
	Sensor::setPin(sensorpin_);
}

Sensor::~Sensor()
= default;
