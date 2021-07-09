// @file      Motionsensor_one.h
// @author    flow@p0cki.net
// @date      01.2017
// @brief     childclass sensor

#include "motionSensor.h"
#include "constants.h"

motionSensor::motionSensor(String n, int p)
	:sensor(digitalIn_sens, n, p)
{

}

motionSensor::~motionSensor()
= default;

bool motionSensor::getValue(logger &log)
{
	log.writeLog("Call - motionGetValue", extremedebug);
	
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
	log.writeLog("Motion is true", sensordata);
}

if (digitalRead(getPin()) == HIGH && iMotionState != 1)
{
	iMotionState = 1;
	iMotionValue = true;
	log.writeLog("Motion is false", sensordata);
}
		return iMotionValue;
}

bool motionSensor::trueIfStatusChanged(logger &log)
{
	log.writeLog("Call - motion - trueIfStatusChanged", extremedebug);
	// toDo!
}