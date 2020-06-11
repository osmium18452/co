#ifndef CO_QUADRUPLE_H
#define CO_QUADRUPLE_H

#include "global.h"

enum instruct {
	GVAR, VAR,
	PARAM, FUNC,
	ASSIGN,
	ADD, SUB, MUL, DIV, MOD,
	CMP, JE, JNE, JMP, JA, JB,SWJMP,
	END,
	PRINT, SCAN,
	COMMA, LABEL,
	LOGIAND, LOGIOR,
	TEMP,
	BITAND, BITOR, BITXOR,BITNOT,
	NE, EQ,
	SHL, SHR,
	LT, LE, GT, GE,
	INC, DEC, NOT, REVERSE,
	PUSH, POP,
	CALL, RET, GETRET,
	RDARR, WRARR,
	KASE_ITEM,
	CREATE_TABLE,DESTROY_TABLE,
	SAVE_REG,RESTORE_REG,
	RESTORE_STACK,
	FLUSH_REG,FLUSH_REGTABLE,
};

struct quadruple_element {
	instruct instruct;
	std::string a;
	std::string b;
	std::string c;
};

void insert_to_quadruple_list(quadruple_element &element);

void print_quadruple_list(std::string &file);

extern std::vector<quadruple_element> quadruple_list;
extern std::string instruct_convert_table[];

#endif //CO_QUADRUPLE_H
