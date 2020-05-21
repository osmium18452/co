#ifndef CO_EXPRESSION_H
#define CO_EXPRESSION_H

#include "global.h"
#include "table.h"

extern int temp_var_num;

void expression();

void init_temp_var();

std::string gen_temp_var();

#endif //CO_EXPRESSION_H
