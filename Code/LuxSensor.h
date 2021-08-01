/*
 * @file           sensor_lux.h
 * @author         flow@p0cki.at
 * @date           04.2016
 * @brief          Sensor to measure Lux with the TSL2561.
 */

#include <iostream>
#include <stdlib.h>

/*@param iOption: Sensor-Resolution Option
 *@param cAddress: i2c-Address from the Sensor (0x29, 0x39, 0x49)
 */
class sensor_lux
{
public:
	sensor_lux(int iOption, char cAddress); // Constructor
	virtual ~sensor_lux();					// Destructor
		
	void setResolution(int iOption);		// Method: set Sensor Resolution
	int getAmbient();						// Method: get Sensor Ambient
	int getIR();							// Method: get Sensor IR
	float getLux();							// Method: get Lux out of Sensor Data
	
//-------------------------------------------------------------------------------	
private:
	int i2cID;								// i2c Idendifier
};