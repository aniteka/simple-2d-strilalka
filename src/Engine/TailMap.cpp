#include "TailMap.hpp"
#include <sol/sol.hpp>




// Construct destruct zone:

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


struct AllInfoAboutTailMap
{
	size_t width;
	size_t height;
	size_t tilewidth;
	size_t tileheight;
	std::vector<Matrix<size_t>> layers;
};
AllInfoAboutTailMap getAllTileMaps(sol::table& main_table)
{
	AllInfoAboutTailMap aiatm;
	aiatm.width = main_table.get<LUA_NUMBER>("width");
	aiatm.height = main_table.get<LUA_NUMBER>("height");
	aiatm.tilewidth = main_table.get<LUA_NUMBER>("tilewidth");
	aiatm.tileheight = main_table.get<LUA_NUMBER>("tileheight");
	sol::table layers = main_table.get<sol::table>("layers");
	for(auto i:layers)
	{
		sol::table data = i
			.second
			.as<sol::table>()
			.get<sol::table>("data");
		Matrix<size_t> mtx({},aiatm.width, aiatm.height);
		for(size_t y = 0; y < aiatm.height; ++y)
			for(size_t x = 0; x < aiatm.width; ++x)
				mtx[y][x] = data.get<LUA_NUMBER>(x + 1 + y * aiatm.width);
		aiatm.layers.push_back(mtx);
	}
	return aiatm;
}

struct AllInfoAboutTileSet
{
	std::string image_name;
	sf::Texture* image;
	size_t imagewidth;
	size_t imageheight;
	size_t tilewidth;
	size_t tileheight;
	size_t tilecount;
	size_t firstid;
};
std::vector<AllInfoAboutTileSet> getAllTileSets(sol::table& main_table)
{
	std::vector<AllInfoAboutTileSet> aiatsv;

	sol::table tile_sets = main_table.get<sol::table>("tilesets");

	for(auto i : tile_sets)
	{
		AllInfoAboutTileSet info;
		sol::table ts = i.second.as<sol::table>();
		info.firstid = ts.get<LUA_NUMBER>("firstgid");


		// Load from another file
		std::string file_name = ts.get<std::string>("exportfilename");
		sol::state SOL_STATE;
		sol::protected_function_result pfr = SOL_STATE.do_file("ResFiles\\" + file_name);
		sol::table set_tbl = pfr.get<sol::table>();
		
		info.tilewidth		= set_tbl.get<LUA_NUMBER>("tilewidth");
		info.tileheight		= set_tbl.get<LUA_NUMBER>("tileheight");
		info.imageheight	= set_tbl.get<LUA_NUMBER>("imageheight");
		info.imagewidth		= set_tbl.get<LUA_NUMBER>("imagewidth");
		info.tilecount		= set_tbl.get<LUA_NUMBER>("tilecount");
		info.image_name		= set_tbl.get<std::string>("image");
		sf::Texture* tx = new sf::Texture;
		tx->loadFromFile("ResFiles\\" + info.image_name);
		info.image = tx;
		
		aiatsv.push_back(info);
	}
	
	return aiatsv;
}

TailMap::TailMap(std::string lua_file)
	: mtx(nullptr)
	, rect(0,0)
	, warp_point{ 0,0 }
{
	sol::state L;
	sol::protected_function_result result = L.do_file(lua_file);
	sol::table tbl = result.get<sol::table>();
	
	auto map_info = getAllTileMaps(tbl);
	auto map_sets_info = getAllTileSets(tbl);

	mtx = new Matrix_texture(
		{},
		map_info.width,
		map_info.height
	);
	rect = sf::Vector2f(map_info.tilewidth, map_info.tileheight);

	for(size_t y = 0; y < map_info.height; ++y)
	{
		for(size_t x = 0; x < map_info.width; ++x)
		{
			auto id = map_info.layers[0][y][x];
			for (auto q : map_sets_info)
				if (id >= q.firstid && id <= q.firstid + q.tilecount)
				{
					sf::Image img = q.image->copyToImage();
					auto rid = id - q.firstid;
					

					auto real_height=
						q.imageheight - (q.imageheight % q.tileheight);
					auto real_width =
						q.imagewidth - (q.imagewidth % q.tilewidth);

					size_t x_i = (q.tilewidth * rid) % real_width;
					size_t y_i =
						(((q.tilewidth * rid) - x_i) / real_width)
						* q.tileheight;

					
					mtx[0][y][x] = new sf::Texture();
					mtx[0][y][x]->loadFromImage(img, sf::IntRect(
						x_i, 
						y_i, 
						q.tilewidth,
						q.tileheight
					));
					goto EXIT;
				}
			EXIT:{}
		}
	}
	initCollisionVector();
}


