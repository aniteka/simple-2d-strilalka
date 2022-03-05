#include "Hero.hpp"

Hero::Hero()
	: Unit()
	, collisions{}
	, texture_rect(sf::Vector2f(10, 10))
	, warp_point{ 0,0 }
{
	texture_rect.setFillColor(sf::Color(0, 0, 0, 255));
	category = "Hero";
	status.is_drawable = true;

	DLOG("Hero status: CREATED");
}

Hero::~Hero()
{
	for(auto i : collisions)
		delete i;
	delete texture_rect.getTexture();
	DLOG("Hero status: DESTROY");
}



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

void Hero::setSize(const sf::Vector2f& size)
{
	texture_rect.setSize(size);
}


void Hero::setTexture(sf::Texture* tx)
{
	texture_rect.setFillColor(sf::Color::White);
	texture_rect.setTexture(tx, true);
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

void Hero::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(!status.is_drawable)
	{
		DLOG("HERO WITH CATEGORY \"%s\" ISN'T DRAWABLE", category.c_str());
		throw "ISN'T DRAWABLE";
	}
		
	target.draw(texture_rect, states);
}

