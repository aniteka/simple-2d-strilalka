#pragma once
#include "../defines.h"
#include "Hero.test.hpp"

int main_test(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}