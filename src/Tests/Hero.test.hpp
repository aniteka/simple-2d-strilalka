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
		DLOG("HeroTest: OK")
	}
};

TEST_F(HeroTest, HeroMove)
{
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
}