#pragma once
#include "defines.h"
#include "Unit.hpp"

class Scene
{
	bool is_running;
	b2World scene_world;
	sf::RenderWindow& scene_window;
	std::list<std::shared_ptr<Unit>> scene_objects;
	
public:
	Scene(sf::RenderWindow& render_window, sf::Vector2f gravitation);
	Scene(sf::RenderWindow& render_window, b2World native_world);


	// Create unit and push it to list
	template<class _Unit = Unit, class ..._Params>
	std::weak_ptr<Unit>
	addUnit(UnitCreator<_Unit> unit, _Params... params);

	
	decltype(scene_objects)& getListOfUnits();
	b2World& getNativeWorld();

	
	// Start all threads
	void enterToScene();
	// Exit from all threads
	// Delete all units
	void exitFromScene();
	// Should be called every frame
	void renderNext();
};


template <class _Unit, class ... _Params>
std::weak_ptr<Unit>
Scene::addUnit(UnitCreator<_Unit> unit, _Params ... params)
{
	scene_objects.push_back(
		unit.create(params...));
	return scene_objects.back();
}

