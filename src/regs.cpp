#include "../headers/reg.h"
#include "../headers/table.h"

std::string regs_convert_table[5]={
		"EAX","EBX","ECX","EDX","MEM",
};

std::string tell_me_the_address(const std::string &var) {
	table_entry entry{};
	std::string ret;
	query_symbol_table(var, entry);
	if (entry.table_level == l)
		ret = "[ebp" + (entry.address < 0 ? std::to_string(entry.address) + "]" : "+" + std::to_string(entry.address) + "]");
	else ret = var;
	return ret;
}
