#include "headers/global.h"
#include "headers/readfile.h"
#include "headers/lex.h"
#include "headers/table.h"
#include "headers/quadruple.h"
#include "headers/sdt.h"
#include "headers/expression.h"
#include "headers/utils.h"
#include "headers/x86.h"
#include "headers/reg.h"

using std::cout;
using std::cin;
using std::endl;

int main(int argc, char **argv) {
	std::string token_file = "../testfile_dir/tokens.txt";
	std::string table_file = "../testfile_dir/table.txt";
	std::string quadruple_file = "../testfile_dir/quadruple.txt";
	std::string para_table_file = "../testfile_dir/para_table.txt";
	std::string string_file = "../testfile_dir/string_table.txt";
	std::string x86_file="../testfile_dir/x86.asm";
	std::string file = "../demos/qsort.c";
	if (argc > 1) file = argv[2];
	std::string s;
	s = readfile(file);
	cout << s << endl;
	get_token(s, false);
	print_token_table(token_file);
	cout << "tokens size: " << tokens.size() << endl;
	curr_token = 0;
	init_symbol_table();
	init_param_table();
	init_string_table();
	init_temp_var();
	init_temp_label();
	parse_program();
	cout << "global symbol table size: " << symbol_table[0].size() << endl;
	print_symbol_table(table_file, 0, true);
	print_quadruple_list(quadruple_file);
	print_string_table(string_file);
	cout << "quadruple list size: " << quadruple_list.size() << endl;
	init_local_symbol_table();
	init_reg_table();
	cout<<"symbol table size :"<<symbol_table.size()<<endl;
	translate_to_x86();
	print_x86_table(x86_file);
	return 0;
}
