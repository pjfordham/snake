cmake_minimum_required(VERSION 3.10)

# set the project name
project(Snake VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include conan configuration
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(SFML_STATIC_LIBRARIES ON)
find_package(SFML 2.5.1 REQUIRED system window graphics)

# add the executable
add_executable(Snake snake.cc support.cc)
target_link_libraries(Snake sfml-system sfml-window sfml-graphics)
