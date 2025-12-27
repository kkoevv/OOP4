cmake_minimum_required(VERSION 3.16)
project(GeometryApp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Основной исполняемый файл
add_executable(geometry_app
    src/main.cpp
)

target_include_directories(geometry_app PUBLIC include)

# Тесты (если нужны)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt")
    add_subdirectory(tests)
endif()