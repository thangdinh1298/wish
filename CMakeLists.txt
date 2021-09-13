cmake_minimum_required(VERSION 3.2)
project(wish)

add_subdirectory(lib/common)

add_executable(wish src/main.cpp)
target_link_libraries(wish PUBLIC utils)
