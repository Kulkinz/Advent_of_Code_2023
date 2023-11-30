cmake_minimum_required(VERSION 3.23)
project(Advent_of_Code_2023)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Helpers)
list(APPEND EXTRA_LIBS Helpers)
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/Helpers")

add_executable(Day1 day1.cpp Helpers/helper.cpp)
