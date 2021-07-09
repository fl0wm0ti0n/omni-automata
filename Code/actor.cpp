// @file           actor.cpp
// @author         flow@p0cki.net
// @date           01.2017
// @brief          baseclass of all actors

#include "actor.h"

actor::actor(t_actor_type t, String n, int p)
	:m_iType(t), m_cName(n), m_iValue(0), m_iPin(p)
{
	pinMode(m_iPin, OUTPUT);
}

actor::~actor()
{

}

bool actor::setValue(int v)
{
	m_iValue = v;
	return true;
}