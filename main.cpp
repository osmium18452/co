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
	std::ostream token_stream(NULL), table_stream(NULL);
	std::string token_file = "../testfile_dir/tokens.txt";
	std::string table_file = "../testfile_dir/table.txt";
	std::filebuf token_buffer, table_buffer;
	token_buffer.open(token_file, std::ios_base::out);
	table_buffer.open(table_file, std::ios_base::out);
	token_stream.rdbuf(&token_buffer);
	table_stream.rdbuf(&table_buffer);
	std::string s;
	std::string file = "../testfile_dir/in2.txt";
	int token_num;
	s = readfile(file);
	cout << s << endl;
	token_num = get_token(s, false);
	cout << "tokens size: "<<tokens.size()<<endl;
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
//	cout << token_num << endl;
	curr_token=0;
	parse_program();
	cout<<"global symbol table size: "<<global_symbol_table.size()<<endl;
	for (const auto& i:global_symbol_table) {
		table_stream << i.first << " " << itype_convert_table[i.second.itype] << " "
		             << dtype_convert_table[i.second.dtype] << " " << i.second.value << " " << i.second.address << endl;
	}
	return 0;
}
