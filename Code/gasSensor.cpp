// 
// 
// 

#include "gasSensor.h"

gasSensor::gasSensor(String n, int p)
	:sensor(t_sensor_type::analogIn_sens, n, p)
{
	sensor::getValue(analogRead(p));
	setPin(p);
}

gasSensor::~gasSensor()
= default;

int gasSensor::setPin(int iPin)
{
	iPinNum = iPin;
	pinMode(iPinNum, INPUT);
}

int gasSensor::getRawValue()
{
	iAnalogValue = analogRead(iPinNum);
	return iAnalogValue;
}

float gasSensor::getCO2Value()
{
	sensorValue = getRawValue();
	sensorResistance = (1023. / (float)sensorValue * 5. - 1.)*RLOAD;

	value = PARA * pow(sensorResistance / RZERO, -PARB);
	return value;
}

float gasSensor::getCOValue()
{
	sensorValue = getRawValue();

	v_out = (float)sensorValue * (v_in / 1023.0);
	vRatio = (v_in - v_out) / v_out;
	sensorResistance = R_Load * vRatio;
	value = (float)(coefficient_A * pow(vRatio, coefficient_B));

	return value;
}