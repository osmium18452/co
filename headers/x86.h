#ifndef CO_X86_H
#define CO_X86_H
#include "global.h"

struct instruct_table_item{
	std::string instr;
	std::string arg1,arg2,arg3;
};

void translate_to_x86(std::string);

#endif //CO_X86_H
