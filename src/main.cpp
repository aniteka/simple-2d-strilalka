#include "defines.h"
#include "Unit.hpp"
#include "Hero.hpp"

#include "Tests/main.test.hpp"




class MainProgram
{
private: /*Constants*/
	const unsigned WINDOW_WIDTH = 500;
	const unsigned WINDOW_HEIGHT = 500;
	const unsigned FRAME_LIMIT = 560;

	const std::string TEST_PNG_FILENAME = "ResFiles\\COLOR_TEST_PNG.png";
	const std::string WINDOW_TITLE = "Strilalka";
	
	const sf::Color BACKGROUND_COLOR = sf::Color::White;

private: /*Vars*/
	sf::RenderWindow window;
	Hero main_hero;


public: /*To use*/
	MainProgram();
	MainProgram(const MainProgram&) = delete;
	MainProgram(MainProgram&&) = delete;
	~MainProgram() = default;

	int run();


private /*Functions*/:
	void events();
	void loadTextures();
	void draw();
};




#ifndef TESTING
int main(int a, char** b)
{
	main_test(a, b);
	DLOG("TESTING END\n")

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
{
	window.setFramerateLimit(FRAME_LIMIT);

	main_hero.setSize(VF(30, 100));
	loadTextures();
}



int MainProgram::run()
{
	while (window.isOpen())
	{
		events();

		window.clear(BACKGROUND_COLOR);
		draw();
		window.display();
	}

	return 0;
}


void MainProgram::events()
{
	sf::Event e;
	while(window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			window.close();
	}
}

void MainProgram::loadTextures()
{
	auto texture_hero = new sf::Texture;
	if (!texture_hero->loadFromFile(TEST_PNG_FILENAME))
		DLOG("ERROR TO LOAD TEXTURE");
	main_hero.setTexture(texture_hero);
}


void MainProgram::draw()
{
	window.draw(main_hero);
}

