#ifndef CO_QUADRUPLE_H
#define CO_QUADRUPLE_H

#include "global.h"

enum instruct{
GVAR,VAR,PARAM,
ASSIGN,
ADD,SUB,MUL,DIV,
CMP,JZ,JNE,
};

struct quadruple_element{
	instruct instruct;
	std::string a;
	std::string b;
	std::string c;
};

void insert_quadruple(quadruple_element &element);

extern std::vector<quadruple_element> quadruple_list;
extern std::string instruct_convert_table[];

#endif //CO_QUADRUPLE_H
