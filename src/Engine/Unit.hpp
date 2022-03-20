#pragma once
#include "defines.h"

#include "Components/mass_data.hpp"


class Unit
	: public sf::Drawable
{
public:
	struct RectAndFrames
	{
		sf::IntRect rect;
		size_t frames;
	};
protected:
	using StatesAndRectsOfTexture
		= std::map<std::string, RectAndFrames>;
	struct Status
	{
		bool is_physics;
		bool is_interrupted;
		bool is_drawable;
		bool is_static;
	} status;

	b2Body* main_body;

	sf::Texture* main_texture;
	StatesAndRectsOfTexture main_states_and_rects_of_texture;
	std::string main_state_of_texture;
	
	std::vector<b2Fixture*> main_collisions;

	sf::Vector2f main_size_body;

public:
	Unit(b2Body*& body);
	Unit(const Unit& unit);
	Unit(Unit&& unit);
	virtual ~Unit() override;

	Unit& operator=(const Unit& unit);
	Unit& operator=(Unit&& unit);
	
	void setPhysicsStatus(bool stat);
	void setInterruptStatus(bool stat);	// TODO
	void setDrawStatus(bool stat);
	void setStaticStatus(bool stat);
	Status getStatus() const;

	// Don't working. WTFFFFFFFFFFFFF
	void setPhysicsBodyUserData(const std::string& str);
	const std::string& setPhysicsBodyUserData();
	
	void addCollisionObject(const b2FixtureDef* b2fd);
	const std::vector<b2Fixture*>& getCollisionObject() const;

	void setTexture( sf::Texture* texture );
	const sf::Texture* getTexture() const;

	void addStateAndRectOfTexture(std::string state, RectAndFrames rect_and_frames);
	void delStateAndRectOfTexture(std::string state);
	const StatesAndRectsOfTexture&
		getStatesAndRectsOfTexture() const;
	RectAndFrames getRectOfTexture(std::string state);

	void setStateOfTexture(std::string state);
	const std::string& getStateOfTexture() const;
	
	sf::Vector2f getPosition();

	float getRotation();

	void setMass(float mass, const sf::Vector2f& point);
	void setMassToCenter(float mass);
	float getMass();
	MassData getMassData();

	void addImpulse(sf::Vector2f impulse, sf::Vector2f point);
	void addImpulseToCenter(sf::Vector2f impulse);
	void addForce(sf::Vector2f force, sf::Vector2f point);
	void addForceToCenter(sf::Vector2f force);

	void setLinearSpeed(const sf::Vector2f& vec);
	sf::Vector2f getLinearSpeed() const;
	void setAngularSpeed(float speed);
	float getAngularSpeed();
	
	void setMainSizeBody( const sf::Vector2f& size );
	const sf::Vector2f& getMainSizeBody() const;
	
	b2Body* getMainBody() const;

	virtual void updateEveryFrame();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

