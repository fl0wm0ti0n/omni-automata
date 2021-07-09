// @file           actor.h
// @author         flow@p0cki.net
// @date           01.2017
// @brief          baseclass of all actors

#ifndef _ACTOR_h
#define _ACTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

enum t_actor_type
{
	undefined_act = 0,
	digitalOut_act = 1,
	analogOut_act = 2,
	I2C_act = 3,
	WS2812_act = 4,
	PWM_act = 5,
	RGB_act = 6
};

class actor
{

private:
	t_actor_type m_iType;
	String m_cName;
	int m_iValue;
	int m_iPin;

 public:
	 actor(t_actor_type t, String n, int p);
	 virtual ~actor();

	 t_actor_type getType()
		{return m_iType;}
	 
	 String getName()
		{return m_cName;}
	 
	 int getValue()
		{return m_iValue;}

	 int getPin()
		{ return m_iPin;}

	 int setPin(int p)
	 {
		 m_iPin = p;
		 pinMode(m_iPin, OUTPUT);
		 return true;
	 }
	
	 virtual bool setValue(int v);
};
#endif