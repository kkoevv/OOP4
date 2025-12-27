cmake_minimum_required(VERSION 3.10)

project(Lab4)

set(CMAKE_BUILD_TYPE Debug)

# Установка стандарта C++20 для всего проекта
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск пакета GoogleTest
find_package(GTest REQUIRED)

add_library(${PROJECT_NAME}_lib main.cpp)
target_include_directories(${PROJECT_NAME}_lib PUBLIC include)

add_executable(
    ${PROJECT_NAME}_exe main.cpp
)
set_target_properties(${PROJECT_NAME}_exe PROPERTIES OUTPUT_NAME "Lab_exe")

# Add debug information
target_compile_options(${PROJECT_NAME}_exe PRIVATE -g)

# Добавление тестов
enable_testing()

# Тестирование собственного класса Array
add_executable(Array_tests_Lab4 test/array_test.cpp)
target_include_directories(Array_tests_Lab4 PUBLIC include)
target_link_libraries(Array_tests_Lab4 GTest::gtest GTest::gtest_main pthread)

# Тестирование фигур
add_executable(Figures_tests_Lab4 test/figure_test.cpp)
target_include_directories(Figures_tests_Lab4 PUBLIC include)
target_link_libraries(Figures_tests_Lab4 GTest::gtest GTest::gtest_main pthread)

# Добавление тестов в тестовый набор
add_test(NAME Array_tests_Lab4 COMMAND Array_tests_Lab4)
add_test(NAME Figures_tests_Lab4 COMMAND Figures_tests_Lab4)