#include "../headers/quadruple.h"

std::vector<quadruple_element> quadruple_list;

std::string instruct_convert_table[] = {
		"VAR","PARAM",
		"ASSIGN",
		"ADD", "SUB", "MUL", "DIV",
		"CMP", "JZ", "JNE",
};

void gen_quadruple(instruct instruct,std::string &a, std::string &b, std::string &c){
	quadruple_element entry{instruct,a,b,c};
	quadruple_list.push_back(entry);
}