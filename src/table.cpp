#include "../headers/global.h"
#include "../headers/table.h"

std::unordered_map<std::string, table_entry> global_symbol_table;
std::unordered_map<std::string, table_entry> local_symbol_table;

std::string itype_convert_table[]={
		"IDN_CONST", "IDN_VAR", "IDN_ARRAY", "IDN_FUNCTION"
};

std::string dtype_convert_table[]={
		"DATA_SHORT", "DATA_INT", "DATA_LONG",
		"DATA_FLOAT", "DATA_DOUBLE",
		"DATA_CHAR", "DATA_VOID"
};

void insert(scope gol, std::string &ident, table_entry entry) {
	std::unordered_map<std::string, table_entry> &table = gol == GLOBAL ? global_symbol_table : local_symbol_table;
	if (table.find(ident)==table.end()){
		table[ident]=entry;
	} else {
		cout<<"identifier "<<ident<<" has already been defined."<<endl;
	}
}

table_entry query(scope gol, std::string &ident) {
	std::unordered_map<std::string, table_entry> table = gol == GLOBAL ? global_symbol_table : local_symbol_table;
	if (table.find(ident)==table.end()){
		cout<<"identifier "<<ident<<" has not been defined."<<endl;
		table_entry t{};
		return t;
	} else {
		return table[ident];
	}
}

