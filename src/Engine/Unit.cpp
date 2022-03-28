#include "Unit.hpp"

Unit::Unit(b2Body* body)
	: status({
		.is_physics = false,
		.is_interrupted = false,
		.is_drawable = false,
		.is_static = false
	})
	, main_body(body)
	, main_texture(nullptr)
	, main_state_of_texture("")
	, main_size_body(10,10)
{
	if (main_body->IsEnabled())
		status.is_physics = true;
	
	if (main_body->GetType() == b2_staticBody)
		status.is_static = true;
	else 

	for (auto i = main_body->GetFixtureList(); i != NULL; i = i->GetNext())
		main_collisions.push_back(i);
}
Unit::Unit(const Unit& unit)
	: status(unit.status)
	, main_body( new b2Body(*unit.getMainBody()) )
	, main_texture( new sf::Texture( *unit.getTexture() ) )
	, main_states_and_rects_of_texture(unit.getStatesAndRectsOfTexture())
	, main_state_of_texture(unit.getStateOfTexture())
	, main_size_body(unit.getMainSizeBody())
{}
Unit::Unit(Unit&& unit)
	: status( std::move(unit.status) )
	, main_body( unit.main_body )
	, main_texture( unit.main_texture )
	, main_states_and_rects_of_texture( std::move(unit.main_states_and_rects_of_texture) )
	, main_state_of_texture( std::move(unit.main_state_of_texture))
	, main_size_body( std::move(unit.main_size_body) )
{
	unit.status = {
		.is_physics = false,
		.is_interrupted = false,
		.is_drawable = false,
		.is_static = false
	};
	unit.main_body = nullptr;
	unit.main_texture = nullptr;
	unit.main_states_and_rects_of_texture.clear();
	unit.main_state_of_texture.clear();
	unit.main_size_body = { 0,0 };
}
Unit::~Unit()
{
	delete main_texture;
	main_body
	->GetWorld()
	->DestroyBody(
		main_body);
}

Unit& Unit::operator=(const Unit& unit)
{
	return *this;
}
Unit& Unit::operator=(Unit&& unit)
{
	return *this;
}



void Unit::setPhysicsStatus(bool stat)
{
	status.is_physics = stat;
	if (stat == true)
		main_body->SetEnabled(true);
	else
		main_body->SetEnabled(false);
}
void Unit::setInterruptStatus(bool stat)
{
	status.is_interrupted = stat;
}
void Unit::setDrawStatus(bool stat)
{
	status.is_drawable = stat;
}
void Unit::setStaticStatus(bool stat)
{
	status.is_static = stat;
	if (stat == true)
		main_body->SetType(b2_staticBody);
	else 
		main_body->SetType(b2_dynamicBody);
}
Unit::Status Unit::getStatus() const
{
	return status;
}



void Unit::setPhysicsBodyUserData(const char* str)
{
	// main_body->SetUserData((void*)str);
}
const char* Unit::getPhysicsBodyUserData()
{
	return (char*)main_body->GetUserData().pointer;
}



void Unit::addCollisionObject(const b2FixtureDef* b2fd)
{
	main_collisions.push_back(
		main_body->CreateFixture(b2fd)
	);
}
const std::vector<b2Fixture*>& Unit::getCollisionObject() const
{
	return main_collisions;
}



void Unit::setTexture(sf::Texture* texture)
{
	main_texture = texture;
}
const sf::Texture* Unit::getTexture() const
{
	return main_texture;
}



void Unit::addStateAndRectOfTexture(std::string state, RectAndFrames rect)
{
	main_states_and_rects_of_texture
		.emplace(state, rect);
}
void Unit::delStateAndRectOfTexture(std::string state)
{
	main_states_and_rects_of_texture
		.erase(main_states_and_rects_of_texture.find(state));
}
const Unit::StatesAndRectsOfTexture& Unit::getStatesAndRectsOfTexture() const
{
	return main_states_and_rects_of_texture;
}
Unit::RectAndFrames Unit::getRectOfTexture(std::string state)
{
	return main_states_and_rects_of_texture.at(state);
}



void Unit::setStateOfTexture(std::string state)
{
	main_state_of_texture = std::move(state);
}
const std::string& Unit::getStateOfTexture() const
{
	return main_state_of_texture;
}



sf::Vector2f Unit::getPosition()
{
	return sf::Vector2f(
		main_body->GetPosition().x,
		main_body->GetPosition().y
	);
}



float Unit::getRotation()
{
	return main_body->GetAngle() * (3.14 / 180);
}



