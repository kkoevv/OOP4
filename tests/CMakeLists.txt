cmake_minimum_required(VERSION 3.16)

find_package(GTest REQUIRED)

add_executable(geometry_tests
    test_main.cpp
    test_point.cpp
    test_figures.cpp
    test_array.cpp
)

target_include_directories(geometry_tests PUBLIC ../include)
target_link_libraries(geometry_tests GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(geometry_tests)