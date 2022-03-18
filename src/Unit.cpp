#include "Unit.hpp"

Unit::Unit(b2Body*& body)
	: status{
		.is_physics = false,
		.is_interrupted = false,
		.is_drawable = false,
		.is_static = true
	}
	, main_body(body)
	, main_texture(nullptr)
	, main_rect_texture(0,0,0,0)
	, main_size_body(0,0)
{
	if (main_body->IsEnabled())
		status.is_physics = true;
	
	if (main_body->GetType() == b2_staticBody)
		status.is_static = true;

	for (auto i = main_body->GetFixtureList(); i != NULL; i = i->GetNext())
		main_collisions.push_back(i);
}
Unit::~Unit()
{
	delete main_texture;
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



void Unit::setPhysicsBodyUserData(const std::string& str)
{
	main_body->SetUserData((void*)str.c_str());
}
const std::string& Unit::setPhysicsBodyUserData()
{
	return std::string((char*)main_body->GetUserData().pointer);
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



void Unit::setRectTexture(const sf::FloatRect& rect)
{
	main_rect_texture = rect;
}
const sf::FloatRect& Unit::getRectTexture()
{
	return main_rect_texture;
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



void Unit::setMainSizeBody(const sf::Vector2f& size)
{
	main_size_body = size;
}
const sf::Vector2f& Unit::getMainSizeBody()
{
	return main_size_body;
}



b2Body* Unit::getMainBody() const
{
	return main_body;
}



void Unit::draw(sf::RenderTarget& target, sf::RenderStates states) const
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
