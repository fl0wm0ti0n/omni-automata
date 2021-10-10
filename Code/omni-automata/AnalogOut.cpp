// @file           analogOut.cpp
// @author         flow@p0cki.net
// @date           08.2019
// @brief          class for analog output

#include "AnalogOut.h"
#include "logger.h"

AnalogOut::AnalogOut(char n[], unsigned short p)
	: Actor(ACTOR_TYP_ANALOG_OUT, ACTOR_SUB_UNDEFINED, n, p)
{
#ifdef DEBUG
	static char* const buffer PROGMEM = "Logging1";
	logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
#endif
	AnalogOut::setEvent(analogRead(Actor::getPin().eins.pin1));
	AnalogOut::fireEvent();
}

AnalogOut::~AnalogOut()
= default;

/// <summary>
/// set event (value) which should sent to the actor
/// </summary>
/// <param name="newevent">event type, which can hold a voltage value, voltage = int * (5.0 / 1023)</param>
/// <returns>true if no error</returns>
bool AnalogOut::setEvent(actor_event newevent)
{
	event = newevent;
	return true;
}

/// <summary>
/// set event (value) which should sent to the actor
/// </summary>
/// <param name="value">voltage value 0.0-5.0, voltage = int * (5.0 / 1023)</param>
/// <returns>true if no error</returns>
bool AnalogOut::setEvent(float value)
{
	// convert Voltage to int (0-1023)
	// int = voltage * (1023 / 5.0);
	value_.int_ = value * (1023 / 5.0);
	event.voltage = value;
	return true;
}

/// <summary>
/// set event (value) which should sent to the actor
/// </summary>
/// <param name="value"> int value 0-1023, int = voltage * (1023 / 5.0)</param>
/// <returns>true if no error</returns>
bool AnalogOut::setEvent(int value)
{
	value_.int_ = value;
	// convert int to voltage (0-1023)
	// voltage = int * (5.0 / 1023);
	event.voltage = value * (5.0 / 1023);
	return true;
}

/// <summary>
/// write already set value to pin
/// </summary>
/// <returns>true if value got updated, else false</returns>
bool AnalogOut::fireEvent()
{
#ifdef DEBUG
	static const char* const buffer PROGMEM = "Call - analogOut - setValue";
	logger_g_->LnWriteLog(buffer, extremedebug);
#endif

	if (analogRead(getPin().eins.pin1) != value_.int_)
	{
		analogWrite(getPin().eins.pin1, value_.int_);
		return true;
	}
	return false;
}

/// <summary>
/// if sensor_result is true analogValue (int) is getting incremented by 1, otherwise it is getting decremented by 1
/// </summary>
/// <param name="sensor_result">result of a sensor or other input</param>
/// <param name="max_value"> max analogValue (max = 1023) </param>
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
	setEvent(lightcounter_);
	fireEvent();
}