// @file           touchSensor.h
// @author         flow@p0cki.at
// @date           11.2016
// @brief          touch sensor Values

#ifndef _HOME_TOUCH_h
#define _HOME_TOUCH_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "sensor.h"
#include "constants.h"



// Schalter ob Boolean oder Analog zurückgegeben wird.
enum t_analog_or_bool
{
	analogReturn = 0,
	booleanReturn = 1,

};

class touchSensor :public sensor
{
	private:
		int		iDigitalValue = 0;
		float	fAnalogValue = 0;
		bool	bTouchState = false;
		float	fThreshold = DEFAULT_THRESHOLD;

	public:
				touchSensor(String n, int p);												// Constructor
		virtual ~touchSensor();																// Destructor

		float	getAnalog(t_analog_or_bool tswitch, logger &logging_one);					// Method: get Touch Analog Value - Gibt True/False oder einen analogen Wert zurück
		float	getAnalogWithDoggle(t_analog_or_bool tswitch, logger &logging_one);		// Method: get Touch Analog Value - Gibt True/False oder einen analogen Wert zurück, aber immer gedoggelt.
		bool	getState(logger &logging_one);											// Method: get Touch Value - Gibt True oder False zurück
		bool	getStateWithDoggle(logger &logging_one);									// Method: get Touch Value - Gibt True oder False zurück, aber immer gedoggelt.
		void	setAnalogTreshold(float threshold, logger &logging_one);					// Method: set Analog Treshold - Setzt den Grenzwert ab wann Analog als True gewertet wird.
		float	getAnalogTreshold(logger &logging_one)									// Method: get Analog Treshold - Liest den Grenzwert aus.
		{
			logging_one.writeLog("Call - touch - getAnalogTreshold", extremedebug);
			return fThreshold;
		};
};
#endif