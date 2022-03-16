#include "defines.h"
#include "Unit.hpp"
#include "Hero.hpp"
#include "Scene.hpp"
#include "TailMap.hpp"

#include "Tests/main.test.hpp"




class MainProgram
{
private: /*Constants*/
	const unsigned WINDOW_WIDTH = 600;
	const unsigned WINDOW_HEIGHT = 600;
	const unsigned FRAME_LIMIT = 60;

	const std::string TEST_PNG_FILENAME
		= "ResFiles\\COLOR_TEST_PNG.png";
	const std::string WINDOW_TITLE
		= "Strilalka";

	const sf::Vector2f SIZE_OF_ONE_TILE_SET
		{ 50.f, 50.f };

	const std::string LUA_FILE
		= "ResFiles\\REALTESTMAP2.lua";
	
	const sf::Color BACKGROUND_COLOR
		= sf::Color::White;


private: /*Vars*/
	sf::RenderWindow window;
	Hero main_hero;
	TailMap main_tail_map;
	Scene main_scene;

public: /*To use*/
	MainProgram();
	MainProgram(const MainProgram&) = delete;
	MainProgram(MainProgram&&) = delete;
	~MainProgram();

	int run();


private /*Functions*/:
	void loadTextures();
	void initTailMap();
	sf::View viewUpdate();
};




#ifndef TESTING
int main(int a, char** b)
{
	#ifdef DEBUG
	main_test(a, b);
	DLOG("TESTING END\n");
	#endif

	MainProgram main;
	return main.run();
}
#else
int main(int argc, char** argv)
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
	fixture.density = 0.f;
	fixture.shape = &shape;
	body->CreateFixture(&fixture);


	body_Constructor.position = b2Vec2(10, 10);
	body_Constructor.type = b2_dynamicBody;
	b2Body* box = world.CreateBody(&body_Constructor);

	b2PolygonShape shape2;
	shape2.SetAsBox(10, 10);
	fixture.density = 1;
	fixture.friction = 0.7f;
	fixture.shape = &shape2;
	box->CreateFixture(&fixture);

	sf::RenderWindow window(sf::VideoMode(500, 500), "name");
	sf::RectangleShape rect_shape(VF(500, 10));
	rect_shape.setPosition(0, 400);
	rect_shape.setFillColor(sf::Color::Red);

	sf::RectangleShape box_shape(VF(10 * 2 , 10 * 2));
	box_shape.setPosition(10, 10);
	box_shape.setFillColor(sf::Color::Black);
	
	while(window.isOpen())
	{
		sf::Event e;
		while(window.pollEvent(e))
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
		window.draw(box_shape);
		window.display();
		world.Step(1 / 60.f, 8, 3);
	}
	return 0;
	//return main_test(argc, argv);
}
#endif








MainProgram::MainProgram()
	: window
		(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
		WINDOW_TITLE)
	, main_hero()
	, main_scene(window)
	, main_tail_map()
{
	window.setFramerateLimit(FRAME_LIMIT);

	// Main hero init
	main_hero.setSize(VF(30, 100));
	main_hero.addCollisionObject(
		new sf::RectangleShape(sf::Vector2f(30, 98))
	);
	main_hero.getCollisionObject()[0]->move(0, 2);
	main_hero.setPoint(P(50, 60));
	
	main_scene.addUnit(
		&main_tail_map,
		&main_hero
	);
	main_scene.setViewCallback([this](){return viewUpdate();});
	
	loadTextures();
	initTailMap();
}



MainProgram::~MainProgram()
{
	program_running = false;
}



int MainProgram::run()
{
	main_scene.run();
	return 0;
}



void MainProgram::loadTextures()
{
	auto texture_hero = new sf::Texture;
	if (!texture_hero->loadFromFile(TEST_PNG_FILENAME))
		DLOG("ERROR TO LOAD TEXTURE");
	main_hero.setTexture(texture_hero);
}



void MainProgram::initTailMap()
{
	main_tail_map = TailMap(
		LUA_FILE
	);
	main_tail_map.setRectHW(
		SIZE_OF_ONE_TILE_SET.x,
		SIZE_OF_ONE_TILE_SET.y
	);
	main_tail_map.setPhysicsStatus(true);
}



sf::View MainProgram::viewUpdate()
{
	return window.getView();
}


