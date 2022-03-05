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
		DLOG("HeroTest: OK");
	}
};

/*
TEST_F(HeroTest, HeroMove)
{
	hero->setPoint( P(20,30) );
	ASSERT_EQ(hero->getPoint(), P(20, 30));

	hero->move( P(1, -1) );
	ASSERT_EQ(hero->getPoint(), P(21, 29));
}
*/