#ifndef CO_SDT_H
#define CO_SDT_H

#include "global.h"
#include "table.h"

extern int curr_token;

void match();
void parse_program();
void parse_const_declaration(scope scope);
void parse_const_definition(scope scope);
void parse_var_declaration(scope scope);
void parse_var_definition(scope scope);
void parse_func_declarartion();
void parse_main_func_declaration();

#endif //CO_SDT_H
