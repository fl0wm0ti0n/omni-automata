// home_ain.h

#ifndef _HOME_GAS_h
#define _HOME_GAS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "Sensor.h"

class GasSensor : public Sensor
{
private:
	int analog_value_;
	int	pin_num_;
	float sensor_value_ = 0;
	float value_ = 0;
	float sensor_resistance_ = 0;
	logger* logger_g_;

	// CO2
	#define RLOAD 10.0
	#define RZERO 76.63
	#define PARA 116.6020682
	#define PARB 2.769034857

	// CO
	#define R_Load 10.0					//Load resistance 10 Kohms on the Sensor potentiometer
	#define coefficient_A 19.32
	#define coefficient_B -0.64
	#define v_in 5
	float v_ratio_ = 0;
	float v_out_;


public:
	GasSensor(char n[], int p);			// Constructor
	virtual ~GasSensor();				// Destructor

	int getRawValue();					// Method: get Value
	int setPin(int iPin);				// Method: set Pin
	float getCO2Value();
	float getCOValue();
};

#endif