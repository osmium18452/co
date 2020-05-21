#ifndef CO_QUADRUPLE_H
#define CO_QUADRUPLE_H

#include "global.h"

enum instruct{
GVAR,VAR,
PARAM,FUNC,
ASSIGN,
ADD,SUB,MUL,DIV,
CMP,JZ,JNE,
END,
PRINT,SCAN,
COMMA,LABEL,
LOGIAND,LOGIOR,
TEMP,
BITAND,BITOR,BITXOR,
NE,EQ,
SHL,SHR,
LT,LE,GT,GE,
};

struct quadruple_element{
	instruct instruct;
	std::string a;
	std::string b;
	std::string c;
};

void insert_to_quadruple_list(quadruple_element &element);
void print_quadruple_list(std::string &file);

extern std::vector<quadruple_element> quadruple_list;
extern std::string instruct_convert_table[];

#endif //CO_QUADRUPLE_H
