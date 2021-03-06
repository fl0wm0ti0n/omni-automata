#include "DirectionEncoder.h"

DirectionEncoder::DirectionEncoder(char n[], unsigned short pSW, unsigned short pCLK, unsigned short pDT)
	:Sensor(SENSOR_TYP_DIGITAL_IN, SENSOR_SUB_MANUALLY, n, sensor_pin_)
{
#ifdef DEBUG
	static char* const buffer PROGMEM = "Logging1";
	logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
#endif

	Sensor::sensor_pin_.drei.pin1 = pSW;
	Sensor::sensor_pin_.drei.pin2 = pCLK;
	Sensor::sensor_pin_.drei.pin3 = pSW;

	old_clk_val_ = digitalRead(sensor_pin_.drei.pin2);
}

DirectionEncoder::~DirectionEncoder()
= default;

int DirectionEncoder::getEncoderValue()
{
#ifdef DEBUG
	static const char* const buffer PROGMEM = "Call - GetEncoder";
	logger_g_->LnWriteLog(buffer, extremedebug);
#endif
	clk_val_ = digitalRead(getPin().drei.pin2);
	if (clk_val_ != old_clk_val_) { // Means the knob is rotating
	  // if the knob is rotating, we need to determine direction
	  // We do that by reading pin B.

		if (digitalRead(getPin().drei.pin1) != clk_val_) {  // Means pin A Changed first - We're Rotating Clockwise
			encoder_pos_count_ = encoder_pos_count_ + clicks_;
			bCW_ = true;
		}
		else {// Otherwise B changed first and we're moving CCW
			bCW_ = false;
			encoder_pos_count_ = encoder_pos_count_ - clicks_;
		}
#ifdef DEBUG
		static const char* const buffer PROGMEM = "Rotated ";
		logger_g_->LnWriteLog(buffer, extremedebug);
#endif

		
		if (bCW_) {
#ifdef DEBUG
			static const char* const buffer PROGMEM = "counterclockwise: ";
			logger_g_->LnWriteLog(buffer, extremedebug);
#endif

			turn_ = -1;
			if (old_turn_ == turn_)
			{
				turn_ = 0;
			}
		}
		else {
#ifdef DEBUG
			static const char* const buffer PROGMEM = "clockwise: ";
			logger_g_->LnWriteLog(buffer, extremedebug);
#endif

			turn_ = 1;
			if (old_turn_ == turn_)
			{
				turn_ = 0;
			}
		}
#ifdef DEBUG
		static const char* const buffer1 PROGMEM = "Encoder Position: ";
		logger_g_->LnWriteLog(buffer1, sensordata);
		logger_g_->WriteLog(encoderPosCount_, sensordata);
		static const char* const buffer2 PROGMEM = "Encoder return: ";
		logger_g_->LnWriteLog(buffer2, sensordata);
		logger_g_->WriteLog(turn_, sensordata);
#endif

	}
	else
	{
		turn_ = 0;
	}
	old_clk_val_ = clk_val_;
	old_turn_ = turn_;
	return  turn_;
}

bool DirectionEncoder::getValue()
{
#ifdef DEBUG
	static const char* const buffer PROGMEM = "Call - EnSwitch";
	logger_g_->LnWriteLog(buffer, extremedebug);
#endif

	if (digitalRead(getPin().drei.pin3) == HIGH)
	{
#ifdef DEBUG
		static const char* const buffer PROGMEM = "Switch: is true";
		logger_g_->LnWriteLog(buffer, sensordata);
#endif

		switch_state_ = true;
	}
	else
	{
#ifdef DEBUG
		static const char* const buffer PROGMEM = "Switch: is false";
		logger_g_->LnWriteLog(buffer, sensordata);
#endif

		switch_state_ = false;
	}
	return switch_state_;
}

bool DirectionEncoder::getSwitchValueDoggle()
{
#ifdef DEBUG
	static const char* const buffer PROGMEM = "Call - EnSwitchDoggle";
	logger_g_->LnWriteLog(buffer, extremedebug);
#endif

	if (digitalRead(getPin().drei.pin3))
	{
		doggle_state_ = !doggle_state_;
#ifdef DEBUG
		static const char* const buffer PROGMEM = "Doggled";
		logger_g_->LnWriteLog(buffer, sensordata);
#endif

	}
	return doggle_state_;
}

bool DirectionEncoder::getSwitchLongValue()
{
#ifdef DEBUG
	static const char* const buffer PROGMEM = "Call - getSwitchLongValue";
	logger_g_->LnWriteLog(buffer, extremedebug);
#endif


	if (digitalRead(getPin().drei.pin3) == LOW && switch_state2_ != false)
	{
		switch_state2_ = false;
		switch_value_ = true;
#ifdef DEBUG
		static const char* const buffer PROGMEM = "Switch is true";
		logger_g_->LnWriteLog(buffer, sensordata);
#endif
	}

	if (digitalRead(getPin().drei.pin3) == HIGH && switch_state2_ != true)
	{
		switch_state2_ = true;
		switch_value_ = false;
#ifdef DEBUG
		static const char* const buffer PROGMEM = "Switch is false";
		logger_g_->LnWriteLog(buffer, sensordata);
#endif
	}
	return switch_value_;
}