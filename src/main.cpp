#include "Engine/defines.h"
#include "Engine/Unit.hpp"


int main()
{
	b2Vec2 gravity(0.f, 9.8f);
	b2World world(gravity);

	b2BodyDef body_Constructor;
	body_Constructor.position = b2Vec2(0, 400);
	body_Constructor.type = b2_staticBody;
	b2Body* body = world.CreateBody(&body_Constructor);

	b2PolygonShape shape;
	shape.SetAsBox(500, 10);
	b2FixtureDef fixture;
	fixture.shape = &shape;
	body->CreateFixture(&fixture);
	

	body_Constructor.position = b2Vec2(10, 10);
	body_Constructor.type = b2_dynamicBody;
	b2Body* box = world.CreateBody(&body_Constructor);
	Unit unit(box);
	unit.setDrawStatus(true);
	unit.setMainSizeBody(sf::Vector2f(80, 80));
	auto texture = new sf::Texture;
	texture->loadFromFile("ResFiles\\main_hero_tailmap.png");
	unit.setTexture(texture);
	unit.addStateAndRectOfTexture(
		"IDLE", 
		Unit::RectAndFrames{
			sf::IntRect(0, 0, 48, 48),
				4
		}
	);
	unit.setStateOfTexture("IDLE");
	
	b2PolygonShape shape2;
	shape2.SetAsBox(80 * 0.69, 80 * 0.69);
	fixture.density = 1;
	fixture.friction = 0.5f;
	fixture.shape = &shape2;
	unit.addCollisionObject(&fixture);

	
	sf::RectangleShape rect_shape(VF(500, 10));
	rect_shape.setPosition(0, 400);
	rect_shape.setFillColor(sf::Color::Red);

	sf::RectangleShape box_shape(VF(10 * 2, 10 * 2));
	box_shape.setPosition(10, 10);
	box_shape.setFillColor(sf::Color::Black);

	bool isWorking = true;

	std::thread draw_thread(
		[&]()
		{
			sf::RenderWindow window(sf::VideoMode(500, 500), "name");
			window.setFramerateLimit(60);
			while (window.isOpen())
			{
				sf::Event e;
				while (window.pollEvent(e))
				{
					if (e.type == sf::Event::Closed)
						window.close();
				}

				box_shape.setPosition(
					box->GetPosition().x,
					box->GetPosition().y
				);
				window.clear(sf::Color::White);
				window.draw(rect_shape);
				// window.draw(box_shape);
				window.draw(unit);
				window.display();
			}
			isWorking = false;
		}
	);

	draw_thread.detach();
	
	while (isWorking)
	{
		world.Step(1 / 40000.f,8, 3);
		unit.setLinearSpeed(VF(10, 
			unit.getLinearSpeed().y
		));
	}
	
	
	return 0;
}