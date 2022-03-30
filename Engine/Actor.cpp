#include "Actor.hpp"
#include "Scene.hpp"

Actor::Actor(b2Body* body)
	: Unit(body)
{
}

Actor::Actor(const Actor& actor)
	: Unit(actor)
{
}

Actor::Actor(Actor&& actor)
	: Unit(actor)
{
}

auto Actor::addKeyAndCallback(sf::Keyboard::Key key, std::function<void(Actor&)> callback) -> void
{
	actor_key_callback_map.emplace(key, callback);
}

auto Actor::getKeysAndCallbacks() -> const decltype(actor_key_callback_map)&
{
	return actor_key_callback_map;
}

auto Actor::addUserDataInterruptAndCallback(const char* name, std::function<void(Actor&, Unit&)> callback) -> void
{
	actor_userdata_of_interrupt_callback_map.emplace(name, callback);
}

auto Actor::getUserDataOfInterruptAndCallbacks() -> const decltype(actor_userdata_of_interrupt_callback_map)&
{
	return
		actor_userdata_of_interrupt_callback_map;
}

void Actor::updateEveryFrame(Scene& main_scene, sf::RenderWindow& main_window, b2World& main_world)
{
	eventUpdate();
}

void Actor::eventUpdate()
{
	if(status.is_interrupted)
		__actorInterruptUpdate();
	__actorKeysCallbacksUpdate();
}

void Actor::__actorKeysCallbacksUpdate()
{
	for(auto&[key, callback] : actor_key_callback_map)
		if (sf::Keyboard::isKeyPressed(key)) callback(*this);
}

void Actor::__actorInterruptUpdate()
{
	std::map<std::function<void(Actor&, Unit&)>*, std::pair<Actor*,Unit*>> to_use;
	for(auto&[user_data, callback] : actor_userdata_of_interrupt_callback_map)
	{
		auto contact_list = main_body->GetContactList();

		for (auto i = contact_list; i != nullptr; i = i->next)
		{
			auto other_body = i->contact->GetFixtureB()->GetBody();
			if (i->contact->GetFixtureB()->GetBody() == main_body)
				other_body = i->contact->GetFixtureA()->GetBody();
			if ((const char*)other_body->GetUserData().pointer == nullptr) 
				continue;
			if (strcmp((const char*)other_body->GetUserData().pointer, user_data) == 0)
			{
				auto& lst = Scene::getGlobalScene().getListOfUnits();
				for(auto& i : lst)
					if (i->getMainBody() == other_body)
						to_use.emplace(&callback, std::make_pair(this, i.get()));
			}
		}	
	}

	for (auto& [callback, params] : to_use)
		(*callback)(*params.first, *params.second);
}
