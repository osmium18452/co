#include "../headers/sdt.h"
#include "../headers/quadruple.h"
#include "../headers/lex.h"
#include "../headers/table.h"
#include "../headers/expression.h"
#include "../headers/sdt_func_decl.h"
#include "../headers/utils.h"

int curr_token;

std::string break_point, continue_point;

/*parse function declaration*/


void match() {
	curr_token++;
}

void parse_program() {
	while (tokens[curr_token].type != TOK_PROG_END) {
		if (tokens[curr_token].type == TOK_CONST) {
			parse_const_declaration(GLOBAL);
		} else if (tokens[curr_token].type == TOK_VOID || tokens[curr_token + 2].type == TOK_LPARE) {
			parse_func_declaration();
		} else if (tokens[curr_token + 2].type == TOK_COMMA || tokens[curr_token + 2].type == TOK_SEMICOLON ||
				   tokens[curr_token + 2].type == TOK_ASSIGN || tokens[curr_token + 2].type == TOK_LBRACKET) {
			parse_var_declaration(GLOBAL);
		}
	}
}

void parse_const_declaration(scope scope) {
	match();
	parse_const_definition(scope);
}

void parse_const_definition(scope scope) {
	dtype dtype = DATA_INT;
	switch (tokens[curr_token].type) {
		case TOK_INT:
			dtype = DATA_INT;
			break;
		case TOK_CHAR:
			dtype = DATA_CHAR;
			break;
		default:
			break;
	}
//	cout<<"***************"<<endl;
	match();
	table_entry entry{};
	std::string ident_name;
	while (true) {
		ident_name = tokens[curr_token].stringval;
//		cout<<"ident_name: "<<ident_name<<endl;
		match();
		match();/*'=' token*/
		switch (dtype) {
			case DATA_INT:
				entry = {IDN_CONST, dtype, tokens[curr_token].intval, -1};
				insert_to_symbol_table(scope, ident_name, entry);
				break;
			case DATA_CHAR:
				entry = {IDN_CONST, dtype, tokens[curr_token].charval, -1};
				insert_to_symbol_table(scope, ident_name, entry);
				break;
		}
		match();
		if (tokens[curr_token].type == TOK_SEMICOLON) {
			match();
			break;
		} else {
			match();
		}
	}
}

void parse_var_declaration(scope scope) {
	parse_var_definition(scope);
}

void parse_var_definition(scope scope) {
	dtype data_type = DATA_INT;
	table_entry entry{};
	quadruple_element element{};
	std::string ident_name;
	switch (tokens[curr_token].type) {
		case TOK_INT:
			data_type = DATA_INT;
			break;
		case TOK_CHAR:
			data_type = DATA_CHAR;
			break;
		default:
			break;
	}
	match();
	while (true) {
		ident_name = tokens[curr_token].stringval;
		if (tokens[curr_token + 1].type == TOK_LBRACKET) {
			match();
			match();//consume the [;
			int array_size = tokens[curr_token].intval;
			match();
			element = {scope == GLOBAL ? GVAR : VAR, data_type == DATA_INT ? "int" : "char", ident_name,
					   std::to_string(array_size)};
			if (element.instruct == VAR) insert_to_quadruple_list(element);
			entry = {IDN_ARRAY, data_type, array_size, -1, scope == GLOBAL ? g : l};
			insert_to_symbol_table(scope, ident_name, entry);
			match();
		} else {
			element = {scope == GLOBAL ? GVAR : VAR, data_type == DATA_INT ? "int" : "char", ident_name, NONE};
			if (element.instruct == VAR) insert_to_quadruple_list(element);
			entry = {IDN_VAR, data_type, -1, -1, scope == GLOBAL ? g : l};
			insert_to_symbol_table(scope, ident_name, entry);
			match();
		}
		if (tokens[curr_token].type == TOK_ASSIGN) {
			match();// =
			std::string res;
			dtype res_dtype;
			expression_without_comma(res, res_dtype);
			element = {ASSIGN, res, ident_name, NONE};
			insert_to_quadruple_list(element);
		}
		if (tokens[curr_token].type == TOK_SEMICOLON) {
			match();
			break;
		} else if (tokens[curr_token].type == TOK_COMMA) {
			match();
		}
	}
}

