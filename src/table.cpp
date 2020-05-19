#include "../headers/global.h"
#include "../headers/table.h"

std::unordered_map<std::string, table_entry> global_symbol_table;
std::unordered_map<std::string, table_entry> local_symbol_table;
std::vector<std::unordered_map<std::string, table_entry>> symbol_table;
int local_symbol_table_level;

std::string itype_convert_table[] = {
		"IDN_CONST", "IDN_VAR", "IDN_ARRAY", "IDN_FUNCTION"
};

std::string dtype_convert_table[] = {
		"DATA_SHORT", "DATA_INT", "DATA_LONG",
		"DATA_FLOAT", "DATA_DOUBLE",
		"DATA_CHAR", "DATA_VOID"
};

void init_symbol_table(){
	if (!symbol_table.empty()) symbol_table.clear();
	std::unordered_map<std::string, table_entry> empty_table;
	symbol_table.push_back(empty_table);
	symbol_table.push_back(empty_table);
	local_symbol_table_level=1;
}

void create_new_local_table() {
	std::unordered_map<std::string, table_entry> empty_table;
	symbol_table.push_back(empty_table);
	local_symbol_table_level++;
}

void destroy_current_local_table() {
	symbol_table.pop_back();
	local_symbol_table_level--;
}

void insert_to_symbol_table(scope gol, std::string &ident, table_entry entry) {
	int table_level = gol == GLOBAL ? 0 : local_symbol_table_level;
	if (symbol_table[table_level].find(ident) == symbol_table[table_level].end()) {
		symbol_table[table_level][ident] = entry;
	} else {
		cout << "identifier " << ident << " has already been defined." << endl;
	}

	/*std::unordered_map<std::string, table_entry> &table = gol == GLOBAL ? global_symbol_table : local_symbol_table;
	if (table.find(ident)==table.end()){
		table[ident]=entry;
	} else {
		cout<<"identifier "<<ident<<" has already been defined."<<endl;
	}*/
}

table_entry query_symbol_table(std::string &ident) {
	int current_table = local_symbol_table_level;
	while (current_table > 0 && symbol_table[current_table].find(ident) == symbol_table[current_table].end()) {
		current_table--;
	}
	if (symbol_table[current_table].find(ident)!=symbol_table[current_table].end()){
		return symbol_table[current_table][ident];
	} else {
		cout<<"cannot find label "<<ident<<endl;
		table_entry tmp_{};
		return tmp_;
	}
	/*std::unordered_map<std::string, table_entry> table = gol == GLOBAL ? global_symbol_table : local_symbol_table;
	if (table.find(ident)==table.end()){
		cout<<"identifier "<<ident<<" has not been defined."<<endl;
		table_entry t{};
		return t;
	} else {
		return table[ident];
	}*/
}

