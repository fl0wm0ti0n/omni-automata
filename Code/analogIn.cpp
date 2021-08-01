// @file      analogIn.cpp
// @author    flow@p0cki.net
// @date      08.2019
// @brief     childclass of Sensor

#include "AnalogIn.h"

AnalogIn::AnalogIn(char n[], unsigned short p)
	:Sensor(analogIn_sens, n, p)
{
#ifdef DEBUG
	static char* const buffer PROGMEM = "Logging1";
	logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
#endif
	setPin(p);
}

AnalogIn::~AnalogIn()
= default;

unsigned short AnalogIn::getAnalogValue()
{
#ifdef DEBUG
	static const char* const buffer PROGMEM = "Call - analogIn.getValue";
	logger_g_->WriteLog(buffer, extremedebug);
#endif

	analog_value_ = analogRead(pin_num_);
	return analog_value_;
}