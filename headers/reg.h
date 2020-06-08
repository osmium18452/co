#ifndef CO_REG_H
#define CO_REG_H

#include "global.h"

enum regs{
	EAX,EBX,ECX,EDX,MEM,
};
extern std::string regs_convert_table[5];

regs where_is_the_var(const std::string &var);
#endif //CO_REG_H
