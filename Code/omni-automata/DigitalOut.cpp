
// 
// 
// 

#include "DigitalOut.h"

DigitalOut::DigitalOut(char n[], int p)
	:Actor(digitalOut_act, n, p)
{
#ifdef DEBUG
	static char* const buffer PROGMEM = "Logging1";
	logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
#endif
	Actor::setValue(digitalRead(p));
}

DigitalOut::~DigitalOut()
{
}

bool DigitalOut::setValue(int v)
{
#ifdef DEBUG
	static const char* const buffer PROGMEM = "Call - DigitalOut - setValue";
	logger_g_->LnWriteLog(buffer, extremedebug);
#endif

	if (getValue() != v)
	{
		Actor::setValue(v);
		digitalWrite(getPin(),v);
	}
	return true;
}

bool DigitalOut::doggle()
{
#ifdef DEBUG
	static const char* const buffer PROGMEM = "Call - DigitalOut - Doggle";
	logger_g_->LnWriteLog(buffer, extremedebug);
#endif

	return setValue(!getValue());
}