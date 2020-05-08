cmake_minimum_required(VERSION 3.16)
project(co)

set(CMAKE_CXX_STANDARD 14)

add_executable(co main.cpp headers/readfile.h headers/global.h src/readfile.cpp)