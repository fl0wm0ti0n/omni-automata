// home_ain.h

#ifndef _HOME_GAS_h
#define _HOME_GAS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "sensor.h"

class gasSensor : public sensor
{
private:
	int iAnalogValue;
	int	iPinNum;
	float sensorValue = 0;
	float value = 0;
	float sensorResistance = 0;

	// CO2
	#define RLOAD 10.0
	#define RZERO 76.63
	#define PARA 116.6020682
	#define PARB 2.769034857

	// CO
	#define R_Load 10.0					//Load resistance 10 Kohms on the sensor potentiometer
	#define coefficient_A 19.32
	#define coefficient_B -0.64
	#define v_in 5
	float vRatio = 0;
	float v_out;


public:
	gasSensor(String n, int p);			// Constructor
	virtual ~gasSensor();				// Destructor

	int getRawValue();					// Method: get Value
	int setPin(int iPin);				// Method: set Pin
	float getCO2Value();
	float getCOValue();
};

#endif