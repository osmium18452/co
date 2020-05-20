cmake_minimum_required(VERSION 3.16)
project(co)

set(CMAKE_CXX_STANDARD 14)

add_executable(co main.cpp headers/readfile.h headers/global.h src/readfile.cpp headers/lex.h src/lex.cpp src/global.cpp headers/table.h src/table.cpp headers/sdt.h src/sdt.cpp headers/quadruple.h src/quadruple.cpp headers/expression.h src/expression.cpp headers/sdt_func_decl.h)