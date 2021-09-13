cmake_minimum_required(VERSION 3.2)

add_library(utils utils.cpp)
target_include_directories(utils PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
