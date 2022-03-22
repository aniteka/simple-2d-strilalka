#include "Engine/defines.h"
#include "Engine/Unit.hpp"


int main()
{
	b2Vec2 gravity(0, 9.8f);
	b2World world(gravity);

	
	UnitCreator creator(&world);
	creator.status = {
		.is_physics = true,
		.is_interrupted = true,
		.is_drawable = true,
		.is_static = false
	};
	creator.start_position = { 50, 0 };
	
	creator.loadTextureFromFile("ResFiles\\main_hero_tailmap.png");
	creator.size_of_visible_texture = { 80,80 };
	creator.addStatesAndTexturesRect({
		MP("IDLE", Unit::RectAndFrames{
			IR(0, 0, 48, 48),
			4
		}),MP("RUN", Unit::RectAndFrames{
			IR(0,48,48,48),
			6
		})
	});
	creator.start_state = "IDLE";
	creator.addBoxCollision(VF(40.f, 40.f));
	
	creator.is_fixed = true;
	creator.mass = 1.f;

	auto unit = creator.create();

	
	UnitCreator creator_box(&world);
	creator_box.status = {
		1,1,1,1
	};
	creator_box.start_position = { 0, 700 };
	creator_box.size_of_visible_texture = { 500, 20 };
	creator_box.addBoxCollision(VF(250, 10));
	auto box = creator_box.create();
	
	bool isWorking = true;


	
	std::thread draw_thread(
		[&]()
		{
			sf::RenderWindow window(sf::VideoMode(1000, 1000), "name");
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
				window.draw(*unit);
				window.draw(*box);
				window.display();
			}
			isWorking = false;
		}
	);

	draw_thread.detach();

	while (isWorking)
	{
		world.Step(1 / 60.f,8, 3);
		std::this_thread::sleep_for(1ms);
	}

	return 0;
}
