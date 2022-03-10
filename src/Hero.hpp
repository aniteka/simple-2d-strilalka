#pragma once
#include "defines.h"
#include "Unit.hpp"


class Hero 
	: public Unit
{
	std::vector<sf::RectangleShape*> collisions;
	sf::RectangleShape texture_rect;
	sf::Point warp_point;

	std::mutex texture_upd_mtx;
	using lock_unlock = std::lock_guard<std::mutex>;

	float cof_move;
	float cof_jump;

	int speed;
	int gravity_force;
	
	sf::Texture idle_texture;
	sf::Texture move_texture;
	sf::Texture jump_texture;
	bool is_texture_updating;

	std::thread texture_updating;

public:
	Hero();
	~Hero() override;
	Hero(const Hero&) = delete;
	Hero(Hero&&) = delete;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setSpeed(int speed);
	int getSpeed() const;

	void setGravityForce(int gf);
	int getGravityForce() const;

	void collisision(sf::RectangleShape* to, sf::RectangleShape* from) override;
	void update() override;
	void addCollisionObject(sf::RectangleShape* sh) override;
	void move(const sf::Point& p) override;
	void setPoint(const sf::Point& p) override;
	void setTextureRect(const sf::IntRect& ir) override;
	void setTexture(sf::Texture* tx) override;
	void setSize(const sf::Vector2f&) override;

	const std::vector<sf::RectangleShape*>& getCollisionObject() const override;
	sf::Point getPoint() const override;
	sf::IntRect getTextureRect() const override;

private:
	void moveKeyboardUpdate();
	void jumpKeyboardUpdate();
	void textureUpdating();
};
