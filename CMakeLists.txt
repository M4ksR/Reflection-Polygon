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

set_target_properties(Reflection-Polygon PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "$<1:${CMAKE_SOURCE_DIR}>"
    PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
