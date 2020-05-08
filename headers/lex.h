#ifndef CO_LEX_H
#define CO_LEX_H

#include "global.h"

enum token_type{
	TOK_CONST,
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
	TOK_CHARCONST,  TOK_STRINGCONST
};

enum state_type{
	STAT_START,
	STAT_IDENT,
	STAT_INT,STAT_DBL,STAT_FLT,STAT_UINT,STAT_ULONG,
	STAT_CHAR1,STAT_CHAR2,STAT_CHAR3,STAT_CHAR4,STAT_CHAR5,
	STAT_STR1,STAT_STR2,STAT_STR3,STAT_STR4,STAT_STR5,
	STAT_SMBL,
	STAT_PLUS,STAT_INCR,
	STAT_SUB,STAT_DECR,
	STAT_BAND,STAT_AND,
	STAT_BOR,STAT_OR,
	STAT_NOT,STAT_NE,
	STAT_ASGN,STAT_EQ,
	STAT_GT,STAT_SR,STAT_GE,
	STAT_LT,STAT_SL,STAT_LE,
	STAT_BLANK
};

int get_token(std::string s);

#endif //CO_LEX_H
