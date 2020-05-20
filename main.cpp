#include "headers/global.h"
#include "headers/readfile.h"
#include "headers/lex.h"
#include "headers/table.h"
#include "headers/quadruple.h"
#include "headers/sdt.h"

using std::cout;
using std::cin;
using std::endl;

int main() {
//	freopen("../accessory-files/out2.txt","w",stdout);
	std::string token_file = "../testfile_dir/tokens.txt";
	std::string table_file = "../testfile_dir/table.txt";
	std::string quadruple_file = "../testfile_dir/quadruple.txt";
	std::string file = "../testfile_dir/in2.txt";
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
				token_stream << i << ": " << token_convert_table[tokens[i].type] << " " << tokens[i].shortval << endl;
				break;
			case TOK_USHORTCONST:
				token_stream << i << ": " << token_convert_table[tokens[i].type] << " " << tokens[i].ushortval << endl;
				break;
			case TOK_INTCONST:
				token_stream << i << ": " << token_convert_table[tokens[i].type] << " " << tokens[i].intval << endl;
				break;
			case TOK_UINTCONST:
				token_stream << i << ": " << token_convert_table[tokens[i].type] << " " << tokens[i].uintval << endl;
				break;
			case TOK_LONGCONST:
				token_stream << i << ": " << token_convert_table[tokens[i].type] << " " << tokens[i].llval << endl;
				break;
			case TOK_ULONGCONST:
				token_stream << i << ": " << token_convert_table[tokens[i].type] << " " << tokens[i].ullval << endl;
				break;
			case TOK_IDENT:
				token_stream << i << ": " << token_convert_table[tokens[i].type] << " " << tokens[i].stringval << endl;
				break;
			case TOK_FLOATCONST:
				token_stream << i << ": " << token_convert_table[tokens[i].type] << " " << tokens[i].floatval << endl;
				break;
			case TOK_DOUBLECONST:
				token_stream << i << ": " << token_convert_table[tokens[i].type] << " " << tokens[i].doubleval << endl;
				break;
			case TOK_CHARCONST:
				token_stream << i << ": " << token_convert_table[tokens[i].type] << " " << tokens[i].charval << endl;
				break;
			default:
				token_stream << i << ": " << token_convert_table[tokens[i].type] << " " << tokens[i].stringval << endl;
				break;
		}
	}
	curr_token = 0;
	local_symbol_table_level = 1;
	init_symbol_table();
	parse_program();
	cout << "global symbol table size: " << symbol_table[0].size() << endl;
	print_symbol_table(table_file,0, true);
	print_quadruple_list(quadruple_file);
	return 0;
}
