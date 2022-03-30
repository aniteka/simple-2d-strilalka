#include "Engine/defines.h"
#include "Engine/Components/file_manager.hpp"

#include "Engine/Unit.hpp"
#include "Engine/Actor.hpp"
#include "Engine/TailMap.hpp"
#include "Engine/Scene.hpp"


int main()
{
	sf::RenderWindow main_program_render_window(sf::VideoMode(500, 500), "");
	main_program_render_window.setFramerateLimit(60);

	
	Scene s(main_program_render_window, VF{ 0, 9.8f });
	Scene::setGlobalScene(s);
	
	UnitCreator creator;
	creator.status = {
		.is_physics = true,
		.is_interrupted = true,
		.is_drawable = true,
		.is_static = false
	};
	creator.start_position = { 50, 100 };
	
	//creator.loadTextureFromFile("ResFiles\\main_hero_tailmap.png");
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
	creator.start_state = "RUN";

	creator.addCircleCollision(40,
		{ 0,0 },
		1.f,
		.0f
	);
	// creator.addBoxCollision(VF(10.f, 40.f), 0.0);
	creator.start_linear_speed = { 10,0 };
	creator.is_fixed = true;
	creator.mass = 1.f;
	creator.user_data = "Hello World";
	
	auto unit = s.addUnit(creator);
	creator.restart();
	
	auto& creator_box = creator;
	
	creator_box.status = {
		1,1,1,1
	};
	creator_box.start_position = { 0, 700 };
	creator_box.size_of_visible_texture = { 500, 20 };
	creator_box.addBoxCollision(VF(250, 10));
	auto box = s.addUnit(creator_box);

	TailMapCreator tailmap_creator;
	tailmap_creator.status = {
		.is_physics = true,
		.is_interrupted = true,
		.is_drawable = true,
		.is_static = true
	};
	tailmap_creator.size_of_visible_texture = { 50,50 };
	auto tailmap = s.addUnit(
		tailmap_creator,
		FM::getResFile("REALTESTMAP2.lua")
	);

	ActorCreator actor_creator;
	actor_creator.status = {1,1,1,1};
	actor_creator.size_of_visible_texture = { 100,100 };
	actor_creator.start_position = { 200, 200 };
	actor_creator.addBoxCollision({ 50,50 }, { 0,0 }, 0, 0.5, 0, 0, true);
	auto actor = s.addUnit(actor_creator);
	actor.lock()->addKeyAndCallback(sf::Keyboard::A, [](Actor& a)
	{
		std::cout << "Work" << std::endl;
	});
	actor.lock()->addUserDataInterruptAndCallback("Hello World", [&s](Actor& from, Unit& to)
	{
		s.destroyUnit(&to);
	});
	
	s.enterToScene();

	
	while(s.isEntering())
		s.renderNext();
		
	

	return 0;
}


//
//int main()
//{
//	b2Vec2 gravity(0, 9.8f);
//	b2World world(gravity);
//
//	
//	UnitCreator creator(&world);
//	creator.status = {
//		.is_physics = true,
//		.is_interrupted = true,
//		.is_drawable = true,
//		.is_static = false
//	};
//	creator.start_position = { 50, 100 };
//	
//	//creator.loadTextureFromFile("ResFiles\\main_hero_tailmap.png");
//	creator.size_of_visible_texture = { 80,80 };
//	creator.addStatesAndTexturesRect({
//		MP("IDLE", Unit::RectAndFrames{
//			IR(0, 0, 48, 48),
//			4
//		}),MP("RUN", Unit::RectAndFrames{
//			IR(0,48,48,48),
//			6
//		})
//	});
//	creator.start_state = "RUN";
//
//	creator.addCircleCollision(40,
//		{ 0,0 },
//		.5f,
//		.0f
//	);
//	// creator.addBoxCollision(VF(10.f, 40.f), 0.0);
//
//	creator.is_fixed = true;
//	creator.mass = 1.f;
//
//	auto unit = creator.create();
//
//	creator.restart();
//	auto& creator_box = creator;
//	
//	creator_box.status = {
//		1,1,1,1
//	};
//	creator_box.start_position = { 0, 700 };
//	creator_box.size_of_visible_texture = { 500, 20 };
//	creator_box.addBoxCollision(VF(250, 10));
//	auto box = creator_box.create();
//
//
//
//	TailMapCreator tailmap_creator(&world);
//	tailmap_creator.status = {
//		.is_physics = true,
//		.is_interrupted = true,
//		.is_drawable = true,
//		.is_static = true
//	};
//	tailmap_creator.size_of_visible_texture = { 50,50 };
//	auto tailmap = tailmap_creator.create(
//		FM::getResFile("REALTESTMAP2.lua")
//	);
//	
//	
//	
//	bool isWorking = true;
//
//
//	
//	std::thread draw_thread(
//		[&]()
//		{
//			sf::RenderWindow window(sf::VideoMode(1000, 1000), "name");
//			window.setFramerateLimit(60);
//			while (window.isOpen())
//			{
//				sf::Event e;
//				while (window.pollEvent(e))
//				{
//					if (e.type == sf::Event::Closed)
//						window.close();
//				}
//
//				/*unit->setLinearSpeed(VF(
//					10,unit->getLinearSpeed().y
//				));*/
//				
//				window.clear(sf::Color::White);
//				window.draw(*unit);
//				window.draw(*tailmap);
//				window.draw(*box);
//				window.display();
//			}
//			isWorking = false;
//		}
//	);
//
//	draw_thread.detach();
//
//	while (isWorking)
//	{
//		world.Step(1 / 60.f,8, 3);
//		std::this_thread::sleep_for(1ms);
//	}
//
//	return 0;
//}
