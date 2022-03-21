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


template<class _MainUnit = Unit>
struct UnitCreator
{
	Unit::Status status;

	sf::Vector2f start_linear_speed;
	float start_angular_speed;
	float start_linear_damping;
	float start_angular_damping;
	float start_angle;

	bool is_fixed;
	bool is_bullet;

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
		, is_fixed(false)
		, is_bullet(false)
		, texture(nullptr)
		, size_of_visible_texture(0,0)
	{}
	~UnitCreator()
	{
		delete texture;
	}

	template<class... _Params>
	_MainUnit* create(_Params... _Vals)
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
		bd.fixedRotation = is_fixed;
		bd.bullet = is_fixed;

		auto unit = new _MainUnit(_Vals..., main_world->CreateBody(&bd));
		unit->setInterruptStatus(status.is_interrupted);
		unit->setDrawStatus(status.is_drawable);

		unit->setTexture( new sf::Texture(*texture) );
		unit->setMainSizeBody(size_of_visible_texture);
		for (auto& i : main_collisions)
			unit->addCollisionObject(&i);
		for (auto& i : states_and_texture_rects)
			unit->addStateAndRectOfTexture(i.first, i.second);
		unit->setStateOfTexture(start_state);
		
		return unit;
	}

	void addCollision(b2FixtureDef collision)
	{
		main_collisions.push_back(collision);
	}
	void addBoxCollision(sf::Vector2f size, float friction = 0.2f)
	{
		b2FixtureDef fixture_def;
		
		auto shape = new b2PolygonShape;
		shape->SetAsBox(
			size.x,
			size.y
		);

		fixture_def.density = 1;
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

