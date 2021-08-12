/*
 * @file           LuxSensor.h
 * @author         flow@p0cki.at
 * @date           08.2021
 * @brief          Sensor to measure Lux with the TSL2561.
 */

/*@param iOption: Sensor-Resolution Option
 *@param cAddress: i2c-Address from the Sensor (0x29, 0x39, 0x49)
 */

#ifndef LUXSENSOR_h
#define LUXSENSOR_h
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Sensor.h"
#include <Adafruit_TSL2561_U.h>
#include <Adafruit_Sensor.h>

enum gain_config
{
	gain1x = 0,
	gain16x = 1,
	gainrangeOn = 2,
	gainrangeOff = 3
};

enum integration_config
{
	INTE13MS = 0,
	INTE101MS = 1,
	INTE402MS = 2
};

enum addr_config
{
	lowaddr = 0,
	highaddr = 1,
	floataddr = 2
};

class LuxSensor :public Sensor
{
public:
	LuxSensor(char n[], int p, gain_config option1, integration_config option2, addr_config option3, int id);	// Constructor
	virtual ~LuxSensor();														// Destructor
	void getLuminosity(unsigned short &amb, unsigned short& inf);				// Method: get Sensor Ambient
	void getLux(float& lux);													// Method: get Lux out of Sensor Data
	void configure(gain_config option1, integration_config option2);
	void configureGain(gain_config option1);
	void configureIntegration(integration_config option2);
	
//-------------------------------------------------------------------------------	
private:
	Adafruit_TSL2561_Unified tsl_;
	logger* logger_g_;
	sensors_event_t event_;
};
#endif