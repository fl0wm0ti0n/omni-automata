// @file           analogOut.cpp
// @author         flow@p0cki.net
// @date           08.2019
// @brief          class for analog output

#include "AnalogOut.h"
#include "logger.h"

AnalogOut::AnalogOut(char n[], int p)
	:Actor(analogOut_act, n, p)
{
#ifdef DEBUG
	static char* const buffer PROGMEM = "Logging1";
	logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
#endif
	Actor::setValue(analogRead(p));
}

AnalogOut::~AnalogOut()
= default;

bool AnalogOut::setValue(int v)
{
#ifdef DEBUG
	static const char* const buffer PROGMEM = "Call - analogOut - setValue";
	logger_g_->LnWriteLog(buffer, extremedebug);
#endif


	if (getValue() != v)
	{
		Actor::setValue(v);
		analogWrite(getPin(), v);
	}
	return true;
}

bool AnalogOut::doggle()
{
	static const char* const buffer PROGMEM = "Call - analogOut - Doggle";
	logger_g_->LnWriteLog(buffer, extremedebug);
	return setValue(!getValue());
}

void AnalogOut::slowly_increase_or_decrease_value(bool sensor_result, int max_value)
{
#ifdef DEBUG
	static const char* const buffer PROGMEM = "Call - LEDSlowlyInDecreaseValue";
	logger_g_->WriteLog(buffer, extremedebug);
#endif
	if (sensor_result)
	{
		if (lightcounter_ != max_value)
		{
			if (lightcounter_ < max_value)
			{
				lightcounter_++;
#ifdef DEBUG
				static const char* const buffer PROGMEM = "Value Up - ";
				logger_g_->LnWriteLog(buffer, extremedebug);
				logger_g_->WriteLog(lightcounter_, extremedebug);
#endif

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
#ifdef DEBUG
				static const char* const buffer PROGMEM = "Value Down - ";
				logger_g_->LnWriteLog(buffer, extremedebug);
				logger_g_->WriteLog(lightcounter_, extremedebug);
#endif
			}
		}
	}
	setValue(lightcounter_);
}