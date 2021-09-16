cmake_minimum_required(VERSION 3.2)

add_library(common strings.cpp)
target_include_directories(common PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

set(tests
    strings_gtest
)

set(test_prefix lib_common)
foreach (test ${tests})
    set(test_name ${test_prefix}_${test})
    add_executable(${test_name} unittests/${test}.cpp)
    target_include_directories(${test_name} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
    target_link_libraries(${test_name}
        gtest
        gmock
        gtest_main
        common
    )
    add_test(${test} ${test_name})
endforeach()
