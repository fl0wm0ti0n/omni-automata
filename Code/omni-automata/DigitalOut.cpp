// @file           analogOut.cpp
// @author         flow@p0cki.net
// @date           08.2019
// @brief          class for analog output

#include "DigitalOut.h"

DigitalOut::DigitalOut(char n[], const unsigned short p)
	:Actor(ACTOR_TYP_DIGITAL_OUT,ACTOR_SUB_UNDEFINED, n, p)
{
#ifdef DEBUG
	static char* const buffer PROGMEM = "Logging1";
	logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
#endif
	DigitalOut::setEvent(digitalRead(Actor::getPin().eins.pin1));
	DigitalOut::fireEvent();
}

DigitalOut::~DigitalOut()
= default;

/// <summary>
/// set event (value) which should sent to the actor
/// </summary>
/// <param name="newevent">event type, which can hold a int value 0/1</param>
/// <returns>true if no error</returns>
bool DigitalOut::setEvent(actor_event newevent)
{
	event = newevent;
	return true;
}

/// <summary>
/// set event (value) which should sent to the actor
/// </summary>
/// <param name="value">int value 0/1</param>
/// <returns>true if no error</returns>
bool DigitalOut::setEvent(int value)
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
bool DigitalOut::fireEvent()
{
#ifdef DEBUG
	static const char* const buffer PROGMEM = "Call - DigitalOut - fireEvent";
	logger_g_->LnWriteLog(buffer, extremedebug);
#endif

	if (digitalRead(getPin().eins.pin1) != value_.int_)
	{
		digitalWrite(getPin().eins.pin1, value_.int_);
		return true;
	}
	return false;
}

bool DigitalOut::doggle()
{
#ifdef DEBUG
	static const char* const buffer PROGMEM = "Call - DigitalOut - Doggle";
	logger_g_->LnWriteLog(buffer, extremedebug);
#endif

	setEvent(value_.int_);
	return fireEvent();
}