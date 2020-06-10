#include "../headers/reg.h"
#include "../headers/table.h"
#include "../headers/x86.h"
#include "../headers/reg_func_def.h"
#include "../headers/utils.h"

int time_stamp;
reg_table_unit reg_table[4];

void init_reg_table(){
	time_stamp=0;
	for (auto i:reg_table){
		i.time_stamp=0;
		i.var=NONE;
	}
}

std::string regs_convert_table[6]={
		"eax","ebx","ecx","edx","mem","imm",
};


std::string tell_me_the_address(const std::string &var) {
	if (is_num(var)) return var;
	table_entry entry{};
	std::string ret;
	query_symbol_table(var, entry);
	if (entry.table_level == l)
		ret = "[ebp" + (entry.address < 0 ? std::to_string(entry.address) + "]" : "+" + std::to_string(entry.address) + "]");
	else ret = "[g_"+var+"]";
	return ret;
}
std::string where_to_write_the_var(const std::string &var){
	std::string ret;
	regs regs=where_is_the_var_2(var);
	if (regs==MEM) return tell_me_the_address(var);
	else {
		reg_table[regs].time_stamp=++time_stamp;
		return regs_convert_table[regs];
	}
}
std::string where_is_the_var(const std::string &var){
	if(is_num(var)) return "dword "+var;
	std::string ret;
	regs reg=where_is_the_var_2(var);
	if (reg==MEM) return "dword "+tell_me_the_address(var);
	else {
		reg_table[reg].time_stamp=++time_stamp;
		return regs_convert_table[reg];
	}
}
std::string give_me_a_reg(const std::string &var){
	regs reg=where_is_the_var_2(var);
	if (reg < 4) return regs_convert_table[reg];
	else {
		int min_ts=INF;
		int min_reg=-1;
		for (int i=0;i<4;i++){
			if (reg_table[i].time_stamp<min_ts) min_ts=reg_table[i].time_stamp,min_reg=i;
		}
		write_the_reg_back(static_cast<regs>(min_reg));
		reg_table[min_reg].var=var;
		reg_table[min_reg].time_stamp=++time_stamp;
		return regs_convert_table[min_reg];
	}
}

regs allocate_a_reg(){
	int min_ts=INF;
	int min_reg=-1;
	for (int i=0;i<4;i++){
		if (reg_table[i].time_stamp<min_ts) min_ts=reg_table[i].time_stamp,min_reg=i;
	}
	write_the_reg_back(static_cast<regs>(min_reg));
	reg_table[min_reg].var=NONE;
	reg_table[min_reg].time_stamp=++time_stamp;
	return static_cast<regs>(min_reg);
}

void change_reg_table_unit(regs regs,const std::string &var){
	reg_table[regs].var=var;
}

void write_the_reg_back(regs regs){
	if (reg_table[regs].var==NONE) return;
	insert_into_x86_table("mov "+tell_me_the_address(reg_table[regs].var)+","+regs_convert_table[regs]);
}

std::string where_to_put_it_in(const std::string &var){
/*i forget what this func is supposed to do...*/
	std::string ret;
	return ret;
}
void flush_the_regs(){
	for (int i=0;i<4;i++){
		write_the_reg_back(static_cast<regs>(i));
		reg_table[i].var=NONE;
		reg_table[i].time_stamp=++time_stamp;
	}
}

regs where_is_the_var_2(const std::string &var){
	if (is_num(var)) return IMM;
	for (int i=0;i<4;i++){
		if (reg_table[i].var==var) return static_cast<regs>(i);
	}
	return MEM;
}

void i_need_reg(regs reg,const std::string &var){
	write_the_reg_back(reg);
	insert_into_x86_table("mov "+regs_convert_table[reg]+","+tell_me_the_address(var));
	reg_table[reg].var=var;
}