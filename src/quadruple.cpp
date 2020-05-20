#include "../headers/quadruple.h"

std::vector<quadruple_element> quadruple_list;

std::string instruct_convert_table[] = {
		"GVAR","VAR",
		"PARAM","FUNC",
		"ASSIGN",
		"ADD", "SUB", "MUL", "DIV",
		"CMP", "JZ", "JNE",
		"END",
};

void insert_quadruple(quadruple_element &element){
	quadruple_list.push_back(element);
}