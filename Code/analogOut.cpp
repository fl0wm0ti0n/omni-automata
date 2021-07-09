// @file           analogOut.cpp
// @author         flow@p0cki.net
// @date           08.2019
// @brief          class for analog output

#include "analogOut.h"
#include "logger.h"

analogOut::analogOut(String n, int p)
	:actor(analogOut_act, n, p)
{
	actor::setValue(analogRead(p));
}

analogOut::~analogOut()
= default;

bool analogOut::setValue(int v, logger &log)
{
	log.writeLog("Call - analogOut - setValue", extremedebug);

	if (getValue() != v)
	{
		actor::setValue(v);
		analogWrite(getPin(), v);
	}
	return true;
}

bool analogOut::doggle(logger &log)
{
	log.writeLog("Call - analogOut - doggle", extremedebug);
	return setValue(!getValue(), log);
}

void analogOut::SlowlyIncreaseOrDecreaseValue(bool sensorResult, int maxValue, logger &log)
{
	log.writeLog("Call - SlowlyIncreaseOrDecreaseValue", extremedebug);

	if (sensorResult == true)
	{
		if (lightcounter_ != maxValue)
		{
			if (lightcounter_ < maxValue)
			{
				lightcounter_++;
				log.writeLog("Value Up - " + String(lightcounter_), extremedebug);
			}
		}
	}
	else
	{
		if (lightcounter_ != 0)
		{
			if (lightcounter_ > 0)
			{
				lightcounter_--;
				log.writeLog("Value Down - " + String(lightcounter_), extremedebug);
			}
		}
	}
	setValue(lightcounter_, log);
}