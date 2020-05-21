#ifndef CO_EXPRESSION_H
#define CO_EXPRESSION_H

#include "global.h"
#include "table.h"

extern int temp_var_num;
extern int curr_token;

extern void match();

void expression(std::string &res,dtype &dtype);

#endif //CO_EXPRESSION_H
