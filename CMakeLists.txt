cmake_minimum_required(VERSION 3.2)
project(wish)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-sign-compare")

enable_testing() #Must be called to enable test discovery by ctest
add_subdirectory(lib/common)
add_subdirectory(contrib/googletest)

add_executable(wish src/main.cpp)
target_link_libraries(wish PUBLIC common)