void parse_func_declaration() {
	if (tokens[curr_token + 1].stringval == "main") {
		parse_main_func_declaration();
	} else if (tokens[curr_token].type == TOK_VOID) {
		parse_func_without_return_value();
	} else {
		parse_func_with_return_value();
	}
}

void parse_main_func_declaration() {
	match();
	match();
	match();
	match();
	quadruple_element element{FUNC, "void", "main", NONE};
	insert_to_quadruple_list(element);
	parse_block();
	element = {END, NONE, NONE, NONE};
	insert_to_quadruple_list(element);
}

void parse_func_with_return_value() {
	parse_func_without_return_value();
}

void parse_func_without_return_value() {
	table_entry entry{};
	quadruple_element element{};
	std::string ident_name;
	std::string tp = "int";
	dtype dtype = DATA_INT;
	int para_table_num;
	switch (tokens[curr_token].type) {
		case TOK_CHAR:
			dtype = DATA_CHAR;
			tp = "char";
			break;
		case TOK_VOID:
			dtype = DATA_VOID;
			tp = "void";
			break;
		default:
			break;
	}
	match();
	para_table_num = allocate_a_param_table();
	entry = {IDN_FUNCTION, dtype, para_table_num, -1};
	ident_name = tokens[curr_token].stringval;
	element = {FUNC, tp, ident_name, NONE};
	match();
	match();//left parenthesis
	insert_to_symbol_table(GLOBAL, ident_name, entry);
	insert_to_quadruple_list(element);
	create_new_local_table();
	if (tokens[curr_token].type != TOK_RPARE) {// function with parameters.
		parse_para_list(para_table_num);
		std::string table_file = "../testfile_dir/table.txt";
		print_symbol_table(table_file, local_symbol_table_level, true);
	}
	match();//right parenthesis
	parse_block();
	destroy_current_local_table();
	element = {END, NONE, NONE, NONE};
	insert_to_quadruple_list(element);
}

void parse_para_list(const int para_table_num) {
	while (true) {
		std::string para_name;
		std::string tp;
		dtype dtype = DATA_INT;
		table_entry entry{};
		quadruple_element element{};
		switch (tokens[curr_token].type) {
			case TOK_INT:
				dtype = DATA_INT;
				tp = "int";
				break;
			case TOK_CHAR:
				dtype = DATA_CHAR;
				tp = "char";
				break;
			default:
				break;
		}
		match();
		para_name = tokens[curr_token].stringval;
		entry = {IDN_VAR, dtype, -1, -1};
		element = {PARAM, tp, para_name, NONE};
		insert_to_symbol_table(LOCAL, para_name, entry);
		insert_to_quadruple_list(element);
		insert_to_para_table(para_table_num, dtype);
		match();
		if (tokens[curr_token].type == TOK_RPARE) {
			break;
		} else {
			match();
		}
	}
}

