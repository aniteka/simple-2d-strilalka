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
	// Staus if physics, draw, static
	Unit::Status status;


	
	// Start speed
	sf::Vector2f start_linear_speed;
	
	// Start angular speed(speed of start angular rotation)
	float start_angular_speed;

	// Attenuation of speed 
	float start_linear_damping;

	// Attenuation of angular speed 
	float start_angular_damping;

	// Angle of body
	float start_angle;

	// Start position of body
	sf::Vector2f start_position;


	
	// Bod will not change his angle
	bool is_fixed;

	// See in documentation
	bool is_bullet;
	
	// Mass of body
	float mass;

	// Gravity scale
	float gravity_scale;
	
	
	// Main texture
	sf::Texture* texture;

	// State(std::string) and rect in texture 
	Unit::StatesAndRectsOfTexture states_and_texture_rects;

	// State from states_and_texture_rects
	std::string start_state;

	sf::Vector2f size_of_visible_texture;

private:
	// All constructors of collision there
	std::vector<b2FixtureDef> main_collisions;

	// Pointer to world, use only for create bodies
	b2World* main_world;

public:
	/// <param name="world">
	/// Pointer to world, use only for create bodies
	/// </param>
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
		, gravity_scale(1)
		, texture(nullptr)
		, size_of_visible_texture(0,0)
	{}
	~UnitCreator()
	{
		for (auto& i : main_collisions)
			delete i.shape;
		if(!texture) delete texture;
	}

	/// <summary>
	/// Create unit var and add it to world
	/// </summary>
	/// <typeparam name="..._Params">
	/// Parameters types for Unit's constructor
	/// </typeparam>
	/// <param name="..._Vals">
	/// Vars for unit's constructor
	/// </param>
	/// <returns>
	/// Smart pointer to unit
	/// </returns>
	template<class... _Params>
	std::shared_ptr<_MainUnit> create(_Params... _Vals) const
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
		bd.gravityScale = gravity_scale;
		
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

		return std::shared_ptr<_MainUnit>(
			static_cast<_MainUnit*>(unit));
	}

	/// <summary>
	/// fully restart of creator
	/// </summary>
	/// <param name="new_world">
	/// if == nullptr, use old world
	/// </param>
	void restart(b2World* new_world = nullptr)
	{
		if (new_world != nullptr)
			main_world = new_world;
		for (auto& i : main_collisions)
			delete i.shape;
		main_collisions.clear();
		if (!texture) delete texture;

		status = {
			.is_physics = false,
			.is_interrupted = false,
			.is_drawable = false,
			.is_static = false
		};
		start_linear_speed = { 0, 0 };
		start_angular_speed = 0;
		start_linear_damping = 0;
		start_angular_damping = 0;
		start_angle = 0;
		start_position = { 0, 0 };
		is_fixed = true;
		is_bullet = false;
		mass = 100;
		gravity_scale = 1;
		texture = nullptr;
		size_of_visible_texture = { 0, 0 };
	}
	




	
	// /\/\/\ Create, Constructors | Collisions \/\/\/


	


	
	void addCollision(b2FixtureDef collision)
	{
		main_collisions.push_back(collision);
	}

	/// <summary>
	/// Add box collision to object
	/// </summary>
	/// <param name="size">
	/// Size of collision(Розмір)
	/// </param>
	/// <param name="position">
	/// Position of collision
	/// (Default is center of body)
	/// </param>
	/// <param name="angle">
	/// Angle of collision
	/// </param>
	/// <param name="density">
	/// Density(Щільність) used to compute the
	/// mass properties of the parent body
	/// </param>
	/// <param name="friction">
	/// Friction(Тертя) of collision([0,1])
	/// </param>
	/// <param name="restitution">
	///	Restitution(Пружність) of the body([0,1])
	/// </param>
	void addBoxCollision(sf::Vector2f size,
						sf::Vector2f position = {0,0},
						float angle = 0.f,
						float density = 0.5f,
						float friction = 0.2f,
						float restitution = 0.f)
	{
		b2FixtureDef fixture_def;
		
		auto shape = new b2PolygonShape;
		shape->SetAsBox(
			size.x,
			size.y,
			b2Vec2(position.x, position.y),
			angle
		);

		fixture_def.restitution = restitution;
		fixture_def.density = density;
		fixture_def.friction = friction;
		fixture_def.shape = shape;
		main_collisions.push_back(fixture_def);
	}

	/// <summary>
	/// Add box collision to object
	/// </summary>
	/// <param name="radius">
	/// Size of collision(Розмір)
	/// </param>
	/// <param name="position">
	/// Position of collision
	/// (Default is center of body)
	/// </param>
	/// <param name="density">
	/// Density(Щільність) used to compute the
	/// mass properties of the parent body
	/// </param>
	/// <param name="friction">
	/// Friction(Тертя) of collision([0,1])
	/// </param>
	/// <param name="restitution">
	///	Restitution(Пружність) of the body([0,1])
	/// </param>
	void addCircleCollision(float radius,
							sf::Vector2f position = {0,0},
							float density = 0.5f,
							float friction = 0.2f,
							float restitution = 0.f)
	{
		b2FixtureDef fixture_def;

		auto shape = new b2CircleShape;
		shape->m_radius = radius;
		shape->m_p.Set(position.x,position.y);

		fixture_def.restitution = restitution;
		fixture_def.density = density;
		fixture_def.friction = friction;
		fixture_def.shape = shape;
		main_collisions.push_back(fixture_def);
	}





	
	// /\/\/\ Collision | States and textures \/\/\/





	
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

