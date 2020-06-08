#ifndef CO_REG_H
#define CO_REG_H

#include "global.h"

enum regs{
	EAX,EBX,ECX,EDX,MEM,
};

struct reg_table_unit{
	std::string var;
	int time_stamp;
};

std::string where_to_write_the_var(const std::string &var);
std::string where_is_the_var(const std::string &var);
std::string give_me_a_reg();
std::string where_to_put_it_in(const std::string &var);
std::string tell_me_the_address(const std::string &var);
void flush_the_regs();
#endif //CO_REG_H
