#include "../headers/quadruple.h"

std::vector<quadruple_element> quadruple_list;

std::string instruct_convert_table[] = {
		"GVAR", "VAR",
		"PARAM", "FUNC",
		"ASSIGN",
		"ADD", "SUB", "MUL", "DIV", "MOD",
		"CMP", "JE", "JNE", "JMP", "JA", "JB","SWJMP",
		"END",
		"PRINT", "SCAN",
		"COMMA", "LABEL",
		"LOGI_AND", "LOGI_OR",
		"TEMP",
		"BITAND", "BITOR", "BITXOR","BITNOT",
		"NE", "EQ",
		"SHL", "SHR",
		"LT", "LE", "GT", "GE",
		"INC", "DEC", "NOT", "REVERSE",
		"PUSH", "POP",
		"CALL", "RET", "GETRET",
		"RDARR", "WRARR",
		"KASE_ITEM",
		"CREATE_TABLE","DESTROY_TABLE",
		"SAVE_REG","RESTORE_REG",
		"RESTORE_STACK",
};

void insert_to_quadruple_list(quadruple_element &element) {
	quadruple_list.push_back(element);
}

void print_quadruple_list(std::string &file) {
	std::ostream quadruple_stream(NULL);
	std::filebuf buffer;
	buffer.open(file, std::ios::out);
	quadruple_stream.rdbuf(&buffer);
	for (const auto &i:quadruple_list) {
		quadruple_stream << instruct_convert_table[i.instruct] << " " << i.a << " " << i.b << " " << i.c << endl;
	}
	quadruple_stream << endl;
}