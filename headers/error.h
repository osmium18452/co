//
// Created by icpc on 2020/6/13.
//

#ifndef CO_ERROR_H
#define CO_ERROR_H

#define EXCODE_IDENTIFIER_EXPECTED 10
#define EXCODE_ASSIGN_EXPECTED 11
#define EXCODE_COMMA_EXPECTED 12
#define EXCODE_SEMICOLON_EXPECTED 13
#define EXCODE_COMMA_AND_SEMICOLON_EXPECTED 14
#define EXCODE_RIGHT_BRACE_EXPECTED 15
#define EXCODE_TOO_MUCH_PARAMS_FOR_FUNC 16
#define EXCODE_TOO_FEW_PARAMS_FOR_FUNC 17
#define EXCODE_FUNC_NOT_DEFINED 18
#define EXCODE_IDENTIFIER_IS_NOT_A_FUNC 19
#define EXCODE_IDENTIFIER_NOT_FOUND 20
#define EXCODE_IDENTIFIER_IS_NOT_ARRAY 21

extern int curr_line_num;
extern bool has_main_func;

void print_error(const std::string &message);
void print_warning(const std::string &message);

void init_error_warning_handler();

void error_warning_handler_summary();

#endif //CO_ERROR_H
