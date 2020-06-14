cmake_minimum_required(VERSION 3.16)
project(co)

set(CMAKE_CXX_STANDARD 14)

add_executable(co main.cpp
		headers/readfile.h
		headers/global.h
		headers/lex.h
		headers/table.h
		headers/sdt.h
		headers/quadruple.h
		headers/expression.h
		headers/sdt_func_decl.h
		headers/expression_func_def.h
		headers/utils.h src/utils.cpp
		headers/x86.h
		headers/reg.h
		headers/x86_func_def.h
		headers/reg_func_def.h
		src/readfile.cpp
		src/lex.cpp
		src/global.cpp
		src/table.cpp
		src/sdt.cpp
		src/quadruple.cpp
		src/expression.cpp
		src/x86.cpp
		src/regs.cpp headers/error.h src/error.cpp headers/optimizer.h src/optimizer.cpp headers/optimizer_func_def.h)
