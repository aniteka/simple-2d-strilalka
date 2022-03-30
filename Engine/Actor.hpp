#pragma once
#include "defines.h"
#include "Unit.hpp"

class Actor
	: public Unit
{
protected:
	std::map < sf::Keyboard::Key, std::function<void(Actor&)> >
		actor_key_callback_map;
	std::map < const char*, std::function<void(Actor&, Unit&)> >
		actor_userdata_of_interrupt_callback_map;
public:
	Actor(b2Body* body);
	Actor(const Actor&);
	Actor(Actor&&);

	auto addKeyAndCallback(
		sf::Keyboard::Key key,
		std::function<void(Actor&)> 
		) -> void;
	auto getKeysAndCallbacks()
		-> const decltype(actor_key_callback_map)&;

	auto addUserDataInterruptAndCallback(
		const char* name,
		std::function<void(Actor&, Unit&)>
		) -> void;
	auto getUserDataOfInterruptAndCallbacks()
		-> const decltype(actor_userdata_of_interrupt_callback_map)&;

	void updateEveryFrame(Scene& main_scene, sf::RenderWindow& main_window, b2World& main_world) override;

	void destroy();
protected:
	void eventUpdate();

private:
	void __actorKeysCallbacksUpdate();
	void __actorInterruptUpdate();
};

using ActorCreator = UnitCreator<Actor>;