void Unit::setMass(float mass, const sf::Vector2f& point)
{
	b2MassData _mass;
	_mass.center = b2Vec2(point.x, point.y);
	_mass.mass = mass;
	main_body->SetMassData(&_mass);
}
void Unit::setMassToCenter(float mass)
{
	b2MassData _mass;
	_mass.center = main_body->GetLocalCenter();
	_mass.mass = mass;
	main_body->SetMassData(&_mass);
}
float Unit::getMass()
{
	return main_body->GetMass();
}
MassData Unit::getMassData()
{
	b2MassData mass_data;
	main_body->GetMassData(&mass_data);
	return MassData
	{
		.mass = mass_data.mass,
		.center = VF(mass_data.center.x, mass_data.center.y)
	};
}



void Unit::setLinearDamping(float damping)
{
	main_body->SetLinearDamping(damping);
}
float Unit::getLinearDamping() const
{
	return main_body->GetLinearDamping();
}
void Unit::setAngularDamping(float damping)
{
	main_body->SetAngularDamping(damping);
}
float Unit::getAngularDamping() const
{
	return main_body->GetAngularDamping();
}



void Unit::addImpulse(sf::Vector2f impulse, sf::Vector2f point)
{
	main_body->ApplyLinearImpulse(
		b2Vec2(impulse.x, impulse.y),
		b2Vec2(point.x, point.y),
		true
	);
}
void Unit::addImpulseToCenter(sf::Vector2f impulse)
{
	main_body->ApplyLinearImpulseToCenter(
		b2Vec2(impulse.x, impulse.y),
		true
	);
}
void Unit::addForce(sf::Vector2f force, sf::Vector2f point)
{
	main_body->ApplyForce(
		b2Vec2(force.x, force.y),
		b2Vec2(point.x, point.y),
		true
	);
}
void Unit::addForceToCenter(sf::Vector2f force)
{
	main_body->ApplyForceToCenter(
		b2Vec2(force.x, force.y),
		true
	);
}



void Unit::setLinearSpeed(const sf::Vector2f& vec)
{
	main_body->SetLinearVelocity(b2Vec2(vec.x, vec.y));
}
sf::Vector2f Unit::getLinearSpeed() const
{
	return {
		main_body->GetLinearVelocity().x,
		main_body->GetLinearVelocity().y
	};
}
void Unit::setAngularSpeed(float speed)
{
	main_body->SetAngularVelocity(speed);
}
float Unit::getAngularSpeed()
{
	return main_body->GetAngularVelocity();
}



void Unit::setMainSizeBody(const sf::Vector2f& size)
{
	main_size_body = size;
}
const sf::Vector2f& Unit::getMainSizeBody() const
{
	return main_size_body;
}



b2Body* Unit::getMainBody() const
{
	return main_body;
}



void Unit::updateEveryFrame(
	class Scene& main_scene,
	sf::RenderWindow& main_window,
	b2World& main_world)
{
		
}

std::map<void*, std::pair<size_t, std::string>> draw_map;

// TODO Angular change 
void Unit::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	const size_t TIME_OF_UPDATING_TEXTURE_RESTART = 100; // mc

	if (draw_map.find((void*)this) == draw_map.end())
		draw_map.emplace((void*)this, std::make_pair(0, ""));
	
	size_t& frame = draw_map[(void*)this].first;
	std::string& previous_state = draw_map[(void*)this].second;
	static sf::Clock frame_clock;

	if (!this->status.is_drawable)
		return;

	sf::RectangleShape draw_rect(main_size_body);
	draw_rect.setPosition(
		main_body->GetPosition().x - this->main_size_body.x / 2,
		main_body->GetPosition().y - this->main_size_body.y / 2
	);
	
	if (main_texture != nullptr)
		draw_rect.setTexture(main_texture);
	else
		draw_rect.setFillColor(sf::Color::Green);
	
	if(main_state_of_texture != "")
	{
		auto& msarof = main_states_and_rects_of_texture;
		if (previous_state != main_state_of_texture)
		{
			previous_state = main_state_of_texture;
			if (msarof.find(main_state_of_texture) == msarof.end())
				throw main_state_of_texture + "is uncertain";
			frame = 0;
		}

		if (frame >=
			msarof
			.at(main_state_of_texture).frames)
			frame = 0;
		
		draw_rect.setTextureRect(
			sf::IntRect(
				msarof.at(main_state_of_texture).rect.left + 
				(msarof.at(main_state_of_texture).rect.width * frame),
				msarof.at(main_state_of_texture).rect.top,
				msarof.at(main_state_of_texture).rect.width
				* ((getLinearSpeed().x >= 0) ? 1 : -1),
				msarof.at(main_state_of_texture).rect.height
			)
		);

		if (frame_clock.getElapsedTime().asMilliseconds() > TIME_OF_UPDATING_TEXTURE_RESTART)
		{
			frame++;
			frame_clock.restart();
		}
	}

	target.draw(draw_rect, states);
}
