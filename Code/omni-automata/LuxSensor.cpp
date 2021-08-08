/*
 * @file           sensor_lux.cpp
 * @author         flow@p0cki.at
 * @date           08.2021
 * @brief          Sensor to measure Lux with the TSL2561.
 */

#include "LuxSensor.h"
using namespace std;

//---Constructor--------------------------------------------------------
LuxSensor::LuxSensor(char n[], int p, gain_config option1, integration_config option2, addr_config option3, int id)
	: Sensor(sensor_type::I2C_sens, n, p)
{
#ifdef DEBUG
	static char* const buffer PROGMEM = "Logging1";
	logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
#endif

	switch (option3)
	{
	case highaddr:
		tsl_ = Adafruit_TSL2561_Unified(TSL2561_ADDR_HIGH, id);
	case lowaddr:
		tsl_ = Adafruit_TSL2561_Unified(TSL2561_ADDR_LOW, id);
	case floataddr:
		tsl_ = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, id);
	}
	
	configure(option1, option2);								// Auflösung einstellen
	tsl_.init();
}
//---Destructor---------------------------------------------------------
LuxSensor::~LuxSensor()
{
}	

/**************************************************************************/
/*
	Configures the gain and integration time for the TSL2561
*/
/**************************************************************************/
void LuxSensor::configure(gain_config option1, integration_config option2)
{
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= extremedebug)
	{
		static const char* const buffer PROGMEM = "Call - configure";
		logger_g_->LnWriteLog(buffer, extremedebug);
	}
#endif

	configureGain(option1);
	configureIntegration(option2);
}

void LuxSensor::configureGain(gain_config option1)
{
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= extremedebug)
	{
		static const char* const buffer PROGMEM = "Call - configureGain";
		logger_g_->LnWriteLog(buffer, extremedebug);
	}
#endif
	switch (option1)
	{
	case gain1x:
		tsl_.setGain(TSL2561_GAIN_1X);
	case gain16x:
		tsl_.setGain(TSL2561_GAIN_1X);
	case gainrangeOn:
		tsl_.enableAutoRange(true);          /* Auto-gain ... switches automatically between 1x and 16x */
	case gainrangeOff:
		tsl_.enableAutoRange(false);          /* Auto-gain ... switches automatically between 1x and 16x */
	}
}

void LuxSensor::configureIntegration(integration_config option2)
{
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= extremedebug)
	{
		static const char* const buffer PROGMEM = "Call - configureIntegration";
		logger_g_->LnWriteLog(buffer, extremedebug);
	}
#endif
	switch (option2)
	{
	case INTE13MS:
		tsl_.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);      /* fast but low resolution */
	case INTE101MS:
		tsl_.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS);  /* medium resolution and speed   */
	case INTE402MS:
		tsl_.setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);  /* 16-bit data but slowest conversions */
	}
}

//---Sensorwerte holen--------------------------------------------------
void LuxSensor::getLuminosity(unsigned short& amb, unsigned short& inf)
{
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= extremedebug)
	{
		static const char* const buffer PROGMEM = "Call - getAmbient";
		logger_g_->LnWriteLog(buffer, extremedebug);
	}
#endif
	
	uint16_t broadband = 0;
	uint16_t infrared = 0;
	tsl_.getLuminosity(&broadband, &infrared);
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= sensordata)
	{
		static const char* const buffer PROGMEM = "Amb: ";
		logger_g_->LnWriteLog(buffer, sensordata);
		logger_g_->LnWriteLog(broadband, sensordata);
		static const char* const buffer PROGMEM = "Inf: ";
		logger_g_->LnWriteLog(buffer, sensordata);
		logger_g_->LnWriteLog(infrared, sensordata);
	}
#endif

}

//---Lux-Berechnung-----------------------------------------------------
void LuxSensor::getLux(float &lux)
{
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= extremedebug)
	{
		static const char* const buffer PROGMEM = "Call - getLux";
		logger_g_->LnWriteLog(buffer, extremedebug);
	}
#endif
	
	/* Get a new sensor event */
	tsl_.getEvent(&event_);	
	lux = event_.light;
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= sensordata)
	{
		static const char* const buffer PROGMEM = "Lux: ";
		logger_g_->LnWriteLog(buffer, sensordata);
		logger_g_->LnWriteLog(lux, sensordata);
	}
#endif
}