#ifndef CO_SDT_H
#define CO_SDT_H

#include "global.h"

extern int curr_token;

void match();
void parse_program();
void parse_const_declaration();
void parse_const_definition();
void parse_var_declaration();
void parse_var_definition();
void parse_func_declarartion();
void parse_main_func_declaration();

#endif //CO_SDT_H
