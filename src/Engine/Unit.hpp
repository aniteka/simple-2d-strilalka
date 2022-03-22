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
	using StatesAndRectsOfTexture
		= std::map<std::string, RectAndFrames>;
	struct Status
	{
		bool is_physics;
		bool is_interrupted;
		bool is_drawable;
		bool is_static;
	};
protected:
	
	Status status;

	b2Body* main_body;

	sf::Texture* main_texture;
	StatesAndRectsOfTexture main_states_and_rects_of_texture;
	std::string main_state_of_texture;
	
	std::vector<b2Fixture*> main_collisions;

	sf::Vector2f main_size_body;

public:
	Unit(b2Body* body);
	Unit(const Unit& unit);
	Unit(Unit&& unit);
	virtual ~Unit() override;

	// Do not use it
	Unit& operator=(const Unit& unit);	
	// Do not use it
	Unit& operator=(Unit&& unit);
	
	virtual void setPhysicsStatus(bool stat);
	virtual void setInterruptStatus(bool stat);	// TODO
	virtual void setDrawStatus(bool stat);
	virtual void setStaticStatus(bool stat);
	virtual Status getStatus() const;

	// Do not use it
	virtual void setPhysicsBodyUserData(const std::string& str);
	// Do not use it
	virtual const std::string& setPhysicsBodyUserData();
	
	virtual void addCollisionObject(const b2FixtureDef* b2fd);
	virtual const std::vector<b2Fixture*>& getCollisionObject() const;

	virtual void setTexture( sf::Texture* texture );
	virtual const sf::Texture* getTexture() const;

	virtual void addStateAndRectOfTexture(std::string state, RectAndFrames rect_and_frames);
	virtual void delStateAndRectOfTexture(std::string state);
	virtual const StatesAndRectsOfTexture&
		getStatesAndRectsOfTexture() const;
	virtual RectAndFrames getRectOfTexture(std::string state);

	virtual void setStateOfTexture(std::string state);
	virtual const std::string& getStateOfTexture() const;
	
	virtual sf::Vector2f getPosition();

	virtual float getRotation();

	virtual void setMass(float mass, const sf::Vector2f& point);
	virtual void setMassToCenter(float mass);
	virtual float getMass();
	virtual MassData getMassData();

	virtual void addImpulse(sf::Vector2f impulse, sf::Vector2f point);
	virtual void addImpulseToCenter(sf::Vector2f impulse);
	virtual void addForce(sf::Vector2f force, sf::Vector2f point);
	virtual void addForceToCenter(sf::Vector2f force);

	virtual void setLinearDamping(float damping);
	virtual float getLinearDamping() const;
	virtual void setAngularDamping(float damping);
	virtual float getAngularDamping() const;
	
	virtual void setLinearSpeed(const sf::Vector2f& vec);
	virtual sf::Vector2f getLinearSpeed() const;
	virtual void setAngularSpeed(float speed);
	virtual float getAngularSpeed();
	
	virtual void setMainSizeBody( const sf::Vector2f& size );
	virtual const sf::Vector2f& getMainSizeBody() const;
	
	virtual b2Body* getMainBody() const;

	virtual void updateEveryFrame();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};



template<class _MainUnit = Unit>
struct UnitCreator
{
	Unit::Status status;

	sf::Vector2f start_linear_speed;
	float start_angular_speed;
	float start_linear_damping;
	float start_angular_damping;
	float start_angle;
	sf::Vector2f start_position;
	
	bool is_fixed;
	bool is_bullet;

	float mass;

	sf::Texture* texture;
	Unit::StatesAndRectsOfTexture states_and_texture_rects;
	std::string start_state;
	
	sf::Vector2f size_of_visible_texture;
private:
	std::vector<b2FixtureDef> main_collisions;
	b2World* main_world;

public:
	UnitCreator(b2World* world)
		: main_world(world)
		, status{
			.is_physics = false,
			.is_interrupted = false,
			.is_drawable = false,
			.is_static = false
		}
		, start_linear_speed(0,0)
		, start_angular_speed(0)
		, start_linear_damping(0)
		, start_angular_damping(0)
		, start_angle(0)
		, start_position(0,0)
		, is_fixed(true)
		, is_bullet(false)
		, mass(100)
		, texture(nullptr)
		, size_of_visible_texture(0,0)
	{}
	~UnitCreator()
	{
		for (auto& i : main_collisions)
			delete i.shape;
		if(!texture)delete texture;
	}

	template<class... _Params>
	Unit* create(_Params... _Vals)
	{
		b2BodyDef bd;
		bd.enabled = status.is_physics;
		bd.type = (status.is_static) ? b2_staticBody : b2_dynamicBody;
		bd.linearVelocity.Set(
			start_linear_speed.x,
			start_linear_speed.y
		);
		bd.angularVelocity = start_angular_speed;
		bd.linearDamping = start_linear_damping;
		bd.angularDamping = start_angular_damping;
		bd.angle = start_angle;
		bd.position.Set(
			start_position.x,
			start_position.y
		);
		bd.fixedRotation = is_fixed;
		bd.bullet = is_fixed;

		Unit* unit = new _MainUnit(_Vals..., main_world->CreateBody(&bd));
		unit->setInterruptStatus(status.is_interrupted);
		unit->setDrawStatus(status.is_drawable);

		if(texture != nullptr)
			unit->setTexture( new sf::Texture(*texture) );
		unit->setMainSizeBody(size_of_visible_texture);
		for (auto& i : main_collisions)
			unit->addCollisionObject(&i);
		for (auto& i : states_and_texture_rects)
			unit->addStateAndRectOfTexture(i.first, i.second);
		unit->setStateOfTexture(start_state);
		
		unit->setMassToCenter(mass);

		return unit;
	}

	void addCollision(b2FixtureDef collision)
	{
		main_collisions.push_back(collision);
	}
	void addBoxCollision(sf::Vector2f size, float friction = 0.8f)
	{
		b2FixtureDef fixture_def;
		
		auto shape = new b2PolygonShape;
		shape->SetAsBox(
			size.x,
			size.y
		);

		fixture_def.density = 0.5f;
		fixture_def.friction = friction;
		fixture_def.shape = shape;
		main_collisions.push_back(fixture_def);
	}
	
	void addStateAndTextureRect(std::string state, Unit::RectAndFrames raf)
	{
		states_and_texture_rects.emplace(state, raf);
	}
	void addStatesAndTexturesRect
		(std::initializer_list < std::pair < std::string, Unit::RectAndFrames> > init)
	{
		for (auto& i : init)
			states_and_texture_rects.insert(i);
	}
	
	void loadTextureFromFile(std::string file_name)
	{
		delete texture;
		texture = new sf::Texture;
		texture->loadFromFile(file_name);
	}
};