TailMap& TailMap::operator=(const TailMap& tm)
{
	delete mtx;
	mtx = new Matrix_texture(tm.getMatrix());
	rect = tm.rect;
	warp_point = tm.warp_point;
	initCollisionVector();
	return *this;
}




// Setters getters zone:

void TailMap::setTail(sf::Texture* rect, size_t x, size_t y) const
{
	mtx[0][y][x] = rect;
}
const TailMap::Matrix_texture& TailMap::getMatrix() const
{
	return *mtx;
}


void TailMap::setSize(const sf::Vector2f& vec)
{
	setRectHW(vec.x, vec.y);
}
void TailMap::setRectHW(float h, float w)
{
	rect = { w,h };
	for (auto i : collision_vector)
		delete i;
	collision_vector.clear();
	initCollisionVector();
}
sf::Vector2f TailMap::getRectHW() const
{
	return rect;
}


void TailMap::setPoint(const sf::Point& p)
{

}
sf::Point TailMap::getPoint() const
{
	return warp_point;
}

const std::vector<sf::RectangleShape*>& TailMap::getCollisionObject() const
{
	return collision_vector;
}

void TailMap::move(const sf::Point& p)
{

}




// Unused zone: 

void TailMap::setTexture(sf::Texture* tx)
{
	// Unused
	DLOG("Function setTexture is unused with TailMap object");
}

void TailMap::addCollisionObject(sf::RectangleShape* sh)
{
	// Unused
	DLOG("Function addCollisionObject is unused with TailMap object");
}

void TailMap::setTextureRect(const sf::IntRect& ir)
{
	// Unused
	DLOG("Function setTextureRect is unused with TailMap object");
}

void TailMap::collisision(sf::RectangleShape* to, sf::RectangleShape* from)
{
	// Unused	
}

sf::IntRect TailMap::getTextureRect() const
{
	// Unused
	DLOG("Function getTextureRect is unused with TailMap object");
	return sf::IntRect(0, 0, 0, 0);
}




// Init

void TailMap::initCollisionVector()
{
	if (mtx == nullptr) return;
	for(auto i = 0; i < mtx->getVerticalSize(); ++i)
	{
		for(auto j = 0; j < mtx->getHorizontalSize(); ++j)
		{
			if(mtx[0][i][j] == nullptr)
				continue;
			auto rect = new sf::RectangleShape();
			rect->setSize(this->rect);
			rect->setPosition(
				j * rect->getSize().x,
				i * rect->getSize().y
			);
			collision_vector.push_back(rect);
		}
	}
}




// Update zone:

void TailMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape shape;
	shape.setSize(rect);
	shape.setPosition(warp_point.x, warp_point.y);
	shape.setOutlineColor(sf::Color::Black);

	for (size_t i = 0; i < mtx->getVerticalSize(); ++i)
	{
		for (size_t j = 0; j < mtx->getHorizontalSize(); ++j)
		{
			if (mtx[0][i][j] == nullptr)
			{
				shape.move(rect.x, 0);
				continue;
			}
			shape.setFillColor(sf::Color::White);
			shape.setTexture(mtx[0][i][j]);
			target.draw(shape, states);
			shape.move(rect.x, 0);
		}
		shape.move(0, rect.y);
		shape.setPosition(warp_point.x, shape.getPosition().y);
	}
}

void TailMap::update()
{}
