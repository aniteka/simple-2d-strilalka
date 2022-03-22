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
	Matrix_texture* mtx;

public:
	TailMap(std::string lua_file, b2Body* body);
	~TailMap() override
	{
		for (auto i : *mtx)
			for (auto j : i)
				delete j;
		delete mtx;
	}

	const Matrix_texture& getMatrix() const;

	void setMainSizeBody(const sf::Vector2f& size) override;
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	void initMainBody_after_mtx_init();

	// Do not use it
	void setTexture(sf::Texture* texture) override { }
	// Do not use it
	const sf::Texture* getTexture() const override {  return nullptr; }

	void addCollisionObject(const b2FixtureDef* b2fd) override {  }
	// Do not use it

	// Do not use it
	void addStateAndRectOfTexture(std::string state, RectAndFrames rect_and_frames) override {  }
	// Do not use it
	void delStateAndRectOfTexture(std::string state) override {  }
	// Do not use it
	const StatesAndRectsOfTexture& getStatesAndRectsOfTexture() const override {  return {}; }
	// Do not use it
	RectAndFrames getRectOfTexture(std::string state) override {  return {}; }

	// Do not use it
	void setStateOfTexture(std::string state) override { }
	// Do not use it
	const std::string& getStateOfTexture() const override { return ""; }
};

using TailMapCreator = UnitCreator<TailMap>;
