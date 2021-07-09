
// 
// 
// 

#include "digitalOut.h"

digitalOut::digitalOut(String n, int p)
	:actor(digitalOut_act, n, p)
{
	actor::setValue(digitalRead(p));
}

digitalOut::~digitalOut()
{
}

bool digitalOut::setValue(int v)
{
	//Serial.begin(9600);
	if (getValue() != v)
	{
		//Serial.println("setValue");
		actor::setValue(v);
		digitalWrite(getPin(),v);
	}
	return true;
}

bool digitalOut::doggle()
{
	return setValue(!getValue());
}