// Motionsensor_one.h

#ifndef _DIRECTIONENCODER_h
#define _DIRECTIONENCODER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "sensor.h"
#include "logger.h"

class directionEncoder : public sensor
{
private:

	int		pinCLK_;	// Connected to CLK on KY-040
	int		pinDT_;		// Connected to DT on KY-040
	int		pinSW_;		// Connected to DT on KY-040
	double	encoderPosCount_ = 0;
	int		oldCLKVal_;
	int		CLKVal_;
	bool	bCW_			= false;
	bool	bSwitchState_	= false;
	bool	bdoggleState_	= false;
	int		turn_			= 0;
	int		oldTurn_		= 0;
	double	clicks_			= 0.5;
	int		iSwitchState_	= 0;
	bool	iSwitchValue_	= 0;

public:
	directionEncoder(String n, int pSW, int pCLK, int pDT);
	virtual ~directionEncoder();
	int getEncoderValue(logger &log);		// Method: get encoder Value
	bool getSwitchValue(logger &log);		// Method: get switch Value
	bool getSwitchValueDoggle(logger& log);
	bool getSwitchLongValue(logger& log);

	void setClickValue(double clicks, logger &log)
	{
		clicks_ = clicks;
	}
};
#endif