#include "defines.h"
#include "Unit.hpp"
#include "Hero.hpp"
#include "Scene.hpp"
#include "TailMap.hpp"

#include "Tests/main.test.hpp"




class MainProgram
{
private: /*Constants*/
	const unsigned WINDOW_WIDTH = 500;
	const unsigned WINDOW_HEIGHT = 500;
	const unsigned FRAME_LIMIT = 560;

	const std::string TEST_PNG_FILENAME
		= "ResFiles\\COLOR_TEST_PNG.png";
	const std::string WINDOW_TITLE
		= "Strilalka";
	
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
	~MainProgram() = default;

	int run();


private /*Functions*/:
	void loadTextures();
	void initTailMap();
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

	main_hero.setSize(VF(30, 100));

	main_scene.addUnit(
		&main_hero,
		&main_tail_map
	);
	
	loadTextures();
	initTailMap();
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
	auto texture_hero = new sf::Texture;
	if (!texture_hero->loadFromFile(TEST_PNG_FILENAME))
		DLOG("ERROR TO LOAD TEXTURE");
	/*
	main_tail_map = TailMap(
		{}
		, 10, 10
	);*/
	main_tail_map = TailMap(
		"ResFiles\\tailMap.lua"
	);
	main_tail_map.setRectHW(50.f, 50.f);
}