void parse_single_statement() {
	std::string res;
	dtype dtype;
	switch (tokens[curr_token].type) {
		case TOK_CONTINUE:
			parse_continue_statement();
			break;
		case TOK_BREAK:
			parse_break_statement();
			break;
		case TOK_CONST:
			parse_const_declaration(LOCAL);
			break;
		case TOK_INT:
		case TOK_CHAR:
			parse_var_declaration(LOCAL);
			break;
		case TOK_LBRACE:
			parse_block();
			break;
		case TOK_IF:
			parse_if_else_statement();
			break;
		case TOK_SWITCH:
			parse_switch_statement();
			break;
		case TOK_FOR:
			parse_for_statement();
			break;
		case TOK_WHILE:
			parse_while_statement();
			break;
		case TOK_DO:
			parse_do_statement();
			break;
		case TOK_WRITE:
			parse_print_statement();
			break;
		case TOK_READ:
			parse_scan_statement();
			break;
		case TOK_RETURN:
			parse_return_statement();
			break;
		case TOK_INC:
		case TOK_DEC:
		case TOK_REVERSE:
		case TOK_LOGINOT:
			expression(res, dtype);
			match();
			break;
		case TOK_IDENT:
			switch (tokens[curr_token + 1].type) {
				case TOK_ASSIGN:
				case TOK_SHLASS:
				case TOK_SHRASS:
				case TOK_MODASS:
				case TOK_MULASS:
				case TOK_DIVASS:
				case TOK_ADDASS:
				case TOK_BITANDASS:
				case TOK_BITORASS:
				case TOK_BITXORASS:
					parse_assignment_statement();
					break;
				case TOK_LPARE:
					parse_func_call_statement(tokens[curr_token].stringval);
					break;
				case TOK_LBRACKET:
					parse_array_assign();
					break;
				default:
					expression(res, dtype);
					match();
					break;
			}
			break;
		default:
			expression(res, dtype);
			match();
			break;
	}
}

void parse_block() {
	match();
	create_new_local_table();
	while (tokens[curr_token].type != TOK_RBRACE) {
		parse_single_statement();
	}
	match();
	std::string table_file = "../testfile_dir/table.txt";
	print_symbol_table(table_file, local_symbol_table_level, true);
	destroy_current_local_table();
}

