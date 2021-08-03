// @file           actor.h
// @author         flow@p0cki.net
// @date           01.2017
// @brief          baseclass of all actors

#ifndef _DECISION_h
#define _DECISION_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "logger.h"

enum decision_type
{
	undefined		= 0,
	lightOn			= 1,
	servoOn 		= 2,
	colorChange		= 3,
	toEffect		= 4
};

class Decisions
{

private:

	decision_type	type_;
	char*			name_;
	logger*			logger_g_;

	// Variablen für Lichtklassen
	int lightcounter_ = 0;
	int lightdoggle_ = 0;
	int lightswitch_ = 0;
	
	// Temp Color
	int colorium_ = 0;

public:
	Decisions(decision_type t, char n[]);
	virtual ~Decisions();

	int color_temperatur_change(float temp, float hum);
	void licht_komplett_schalten_sobald_impuls(bool o_sensor, int o_actor);
	int licht_an_solange_input_impuls_an(bool o_sensor);
	int licht_an_solange_input_impuls_an_aus_erlaubt_nach255(bool o_sensor, int o_actor);

	decision_type getType()
	{
		return type_;
	}

	char* getName()
	{
		return name_;
	}
};
#endif