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
		DLOG("HeroTest: END")
	}
};

TEST_F(HeroTest, HeroMoveTest)
{
	DLOG("HERO MOVE TEST START")
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
	DLOG("HERO MOVE TEST END")
}

TEST_F(HeroTest, HeroDrawTest)
{
	DLOG("HERO DRAW TEST START")
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
	DLOG("HERO DRAW TEST END")
}