void parse_print_statement() {
	quadruple_element element{};
	std::string dtp;
	std::string res;
	dtype dtype;
	table_entry entry{};
	std::string s;
	std::string slabel;
	match();// printf
	match();// (
	element = {SAVE_REG, NONE, NONE, NONE};
	insert_to_quadruple_list(element);
	while (true) {
		switch (tokens[curr_token].type) {
			case TOK_STRINGCONST:
				s = tokens[curr_token].stringval;
				if (!query_string_table(s, slabel)) {
					insert_to_string_table(s, slabel);
				}
				element = {PRINT, "string", slabel, NONE};
				insert_to_quadruple_list(element);
				match();
				break;
			case TOK_INTCONST:
			case TOK_CHARCONST:
				element = {PRINT, tokens[curr_token].type == TOK_INTCONST ? "int" : "char", std::to_string(
						tokens[curr_token].type == TOK_INTCONST ? tokens[curr_token].intval
																: tokens[curr_token].charval), NONE};
				insert_to_quadruple_list(element);
				match();
				break;
			case TOK_IDENT:
				query_symbol_table(tokens[curr_token].stringval, entry);
				switch (entry.itype) {
					case IDN_VAR:
					case IDN_ARRAY:
						if (entry.itype==IDN_ARRAY&&entry.dtype==DATA_CHAR&&tokens[curr_token+1].type!=TOK_LBRACKET){
							element={PRINT,"string",tokens[curr_token].stringval,NONE};
							insert_to_quadruple_list(element);
						} else {
							expression_without_comma(res, dtype);
							dtp = entry.dtype == DATA_CHAR ? "char" : "int";
							element = {PRINT, dtp, res, NONE};
							insert_to_quadruple_list(element);
						}
//						match();
						break;
						/*parse_array_read(res, dtype, tokens[curr_token].stringval);
						dtp = dtype == DATA_CHAR ? "char" : "int";
						element = {PRINT, dtp, res, NONE};
						insert_to_quadruple_list(element);
						break;*/
					case IDN_FUNCTION:
						parse_non_void_func_call(res, dtype, tokens[curr_token].stringval);
						dtp = dtype == DATA_CHAR ? "char" : "int";
						element = {PRINT, dtp, res, NONE};
						insert_to_quadruple_list(element);
						break;
					case IDN_CONST:
						res = entry.dtype == DATA_CHAR ? std::to_string((char) (entry.value)) : std::to_string(
								entry.value);
						element = {PRINT, "const", res, NONE};
						insert_to_quadruple_list(element);
						match();
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
		if (tokens[curr_token].type != TOK_COMMA) break;
		else match();
	}
	match();// )
	match();// ;
	element = {RESTORE_REG, NONE, NONE, NONE};
	insert_to_quadruple_list(element);
}

void parse_scan_statement() {
	quadruple_element element{};
	table_entry entry{};
	std::string tmp_var, index, arr_name;
	dtype index_dtype;
	match();// scanf
	match();// (
	element = {FLUSH_REG, NONE, NONE, NONE};
	insert_to_quadruple_list(element);
	while (true) {
		if (tokens[curr_token].type != TOK_IDENT) {
			cout << "error" << endl;
			break;
		} else {
			query_symbol_table(tokens[curr_token].stringval, entry);
			switch (entry.itype) {
				case IDN_VAR:
					element = {SCAN, entry.dtype == DATA_INT ? "int" : "char", tokens[curr_token].stringval, NONE};
					insert_to_quadruple_list(element);
					match();
					break;
				case IDN_ARRAY:
					if (tokens[curr_token + 1].type == TOK_LBRACKET) {
						tmp_var = gen_temp_var();
						element = {SCAN, entry.dtype == DATA_INT ? "int" : "char", tmp_var, NONE};
						insert_to_quadruple_list(element);
						arr_name = tokens[curr_token].stringval;
						match();
						match();// [
						expression(index, index_dtype);
						match();// ]
						element = {WRARR, arr_name, index, tmp_var};
						insert_to_quadruple_list(element);
					} else if (entry.dtype == DATA_CHAR) {
						element = {SCAN, "string", tokens[curr_token].stringval, NONE};
						insert_to_quadruple_list(element);
						match();
					} else {
						cout << "you can't read an array" << endl;
						match();
					}
					break;
				default:
					break;
			}
		}
		if (tokens[curr_token].type != TOK_COMMA) break;
		else match();
	}
	match();
	match();
	element = {FLUSH_REGTABLE, NONE, NONE, NONE};
	insert_to_quadruple_list(element);
}

void parse_assignment_statement() {
	switch (tokens[curr_token + 1].type) {
		case TOK_ASSIGN:
			parse_ass();
			break;
		case TOK_SHLASS:
			parse_shlass();
			break;
		case TOK_SHRASS:
			parse_shrass();
			break;
		case TOK_MODASS:
			parse_modass();
			break;
		case TOK_MULASS:
			parse_mulass();
			break;
		case TOK_DIVASS:
			parse_divass();
			break;
		case TOK_ADDASS:
			parse_addass();
			break;
		case TOK_SUBASS:
			parse_subass();
			break;
		case TOK_BITANDASS:
			parse_bitandass();
			break;
		case TOK_BITORASS:
			parse_bitorass();
			break;
		case TOK_BITXORASS:
			parse_bitxorass();
			break;
		default:
			break;
	}
}

void parse_bitorass() {
	std::string id = tokens[curr_token].stringval;
	match();
	match();
	std::string res;
	dtype res_dtype;
	expression(res, res_dtype);
	quadruple_element element{BITOR, id, res, id};
	insert_to_quadruple_list(element);
	match();
}

void parse_bitandass() {
	std::string id = tokens[curr_token].stringval;
	match();
	match();
	std::string res;
	dtype res_dtype;
	expression(res, res_dtype);
	quadruple_element element{BITAND, id, res, id};
	insert_to_quadruple_list(element);
	match();
}

void parse_bitxorass() {
	std::string id = tokens[curr_token].stringval;
	match();
	match();
	std::string res;
	dtype res_dtype;
	expression(res, res_dtype);
	quadruple_element element{BITXOR, id, res, id};
	insert_to_quadruple_list(element);
	match();
}

void parse_argument_list(const std::vector<dtype> &param_list) {
	std::stack<quadruple_element> temp_quadruple_stack;
	std::string temp_var;
	dtype temp_dtype;
	int arg_cnt = 0;
	if (param_list.empty()) {
		if (tokens[curr_token].type != TOK_RPARE) {
			cout << "this is a function without params" << endl;
			return;
		} else return;
	}
	auto iter = quadruple_list.end();
	while (true) {
		expression_without_comma(temp_var, temp_dtype);
		if (temp_dtype != param_list[arg_cnt]) {
			cout << "not matched param data type" << endl;
			return;
		}
		if (++arg_cnt > param_list.size()) {
			cout << "too much args for function emm" << endl;
			return;
		}
		quadruple_element element{PUSH, temp_dtype == DATA_INT ? "int" : "char", temp_var, NONE};
		temp_quadruple_stack.push(element);
		if (tokens[curr_token].type != TOK_COMMA) break;
		else match();
	}
	while (!temp_quadruple_stack.empty()) {
		insert_to_quadruple_list(temp_quadruple_stack.top());
		temp_quadruple_stack.pop();
	}
//	std::reverse(iter,quadruple_list.end());
	if (arg_cnt < param_list.size()) {
		cout << "too few args for func" << endl;
	}
}

void parse_func_call_statement(const std::string &id) {
	table_entry entry{};
	if (!query_symbol_table(id, entry)) {
		cout << "function " << id << " not defined." << endl;
		return;
	}
	if (entry.itype != IDN_FUNCTION) {
		cout << "identifier " << id << " is not a function" << endl;
		return;
	}
	match();// identifier
	match();// (
	std::vector<dtype> para_list = get_para_table(entry.value);
	if (!para_list.empty() && tokens[curr_token].type == TOK_RPARE) {
		cout << "expected args" << endl;
		return;
	}
	quadruple_element element{};
	element = {SAVE_REG, NONE, NONE, NONE};
	insert_to_quadruple_list(element);
	parse_argument_list(para_list);
	match();// )
	element = {CALL, id, NONE, NONE};
	insert_to_quadruple_list(element);
	element = {RESTORE_STACK, std::to_string(para_list.size()), NONE, NONE};
	insert_to_quadruple_list(element);
	element = {RESTORE_REG, NONE, NONE, NONE};
	insert_to_quadruple_list(element);
	match();// ;
}

void parse_non_void_func_call(std::string &res, dtype &data_type, const std::string &id) {
	table_entry entry{};
	quadruple_element element{};
	if (!query_symbol_table(id, entry)) {
		cout << "cannot find identifier " << id << endl;
		return;
	}
	if (entry.itype != IDN_FUNCTION) {
		cout << id << " is not a function" << endl;
		return;
	}
	if (entry.dtype == DATA_VOID) {
		cout << "function " << id << " has no return value" << endl;
		return;
	}
	match();// identifier
	match();// (
	std::vector<dtype> para_list = get_para_table(entry.value);
	if (!para_list.empty() && tokens[curr_token].type == TOK_RPARE) {
		cout << "expected args" << endl;
		return;
	}
	element = {SAVE_REG, NONE, NONE, NONE};
	insert_to_quadruple_list(element);

	parse_argument_list(para_list);

	match();// )
	element = {CALL, id, NONE, NONE};
	insert_to_quadruple_list(element);
	res = gen_temp_var();
	data_type = entry.dtype;
	element = {TEMP, data_type == DATA_INT ? "int" : "char", res, NONE};
	insert_to_quadruple_list(element);
	element = {GETRET, res, NONE, NONE};
	insert_to_quadruple_list(element);
	element = {RESTORE_STACK, std::to_string(para_list.size()), NONE, NONE};
	insert_to_quadruple_list(element);
	element = {RESTORE_REG, NONE, NONE, NONE};
	insert_to_quadruple_list(element);
}

void parse_array_read(std::string &res, dtype &data_dtype, const std::string &id) {
	table_entry entry{};
	std::string index;
	dtype index_dtype;
	quadruple_element element{};
	if (!query_symbol_table(id, entry)) {
		cout << "cannot find identifier" << id << endl;
		return;
	}
	if (entry.itype != IDN_ARRAY) {
		cout << id << " is not an array" << endl;
		return;
	}
	match();// identifier
	match();// [
	expression(index, index_dtype);
	match();// ]
	res = gen_temp_var();
	data_dtype = entry.dtype;
	element = {TEMP, data_dtype == DATA_INT ? "int" : "char", res, NONE};
	insert_to_quadruple_list(element);
	element = {RDARR, id, index, res};
	insert_to_quadruple_list(element);
}

void parse_array_assign() {
	table_entry entry{};
	std::string id = tokens[curr_token].stringval;
	std::string index;
	dtype index_dtype;
	std::string res;
	dtype res_type;
	match();// identifier.
	if (!query_symbol_table(id, entry)) {
		cout << "cannot find identifier" << id << endl;
		return;
	}
	if (entry.itype != IDN_ARRAY) {
		cout << id << " is not an array" << endl;
		return;
	}
	match();// [
	expression(index, index_dtype);
	match();// ]
	match();// =
	expression(res, res_type);
	quadruple_element element{WRARR, id, index, res};
	insert_to_quadruple_list(element);
	match();// ;
}

void parse_return_statement() {
	match();
	std::string ret_val;
	dtype ret_dtype;
	quadruple_element element;
	if (tokens[curr_token].type == TOK_SEMICOLON) {
		element = {RET, NONE, NONE, NONE};
		insert_to_quadruple_list(element);
	} else {
		expression(ret_val, ret_dtype);
		element = {RET, ret_val, NONE, NONE};
		insert_to_quadruple_list(element);
	}
	match();// ;
}

void parse_if_else_statement() {
	match();// if
	match();// (
	std::string res;
	dtype res_dtype;
	quadruple_element element{};
	std::string false_label, end_label;
	false_label = gen_temp_label();
	end_label = gen_temp_label();
	expression(res, res_dtype);
	match();// )
	element = {CMP, res, "0", NONE};
	insert_to_quadruple_list(element);
	element = {JE, false_label, NONE, NONE};
	insert_to_quadruple_list(element);
	if (tokens[curr_token].type == TOK_LBRACE) {
		parse_block();
	} else {
		parse_single_statement();
	}
	element = {JMP, end_label, NONE, NONE};
	insert_to_quadruple_list(element);
	element = {LABEL, false_label, NONE, NONE};
	insert_to_quadruple_list(element);
	if (tokens[curr_token].type == TOK_ELSE) {
		match();// else
		if (tokens[curr_token].type == TOK_LBRACE) {
			parse_block();
		} else {
			parse_single_statement();
		}
	}
	element = {LABEL, end_label};
	insert_to_quadruple_list(element);
}

void parse_for_statement() {
	std::string start_label, end_label;
	std::string res;
	dtype res_dtype;
	quadruple_element element{};
	std::vector<quadruple_element> quadruple_element_for_exp3;
	int quadruple_list_size_b4_stmt3;
	create_new_local_table();
	start_label = gen_temp_label();
	end_label = gen_temp_label();
	continue_point = start_label;
	break_point = end_label;
	match();//for
	match();//(
	parse_single_statement();
	element = {LABEL, start_label, NONE, NONE};
	insert_to_quadruple_list(element);
	expression(res, res_dtype);
	match();//;
	element = {CMP, res, "0", NONE};
	insert_to_quadruple_list(element);
	element = {JE, end_label, NONE, NONE};
	insert_to_quadruple_list(element);
	quadruple_list_size_b4_stmt3 = quadruple_list.size();
	expression(res, res_dtype);
	while (quadruple_list.size() > quadruple_list_size_b4_stmt3) {
		quadruple_element_for_exp3.push_back(quadruple_list.back());
		quadruple_list.pop_back();
	}
	match();// )
	if (tokens[curr_token].type == TOK_LBRACE) {
		parse_block();
	} else {
		parse_single_statement();
	}
	while (!quadruple_element_for_exp3.empty()) {
		quadruple_list.push_back(quadruple_element_for_exp3.back());
		quadruple_element_for_exp3.pop_back();
	}
	element = {JMP, start_label, NONE, NONE};
	insert_to_quadruple_list(element);
	element = {LABEL, end_label, NONE, NONE};
	insert_to_quadruple_list(element);
	destroy_current_local_table();
}

void parse_while_statement() {
	std::string start_label, end_label;
	std::string res;
	dtype res_dtype;
	quadruple_element element{};
	start_label = gen_temp_label();
	end_label = gen_temp_label();
	continue_point = start_label;
	break_point = end_label;
	element = {LABEL, start_label, NONE, NONE};
	insert_to_quadruple_list(element);
	match();// while
	match();// (
	expression(res, res_dtype);
	match();// )
	element = {CMP, res, "0", NONE};
	insert_to_quadruple_list(element);
	element = {JE, end_label, NONE, NONE};
	insert_to_quadruple_list(element);
	if (tokens[curr_token].type == TOK_LBRACE) {
		parse_block();
	} else {
		parse_single_statement();
	}
	element = {JMP, start_label, NONE, NONE};
	insert_to_quadruple_list(element);
	element = {LABEL, end_label, NONE, NONE};
	insert_to_quadruple_list(element);
}

void parse_do_statement() {
	std::string start_label, end_label;
	std::string res;
	dtype res_dtype;
	quadruple_element element{};
	start_label = gen_temp_label();
	end_label = gen_temp_label();
	continue_point = start_label;
	break_point = end_label;
	element = {LABEL, start_label, NONE, NONE};
	insert_to_quadruple_list(element);
	match();//do
	parse_block();
	match();//while
	match();//(
	expression(res, res_dtype);
	element = {CMP, res, "0", NONE};
	insert_to_quadruple_list(element);
	element = {JE, end_label, NONE, NONE};
	insert_to_quadruple_list(element);
	element = {JMP, start_label, NONE, NONE};
	insert_to_quadruple_list(element);
	element = {LABEL, end_label, NONE, NONE};
	insert_to_quadruple_list(element);
}

void parse_switch_statement() {
	std::string label_end_of_switch, label_case, label_default, label_jump_table;
	std::string res;
	dtype res_dtype;
	std::vector<kase_table> case_table;
	quadruple_element element{};
	std::vector<quadruple_element> head_of_switch;
	label_end_of_switch = gen_temp_label("end_of_switch");
	label_default = gen_temp_label("default");
	label_jump_table = gen_temp_label("jump_table");
	break_point = label_end_of_switch;
	match();//switch
	match();//(
	expression(res, res_dtype);
	auto place_recorder = quadruple_list.end() - quadruple_list.begin();
	match();//)
	match();//{
	while (tokens[curr_token].type != TOK_RBRACE) {
		if (tokens[curr_token].type == TOK_CASE) {
			match();//case
			label_case = gen_temp_label("case");
			element = {LABEL, label_case, NONE, NONE};
			insert_to_quadruple_list(element);
			case_table.push_back(kase_table{tokens[curr_token].intval, label_case});
			match();// const int
			match();// :
		} else if (tokens[curr_token].type == TOK_DEFAULT) {
			match();//default
			match();//:
			element = {LABEL, label_default, NONE, NONE};
			insert_to_quadruple_list(element);
		} else {
			parse_single_statement();
		}
	}
	element = {LABEL, label_end_of_switch, NONE, NONE};
	insert_to_quadruple_list(element);
	match();//}
	//generate jump table.
	std::sort(case_table.begin(), case_table.end());
	for (const auto &i:case_table) {
		cout << i.kase_num << " " << i.kase_label << endl;
	}
	element = {CMP, res, std::to_string(case_table.begin()->kase_num), NONE};
	head_of_switch.push_back(element);
	element = {JB, label_default, NONE, NONE};
	head_of_switch.push_back(element);
	element = {CMP, res, std::to_string((case_table.end() - 1)->kase_num), NONE};
	head_of_switch.push_back(element);
	element = {JA, label_default, NONE, NONE};
	head_of_switch.push_back(element);
	element = {SUB, res, std::to_string(case_table.begin()->kase_num), res};
	head_of_switch.push_back(element);
	element = {SWJMP, res, label_jump_table, NONE};
	head_of_switch.push_back(element);
	element = {LABEL, label_jump_table, NONE, NONE};
	head_of_switch.push_back(element);
	std::vector<std::string> tmp_vec_0;
	for (int i = case_table.begin()->kase_num; i <= (case_table.end() - 1)->kase_num; i++) {
		tmp_vec_0.push_back(label_default);
	}
	int tmp_num_rec = case_table.begin()->kase_num;
	for (auto &i:case_table) {
		i.kase_num -= tmp_num_rec;
	}
	for (const auto &i:case_table) {
		tmp_vec_0[i.kase_num] = i.kase_label;
	}
	for (const auto &i:tmp_vec_0) {
		element = {KASE_ITEM, i, NONE, NONE};
		head_of_switch.push_back(element);
	}
	quadruple_list.insert(quadruple_list.begin() + place_recorder, head_of_switch.begin(), head_of_switch.end());
}

void parse_ass() {
	std::string id = tokens[curr_token].stringval;
	match();// identifier.
	match();// =
	std::string res;
	dtype res_dtype;
	expression(res, res_dtype);
	quadruple_element element{ASSIGN, res, id, NONE};
	insert_to_quadruple_list(element);
	match();// ;
}

void parse_addass() {
	std::string id = tokens[curr_token].stringval;
	match();
	match();
	std::string res;
	dtype res_dtype;
	expression(res, res_dtype);
	quadruple_element element{ADD, id, res, id};
	insert_to_quadruple_list(element);
	match();
}

void parse_subass() {
	std::string id = tokens[curr_token].stringval;
	match();
	match();
	std::string res;
	dtype res_dtype;
	expression(res, res_dtype);
	quadruple_element element{SUB, id, res, id};
	insert_to_quadruple_list(element);
	match();
}

void parse_modass() {
	std::string id = tokens[curr_token].stringval;
	match();
	match();
	std::string res;
	dtype res_dtype;
	expression(res, res_dtype);
	quadruple_element element{MOD, id, res, id};
	insert_to_quadruple_list(element);
	match();
}

void parse_mulass() {
	std::string id = tokens[curr_token].stringval;
	match();
	match();
	std::string res;
	dtype res_dtype;
	expression(res, res_dtype);
	quadruple_element element{MUL, id, res, id};
	insert_to_quadruple_list(element);
	match();
}

void parse_divass() {
	std::string id = tokens[curr_token].stringval;
	match();
	match();
	std::string res;
	dtype res_dtype;
	expression(res, res_dtype);
	quadruple_element element{DIV, id, res, id};
	insert_to_quadruple_list(element);
	match();
}

void parse_shlass() {
	std::string id = tokens[curr_token].stringval;
	match();
	match();
	std::string res;
	dtype res_dtype;
	expression(res, res_dtype);
	quadruple_element element{SHL, id, res, id};
	insert_to_quadruple_list(element);
	match();
}

void parse_shrass() {
	std::string id = tokens[curr_token].stringval;
	match();
	match();
	std::string res;
	dtype res_dtype;
	expression(res, res_dtype);
	quadruple_element element{SHR, id, res, id};
	insert_to_quadruple_list(element);
	match();
}

void parse_break_statement() {
	quadruple_element element{JMP, break_point, NONE, NONE};
	insert_to_quadruple_list(element);
	match();
	match();
}

void parse_continue_statement() {
	quadruple_element element{JMP, continue_point, NONE, NONE};
	insert_to_quadruple_list(element);
	match();
	match();
}

