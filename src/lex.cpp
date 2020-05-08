#include "../headers/global.h"
#include "../headers/lex.h"

std::unordered_set<char> blank_set({' ', '\t', '\v', '\f', '\n', '\r',});

std::unordered_map<char, char> convert_table({
	{'a', '\a'},
	{'b', '\b'},
	{'t', '\t'},
	{'v', '\v'},
	{'f', '\f'},
	{'n', '\n'},
	{'r', '\r'},
                                             });

std::unordered_map<std::string, token_type> string_to_token({
	{"const",    TOK_CONST},
	{"signed",   TOK_SIGNED},   {"unsigned", TOK_UNSIGNED},
	{"void",     TOK_VOID},
	{"char",     TOK_CHAR},
	{"int",      TOK_INT},      {"short",    TOK_SHORT},    {"long",     TOK_LONG},
	{"float",    TOK_FLOAT},    {"double",   TOK_DOUBLE},
	{"if",       TOK_IF},       {"else",     TOK_ELSE},
	{"for",      TOK_FOR},      {"while",    TOK_WHILE},    {"do",       TOK_DO},
	{"return",   TOK_RETURN},
	{",",        TOK_COMMA},
	{";",        TOK_SEMICOLON},
	{"(",        TOK_LPARE},    {")",        TOK_RPARE},
	{"[",        TOK_LBRACKET}, {"]",        TOK_RBRACKET},
	{"{",        TOK_LBRACE},   {"}",        TOK_RBRACE},
	{"++",       TOK_INC},      {"--",       TOK_DEC},
	{"~",        TOK_BITNOT},   {"!",        TOK_LOGINOT},
	{"*",        TOK_MUL},      {"/",        TOK_DIV},      {"%",        TOK_MOD},
	{"+",        TOK_PLUS},     {"-",        TOK_SUB},
	{"<<",       TOK_SHL},      {">>",       TOK_SHR},
	{"<",        TOK_LT},       {">",        TOK_GT},
	{"<=",       TOK_LE},       {">=",       TOK_GE},
	{"==",       TOK_EQ},       {"!=",       TOK_NE},
	{"&",        TOK_BITAND},   {"^",        TOK_BITXOR},   {"|",        TOK_BITOR},
	{"&&",       TOK_LOGIAND},  {"||",       TOK_LOGIOR},
	{"?",        TOK_QM},       {":",        TOK_COLON},
	{"=",        TOK_ASSIGN},
                                                            });