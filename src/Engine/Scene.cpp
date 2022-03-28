#include "Scene.hpp"
#include <shared_mutex>

std::shared_mutex exit_mutex;
std::condition_variable synk_var;
Scene* Scene::global_scene = nullptr;

Scene::Scene(sf::RenderWindow& render_window, sf::Vector2f gravitation)
	: is_entering(false)
	, scene_world( b2Vec2(gravitation.x, gravitation.y) )
	, scene_window(render_window)
{}

Scene::Scene(sf::RenderWindow& render_window, b2World native_world)
	: is_entering(false)
	, scene_world(native_world)
	, scene_window(render_window)
{}

Scene::~Scene()
{
	exitFromScene();
}

decltype(Scene::scene_units)& Scene::getListOfUnits()
{
	return scene_units;
}

const b2World& Scene::getNativeWorld() const
{
	return scene_world;
}

const sf::RenderWindow& Scene::getWindow() const
{
	return scene_window;
}

bool Scene::isEntering() const
{
	return is_entering;
}



void Scene::enterToScene()
{
	if (&getGlobalScene() != this)
		return;
	is_entering = true;
	std::thread world_update([this]()
	{
		this->__world_update();
	});
	std::thread unit_update([this]()
	{
		this->__world_update();
	});

	world_update.detach();
	unit_update.detach();
}

void Scene::exitFromScene()
{
	is_entering = false;
	while(!exit_mutex.try_lock())
		synk_var.notify_all();
	exit_mutex.unlock();
	scene_units.clear();
}







void Scene::renderNext()
{
	std::unique_lock ulock(units_mutex, std::defer_lock);
	if (is_entering == false) goto EXIT;
	sf::Event e;
	while(scene_window.pollEvent(e))
	{
		if(e.type == sf::Event::Closed)
		{
			exitFromScene();
			goto EXIT;
		}
	}

	scene_window.clear(sf::Color::White);

	ulock.lock();
	for (auto& i : scene_units)
		scene_window.draw(*i);
	ulock.unlock();
	synk_var.notify_all();
	
	scene_window.display();

	EXIT:{}
}

void Scene::__world_update()
{
	exit_mutex.lock_shared();
	while (is_entering)
	{
		std::unique_lock ulock(units_mutex);
		synk_var.wait(ulock);
		scene_world.Step(1.f / 20.f, 8, 3);
		ulock.unlock();
		
	}
	exit_mutex.unlock_shared();
}
void Scene::__unit_update()
{
	exit_mutex.lock_shared();
	while (is_entering)
	{
		units_mutex.lock();
		for (auto& i : scene_units)
			i->updateEveryFrame(
				*this,
				scene_window,
				scene_world
			);
		units_mutex.unlock();
		
		std::this_thread::sleep_for(20ms);
	}
	exit_mutex.unlock_shared();
}


void Scene::setGlobalScene(Scene& scene)
{
	global_scene = &scene;
}

const Scene& Scene::getGlobalScene()
{
	return *global_scene;
}
