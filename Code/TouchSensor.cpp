// @file           home_touch.cpp
// @author         flow@p0cki.at
// @date           11.2016
// @brief          touch sensor Values

#include "touchSensor.h"

touchSensor::touchSensor(String n, int p)
	:sensor(digitalIn_sens, n, p)
{

}

touchSensor::~touchSensor()
= default;

// Gibt den Status des Sensors als Boolean zurück.
bool touchSensor::getState(logger &log)
{
	log.writeLog("Call - touch - getState", extremedebug);
	if (digitalRead(getPin()) == HIGH)
	{
		log.writeLog("Touch: is true", sensordata);
		bTouchState = true;
	}
	else
	{
		log.writeLog("Touch: is false", sensordata);
		bTouchState = false;
	}
	return bTouchState;
}

// Wechselt, wenn sich der Status des Sensors geändert hat. den Boolean als Doggle zwischen True und False und gibt den gewechselten Status als Boolean zurück.
bool touchSensor::getStateWithDoggle(logger &log)
{
	log.writeLog("Call - touch - getStateWithDoggle", extremedebug);
	if (digitalRead(getPin()) == HIGH && iDigitalValue != 0)
	{
		log.writeLog("Touch: is false", sensordata);
		iDigitalValue	= 0;
		bTouchState		= false;
	}
	if (digitalRead(getPin()) == HIGH && iDigitalValue != 1)
	{
		log.writeLog("Touch: is true", sensordata);
		iDigitalValue	= 1;
		bTouchState		= true;
	}
	return bTouchState; 
}

// Gibt den analogen Wert des Sensors zurück.
float touchSensor::getAnalog(t_analog_or_bool tswitch, logger &log)
{

	log.writeLog("Call - touch - getAnalog", extremedebug);
	fAnalogValue = analogRead(getPin());

	if (fAnalogValue >= fThreshold)
	{
		bTouchState = true;
	}
	else
	{;
		bTouchState = false;
	}

	// Schalter ob boolean oder Analog zurückgegeben wird.
	if (tswitch == booleanReturn)
	{
		return bTouchState;
	}
	log.writeLog("Touch: Analoger Wert = " + String(fAnalogValue), sensordata);
	return fAnalogValue;
}

// Wechselt, wenn sich der Status des Sensors geändert hat. den Boolean als Doggle zwischen True und False und gibt den gewechselten Status als Boolean zurück.
float touchSensor::getAnalogWithDoggle(t_analog_or_bool tswitch, logger &log)
{
	log.writeLog("Call - touch - getAnalogWithDoggle", extremedebug);
	fAnalogValue = analogRead(getPin());
	if (fAnalogValue >= fThreshold && iDigitalValue != 0)
	{
		iDigitalValue	= 0;
		bTouchState		= false;
		log.writeLog("Touch: is false", sensordata);
	}
	if (fAnalogValue >= fThreshold && iDigitalValue != 1)
	{
		iDigitalValue	= 1;
		bTouchState		= true;
		log.writeLog("Touch: is true", sensordata);
	}

	// Schalter ob boolean oder Analog zurückgegeben wird.
	if (tswitch == booleanReturn)
	{
		return bTouchState;
	}
	log.writeLog("Touch: Analoger Wert = " + String(fAnalogValue), sensordata);
	return fAnalogValue;
}

void touchSensor::setAnalogTreshold(float threshold, logger &log)
{
	log.writeLog("Call - touch - setAnalogTreshold", extremedebug);
	fThreshold = threshold;
}