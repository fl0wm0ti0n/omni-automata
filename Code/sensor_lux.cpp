/*
 * @file           sensor_lux.cpp
 * @author         flow@p0cki.at
 * @date           04.2016
 * @brief          Sensor to measure Lux with the TSL2561.
 */

#include <stdlib.h>
#include "sensor_lux.h"
#include <math.h>


using namespace std;

//---Constructor--------------------------------------------------------
sensor_lux::sensor_lux(int iOption, char cAddress)
	: i2cID(-1)
{
	i2cID = wiringPiI2CSetup(cAddress);					// Sensor initialisieren
	
	wiringPiI2CWriteReg8(i2cID, 0x80, 0x03);			// Sensor einschalten
	
	setResolution(iOption);								// Auflösung einstellen
}
//---Destructor---------------------------------------------------------
sensor_lux::~sensor_lux()
{
	wiringPiI2CWriteReg8(i2cID, 0x80, 0x00);			// Sensor ausschalten
}	

//---AUFLÖSUNG EINSTELLEN-----------------------------------------------
void sensor_lux::setResolution(int iOption)
{
	int cRegister;
//---Sensor-Auflösung------(default = hoch)
	switch (iOption) {
	case 1:
		cRegister = 0x00;
		break;
	case 2:
		cRegister = 0x01;
		break;
	default:
		cRegister = 0x02;
	}
//---Sensorwerte-anfordern
	wiringPiI2CWriteReg8(i2cID, 0x81, cRegister);		// Auflösung einstellen
}
//---Sensorwerte holen--------------------------------------------------
int sensor_lux::getAmbient()
{
	int iLuxHigh =  wiringPiI2CReadReg8(i2cID, 0x8c);
	int iLuxLow =  wiringPiI2CReadReg8(i2cID, 0x8d);
	LOG(info, "Amb High: " << iLuxHigh << ", Low: " << iLuxLow);
	
	return (iLuxHigh < 0 || iLuxLow < 0)? -1: (iLuxHigh * 256) + iLuxLow ;
}

int sensor_lux::getIR()
{
	int iIRHigh =  wiringPiI2CReadReg8(i2cID, 0x8e);
	int iIRLow =  wiringPiI2CReadReg8(i2cID, 0x8f);
	LOG(info, "IR High: " << iIRHigh << ", Low: " << iIRLow);
	
	return (iIRHigh < 0 || iIRLow < 0)? -1 : (iIRHigh * 256) + iIRLow;
}

//---Lux-Berechnung-----------------------------------------------------
float sensor_lux::getLux()
{
	int iIR			= getIR();				//führt getIR aus
	int iLux		= getAmbient();			//führt getAmbient aus
	float iValue	= iIR / float(iLux);
	float iValueFin;
	
	//Berechnung lt. Datenblatt TSL2561T
	if (iValue > 0 && iValue <= 0.50)
		iValueFin = 0.0304	* iLux	- 0.062		* iLux * pow(iValue, 1.4);
	else if (iValue > 0.50 && iValue <= 0.61)
		iValueFin = 0.0224	* iLux	- 0.031		* iIR;
	else if (iValue > 0.61 && iValue <= 0.80)
		iValueFin = 0.0128	* iLux	- 0.0153	* iIR;
	else if (iValue > 0.80 && iValue <= 1.3)
		iValueFin = 0.00146 * iLux	- 0.00112	* iIR;
	else
		iValueFin = 0; 
	LOG(info, "iLux: " << iLux << ", iIR: " << iIR);
	LOG(info, "iValue: " << iValue);
	
	return iValueFin;
}