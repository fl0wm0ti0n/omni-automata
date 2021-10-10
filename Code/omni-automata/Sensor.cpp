
// @file           Sensor.cpp
// @author         flow@p0cki.at
// @date           01.2017
// @brief          baseclass of all sensors

#include "Sensor.h"

Sensor::Sensor(sensor_type t, sensor_subtype s, char n[], sensor_pins p)
	:event_(), type_(t), subtype_(s), sensorname_(n), sensorvalue_(0), sensor_pin_(p), id_(current_id++)
{
}

Sensor::~Sensor()
= default;
