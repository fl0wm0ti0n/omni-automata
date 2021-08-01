#pragma once
#ifndef _DIGITALIN_h
#define _DIGITALIN_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "logger.h"
#include "Sensor.h"
#include <Bounce2.h>

class DigitalIn final :public Sensor
{
private:
	bool	b_switch_state_ = false;
	logger* logger_g_;
	Bounce input_;
	
public:
	DigitalIn(char n[], unsigned short p);
	~DigitalIn();
	bool getFell();
	bool getRose();
	bool getChanged();
	virtual bool getValue();
	virtual bool setPin(unsigned short p);
	void update_debounce();
	void set_debounce_interval(unsigned short interval);
};
#endif