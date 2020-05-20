#include "../headers/global.h"
#include "../headers/table.h"

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

void init_symbol_table() {
	if (!symbol_table.empty()) symbol_table.clear();
	std::unordered_map<std::string, table_entry> empty_table;
	symbol_table.push_back(empty_table);
	local_symbol_table_level = 0;
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
}

table_entry query_symbol_table(std::string &ident) {
	int current_table = local_symbol_table_level;
	while (current_table > 0 && symbol_table[current_table].find(ident) == symbol_table[current_table].end()) {
		current_table--;
	}
	if (symbol_table[current_table].find(ident) != symbol_table[current_table].end()) {
		return symbol_table[current_table][ident];
	} else {
		cout << "cannot find label " << ident << endl;
		table_entry tmp_{};
		return tmp_;
	}
}

void print_symbol_table(std::string &file, int which_table, bool append) {
	std::ostream table_stream(NULL);
	std::filebuf buffer;
	buffer.open(file, append ? std::ios::app : std::ios::out);
	table_stream.rdbuf(&buffer);
	if (which_table == 0) {
		table_stream << "/***** GLOBAL SYMBOL TABLE *****/" << endl;
	} else {
		table_stream << "/***** LOCAL SYMBOL TABLE "<<which_table<<" *****/" << endl;
	}
	for (const auto &i:symbol_table[which_table]) {
		table_stream << i.first << " " << itype_convert_table[i.second.itype] << " "
		             << dtype_convert_table[i.second.dtype] << " " << i.second.value << " " << i.second.address << endl;
	}
	table_stream << endl;
}
