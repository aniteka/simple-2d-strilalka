project(Strelalka)
cmake_minimum_required (VERSION 2.8.12)
set (CMAKE_CXX_STANDARD 20)

include(conanbuildinfo.cmake)
conan_basic_setup()

# Add source to this project's executable.
add_executable (Strelalka 
	main.cpp 
	Hero.cpp
	"defines.h" 
	"Unit.hpp"
	"Hero.hpp"
 "Tests/Hero.test.hpp" "Tests/main.test.hpp")

target_link_libraries(Strelalka ${CONAN_LIBS})