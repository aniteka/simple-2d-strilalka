#ifndef DEFINES_H
#define DEFINES_H

#define DEBUG
//#define TESTING
#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <array>
#include <thread>
#include <mutex>
#include <atomic>

#include <gtest/gtest.h>
#include <SFML/Graphics.hpp>



using namespace std::string_literals;
using namespace std::chrono_literals;



// \/\/\/LOGGER\/\/\/


#ifdef DEBUG
inline FILE* DLOGFILE___ = NULL;
inline std::string DLOGFILENAME___;

#define DPRINT(str,...)	printf( (""s + std::string(str)).c_str() , __VA_ARGS__)

#define DASSERT(eq)		assert(eq)		

#define DLOG(str,...)											\
{																\
	if(DLOGFILE___ == NULL)										\
	{															\
		DLOGFILENAME___											\
			= "LogFiles\\logfile_"s								\
			+ std::to_string(time(0))							\
			+ ".log"s;											\
		fopen_s( &DLOGFILE___, DLOGFILENAME___.c_str(), "a" );	\
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
	fopen_s( &DLOGFILE___, DLOGFILENAME___.c_str(), "a" );		\
}(void)(0)

#else
#define DPIRIN(...)
#define DASSERT(...)
#define DLOG(...)	
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
using VF = sf::Vector2f;
using VI = sf::Vector2i;

#endif
