#include "Engine/defines.h"
#include "Engine/Unit.hpp"


int main()
{
	b2Vec2 gravity(0, 9.8f);
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
	
	UnitCreator creator(&world);
	creator.status = {
		.is_physics = true,
		.is_interrupted = true,
		.is_drawable = true,
		.is_static = false
	};

	creator.loadTextureFromFile("ResFiles\\main_hero_tailmap.png");
	creator.size_of_visible_texture = { 80,80 };
	creator.addStateAndTextureRect(
		"IDLE", Unit::RectAndFrames{
			IR(0, 0, 48, 48),
			4
		}
	);
	creator.start_state = "IDLE";
	creator.addBoxCollision(VF(80.f * 0.69f, 80.f * 0.69f));
	creator.is_fixed = true;
	
	auto unit = creator.create();
	
	bool isWorking = true;

	sf::RectangleShape rect_shape(VF(500, 10));
	rect_shape.setPosition(0, 400);
	rect_shape.setFillColor(sf::Color::Red);

	
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

				window.clear(sf::Color::White);
				window.draw(rect_shape);
				window.draw(*unit);
				window.display();
			}
			isWorking = false;
		}
	);

	draw_thread.detach();
	
	while (isWorking)
	{
		world.Step(1 / 40000.f,8, 3);
		unit->setLinearSpeed(VF(10, 
			unit->getLinearSpeed().y
		));
	}
	
}


