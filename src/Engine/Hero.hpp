#pragma once
#include "defines.h"

#include "Unit.hpp"



class Hero
	: public Unit
{
protected:
	float jump_impulse;

public:
	Hero(sf::Vector2f collision_oval, b2Body*& body);
	
};
