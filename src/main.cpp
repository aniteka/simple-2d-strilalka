#include "defines.h"
#include "Unit.hpp"
#include "Hero.hpp"

#include "Tests/main.test.hpp"

#ifndef TESTING
int main()
{
	sf::RenderWindow window(
		sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
		"Strilalka"
	);

	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color(255, 255, 255));

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
