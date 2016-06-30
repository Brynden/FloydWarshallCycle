cmake_minimum_required(VERSION 3.5)
project(Laboratorio_3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES matriz.c)
add_executable(Laboratorio_3 ${SOURCE_FILES})