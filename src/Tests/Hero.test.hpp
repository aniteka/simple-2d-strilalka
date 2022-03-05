#pragma once
#include "../defines.h"
#include "../Hero.hpp"
struct HeroTest
	: testing::Test
{
	Hero hero;
	HeroTest()
		: hero()
	{}

	~HeroTest()
	{
		DLOG("HeroTest: END");
	}
};

TEST_F(HeroTest, HeroMoveTest)
{
	DLOG("HERO MOVE TEST START");
	// Change warp point position
	hero.setPoint( P(20,30) );
	ASSERT_EQ(hero.getPoint(), P(20, 30));

	// Change position
	hero.move( P(1, -1) );
	ASSERT_EQ(hero.getPoint(), P(21, 29));

	// Change position 2
	auto shape = new sf::RectangleShape(sf::Vector2f(10, 10));
	shape->setPosition(200, 200);
	hero.addCollisionObject(shape);
	hero.move(P(10, 10));
	ASSERT_EQ(hero.getCollisionObject()[0]->getPosition(), sf::Vector2f(210, 210));
	DLOG("HERO MOVE TEST END");
}

TEST_F(HeroTest, HeroDrawTest)
{
	DLOG("HERO DRAW TEST START");
	sf::RenderWindow window(
		sf::VideoMode(100, 100),
		" "
	);

	// Hero draw test1
	window.clear(sf::Color(255, 255, 255));
	window.draw(hero);
	ASSERT_EQ(window.capture().getPixel(0,0) , sf::Color(0, 0, 0, 255));
	ASSERT_NE(window.capture().getPixel(20, 20), sf::Color(0, 0, 0, 255));

	// Hero draw after move test2
	hero.move( P(1, 1) );
	window.clear(sf::Color::White);
	window.draw(hero);
	ASSERT_NE(window.capture().getPixel(0,0) , sf::Color(0, 0, 0, 255));
	ASSERT_EQ(window.capture().getPixel(1,1) , sf::Color(0, 0, 0, 255));

	// Hero draw after changing draw status test3
	hero.setDrawStatus(false);
	ASSERT_ANY_THROW(window.draw(hero));
	
	window.close();
	DLOG("HERO DRAW TEST END");
}

TEST_F(HeroTest, HeroTextureTest)
{
	auto tx = new sf::Texture;
	if (!tx->loadFromFile("ResFiles\\COLOR_TEST_PNG.png"))
		DLOG("FAIL TO LOAD COLOR_TEST_PNG.png, WHILE UNIT TESTING");
	hero.setTexture(tx);
	hero.setSize(VF(100, 100));

	sf::RenderWindow rw(
		sf::VideoMode(100, 100),
		"", 
		sf::Style::None
	);

	rw.clear(sf::Color::White);
	rw.draw(hero);

	auto i = rw.capture();
	ASSERT_EQ(i.getPixel(0, 0),		sf::Color(0xFE,0XFE,0XFE,0XFF));
	ASSERT_EQ(i.getPixel(12, 0),	sf::Color(0xFE,0xFE,0x00,0xFF));
	ASSERT_EQ(i.getPixel(25, 0),	sf::Color(0x00,0xFE,0xFE,0xFF));
	ASSERT_EQ(i.getPixel(38, 0),	sf::Color(0x00,0xFE,0x00,0xFF));
	ASSERT_EQ(i.getPixel(52, 0),	sf::Color(0xFE,0x00,0xFE,0xFF));
	ASSERT_EQ(i.getPixel(68, 0),	sf::Color(0xFE,0x00,0x00,0xFF));
	ASSERT_EQ(i.getPixel(84, 0),	sf::Color(0x00,0x00,0xFE,0xFF));
	ASSERT_EQ(i.getPixel(98, 0),	sf::Color(0x00,0x00,0x00,0xFF));

	hero.setSize(VF(100, 100));
	
	hero.setTextureRect(sf::IntRect(0, 0, 1, 1));
	rw.clear(sf::Color::White);
	rw.draw(hero);
	i = rw.capture();
	ASSERT_EQ(i.getPixel(0, 0),		sf::Color(0xFE,0XFE,0XFE,0XFF));

	hero.setTextureRect(sf::IntRect(80, 0, 1, 1));
	rw.clear(sf::Color::White);
	rw.draw(hero);
	i = rw.capture();
	ASSERT_EQ(i.getPixel(0, 0),	sf::Color(0xFE,0xFE,0x00,0xFF));

	hero.setTextureRect(sf::IntRect(160, 0, 1, 1));
	rw.clear(sf::Color::White);
	rw.draw(hero);
	i = rw.capture();
	ASSERT_EQ(i.getPixel(0, 0), sf::Color(0x00, 0xFE, 0xFE, 0xFF));
	
	hero.setTextureRect(sf::IntRect(240, 0, 1, 1));
	rw.clear(sf::Color::White);
	rw.draw(hero);
	i = rw.capture();
	ASSERT_EQ(i.getPixel(0, 0), sf::Color(0x00, 0xFE, 0x00, 0xFF));

	hero.setTextureRect(sf::IntRect(320, 0, 1, 1));
	rw.clear(sf::Color::White);
	rw.draw(hero);
	i = rw.capture();
	ASSERT_EQ(i.getPixel(0, 0),	sf::Color(0xFE,0x00,0xFE,0xFF));

	hero.setTextureRect(sf::IntRect(400, 0, 1, 1));
	rw.clear(sf::Color::White);
	rw.draw(hero);
	i = rw.capture();
	ASSERT_EQ(i.getPixel(0, 0),	sf::Color(0xFE,0x00,0x00,0xFF));

	hero.setTextureRect(sf::IntRect(480, 0, 1, 1));
	rw.clear(sf::Color::White);
	rw.draw(hero);
	i = rw.capture();
	ASSERT_EQ(i.getPixel(0, 0),	sf::Color(0x00,0x00,0xFE,0xFF));

	hero.setTextureRect(sf::IntRect(560, 0, 1, 1));
	rw.clear(sf::Color::White);
	rw.draw(hero);
	i = rw.capture();
	ASSERT_EQ(i.getPixel(0, 0),	sf::Color(0x00,0x00,0x00,0xFF));

}
