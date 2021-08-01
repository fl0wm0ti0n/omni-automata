// 
// 
// 

#include "DHT.h"
#include "DhtSensor.h"
#include "logger.h"

DhtSensor::DhtSensor(char n[], int p)
	:Sensor(t_sensor_type::DHT_sens, n, p)
{
#ifdef DEBUG
static char* const buffer PROGMEM = "Logging1";
logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
#endif
	dht_.begin();
}

DhtSensor::~DhtSensor()
= default;

float DhtSensor::getTempValue()
{
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= extremedebug)
	{
		static const char* const buffer PROGMEM = "Call - DHT.getTempValue";
		logger_g_->LnWriteLog(buffer, extremedebug);
	}
#endif
	temp_ = dht_.readTemperature();
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= sensordata)
	{
		static const char* const buffer PROGMEM = "Temp = ";
		logger_g_->LnWriteLog(buffer, sensordata);
		logger_g_->WriteLog(temp, sensordata);
		static const char* const buffer PROGMEM = "C";
		logger_g_->WriteLog(buffer, sensordata);
	}
#endif
	return temp_;
}

float DhtSensor::getHumValue()
{
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= extremedebug)
	{
		static const char* const buffer PROGMEM = "Call - DHT.getHumValue";
		logger_g_->LnWriteLog(buffer, extremedebug);
	}
#endif
	hum_ = dht_.readHumidity();
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= sensordata)
	{
		static const char* const buffer PROGMEM = "Humid = ";
		logger_g_->LnWriteLog(buffer, sensordata);
		logger_g_->WriteLog(hum, sensordata);
		static const char* const buffer PROGMEM = "%";
		logger_g_->WriteLog(buffer, sensordata);
	}
#endif
	return hum_;
}

float DhtSensor::getTempValueOnlyIfChanged()
{
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= extremedebug)
	{
		static const char* const buffer PROGMEM = "Call - DHT.getTempValueOnlyIfChanged";
		logger_g_->LnWriteLog(buffer, extremedebug);
	}
#endif
	temp_ = dht_.readTemperature();
	if (temp_ != savetemp_)
	{
#ifdef DEBUG
		if (logger_g_->GetLogLevel() >= sensordata)
		{
			static const char* const buffer PROGMEM = "Temp = ";
			logger_g_->LnWriteLog(buffer, sensordata);
			logger_g_->WriteLog(temp, sensordata);
			static const char* const buffer PROGMEM = "C";
			logger_g_->WriteLog(buffer, sensordata);
		}
#endif
		savetemp_ = temp_;
	}
	return temp_;
}

float DhtSensor::getHumValueOnlyIfChanged()
{
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= extremedebug)
	{
		static const char* const buffer PROGMEM = "Call - DHT.getHumValueOnlyIfChanged";
		logger_g_->LnWriteLog(buffer, extremedebug);
	}
#endif
	hum_ = dht_.readHumidity();
	if (hum_ != savehum_)
	{
#ifdef DEBUG
		if (logger_g_->GetLogLevel() >= sensordata)
		{
			static const char* const buffer PROGMEM = "Humid = ";
			logger_g_->LnWriteLog(buffer, sensordata);
			logger_g_->WriteLog(hum, sensordata);
			static const char* const buffer PROGMEM = "%";
			logger_g_->WriteLog(buffer, sensordata);
	}
#endif
		savehum_ = hum_;
	}
	return hum_;
}