#pragma once
#include <iostream>
#include <cassert>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include <SFML/Graphics.hpp>



using namespace std::string_literals;



// \/\/\/MAIN VAR'S\/\/\/
constexpr size_t WINDOW_WIDTH = 500;
constexpr size_t WINDOW_HEIGHT = 500;
// /\/\/\MAIN VAR'S/\/\/\)



// \/\/\/LOGGER\/\/\/


#ifdef DEBUG

FILE* DLOGFILE___ = NULL;

#define DPRINT(str,...)	printf( (""s + std::string(str)).c_str() , __VA_ARGS__)

#define DASSERT(eq)		assert(eq)		

#define DLOG(str,...)											\
{																\
	if(DLOGFILE___ == NULL)										\
	{															\
		fopen_s( &DLOGFILE___, "logfile.log", "a" );			\
		time_t _t = time((0));									\
		fprintf(DLOGFILE___										\
			,	"--------------------------------------------\n"\
				"LOG SESASON STARTED AT TIME: %s\n"				\
			, ctime(&_t));										\
	}															\
	time_t _t = time((0));										\
	std::string to_output =										\
		"FILE: \""s		+ __FILE__ + "\""s+						\
		" | LINE: "s	+ std::to_string(__LINE__) +			\
		" | TIME: "s	+ ctime(&_t) +							\
		">>> "			+ std::string(str) + "\n";				\
	printf( to_output.c_str() , __VA_ARGS__ );					\
	fprintf( DLOGFILE___, to_output.c_str(), __VA_ARGS__ );		\
	fclose( DLOGFILE___ );										\
	fopen_s( &DLOGFILE___, "logfile.log", "a" );				\
}				

#else
#define DPIRIN		(...)
#define DASSERT		(...)
#define DLOG		(...)
#endif


// /\/\//\LOGGER/\/\/\)


namespace sf
{
	struct Point
	{
		float_t x;
		float_t y;
		auto operator<=>(const Point&) const = default;
	};
};

using P = sf::Point;
