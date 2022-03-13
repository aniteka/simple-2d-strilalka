#pragma once
#include "defines.h"


class Unit
	: public sf::Drawable
{
protected:
	struct Status
	{
		bool is_physics;
		bool is_interrupted;
		bool is_drawable;
		bool is_nstatic;
	} status;

	std::string category;
	std::vector<std::string> interrupt_this;
	std::vector<std::string> block_this;
public:
	Unit();
	virtual ~Unit() {}

	void setPhysicsStatus(bool stat)
	{
		status.is_physics = stat;
	}
	void setInterruptStatus(bool stat)
	{
		status.is_interrupted = stat;
	}
	void setDrawStatus(bool stat)
	{
		status.is_drawable = stat;
	}
	void setNoStaticStatus(bool stat)
	{
		status.is_nstatic = stat;
	}
	void setCategory(const std::string& ctg)
	{
		category = ctg;
	}
	
	Status getStatus() const
	{
		return status;
	}
	std::string getCategory() const
	{
		return category;
	}

	virtual void collisision(sf::RectangleShape* to, sf::RectangleShape* from) = 0;

	virtual void addCollisionObject(sf::RectangleShape* sh) = 0;
	virtual void move(const sf::Point& p) = 0;
	virtual void setPoint(const sf::Point& p) = 0;
	virtual void setTextureRect(const sf::IntRect& ir) = 0;
	virtual void setSize(const sf::Vector2f&) = 0;
	virtual void setTexture(sf::Texture* tx) = 0;
	virtual void update() = 0;

	virtual const std::vector<sf::RectangleShape*>& getCollisionObject() const = 0;
	virtual sf::Point getPoint() const = 0;
	virtual sf::IntRect getTextureRect() const = 0;
};

