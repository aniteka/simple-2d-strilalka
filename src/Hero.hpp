#pragma once
#include "defines.h"
#include "Unit.hpp"


class Hero
	: public Unit
	, public sf::Drawable
{
	std::vector<sf::RectangleShape*> collisions;
	sf::RectangleShape texture_rect;
	sf::Point warp_point;

public:
	Hero();
	~Hero() override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
	void addCollisionObject(sf::RectangleShape* sh) override;
	void move(const sf::Point& p) override;
	void setPoint(const sf::Point& p) override;
	void setTextureRect(const sf::IntRect& ir) override;
	void setTexture(sf::Texture* tx) override;
	void setSize(const sf::Vector2f&) override;

	const std::vector<sf::RectangleShape*>& getCollisionObject() const override;
	sf::Point getPoint() const override;
	sf::IntRect getTextureRect() const override;
};
