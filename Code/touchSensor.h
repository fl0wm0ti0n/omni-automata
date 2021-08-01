// @file           touchSensor.h
// @author         flow@p0cki.at
// @date           11.2016
// @brief          touch Sensor Values

#ifndef _HOME_TOUCH_h
#define _HOME_TOUCH_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Sensor.h"
#include "constants.h"



// Schalter ob Boolean oder Analog zurückgegeben wird.
enum t_analog_or_bool
{
	analogReturn = 0,
	booleanReturn = 1,

};

class TouchSensor : public Sensor
{
	private:
		int		digital_value_ = 0;
		float	analog_value_ = 0;
		bool	touch_state_ = false;
		float	threshold_ = DEFAULT_THRESHOLD;
		logger* logger_g_;
	
	public:
				TouchSensor(char n[], int p);						// Constructor
		virtual ~TouchSensor();										// Destructor

		float	getAnalog(t_analog_or_bool tswitch);				// Method: get Touch Analog Value - Gibt True/False oder einen analogen Wert zurück
		float	getAnalogWithDoggle(t_analog_or_bool tswitch);		// Method: get Touch Analog Value - Gibt True/False oder einen analogen Wert zurück, aber immer gedoggelt.
		bool	getState();											// Method: get Touch Value - Gibt True oder False zurück
		bool	getStateWithDoggle();								// Method: get Touch Value - Gibt True oder False zurück, aber immer gedoggelt.
		void	setAnalogTreshold(float threshold);					// Method: set Analog Treshold - Setzt den Grenzwert ab wann Analog als True gewertet wird.
		float	getAnalogTreshold()									// Method: get Analog Treshold - Liest den Grenzwert aus.
		{
			logging_one.writeLog("Call - touch - getAnalogTreshold", extremedebug);
			return threshold_;
		};
};
#endif