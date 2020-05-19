#ifndef CO_QUADRUPLE_H
#define CO_QUADRUPLE_H

#include "global.h"

enum instruct{
VAR,PARAM,
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

void gen_quadruple(instruct instruct,std::string a, std::string b, std::string c);

extern std::vector<quadruple_element> quadruple_list;
extern std::string instruct_convert_table[];

#endif //CO_QUADRUPLE_H
