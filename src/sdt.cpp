#include "../headers/sdt.h"
#include "../headers/quadruple.h"
#include "../headers/lex.h"
#include "../headers/table.h"

int curr_token;

void match() {
	curr_token++;
}

void parse_program() {
	parse_const_declaration();
//	parse_var_declaration();
}

void parse_const_declaration() {
	while (tokens[curr_token].type == TOK_CONST) {
		match();
//		cout << "curr_token: " << curr_token << " token type: " << token_convert_table[tokens[curr_token].type] << endl;
		parse_const_definition();
	}
}

void parse_const_definition() {
	dtype dtype;
	switch (tokens[curr_token].type) {
		case TOK_INT:
			dtype = DATA_INT;
			break;
		case TOK_SHORT:
			dtype = DATA_SHORT;
			break;
		case TOK_LONG:
			dtype = DATA_LONG;
			break;
		case TOK_FLOAT:
			dtype = DATA_FLOAT;
			break;
		case TOK_DOUBLE:
			dtype = DATA_DOUBLE;
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
		match();
		match();/*'=' token*/
		switch (dtype) {
			case DATA_SHORT:
				entry = {IDN_CONST, dtype, tokens[curr_token].shortval, -1};
				insert(GLOBAL, ident_name, entry);
				break;
			case DATA_INT:
				entry = {IDN_CONST, dtype, tokens[curr_token].intval, -1};
				insert(GLOBAL, ident_name, entry);
				break;
			case DATA_LONG:
				entry = {IDN_CONST, dtype, tokens[curr_token].llval, -1};
				insert(GLOBAL, ident_name, entry);
				break;
			case DATA_CHAR:
				entry = {IDN_CONST, dtype, tokens[curr_token].charval, -1};
				insert(GLOBAL, ident_name, entry);
				break;
			default:
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

void parse_var_declaration() {

}

void parse_var_definition() {

}


