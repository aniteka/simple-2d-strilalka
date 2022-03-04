project(Mehanika_)
cmake_minimum_required (VERSION 2.8.12)
set (CMAKE_CXX_STANDARD 20)

include(conanbuildinfo.cmake)
conan_basic_setup()

# Add source to this project's executable.
add_executable (Mehanika_ main.cpp "defines.h" "Unit.hpp")

target_link_libraries(Mehanika_ ${CONAN_LIBS})