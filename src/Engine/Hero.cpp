#include "Hero.hpp"

Hero::Hero(sf::Vector2f collision_oval, b2Body*& body)
	: Unit(body)
	, jump_impulse(10.f)
{
	this->status = {
		.is_physics = true,
		.is_interrupted = true,
		.is_drawable = true,
		.is_static = false
	};

}


