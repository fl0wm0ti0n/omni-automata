// @file      Motionsensor_one.h
// @author    flow@p0cki.net
// @date      01.2017
// @brief     childclass sensor

#include "motionSensor.h"
#include "constants.h"

motionSensor::motionSensor(char n[], int p)
	:sensor(digitalIn_sens, n, p)
{
#ifdef DEBUG
	static char* const buffer PROGMEM = "Logging1";
	logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
#endif
}

motionSensor::~motionSensor()
= default;

bool motionSensor::getValue()
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

if (digitalRead(getPin()) == LOW && iMotionState != 0)
{
	iMotionState = 0;
	iMotionValue = false;
#ifdef DEBUG
	static const char* const buffer PROGMEM = "Motion is true";
	logger_g_->LnWriteLog(buffer, sensordata);
#endif
}

if (digitalRead(getPin()) == HIGH && iMotionState != 1)
{
	iMotionState = 1;
	iMotionValue = true;
#ifdef DEBUG
	static const char* const buffer PROGMEM = "Motion is false";
	logger_g_->LnWriteLog(buffer, sensordata);
#endif
}
		return iMotionValue;
}

bool motionSensor::trueIfStatusChanged()
{
#ifdef DEBUG
	static const char* const buffer PROGMEM = "Call - motion - trueIfStatusChanged";
	logger_g_->LnWriteLog(buffer, extremedebug);
#endif
	// toDo!
}