#define DEBUG
#include "defines.h"
#include "Unit.hpp"

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
