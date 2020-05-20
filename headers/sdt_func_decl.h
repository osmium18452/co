#ifndef CO_SDT_FUNC_DECL_H
#define CO_SDT_FUNC_DECL_H

void parse_const_declaration(scope scope);

void parse_const_definition(scope scope);

void parse_var_declaration(scope scope);

void parse_var_definition(scope scope);

void parse_func_declarartion();

void parse_func_with_return_value();

void parse_func_without_return_value();

void parse_main_func_declaration();

void parse_para_list();

void parse_block();

void parse_assignment_statement();

void parse_func_call_statement(std::string &res, dtype &dtype);

void parse_void_func_call_statement();

void parse_if_else_statement();

void parse_for_statement();

void parse_while_statement();

void parse_do_statement();

void parse_switch_statement();

void parse_ass();

void parse_addass();

void parse_subass();

void parse_modass();

void parse_mulass();

void parse_divass();

void parse_shlass();

void parse_shrass();

void parse_print_statement();

void parse_scan_statement();

void parse_single_statement();

void parse_array_read(std::string &res, dtype &dtype, const std::string &id);

void parse_array_assign();

#endif //CO_SDT_FUNC_DECL_H
