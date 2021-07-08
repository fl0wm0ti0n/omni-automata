// @file      analogIn.cpp
// @author    flow@p0cki.net
// @date      08.2019
// @brief     childclass of sensor

#include "analogIn.h"

analogIn::analogIn(String n, int p)
	:sensor(analogIn_sens, n, p)
{
	sensor::getValue(analogRead(p));
	setPin(p);
}

analogIn::~analogIn()
= default;

int analogIn::setPin(int iPin)
{
	iPinNum = iPin;
	pinMode(iPinNum, INPUT);
}

int analogIn::getValue()
{
	iAnalogValue = analogRead(iPinNum);
	return iAnalogValue;
}