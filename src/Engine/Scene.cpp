#include "Scene.hpp"

Scene::Scene(sf::RenderWindow& render_window, sf::Vector2f gravitation)
	: is_running(false)
	, scene_world( b2Vec2(gravitation.x, gravitation.y) )
	, scene_window(render_window)
{
}

Scene::Scene(sf::RenderWindow& render_window, b2World native_world)
	: is_running(false)
	, scene_world(native_world)
	, scene_window(render_window)
{
}

decltype(Scene::scene_objects)& Scene::getListOfUnits()
{
}

b2World& Scene::getNativeWorld()
{
}

void Scene::enterToScene()
{
}

void Scene::exitFromScene()
{
}

void Scene::renderNext()
{
}
