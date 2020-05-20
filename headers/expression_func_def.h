#ifndef CO_EXPRESSION_FUNC_DEF_H
#define CO_EXPRESSION_FUNC_DEF_H

#include "global.h"
#include "table.h"

extern void parse_func_call_statement(std::string &res, dtype &dtype);

extern void parse_array_read(std::string &res, dtype &dtype, const std::string &id);

/*factor:   identifier
 *          immidiate number
 *          func call (with return value)
 *          array read
 */
void parse_factor();

void parse_exp1();
void parse_exp2();
void parse_exp3();
void parse_exp4();
void parse_exp5();
void parse_exp6();
void parse_exp7();
void parse_exp8();
void parse_exp9();
void parse_exp10();
void parse_exp11();
void parse_exp12();
void parse_exp13();
void parse_exp14();
void parse_exp15();


#endif //CO_EXPRESSION_FUNC_DEF_H
