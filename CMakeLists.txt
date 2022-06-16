cmake_minimum_required(VERSION 3.10)

# set the project name
project(Snake VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(Snake snake.cc)
target_link_libraries(Snake sfml-system sfml-window sfml-graphics)
