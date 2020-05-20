#include "../headers/sdt.h"
#include "../headers/quadruple.h"
#include "../headers/lex.h"
#include "../headers/table.h"
#include "../headers/expression.h"
#include "../headers/sdt_func_decl.h"

int curr_token;

/*parse function declaration*/


void match() {
	curr_token++;
}

void parse_program() {
	while (tokens[curr_token].type != TOK_PROG_END) {
		if (tokens[curr_token].type == TOK_CONST) {
			parse_const_declaration(GLOBAL);
		} else if (tokens[curr_token].type == TOK_VOID || tokens[curr_token + 2].type == TOK_LPARE) {
			parse_func_declarartion();
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
	dtype dtype = DATA_INT;
	table_entry entry{};
	quadruple_element element{};
	std::string ident_name;
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
	match();
	while (true) {
		ident_name = tokens[curr_token].stringval;
		if (tokens[curr_token + 1].type == TOK_LBRACKET) {
			match();
			match();//consume the [;
			int array_size = tokens[curr_token].intval;
			match();
			element = {scope == GLOBAL ? GVAR : VAR, dtype == DATA_INT ? "int" : "char", ident_name,
			           std::to_string(array_size)};
			insert_to_quadruple_list(element);
			entry = {IDN_ARRAY, dtype, array_size, -1};
			insert_to_symbol_table(scope, ident_name, entry);
			match();
		} else {
			element = {scope == GLOBAL ? GVAR : VAR, dtype == DATA_INT ? "int" : "char", ident_name, NONE};
			insert_to_quadruple_list(element);
			entry = {IDN_VAR, dtype, -1, -1};
			insert_to_symbol_table(scope, ident_name, entry);
			match();
		}
		if (tokens[curr_token].type == TOK_ASSIGN) {
			match();
			element = {ASSIGN, dtype == DATA_INT ? std::to_string(tokens[curr_token].intval) : std::to_string(
					tokens[curr_token].charval), ident_name, NONE};
			insert_to_quadruple_list(element);
			match();
			if (tokens[curr_token].type == TOK_SEMICOLON) {
				match();
				break;
			} else {
				match();
			}
		} else if (tokens[curr_token].type == TOK_SEMICOLON) {
			match();
			break;
		} else if (tokens[curr_token].type == TOK_COMMA) {
			match();
		}
	}
}

void parse_func_declarartion() {
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
	switch (tokens[curr_token].type) {
		case TOK_CHAR:
			dtype = DATA_CHAR;
			tp = "char";
			break;
		case TOK_VOID:
			dtype = DATA_VOID;
			tp = "void";
			break;
	}
	match();
	entry = {IDN_FUNCTION, dtype, -1, -1};
	ident_name = tokens[curr_token].stringval;
	element = {FUNC, tp, ident_name, NONE};
	match();
	match();//left parenthesis
	insert_to_symbol_table(GLOBAL, ident_name, entry);
	insert_to_quadruple_list(element);
	create_new_local_table();
	if (tokens[curr_token].type != TOK_RPARE) {// function with parameters.
		parse_para_list();
		std::string table_file = "../testfile_dir/table.txt";
		print_symbol_table(table_file, local_symbol_table_level, true);
	}
	match();//right parenthesis
	parse_block();
	element = {END, NONE, NONE, NONE};
	insert_to_quadruple_list(element);
	destroy_current_local_table();
}

void parse_para_list() {
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
		match();
		if (tokens[curr_token].type == TOK_RPARE) {
			break;
		} else {
			match();
		}
	}
}

void parse_single_statement(){
	switch (tokens[curr_token].type) {
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
		case TOK_IDENT:
			switch (tokens[curr_token + 1].type) {
				case TOK_ASSIGN:
				case TOK_SHLASS:
				case TOK_SHRASS:
				case TOK_MODASS:
				case TOK_MULASS:
				case TOK_DIVASS:
				case TOK_ADDASS:
				case TOK_SUBASS:
					parse_assignment_statement();
					break;
				case TOK_LPARE:
					parse_func_call_statement();
					break;
				default:
					expression();
					break;
			}
			break;
		default:
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
		default:
			break;
	}
}

void parse_func_call_statement() {

}

void parse_if_else_statement() {

}

void parse_for_statement() {

}

void parse_while_statement() {

}

void parse_do_statement() {

}

void parse_switch_statement() {

}

void parse_print_statement(){

}

void parse_scan_statement(){

}

void parse_ass() {

}

void parse_addass() {

}

void parse_subass() {

}

void parse_modass() {

}

void parse_mulass() {

}

void parse_divass() {

}

void parse_shlass() {

}

void parse_shrass() {

}