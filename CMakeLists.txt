cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(solunar)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOLUNAR_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(external)
add_subdirectory(src)