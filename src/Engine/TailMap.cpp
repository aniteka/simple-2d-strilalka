#include "TailMap.hpp"
#include <sol/sol.hpp>

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

TailMap::TailMap(std::string lua_file, b2Body* body)
	: Unit(body)
	, mtx(nullptr)
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
	main_size_body = sf::Vector2f(map_info.tilewidth, map_info.tileheight);

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

	for (auto& i : map_sets_info)
		delete i.image;

	initMainBody_after_mtx_init();
}
TailMap::TailMap(const TailMap& tailmap)
	: Unit(tailmap)
	, mtx(nullptr)
{
	if(tailmap.mtx != nullptr)
		mtx = new Matrix_texture(tailmap.mtx[0]);
}
TailMap::TailMap(TailMap&& tailmap)
	: Unit(std::move(tailmap))
	, mtx(tailmap.mtx)
{
	tailmap.mtx = nullptr;
}
TailMap::~TailMap()
{
	for (auto& i : *mtx)
		for (auto& j : i)
			delete j;
	delete mtx;
}


TailMap& TailMap::operator=(const TailMap&)
{
	return *this;
}
TailMap& TailMap::operator=(TailMap&&)
{
	return *this;
}



const TailMap::Matrix_texture& TailMap::getMatrix() const
{
	return *mtx;
}



void TailMap::setMainSizeBody(const sf::Vector2f& size)
{
	main_size_body = size;
	initMainBody_after_mtx_init();
}



void TailMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape shape;
	shape.setSize(main_size_body);
	shape.setPosition(
		main_body->GetPosition().x,
		main_body->GetPosition().y
	);
	shape.setOutlineColor(sf::Color::Black);

	for (size_t i = 0; i < mtx->getVerticalSize(); ++i)
	{
		for (size_t j = 0; j < mtx->getHorizontalSize(); ++j)
		{
			if (mtx[0][i][j] == nullptr)
			{
				shape.move(main_size_body.x, 0);
				continue;
			}
			shape.setFillColor(sf::Color::White);
			shape.setTexture(mtx[0][i][j]);
			target.draw(shape, states);
			shape.move(main_size_body.x, 0);
		}
		shape.move(0, main_size_body.y);
		shape.setPosition(
			main_body->GetPosition().x,
			shape.getPosition().y
		);
	}
}



void TailMap::initMainBody_after_mtx_init()
{
	for (auto i : main_collisions)
		main_body->DestroyFixture(i);
	main_collisions.clear();
	
	b2FixtureDef fixture_def;

	b2PolygonShape polygon_shape;
	fixture_def.shape = &polygon_shape;
	fixture_def.density = 0.5f;
	fixture_def.friction = 0.6f;

for (size_t y = 0; y < mtx[0].getVerticalSize(); ++y)
	for (size_t x = 0; x < mtx[0].getHorizontalSize(); ++x)
	{
		if(mtx[0][y][x] == nullptr)
			continue;
		polygon_shape.SetAsBox(
			getMainSizeBody().x / 2,
			getMainSizeBody().y / 2,
			b2Vec2(
				getPosition().x + getMainSizeBody().x / 2 + getMainSizeBody().x * x,
				getPosition().y + getMainSizeBody().y / 2 + getMainSizeBody().y * y
			),0
		);
		main_collisions.push_back(main_body->CreateFixture(&fixture_def));
	}
}

