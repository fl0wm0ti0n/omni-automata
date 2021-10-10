#ifndef _HOME_DOUT_h
#define _HOME_DOUT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Actor.h"
#include "logger.h"

class DigitalOut:public Actor
{
	logger* logger_g_;
	
public:
	 DigitalOut(char n[], unsigned short p);
	 virtual ~DigitalOut();
	 bool	doggle();

	 /*common functions*/
	 bool	fireEvent()						override;
	 bool	setEvent(actor_event newevent)	override;
	 //bool	setEvent(float value)			override { return false; }
	 bool	setEvent(int value)				override;
};

#endif

