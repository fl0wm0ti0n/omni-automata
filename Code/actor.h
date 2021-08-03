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

enum actor_type
{
	undefined_act = 0,
	digitalOut_act = 1,
	analogOut_act = 2,
	I2C_act = 3,
	WS2812_act = 4,
	PWM_act = 5,
	RGB_act = 6
};

class Actor
{

private:
	actor_type type_;
	char* name_;

 public:
	 Actor(actor_type t, char n[], int p);
	 Actor(actor_type t, char n[], int p1, int p2, int p3);
	 virtual ~Actor();

	 actor_type getType()
		{return type_;}
	 
	 char* getName()
		{return name_;}
	 
	 int getValue()
		{return value_;}

	 int getPin()
		{ return pin1_;}

	 int setPin(int p)
	 {
		 pin1_ = p;
		 pinMode(pin1_, OUTPUT);
		 return true;
	 }
	
	 virtual bool setValue(int v);

protected:
		int value_;
		int pin1_;
		int	pin2_;
		int	pin3_;

};
#endif