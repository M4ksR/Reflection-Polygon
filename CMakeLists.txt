cmake_minimum_required(VERSION 3.16)

project(ReflectionPolygon LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Reflection-Polygon
    main.cpp
    source/bmp.cpp
    source/clipping.cpp
    source/matrix.cpp
    source/projection.cpp
    source/reflection.cpp
)

target_include_directories(Reflection-Polygon PRIVATE
    headers
)
