// Motionsensor_one.h

#ifndef _DIRECTIONENCODER_h
#define _DIRECTIONENCODER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "Sensor.h"
#include "logger.h"

class DirectionEncoder final : public Sensor
{
private:
	int		encoder_pos_count_ = 0;
	byte	old_clk_val_;
	byte	clk_val_;
	bool	bCW_			= false;
	bool	switch_state_	= false;
	bool	doggle_state_	= false;
	int		turn_			= 0;
	byte	old_turn_		= 0;
	float	clicks_			= 0.5;
	bool	switch_state2_	= false;
	bool	switch_value_	= 0;
	logger* logger_g_;

public:
	DirectionEncoder(char n[], unsigned short pSW, unsigned short pCLK, unsigned short pDT);
	~DirectionEncoder();
	int getEncoderValue();			// Method: get encoder Value
	bool getValue();				// Method: get switch Value
	bool getSwitchValueDoggle();
	bool getSwitchLongValue();

	void setClickValue(float clicks)
	{
		clicks_ = clicks;
	}
};
#endif