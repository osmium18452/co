#include "headers/global.h"
#include "headers/readfile.h"
#include "headers/lex.h"

using std::cout;
using std::cin;
using std::endl;

std::string conver_table[]={
		"TOK_CONST", "TOK_IDENT",
		"TOK_READ","TOK_WRITE",
		"TOK_NIL",
		"TOK_BLANK",
		"TOK_SIGNED",     "TOK_UNSIGNED",
		"TOK_VOID",
		"TOK_SHORT",      "TOK_INT",        "TOK_LONG",
		"TOK_FLOAT",      "TOK_DOUBLE",
		"TOK_CHAR",
		"TOK_IF",         "TOK_ELSE",
		"TOK_FOR",        "TOK_WHILE",      "TOK_DO",
		"TOK_RETURN",
		"TOK_COMMA",
		"TOK_SEMICOLON",
		"TOK_LPARE",      "TOK_RPARE",
		"TOK_LBRACKET",   "TOK_RBRACKET",
		"TOK_LBRACE",     "TOK_RBRACE",
		"TOK_INC",        "TOK_DEC",
		"TOK_BITNOT",     "TOK_LOGINOT",
		"TOK_PLUS",       "TOK_SUB",
		"TOK_MUL",        "TOK_DIV",        "TOK_MOD",
		"TOK_SHL",        "TOK_SHR",
		"TOK_LT",         "TOK_GT",
		"TOK_LE",         "TOK_GE",
		"TOK_EQ",         "TOK_NE",
		"TOK_BITAND",     "TOK_LOGIAND",
		"TOK_BITOR",      "TOK_LOGIOR",
		"TOK_BITXOR",
		"TOK_QM",         "TOK_COLON",
		"TOK_ASSIGN",
		"TOK_INTCONST",   "TOK_UINTCONST",
		"TOK_SHORTCONST", "TOK_USHORTCONST",
		"TOK_LONGCONST",  "TOK_ULONGCONST",
		"TOK_FLOATCONST", "TOK_DOUBLECONST",
		"TOK_CHARCONST",  "TOK_STRINGCONST",
		"TOK_ADDASS",     "TOK_SUBASS",
		"TOK_SHLASS",     "TOK_SHRASS",
		"TOK_MULASS",     "TOK_DIVASS",     "TOK_MODASS",
};

int main() {
	freopen("../accessory-files/out2.txt","w",stdout);
	std::string s;
	std::string file = "../accessory-files/in2.txt";
	int token_num;
	s = readfile(file);
	cout<<s<<endl;
	token_num = get_token(s, false);
	for (int i = 0; i < token_num; i++) {
		switch (tokens[i].type) {
			case TOK_SHORTCONST:
				cout << conver_table[tokens[i].type] << " " << tokens[i].shortval << endl;
				break;
			case TOK_USHORTCONST:
				cout << conver_table[tokens[i].type] << " " << tokens[i].ushortval << endl;
				break;
			case TOK_INTCONST:
				cout << conver_table[tokens[i].type] << " " << tokens[i].intval << endl;
				break;
			case TOK_UINTCONST:
				cout << conver_table[tokens[i].type] << " " << tokens[i].uintval << endl;
				break;
			case TOK_LONGCONST:
				cout << conver_table[tokens[i].type] << " " << tokens[i].llval << endl;
				break;
			case TOK_ULONGCONST:
				cout << conver_table[tokens[i].type] << " " << tokens[i].ullval << endl;
				break;
			case TOK_IDENT:
				cout << conver_table[tokens[i].type] << " " << tokens[i].stringval << endl;
				break;
			case TOK_FLOATCONST:
				cout << conver_table[tokens[i].type] << " " << tokens[i].floatval << endl;
				break;
			case TOK_DOUBLECONST:
				cout << conver_table[tokens[i].type] << " " << tokens[i].doubleval << endl;
				break;
			case TOK_CHARCONST:
				cout << conver_table[tokens[i].type] << " " << tokens[i].charval << endl;
				break;
			default:
				cout << conver_table[tokens[i].type] << " " << tokens[i].stringval << endl;
				break;
		}
	}
	cout<<token_num<<endl;
	return 0;
}
