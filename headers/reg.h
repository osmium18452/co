#ifndef CO_REG_H
#define CO_REG_H

#include "global.h"

enum regs{
	EAX,EBX,ECX,EDX,MEM,IMM,
};

struct reg_table_unit{
	std::string var;
	int time_stamp;
};

extern std::string regs_convert_table[6];

std::string where_to_write_the_var(const std::string &var);
std::string where_is_the_var(const std::string &var);
std::string give_me_a_reg(const std::string &var);
std::string where_to_put_it_in(const std::string &var);
std::string tell_me_the_address(const std::string &var);
regs where_is_the_var_2(const std::string &var);
void flush_the_regs();
void init_reg_table();
void i_need_reg(regs reg,const std::string &var);
void write_the_reg_back(regs regs);
regs allocate_a_reg();
void change_reg_table_unit(regs regs,const std::string &var);
#endif //CO_REG_H
