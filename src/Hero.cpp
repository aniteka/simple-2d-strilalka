#include "Hero.hpp"




void Hero::addCollisionObject(sf::RectangleShape* sh)
{
	collisions.push_back(sh);
}

void Hero::move(const sf::Point& p)
{
	for(auto& i : collisions)
		i->move(p.x, p.y);
	texture_rect.move(p.x, p.y);
	warp_point = {
		.x = warp_point.x + p.x,
		.y = warp_point.y + p.y
	};
}

void Hero::setPoint(const sf::Point& p)
{
	warp_point = p;
}


void Hero::setTextureRect(const sf::IntRect& ir)
{
	texture_rect.setTextureRect(ir);
}


void Hero::setTexture(sf::Texture& tx)
{
	texture_rect.setTexture(&tx);
}


const std::vector<sf::RectangleShape*>& Hero::getCollisionObject() const 
{
	return collisions;
}

sf::Point Hero::getPoint() const
{
	return warp_point;
}

sf::IntRect Hero::getTextureRect() const
{
	return texture_rect.getTextureRect();
}

Hero::~Hero()
{
	for(auto i : collisions)
	{
		delete i;
	}
	DLOG("Hero status: DESTROY")
}

