#include "defines.h"
#include "Unit.hpp"
#include "Hero.hpp"

#include "Tests/main.test.hpp"



#ifndef TESTING
int main(int a, char** b)
{
	main_test(a, b);
	DLOG("TESTING END\n")
	
	sf::RenderWindow window(
		sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
		"Strilalka"
	);

	Hero main_hero;
	sf::Texture tx;
	
	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color(255, 255, 255));
		window.draw(main_hero);
		window.display();
	}
	
	return 0;
}
#else
int main(int argc, char** argv)
{
	return main_test(argc, argv);
}
#endif
