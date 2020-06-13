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

extern int curr_line_num;
extern bool has_main_func;

void print_error(const std::string &message);
void print_waring(const std::string &message);

void init_error_warning_handler();

void error_warning_handler_summary();

#endif //CO_ERROR_H
