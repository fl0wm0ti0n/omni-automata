// @file           home_touch.cpp
// @author         flow@p0cki.at
// @date           11.2016
// @brief          touch Sensor Values

#include "TouchSensor.h"

TouchSensor::TouchSensor(char n[], int p)
	:Sensor(digitalIn_sens, n, p)
{
#ifdef DEBUG
	static char* const buffer PROGMEM = "Logging1";
	logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
#endif
}

TouchSensor::~TouchSensor()
= default;

// Gibt den Status des Sensors als Boolean zurück.
bool TouchSensor::getState()
{
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= extremedebug)
	{
		static const char* const buffer PROGMEM = "Call - touch - getState";
		logger_g_->LnWriteLog(buffer, extremedebug);
	}
#endif
	if (digitalRead(getPin()) == HIGH)
	{
		touch_state_ = true;
	}
	else
	{
		touch_state_ = false;
	}
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= sensordata)
	{
		static const char* const buffer PROGMEM = "Touch is ";
		logger_g_->LnWriteLog(buffer, sensordata);
		logger_g_->WriteLog(touch_state_, sensordata);
	}
#endif
	return touch_state_;
}

// Wechselt, wenn sich der Status des Sensors geändert hat. den Boolean als Doggle zwischen True und False und gibt den gewechselten Status als Boolean zurück.
bool TouchSensor::getStateWithDoggle()
{
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= extremedebug)
	{
		static const char* const buffer PROGMEM = "Call - touch - getStateWithDoggle";
		logger_g_->LnWriteLog(buffer, extremedebug);
	}
#endif
	if (digitalRead(getPin()) == HIGH && digital_value_ != 0)
	{
		digital_value_	= 0;
		touch_state_		= false;
	}
	if (digitalRead(getPin()) == HIGH && digital_value_ != 1)
	{
		digital_value_	= 1;
		touch_state_		= true;
	}
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= sensordata)
	{
		static const char* const buffer PROGMEM = "Touch is ";
		logger_g_->LnWriteLog(buffer, sensordata);
		logger_g_->WriteLog(touch_state_, sensordata);
	}
#endif
	return touch_state_; 
}

// Gibt den analogen Wert des Sensors zurück.
float TouchSensor::getAnalog(t_analog_or_bool tswitch)
{
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= extremedebug)
	{
		static const char* const buffer PROGMEM = "Call - touch - getAnalog";
		logger_g_->LnWriteLog(buffer, extremedebug);
	}
#endif
	analog_value_ = analogRead(getPin());

	if (analog_value_ >= threshold_)
	{
		touch_state_ = true;
	}
	else
	{;
		touch_state_ = false;
	}

	// Schalter ob boolean oder Analog zurückgegeben wird.
	if (tswitch == booleanReturn)
	{
		return touch_state_;
	}
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= sensordata)
	{
		static const char* const buffer PROGMEM = "Touch: AnalogValue = ";
		logger_g_->LnWriteLog(buffer, sensordata);
		logger_g_->WriteLog(analog_value_, sensordata);
	}
#endif
	return analog_value_;
}

// Wechselt, wenn sich der Status des Sensors geändert hat. den Boolean als Doggle zwischen True und False und gibt den gewechselten Status als Boolean zurück.
float TouchSensor::getAnalogWithDoggle(t_analog_or_bool tswitch)
{
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= extremedebug)
	{
		static const char* const buffer PROGMEM = "Call - touch - getAnalogWithDoggle";
		logger_g_->LnWriteLog(buffer, extremedebug);
	}
#endif
	analog_value_ = analogRead(getPin());
	if (analog_value_ >= threshold_ && digital_value_ != 0)
	{
		digital_value_	= 0;
		touch_state_		= false;
	}
	if (analog_value_ >= threshold_ && digital_value_ != 1)
	{
		digital_value_	= 1;
		touch_state_		= true;
	}
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= sensordata)
	{
		static const char* const buffer PROGMEM = "Touch is ";
		logger_g_->LnWriteLog(buffer, sensordata);
		logger_g_->WriteLog(touch_state_, sensordata);
	}
#endif
	// Schalter ob boolean oder Analog zurückgegeben wird.
	if (tswitch == booleanReturn)
	{
		return touch_state_;
	}
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= sensordata)
	{
		static const char* const buffer PROGMEM = "Touch: AnalogValue = ";
		logger_g_->LnWriteLog(buffer, sensordata);
		logger_g_->WriteLog(analog_value_, sensordata);
	}
#endif
	return analog_value_;
}

void TouchSensor::setAnalogTreshold(float threshold)
{
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= extremedebug)
	{
		static const char* const buffer PROGMEM = "Call - touch - setAnalogTreshold";
		logger_g_->LnWriteLog(buffer, extremedebug);
	}
#endif
	threshold_ = threshold;
}