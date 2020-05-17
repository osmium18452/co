#ifndef CO_GLOBAL_H
#define CO_GLOBAL_H

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cctype>
#include <vector>
#include <sstream>

#define LL long long


enum token_type{
	TOK_CONST, TOK_IDENT,
	TOK_READ, TOK_WRITE,
	TOK_NIL,
	TOK_BLANK,
	TOK_SIGNED,     TOK_UNSIGNED,
	TOK_VOID,
	TOK_SHORT,      TOK_INT,        TOK_LONG,
	TOK_FLOAT,      TOK_DOUBLE,
	TOK_CHAR,
	TOK_IF,         TOK_ELSE,
	TOK_FOR,        TOK_WHILE,      TOK_DO,
	TOK_RETURN,
	TOK_COMMA,
	TOK_SEMICOLON,
	TOK_LPARE,      TOK_RPARE,
	TOK_LBRACKET,   TOK_RBRACKET,
	TOK_LBRACE,     TOK_RBRACE,
	TOK_INC,        TOK_DEC,
	TOK_BITNOT,     TOK_LOGINOT,
	TOK_PLUS,       TOK_SUB,
	TOK_MUL,        TOK_DIV,        TOK_MOD,
	TOK_SHL,        TOK_SHR,
	TOK_LT,         TOK_GT,
	TOK_LE,         TOK_GE,
	TOK_EQ,         TOK_NE,
	TOK_BITAND,     TOK_LOGIAND,
	TOK_BITOR,      TOK_LOGIOR,
	TOK_BITXOR,
	TOK_QM,         TOK_COLON,
	TOK_ASSIGN,
	TOK_INTCONST,   TOK_UINTCONST,
	TOK_SHORTCONST, TOK_USHORTCONST,
	TOK_LONGCONST,  TOK_ULONGCONST,
	TOK_FLOATCONST, TOK_DOUBLECONST,
	TOK_CHARCONST,  TOK_STRINGCONST,
	TOK_ADDASS,     TOK_SUBASS,
	TOK_SHLASS,     TOK_SHRASS,
	TOK_MULASS,     TOK_DIVASS,     TOK_MODASS
};

struct token{
	token_type type;
	signed short shortval;
	signed int intval;
	signed LL llval;
	unsigned short ushortval;
	unsigned int uintval;
	unsigned LL ullval;
	float floatval;
	double doubleval;
	char charval;
	std::string stringval;
};

extern std::string test_str;
extern std::vector<token> tokens;

#endif //CO_GLOBAL_H
