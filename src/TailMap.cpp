#include "TailMap.hpp"
#include <sol/sol.hpp>

TailMap::TailMap(Matrix_texture::init_list init_list, size_t h_size, size_t v_size)
	: mtx(new Matrix(init_list, h_size, v_size))
	, rect(10,10)
	, warp_point{ 0,0 }
{
	initCollisionVector();
}

TailMap::TailMap()
	: mtx(nullptr)
	, rect(10,10)
	, warp_point{ 0,0 }
{
	initCollisionVector();
}

TailMap::TailMap(std::string lua_file)
	: mtx(nullptr)
	, rect(0,0)
	, warp_point{ 0,0 }
{
	sol::state L;
	sol::protected_function_result result = L.do_file(lua_file);
	sol::table tbl = result.get<sol::table>();
	for(auto& i : tbl)
	{
		DLOG(i.first.as<std::string>().c_str());
		if (i.first.as<std::string>() == "tilewidth")
			rect.x = static_cast<float>(i.second.as<LUA_NUMBER>());
		if (i.first.as<std::string>() == "tileheight")
			rect.y = static_cast<float>(i.second.as<LUA_NUMBER>());
	}
}


TailMap& TailMap::operator=(const TailMap& tm)
{
	delete mtx;
	mtx = new Matrix_texture(tm.getMatrix());
	rect = tm.rect;
	initCollisionVector();
	return *this;
}



void TailMap::setTail(sf::Texture* rect, size_t x, size_t y) const
{
	mtx[0][y][x] = rect;
}

const TailMap::Matrix_texture& TailMap::getMatrix() const 
{
	return *mtx;
}

void TailMap::setRectHW(float h, float w)
{
	rect = { w,h };
}


sf::Vector2f TailMap::getRectHW() const
{
	return rect;
}


void TailMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape shape;
	shape.setSize(rect);
	shape.setPosition(0, 0);
	
	for (auto i = 0; i < mtx->getVerticalSize(); ++i)
	{
		for (auto j = 0; j < mtx->getHorizontalSize(); ++j)
		{
			if(mtx[0][i][j] == nullptr)
				shape.setFillColor(sf::Color(0, 0, 0, 0));
			else
			{
				shape.setFillColor(sf::Color::White);
				shape.setTexture(mtx[0][i][j]);
			}
			shape.move(rect.x, 0);
			target.draw(shape, states);
		}
		shape.move(0, rect.y);
	}
}

void TailMap::addCollisionObject(sf::RectangleShape* sh)
{
}

void TailMap::move(const sf::Point& p)
{
}

void TailMap::setPoint(const sf::Point& p)
{}

void TailMap::setSize(const sf::Vector2f&)
{}

void TailMap::setTextureRect(const sf::IntRect& ir)
{}

void TailMap::update()
{}

void TailMap::collisision(sf::RectangleShape* to, sf::RectangleShape* from)
{}

void TailMap::setTexture(sf::Texture* tx)
{}

const std::vector<sf::RectangleShape*>& TailMap::getCollisionObject() const
{
	return collision_vector;
}

sf::Point TailMap::getPoint() const
{
	return warp_point;
}

sf::IntRect TailMap::getTextureRect() const
{
	DLOG("Function getTextureRect is unused with TailMap object");
	return sf::IntRect(0, 0, 0, 0);
}

void TailMap::initCollisionVector()
{
	if (mtx == nullptr) return;
	for(auto i = 0; i < mtx->getVerticalSize(); ++i)
	{
		for(auto j = 0; j < mtx->getHorizontalSize(); ++j)
		{
			auto rect = new sf::RectangleShape();
			rect->setSize(this->rect);
			rect->setPosition(
				j * rect->getSize().x,
				i + rect->getSize().y
			);
			collision_vector.push_back(rect);
		}
	}
}

