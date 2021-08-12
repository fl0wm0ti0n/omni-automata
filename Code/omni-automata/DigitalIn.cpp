#include "DigitalIn.h"

DigitalIn::DigitalIn(char n[], unsigned short p)
	:Sensor(SENSOR_TYP_DIGITAL_IN,SENSOR_SUB_UNDEFINED, n, p)
{
#ifdef DEBUG
	static char* const buffer PROGMEM = "Logging1";
	logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
#endif
	setPin(p);
	set_debounce_interval(DEFAULT_DEBOUNCE);
}

DigitalIn::~DigitalIn()
= default;

 bool DigitalIn::setPin(unsigned short p)
{
	 input_ = Bounce();
	 input_.attach(p, INPUT_PULLUP);

	return true;
}

 void DigitalIn::update_debounce()
 {
	 input_.update();
 }

 void DigitalIn::set_debounce_interval(unsigned short interval)
 {
	 input_.interval(interval);
 }

bool DigitalIn::getValue()
{
#ifdef DEBUG
	static const char* const buffer PROGMEM = "Call - digitalIn.getValue";
	logger_g_->LnWriteLog(buffer, extremedebug);
#endif

	if (input_.read() == HIGH)
	{
		//Serial.println(F("Switch: is true"));
#ifdef DEBUG
		static const char* const buffer PROGMEM = "Switch: is true";
		logger_g_->LnWriteLog(buffer, sensordata);
#endif
		b_switch_state_ = true;
	}
	else
	{
		//Serial.println(F("Switch: is false"));
#ifdef DEBUG

		static const char* const buffer PROGMEM = "Switch: is false";
		logger_g_->LnWriteLog(buffer, sensordata);
#endif
		b_switch_state_ = false;
	}
	return b_switch_state_;
}

bool DigitalIn::getFell()
{
#ifdef DEBUG
	static const char* const buffer PROGMEM = "Call - digitalIn.getFell";
	logger_g_->LnWriteLog(buffer, extremedebug);
#endif
	return input_.fell();
}

bool DigitalIn::getRose()
{
#ifdef DEBUG
	static const char* const buffer PROGMEM = "Call - digitalIn.getRose";
	logger_g_->LnWriteLog(buffer, extremedebug);
#endif
	return input_.rose();
}

bool DigitalIn::getChanged()
{
#ifdef DEBUG
	static const char* const buffer PROGMEM = "Call - digitalIn.getChanged";
	logger_g_->LnWriteLog(buffer, extremedebug);
#endif
	return input_.changed();
}