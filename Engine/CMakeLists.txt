set (CMAKE_CXX_STANDARD 20)

include(conanbuildinfo.cmake)
conan_basic_setup()

add_library(Engine STATIC 
	"defines.h"
	"Unit.hpp"
	"Unit.cpp"
	"Scene.hpp"
	"Scene.cpp"
	"TailMap.hpp"
	"TailMap.cpp"
	"Character.hpp" 
	"Character.cpp"
	"Components/matrix.hpp"
	"Components/mass_data.hpp"
	"Components/file_manager.hpp"
 "Actor.hpp" "Actor.cpp")

target_link_libraries(Engine ${CONAN_LIBS})


