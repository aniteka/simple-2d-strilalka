#pragma once
#include "defines.h"
#include "Unit.hpp"

template<class _Type>
class Matrix
	: public std::vector< std::vector< _Type > >
{
	const size_t h_size;
	const size_t v_size;
public:
	using type = _Type;
	using parent_type = std::vector< std::vector< _Type > >;
	using init_list = std::initializer_list<std::vector<_Type>>;
	Matrix( 
		std::initializer_list<std::vector< _Type >> init,
		size_t h_size_,
		size_t v_size_
	)
		: parent_type(init)
		, h_size(h_size_)
		, v_size(v_size_)
	{
		this->resize(v_size);
		for (size_t i = 0; i < v_size; ++i)
			this->at(i).resize(h_size);
	}
	Matrix(const Matrix& mtx)
		: h_size(mtx.getHorizontalSize())
		, v_size(mtx.getVerticalSize())
	{
		for(auto i : mtx)
			this->push_back(i);
	}
	
	size_t getHorizontalSize() const noexcept
	{
		return h_size;
	}

	size_t getVerticalSize() const noexcept
	{
		return v_size;
	}
};

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

