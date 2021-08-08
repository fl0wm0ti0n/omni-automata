// @file           actor.cpp
// @author         flow@p0cki.net
// @date           01.2017
// @brief          baseclass of all actors

#include "Actor.h"

Actor::Actor(actor_type t, char n[], int p)
	:type_(t), name_(n), value_(0), pin1_(p)
{
	pinMode(pin1_, OUTPUT);
}

Actor::Actor(actor_type t, char n[], int p1, int p2, int p3)
	: type_(t), name_(n), value_(0), pin1_(p1), pin2_(p2), pin3_(p3)
{
	pinMode(pin1_, OUTPUT);
	pinMode(pin2_, OUTPUT);
	pinMode(pin3_, OUTPUT);
}

Actor::~Actor()
{

}

bool Actor::setValue(int v)
{
	value_ = v;
	return true;
}