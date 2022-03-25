project(Strelalka)
cmake_minimum_required (VERSION 2.8.12)
set (CMAKE_CXX_STANDARD 20)

include(conanbuildinfo.cmake)
conan_basic_setup()

# Add source to this project's executable.
add_executable (${PROJECT_NAME} 
	main.cpp
	"Engine/defines.h"
	"Engine/Unit.cpp"
	"Engine/Unit.hpp"
	"Engine/Hero.cpp"
	"Engine/Hero.hpp"
	"Engine/TailMap.hpp"
	"Engine/TailMap.cpp"
	"Engine/Components/mass_data.hpp"
	"Engine/Components/matrix.hpp"
	"Engine/Components/file_manager.hpp"
)	

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
target_include_directories(${PROJECT_NAME} PRIVATE .)