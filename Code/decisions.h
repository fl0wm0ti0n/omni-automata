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

enum t_decision_type
{
	undefined		= 0,
	lightOn			= 1,
	servoOn 		= 2,
	colorChange		= 3,
	toEffect		= 4
};

class decisions
{

private:

	t_decision_type	m_iType;
	String m_cName;

	// Variablen für Lichtklassen
	int lightcounter = 0;

	// Temp Color
	int colorium = 0;

public:
	decisions(t_decision_type t, String n);
	virtual ~decisions();

	int colorTemperaturChange(float temp, float hum, logger &log);
	int LichtKomplettSchalten_SobaldImpuls(bool o_sensor, int o_actor, logger &log);
	int lichtAnSolangeInputImpulsAn(bool o_sensor, logger &log);
	int LichtAnSolangeInputImpulsAn_AusErlaubtNach255(bool o_sensor, int o_actor, logger &log);

	t_decision_type getType()
	{
		return m_iType;
	}

	String getName()
	{
		return m_cName;
	}
};
#endif