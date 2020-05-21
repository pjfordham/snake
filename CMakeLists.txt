cmake_minimum_required(VERSION 3.10)

# set the project name
project(Snake VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include conan configuration
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# add the executable
add_executable(Snake snake.cc support.cc)

list(APPEND EXTRA_LIBS sfml-graphics)
list(APPEND EXTRA_LIBS sfml-window)
list(APPEND EXTRA_LIBS sfml-system)
target_link_libraries(Snake PUBLIC ${EXTRA_LIBS})
