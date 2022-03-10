#pragma once
#include "defines.h"
#include "Unit.hpp"


class Scene
{
	std::vector<class Unit*> units;
	sf::RenderWindow& main_window;
public:
	Scene(sf::RenderWindow&);
	~Scene();
	Scene(const Scene&) = delete;
	Scene(Scene&&) = delete;
	
	template<class..._Units>
	void addUnit(_Units... _refs_to_static_members)
	{
		(units.push_back(_refs_to_static_members), ...);
	}

	void run();

private:
	void events();
	void draw();
	void update();
};
