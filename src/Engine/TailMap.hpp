#pragma once
#include "defines.h"

#include "Unit.hpp"
#include "Components/matrix.hpp"

class TailMap
	: public Unit
{
public:
	using Matrix_texture = Matrix<sf::Texture*>;

private:
	std::vector<sf::RectangleShape*> collision_vector;
	Matrix_texture* mtx;
	
	sf::Vector2f rect;
	sf::Point warp_point;

public:
	TailMap();
	TailMap(Matrix_texture::init_list init_list, size_t h_size, size_t v_size);
	TailMap(std::string lua_file);
	TailMap(TailMap&&) = default;
	TailMap(const TailMap&) = default;
	TailMap& operator=(const TailMap&);
	~TailMap() override
	{
		for (auto i : collision_vector)
			delete i;
		delete mtx;
	}

	void setTail(sf::Texture* rect, size_t x, size_t y) const;
	const Matrix_texture& getMatrix() const;
	void setRectHW(float h, float w);
	sf::Vector2f getRectHW() const;

	// Override ZONE:
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void addCollisionObject(sf::RectangleShape* sh) override;
	void collisision(sf::RectangleShape* to, sf::RectangleShape* from) override;
	void move(const sf::Point& p) override;
	void setPoint(const sf::Point& p) override;
	void setSize(const sf::Vector2f&) override;
	void setTexture(sf::Texture* tx) override;
	void setTextureRect(const sf::IntRect& ir) override;
	void update() override;

	const std::vector<sf::RectangleShape*>& getCollisionObject() const override;
	sf::Point getPoint() const override;
	sf::IntRect getTextureRect() const override;
private:
	void initCollisionVector();
};

