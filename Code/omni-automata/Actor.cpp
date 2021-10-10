// @file           actor.cpp
// @author         flow@p0cki.net
// @date           01.2017
// @brief          baseclass of all actors

#include "Actor.h"

Actor::Actor(actor_type t, actor_subtype s, char n[], actor_pins p)
	: type_(t), subtype_(s), actor_pin_(p), name_(n), id_(current_id++), event()
{
}

Actor::Actor(actor_type t, actor_subtype s, char n[], const unsigned short p1)
	: type_(t), subtype_(s), name_(n), id_(current_id++), event()
{
	actor_pin_.eins.pin1 = p1;
}

Actor::Actor(actor_type t, actor_subtype s, char n[], const unsigned short p1, const unsigned short p2)
	: type_(t), subtype_(s), actor_pin_(), name_(n), id_(current_id++), event()
{
	actor_pin_.zwei.pin1 = p1;
	actor_pin_.zwei.pin2 = p2;
}

Actor::Actor(actor_type t, actor_subtype s, char n[], const unsigned short p1, const unsigned short p2, const unsigned short p3)
	: type_(t), subtype_(s), actor_pin_(), name_(n), id_(current_id++), event()
{
	actor_pin_.drei.pin1 = p1;
	actor_pin_.drei.pin2 = p2;
	actor_pin_.drei.pin3 = p3;
}

Actor::~Actor()
= default;
