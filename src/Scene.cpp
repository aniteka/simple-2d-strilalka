#include "Scene.hpp"

Scene::Scene(sf::RenderWindow& mw)
	: main_window(mw)
{
	
}

Scene::~Scene()
{
}




void Scene::run()
{
	while (main_window.isOpen())
	{
		events();

		update();
		
		main_window.clear(sf::Color::White);
		draw();
		main_window.display();
	}

}


void Scene::events()
{
	sf::Event e;
	while (main_window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			main_window.close();
	}
}

void Scene::draw()
{
	for (auto& i : units)
		main_window.draw(*i);
}


void Scene::update()
{
	for (auto& i : units)
		i->update();
}


