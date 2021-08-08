
// @file           home_doggle.cpp
// @author         flow@p0cki.at
// @date           12.2016
// @brief          flip a Value

#include "Doggle.h"

int Doggle::flip_ = false;
int Doggle::flop_ = false;

Doggle::Doggle()
{
	return_value_ = false;
}

Doggle::~Doggle()
{

}

int Doggle::flip(int iValue)
{

	//********************** routine ************************
	if (iValue == HIGH)
	{
		if (!flop_)
		{
			flop_ = true;
			flip_ = !flip_;

			if (flip_)
			{
				return_value_ = true;
			}
			else
			{
				return_value_ = false;
			}
		}
	}
	else
	{
		flop_ = false;
	}
	return return_value_;
}