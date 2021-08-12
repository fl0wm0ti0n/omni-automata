// @file      Motionsensor_one.h
// @author    flow@p0cki.net
// @date      01.2017
// @brief     childclass Sensor

#include "MotionSensor.h"
#include "constants.h"

MotionSensor::MotionSensor(char n[], int p)
	:Sensor(SENSOR_TYP_DIGITAL_IN, SENSOR_SUB_UNDEFINED, n, p)
{
#ifdef DEBUG
	static char* const buffer PROGMEM = "Logging1";
	logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
#endif
}

MotionSensor::~MotionSensor()
= default;

bool MotionSensor::getValue()
{
#ifdef DEBUG
	static const char* const buffer PROGMEM = "Call - motionGetValue";
	logger_g_->LnWriteLog(buffer, extremedebug);
#endif
	/*if (digitalRead(getPin()) == HIGH)
	{
		logging_one.writeLog("Motion: is true", sensordata);
		iMotionValue = true;
	}
	else
	{
		logging_one.writeLog("Motion: is false", sensordata);
		iMotionValue = false;
	}*/

if (digitalRead(getPin()) == LOW && motion_state_ != 0)
{
	motion_state_ = 0;
	motion_value_ = false;
#ifdef DEBUG
	static const char* const buffer PROGMEM = "Motion is true";
	logger_g_->LnWriteLog(buffer, sensordata);
#endif
}

if (digitalRead(getPin()) == HIGH && motion_state_ != 1)
{
	motion_state_ = 1;
	motion_value_ = true;
#ifdef DEBUG
	static const char* const buffer PROGMEM = "Motion is false";
	logger_g_->LnWriteLog(buffer, sensordata);
#endif
}
	return motion_value_;
}

bool MotionSensor::true_if_status_changed()
{
#ifdef DEBUG
	static const char* const buffer PROGMEM = "Call - motion - trueIfStatusChanged";
	logger_g_->LnWriteLog(buffer, extremedebug);
#endif
	// toDo!
	return true;
}