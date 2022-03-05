#pragma once
#include "defines.h"
#include "Unit.hpp"


class Hero
	: public Unit
{
	std::vector<sf::Shape*> collisions;
	sf::RectangleShape texture_rect;
	sf::Point warp_point;

public:
	Hero()
		: Unit()
		, texture_rect(sf::Vector2f(10,10))
		, warp_point{0,0} 
	{
		
	}


	void addCollisionObject(sf::Shape* sh) override;
	void move(const sf::Point& p) override;
	void setPoint(const sf::Point& p) override;
	void setTextureRect(const sf::IntRect& ir) override;
	void setTexture(sf::Texture& tx) override;

	sf::Point getPoint() const override;
	sf::IntRect getTextureRect() const override;
};
