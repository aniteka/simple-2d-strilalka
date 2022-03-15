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
	const unsigned FRAME_LIMIT = 660;

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
	return main_test(argc, argv);
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


