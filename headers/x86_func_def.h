#ifndef CO_X86_FUNC_DEF_H
#define CO_X86_FUNC_DEF_H

#include "global.h"

void build_symbol_table();

void inc_ident();
void dec_ident();

void insert_into_x86_table(const std::string &s);

void gen_data_section();
void gen_text_section();
void gen_bss_section();

void gen_global_table();
void gen_string_table();
void gen_start_code();

void translate_assign();

void translate_add();
void translate_sub();
void translate_mod();
void translate_mul();
void translate_div();

void translate_cmp();
void translate_je();
void translate_jmp();
void translate_ja();
void translate_jb();
void translate_swjmp();

void translate_end();

void translate_print();
void translate_scan();

void translate_label();

void translate_logiand();
void translate_logior();

void translate_bitand();
void translate_bitor();
void translate_bitxor();

void translate_ne();
void translate_eq();

void translate_shl();
void translate_shr();

void translate_le();
void translate_lt();
void translate_gt();
void translate_ge();

void translate_inc();
void translate_dec();
void translate_not();
void translate_reverse();

void translate_push();

void translate_call();
void translate_ret();
void translate_getret();

void translate_rdarr();
void translate_wrarr();

void translate_kase_item();

#endif //CO_X86_FUNC_DEF_H
