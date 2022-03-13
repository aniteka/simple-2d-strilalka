#include "Scene.hpp"

Scene::Scene(sf::RenderWindow& mw)
	: main_window(mw)
	, view_control_callback([this]()
	{
		return main_window.getView();
	})
{
}

Scene::~Scene()
{
}



sf::View Scene::getView()
{
	return main_window.getView();
}
void Scene::setView(sf::View view)
{
	main_window.setView(view);
}
void Scene::setView(sf::FloatRect fr)
{
	sf::View v(fr);
	main_window.setView(v);
}

void Scene::setViewCallback(const decltype(view_control_callback)& vcc)
{
	view_control_callback = vcc;
}
const decltype(Scene::view_control_callback)& Scene::getViewCallback() const
{
	return view_control_callback;
}



void Scene::run()
{
	while (main_window.isOpen())
	{
		events();

		update();

		main_window.setView(view_control_callback());
		
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
	collisionUpdate();
}


bool ifTheBoxesIntersect(sf::RectangleShape* a, sf::RectangleShape* b)
{
	if (
		(
		(a->getPosition().x + a->getSize().x) > b->getPosition().x &&
		(a->getPosition().x + a->getSize().x) < (b->getPosition().x + b->getSize().x) &&
		(a->getPosition().y + a->getSize().y) > b->getPosition().y &&
		(a->getPosition().y + a->getSize().y) < (b->getPosition().y + b->getSize().y)
		) || (
		(b->getPosition().x + b->getSize().x) > a->getPosition().x &&
		(b->getPosition().x + b->getSize().x) < (a->getPosition().x + a->getSize().x) &&
		(b->getPosition().y + b->getSize().y) > a->getPosition().y &&
		(b->getPosition().y + b->getSize().y) < (a->getPosition().y + a->getSize().y)
		)
	)
	return true;
	return false;
}
void Scene::collisionUpdate()
{
	for(size_t i = 0; i < units.size(); ++i)
	{
		if(	!(units[i]->getStatus().is_nstatic && 
			units[i]->getStatus().is_physics))
			continue;
		for(size_t j = i + 1; j < units.size(); ++j)
		{
			if(!units[j]->getStatus().is_physics)
				continue;
			for(auto r1 : units[i]->getCollisionObject())
				for(auto r2 : units[j]->getCollisionObject())
					if(ifTheBoxesIntersect(r1,r2))
						units[i]->collisision(r1, r2);
		}
	}
}
