project(Game)
cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 20)

include(conanbuildinfo.cmake)
conan_basic_setup()

# Add source to this project's executable.
add_executable (Game
	main.cpp
	"MainHero.h" 
	"MainHero.cpp"
)	


target_link_libraries(Game 
	${CONAN_LIBS}
	Engine
	SFGUI
)
target_include_directories(Game PRIVATE  
	"../SFGUI/include/"
	..
)