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
#include "headers/error.h"
#include "headers/optimizer.h"

using std::cout;
using std::cin;
using std::endl;

int main(int argc, char **argv) {
	std::vector<std::string> args;
	if (argc < 2) {
		cout << "you must specify a file for the compiler or type \"co -h\" for help." << endl;
		return 0;
	}
	args.reserve(argc);
	for (int i = 0; i < argc; i++) {
		args.emplace_back(argv[i]);
	}
	if (args[1] == "-h" || args[1] == "--help") {
		cout << "co <input_file> [option][file]" << endl;
		cout << "options:" << endl;
		cout << "-h --help: show this guide." << endl;
		cout << "-k --tokens: set the file that write the tokens in." << endl;
		cout << "-b --table: set the file that write the symbol table in." << endl;
		cout << "-q --quadruple: set the file that write the quadruples in." << endl;
		cout << "-p --param: set the file that write the paramater table in." << endl;
		cout << "-s --string: set the file that write the string table in." << endl;
		cout << "-x --x86: set the file that write the x86 asm in." << endl;
		cout << "-o --output: set the name of the executable file." << endl;
		cout << "-O : use optimization" << endl;
		return 0;
	}
	std::string token_file = "../testfile_dir/tokens.txt";
	std::string table_file = "../testfile_dir/table.txt";
	std::string quadruple_file = "../testfile_dir/quadruple.txt";
	std::string para_table_file = "../testfile_dir/para_table.txt";
	std::string string_file = "../testfile_dir/string_table.txt";
	std::string x86_file = "../testfile_dir/x86.asm";
	bool print_which[5] = {false};
	bool optimizee = false;
	for (int i = 2; i < argc; i += 2) {
		if (args[i] == "-k" || args[i] == "--tokens") {
			print_which[0] = true;
			if (args[i + 1] != "default") token_file = args[i + 1];
		}
		if (args[i] == "-b" || args[i] == "--table") {
			print_which[1] = true;
			if (args[i + 1] != "default") table_file = args[i + 1];
		}
		if (args[i] == "-q" || args[i] == "--quadruple") {
			print_which[2] = true;
			if (args[i + 1] != "default") quadruple_file = args[i + 1];
		}
		if (args[i] == "-p" || args[i] == "--param") {
			print_which[3] = true;
			if (args[i + 1] != "default") para_table_file = args[i + 1];
		}
		if (args[i] == "-s" || args[i] == "--string") {
			print_which[4] = true;
			if (args[i + 1] != "default") string_file = args[i + 1];
		}
		if (args[i] == "-x" || args[i] == "--x86") {
			if (args[i + 1] != "default") x86_file = args[i + 1];
		}
		if (args[i] == "-O") {
			optimizee = true;
		}
	}
	std::string file = args[1];
	std::string s;
	s = readfile(file);
	cout << s << endl;
	get_token(s, false);
	if (print_which[0]) print_token_table(token_file);
	curr_token = 0;
	init_symbol_table();
	init_param_table();
	init_string_table();
	init_temp_var();
	init_temp_label();
	init_error_warning_handler();
	parse_program();
	error_warning_handler_summary();
	if (print_which[2])print_quadruple_list(quadruple_file);
	if (print_which[4])print_string_table(string_file);
	init_local_symbol_table();
	init_reg_table();
	translate_to_x86();
	if (optimizee) optimize();
	print_x86_table(x86_file);
	return 0;
}
