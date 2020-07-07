#ifndef CO_X86_H
#define CO_X86_H

#include "global.h"

#define INT_SIZE 4

enum _instr {
	_mov_,
	_pop_, _push_,
	_popa_, _pusha_,
	_lea_,
	_cdq_,
	_add_, _sub_, _imul_, _idiv_,
	_inc_, _dec_,
	_and_, _not_, _or_, _xor_,
	_shl_, _shr_,
	_cmp_,
	_je_, _jne_, _jmp_,
	_jg_, _jl_,
	_ja_, _jb_,
	_setl_, _setle_, _setg_, _setge_,
	_sete_, _setne_,
	_ret_, _leave_,
	_int_,
	_label_,
	_call_,
	_dd_,
};

struct instr_table_element {
	int ident;
	_instr instr;
	std::string desc, src;
};

void translate_to_x86();

void print_x86_table(const std::string &file);

void insert_into_x86_table(const std::string &s);

void insert_into_x86_table(_instr instr, const std::string &desc, const std::string &src);

void insert_into_x86_table(_instr instr, const std::string &desc);

void insert_into_x86_table(_instr instr);

#endif //CO_X86_H
