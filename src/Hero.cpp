#include "Hero.hpp"

Hero::Hero()
	: Unit()
	, collisions{}
	, texture_rect(sf::Vector2f(10, 10))
	, warp_point{ 0,0 }
	, cof_move(0)
	, cof_jump(0)
	, speed(1)
	, gravity_force(1)
	, is_texture_updating(false)
{
	texture_rect.setFillColor(sf::Color(0, 0, 0, 255));
	category = "Hero";
	status.is_drawable = true;
	status.is_physics = true;

	texture_updating = std::thread(
		[this]() { this->textureUpdating(); }
	);

	DLOG("Hero status: CREATED");
}

void Hero::collisision(sf::RectangleShape* to, sf::RectangleShape* from)
{
	auto pto = to->getPosition();
	auto sto = to->getSize();
	auto pfrom = to->getPosition();
	auto sfrom = to->getSize();
	// Left
	if (pfrom.x < pto.x + sto.x)
		if (cof_move > 0) cof_move = 0;
	// Right
	if (pfrom.x + sfrom.x > pto.x)
		if (cof_move < 0) cof_move = 0;
}


Hero::~Hero()
{
	for(auto i : collisions)
		delete i;
	delete texture_rect.getTexture();
	texture_updating.join();
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
void Hero::setTexture(sf::Texture* tx)
{
	texture_rect.setFillColor(sf::Color::White);
	texture_rect.setTexture(tx, true);
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


void Hero::setSpeed(int speed)
{
	this->speed = speed;
}
int Hero::getSpeed() const
{
	return speed;
}
void Hero::setGravityForce(int gf)
{
	gravity_force = gf;
}
int Hero::getGravityForce() const
{
	return gravity_force;
}


void Hero::moveKeyboardUpdate()
{
	static sf::Clock cl;
	if(cl.getElapsedTime().asMilliseconds() < 10)
		return;
	cl.restart();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		cof_move += 0.1f;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		cof_move -= 0.1f;
	else
	{
		if (cof_move > 0.1f) cof_move -= 0.1f;
		else if (cof_move < -0.1f) cof_move += 0.1f;
		else cof_move = .0f;
	}
	if (cof_move > 1) cof_move = 1;
	if (cof_move < -1) cof_move = -1;
}
void Hero::jumpKeyboardUpdate()
{
	static sf::Clock cl;
	if (cl.getElapsedTime().asMilliseconds() < 10)
		return;
	cl.restart();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && cof_jump < 0.1f && cof_jump > -0.1f)
		cof_jump -= 1.f;
	else
		cof_jump += 0.01f;
	if (cof_jump < -2) cof_jump = -2;
}

void Hero::update()
{
	if (status.is_physics)
	{
		moveKeyboardUpdate();
		jumpKeyboardUpdate();
		move(P(speed * cof_move, gravity_force * cof_jump));
	}
}

void Hero::textureUpdating()
{
	while(is_texture_updating)
	{
		std::this_thread::sleep_for(1s);

	}
}

