#ifndef CO_X86_H
#define CO_X86_H
#include "global.h"
#define INT_SIZE 4

/*struct instruct_table_item{
	std::string instr;
	std::string arg1,arg2,arg3;
};*/

//extern std::unordered_map<std::string, std::string> string_table;

void translate_to_x86();
void print_x86_table(const std::string &file);


#endif //CO_X86_H
