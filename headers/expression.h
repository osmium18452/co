#ifndef CO_EXPRESSION_H
#define CO_EXPRESSION_H

#include "global.h"
#include "table.h"

extern int temp_var_num;
extern int curr_token;
extern int curr_line_num;

extern void match();

void expression(std::string &res,dtype &dtype);
void expression_without_comma(std::string &res,dtype &res_type);

#endif //CO_EXPRESSION_H
