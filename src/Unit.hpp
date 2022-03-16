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

	b2Body* main_body;

	sf::Texture* main_texture;
	sf::FloatRect main_rect_texture;

	std::vector<b2Fixture*> main_collisions;

	sf::Vector2f main_size_body;

public:
	Unit(b2Body*& body);
	virtual ~Unit()
	{
		delete main_texture;
	}

	//TODO
	// Немає опису робот функцій, стан фізики і статики не робочий
	// Невистачає функцій роботи з фізикою
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
	Status getStatus() const
	{
		return status;
	}

	void setPhysicsBodyUserData(const std::string& str)
	{
		main_body->SetUserData((void*)str.c_str());
	}
	const std::string& setPhysicsBodyUserData()
	{
		return std::string((char*)main_body->GetUserData().pointer);
	}
	
	void addCollisionObject(const b2FixtureDef* b2fd)
	{
		main_collisions.push_back(
			main_body->CreateFixture(b2fd)
		);
	}
	const std::vector<b2Fixture*>& getCollisionObject() const
	{
		return main_collisions;
	}

	void setTexture( sf::Texture* texture )
	{
		main_texture = texture;
	}
	const sf::Texture* getTexture() const
	{
		return main_texture;
	}

	void setRectTexture( const sf::FloatRect& rect )
	{
		main_rect_texture = rect;
	}
	const sf::FloatRect& getRectTexture()
	{
		return main_rect_texture;
	}

	void setMainSizeBody( const sf::Vector2f& size )
	{
		main_size_body = size;
	}
	const sf::Vector2f& getMainSizeBody()
	{
		return main_size_body;
	}
	
	b2Body* getMainBody() const
	{
		return main_body;
	}

	virtual void updateEveryFrame() = 0;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		if (!this->status.is_drawable)
			return;
		sf::RectangleShape draw_rect(main_size_body);
		draw_rect.setPosition
		(
			main_body->GetPosition().x,
			main_body->GetPosition().y
		);
		target.draw(draw_rect, states);
	}
};

