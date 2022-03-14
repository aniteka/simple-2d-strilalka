#pragma once
#include "defines.h"
#include "Unit.hpp"


class Scene
{
	std::vector<class Unit*> units;
	sf::RenderWindow& main_window;
	std::function<sf::View()> view_control_callback;
public:
	Scene(sf::RenderWindow&);
	~Scene();
	Scene(const Scene&) = delete;
	Scene(Scene&&) = delete;
	
	template<class..._Units>
	void addUnit(_Units... _refs_to_static_members)
	{
		(units.push_back(_refs_to_static_members), ...);
		std::sort(units.begin(), units.end(),
			[](Unit* a, Unit* b)
			{
				return
					a->getStatus().is_nstatic >
					b->getStatus().is_nstatic;
			}
		);
	}

	void setViewCallback(const decltype(view_control_callback)&);
	const decltype(view_control_callback)& getViewCallback() const;
	
	sf::View getView();
	void setView(sf::View);
	void setView(sf::FloatRect);
	
	void run();

private:
	void events();
	void draw();
	void update();
	void collisionUpdate();
};
