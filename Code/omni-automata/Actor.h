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

#include "IActor.h"

class Actor : public IActor
{

protected:
	actor_type				type_;
	actor_subtype			subtype_;
	actor_pins				actor_pin_;
	//actor_pin_values		actor_pin_values_;
	char*					name_;
	int						id_;					// instance id
	static int				current_id;				// static for sensor id shared between all instances
	union value
	{
		float				float_;
		int					int_;
	} value_;

	//virtual bool			setValue(int v)		{ return true; }
	//virtual bool			setValue(float v)	{ return true; }
	//virtual bool			setValue(bool v)	{ return true; }
	//virtual void			getValue(int& v)	{ }
	//virtual void			getValue(float& v)	{ }
	//virtual void			getValue(bool& v)	{ }

public:
	Actor(actor_type t, actor_subtype s, char n[], actor_pins p);
	Actor(actor_type t, actor_subtype s, char n[], unsigned short p1);
	Actor(actor_type t, actor_subtype s, char n[], unsigned short p1, unsigned short p2);
	Actor(actor_type t, actor_subtype s, char n[], unsigned short p1, unsigned short p2, unsigned short p3);
	
	virtual	~Actor();
			actor_event		event;
	virtual actor_type		getType()							override {return type_;}
	virtual actor_subtype	getSubtype()						override {return subtype_;}
	virtual char*			getName()							override {return name_;}
	virtual actor_pins		getPin()							override {return actor_pin_;}
	virtual actor_event		getEvent()							override {return event;}
	virtual bool			fireEvent()							override {return true;}
	virtual bool			setEvent(actor_event actor_event)	override {event = actor_event; return true;}
	virtual bool			setEvent(int value) 				override {value_.int_ = value;  return true; }
	virtual bool			setEvent(float value) 				override {value_.float_ = value; return true;}
	virtual bool			setPin(actor_pins p)				override
	{
		actor_pin_ = p;
		if (actor_pin_.eins.pin1)
		{
			pinMode(actor_pin_.eins.pin1, OUTPUT);
			return true;
		}
		if (actor_pin_.zwei.pin1 && actor_pin_.zwei.pin2)
		{
			pinMode(actor_pin_.zwei.pin1, OUTPUT);
			pinMode(actor_pin_.zwei.pin2, OUTPUT);
			return true;
		}
		if (actor_pin_.drei.pin1 && actor_pin_.drei.pin2 && actor_pin_.drei.pin3)
		{
			pinMode(actor_pin_.drei.pin1, OUTPUT);
			pinMode(actor_pin_.drei.pin2, OUTPUT);
			pinMode(actor_pin_.drei.pin3, OUTPUT);
			return true;
		}
		return false;
	}
};
#endif