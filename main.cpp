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
	std::string file = "../testfile_dir/in2.txt";
	if (argc > 1) file = argv[2];
	std::ostream token_stream(NULL);
	std::filebuf token_buffer;
	token_buffer.open(token_file, std::ios_base::out);
	token_stream.rdbuf(&token_buffer);
	std::string s;
	int token_num;
	s = readfile(file);
	cout << s << endl;
	token_num = get_token(s, false);
	cout << "tokens size: " << tokens.size() << endl;
	for (int i = 0; i < token_num; i++) {
		switch (tokens[i].type) {
			case TOK_SHORTCONST:
				token_stream << i << ": " << token_convert_table[tokens[i].type] << " " << tokens[i].shortval << " "
				             << tokens[i].line_num << endl;
				break;
			case TOK_USHORTCONST:
				token_stream << i << ": " << token_convert_table[tokens[i].type] << " " << tokens[i].ushortval << " "
				             << tokens[i].line_num << endl;
				break;
			case TOK_INTCONST:
				token_stream << i << ": " << token_convert_table[tokens[i].type] << " " << tokens[i].intval << " "
				             << tokens[i].line_num << endl;
				break;
			case TOK_UINTCONST:
				token_stream << i << ": " << token_convert_table[tokens[i].type] << " " << tokens[i].uintval << " "
				             << tokens[i].line_num << endl;
				break;
			case TOK_LONGCONST:
				token_stream << i << ": " << token_convert_table[tokens[i].type] << " " << tokens[i].llval << " "
				             << tokens[i].line_num << endl;
				break;
			case TOK_ULONGCONST:
				token_stream << i << ": " << token_convert_table[tokens[i].type] << " " << tokens[i].ullval << " "
				             << tokens[i].line_num << endl;
				break;
			case TOK_IDENT:
				token_stream << i << ": " << token_convert_table[tokens[i].type] << " " << tokens[i].stringval << " "
				             << tokens[i].line_num << endl;
				break;
			case TOK_FLOATCONST:
				token_stream << i << ": " << token_convert_table[tokens[i].type] << " " << tokens[i].floatval << " "
				             << tokens[i].line_num << endl;
				break;
			case TOK_DOUBLECONST:
				token_stream << i << ": " << token_convert_table[tokens[i].type] << " " << tokens[i].doubleval << " "
				             << tokens[i].line_num << endl;
				break;
			case TOK_CHARCONST:
				token_stream << i << ": " << token_convert_table[tokens[i].type] << " " << tokens[i].charval << " "
				             << tokens[i].line_num << endl;
				break;
			default:
				token_stream << i << ": " << token_convert_table[tokens[i].type] << " " << tokens[i].stringval << " "
				             << tokens[i].line_num << endl;
				break;
		}
	}
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
