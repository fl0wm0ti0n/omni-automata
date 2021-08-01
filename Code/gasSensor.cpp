// 
// 
// 

#include "GasSensor.h"

GasSensor::GasSensor(char n[], int p)
	:Sensor(t_sensor_type::analogIn_sens, n, p)
{
#ifdef DEBUG
	static char* const buffer PROGMEM = "Logging1";
	logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
#endif
	Sensor::getValue();
	setPin(p);
}

GasSensor::~GasSensor()
= default;

int GasSensor::setPin(int iPin)
{
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= extremedebug)
	{
		static const char* const buffer PROGMEM = "Call - CO.setPin";
		logger_g_->LnWriteLog(buffer, extremedebug);
	}
#endif
	pin_num_ = iPin;
	pinMode(pin_num_, INPUT);
}

int GasSensor::getRawValue()
{
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= extremedebug)
	{
		static const char* const buffer PROGMEM = "Call - CO.getRawValue";
		logger_g_->LnWriteLog(buffer, extremedebug);
	}
#endif
	analog_value_ = analogRead(pin_num_);
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= sensordata)
	{
		static const char* const buffer PROGMEM = "analog_value_ = ";
		logger_g_->LnWriteLog(buffer, sensordata);
		logger_g_->WriteLog(analog_value_, sensordata);
	}
#endif
	return analog_value_;
}

float GasSensor::getCO2Value()
{
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= extremedebug)
	{
		static const char* const buffer PROGMEM = "Call - CO.getCO2Value";
		logger_g_->LnWriteLog(buffer, extremedebug);
	}
#endif
	sensor_value_ = getRawValue();
	sensor_resistance_ = (1023. / (float)sensor_value_ * 5. - 1.) * RLOAD;
	value_ = PARA * pow(sensor_resistance_ / RZERO, -PARB);
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= sensordata)
	{
		static const char* const buffer PROGMEM = "value_ = ";
		logger_g_->LnWriteLog(buffer, sensordata);
		logger_g_->WriteLog(value_, sensordata);
	}
#endif
	return value_;
}

float GasSensor::getCOValue()
{
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= extremedebug)
	{
		static const char* const buffer PROGMEM = "Call - CO.getCO2Value";
		logger_g_->LnWriteLog(buffer, extremedebug);
	}
#endif
	sensor_value_ = getRawValue();
	v_out_ = (float)sensor_value_ * (v_in / 1023.0);
	v_ratio_ = (v_in - v_out_) / v_out_;
	sensor_resistance_ = R_Load * v_ratio_;
	value_ = (float)(coefficient_A * pow(v_ratio_, coefficient_B));
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= sensordata)
	{
		static const char* const buffer PROGMEM = "value_ = ";
		logger_g_->LnWriteLog(buffer, sensordata);
		logger_g_->WriteLog(value_, sensordata);
	}
#endif
	return value_;
}