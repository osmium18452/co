#include "../headers/global.h"
#include "../headers/expression.h"
#include "../headers/expression_func_def.h"
#include "../headers/utils.h"
#include "../headers/lex.h"
#include "../headers/quadruple.h"
#include "../headers/error.h"

std::string dtype_convert_table_2[]={
		"int","char","void"
};

void expression(std::string &res, _dtype &res_dtype) {
	parse_exp14(res, res_dtype);
}

void expression_without_comma(std::string &res, _dtype &res_type) {
	parse_exp13(res, res_type);
}

/*factor:   identifier
 *          immediate number
 *          func call (with return value)
 *          array read
 */
void parse_factor(std::string &res, _dtype &res_dtype) {
	std::string temp_res, id_name;
	_dtype temp_dtype;
	table_entry entry{};
	switch (tokens[curr_token].type) {
		case TOK_IDENT:
			id_name = tokens[curr_token].stringval;
			if (!query_symbol_table(id_name, entry)) {
				print_error("identifier " + tokens[curr_token].stringval + " undefined");
				exit(EXCODE_IDENTIFIER_NOT_FOUND);
			}
			switch (entry.itype) {
				case IDN_FUNCTION:
					parse_non_void_func_call(res, res_dtype, id_name);
					break;
				case IDN_CONST:
					res_dtype = entry.dtype;
					if (res_dtype == DATA_INT) res = std::to_string(entry.value);
					else res = "\'" + std::to_string((char) entry.value) + "\'";
					match();
					break;
				case IDN_ARRAY:
					parse_array_read(res, res_dtype, id_name);
					break;
				case IDN_VAR:
					res = id_name;
					res_dtype = entry.dtype;
					match();
				default:
					break;
			}
			break;
		case TOK_LPARE:
			match();//(
			expression(res, res_dtype);
			if (tokens[curr_token].type == TOK_RPARE) match();// )
			else {
				print_error("expected right parenthesis, but got "
							+ (tokens[curr_token].stringval.empty() ? "nothing" : tokens[curr_token].stringval));
			}
			break;
		default:
			res = std::to_string(tokens[curr_token].intval);
			res_dtype = tokens[curr_token].type == TOK_CHARCONST ? DATA_CHAR : DATA_INT;
			match();
			break;
	}
}

void parse_exp1(std::string &res, _dtype &res_dtype) {
	parse_factor(res, res_dtype);
	if (tokens[curr_token].type == TOK_INC || tokens[curr_token].type == TOK_DEC) {
		_instruct instr = tokens[curr_token].type == TOK_INC ? INC : DEC;
		quadruple_element element{};
		match();
		if (res_dtype != DATA_INT) {
			print_warning("type of left and right side of operand don't match.");
		}
		if (instr == DEC) {
			element = {DEC, res, NONE, NONE};
			insert_to_quadruple_list(element);
		} else {
			element = {INC, res, NONE, NONE};
			insert_to_quadruple_list(element);
		}
	}
}/* (backward) ++ -- */

void parse_exp2(std::string &res, _dtype &res_dtype) {
	std::string temp_var;
	_instruct instr;
	quadruple_element element{};
	bool flag = false;
	if (tokens[curr_token].type == TOK_INC || tokens[curr_token].type == TOK_DEC ||
		tokens[curr_token].type == TOK_SUB || tokens[curr_token].type == TOK_LOGINOT) {
		flag = true;
		switch (tokens[curr_token].type) {
			case TOK_INC:
				instr = INC;
				break;
			case TOK_DEC:
				instr = DEC;
				break;
			case TOK_SUB:
				instr = REVERSE;
				break;
			case TOK_LOGINOT:
				instr = NOT;
				break;
			default:
				break;
		}
		match();
	}
	parse_exp1(res, res_dtype);
	if (flag && (instr == REVERSE || instr == INC || instr == DEC || instr == NOT)) {
		int t1;
		switch (instr) {
			case INC:
				if (is_const(res, t1)) {
					res = std::to_string(t1 + 1);
				} else {
					if (res_dtype != DATA_INT) {
						print_warning("you're trying to inc/dec an identifier that is not an integer.");
					}
					element = {INC, res, NONE, NONE};
					insert_to_quadruple_list(element);
				}
				break;
			case DEC:
				if (is_const(res, t1)) {
					res = std::to_string(t1 - 1);
				} else {
					if (res_dtype != DATA_INT) {
						print_warning("you're trying to inc/dec an identifier that is not an integer.");
					}
					element = {DEC, res, NONE, NONE};
					insert_to_quadruple_list(element);
				}
				break;
			case REVERSE:
				if (is_const(res, t1)) {
					res = std::to_string(-t1);
				} else {
					if (res_dtype != DATA_INT) {
						print_warning("you're trying to inc/dec an identifier that is not an integer.");
					}
					std::string new_res = gen_temp_var();
					element = {TEMP, "int", new_res, NONE};
					insert_to_quadruple_list(element);
					element = {SUB, "0", res, new_res};
					insert_to_quadruple_list(element);
					res = new_res;
				}
				break;
			case NOT:
				if (is_const(res, t1)) {
					res = std::to_string(t1 ? 0 : 1);
				} else {
					std::string new_res = gen_temp_var();
					element = {TEMP, "int", new_res, NONE};
					insert_to_quadruple_list(element);
					element = {NOT, res, new_res, NONE};
					insert_to_quadruple_list(element);
					res = new_res;
				}
				break;
		}
	}
}/* (frontward) ++ -- $ ! */
void parse_exp3(std::string &res, _dtype &res_dtype) {
	std::string temp_var;
	_dtype temp_dtype;
	quadruple_element element{};
	_instruct instr;
	parse_exp2(res, res_dtype);
	while (tokens[curr_token].type == TOK_MUL || tokens[curr_token].type == TOK_DIV ||
		   tokens[curr_token].type == TOK_MOD) {
		instr = tokens[curr_token].type == TOK_MUL ? MUL : tokens[curr_token].type == TOK_DIV ? DIV : MOD;
		match();
		parse_exp2(temp_var, temp_dtype);
		int t1, t2;
		if (is_const(res, t1) && is_const(temp_var, t2)) {
			res = std::to_string(instr == MUL ? t1 * t2 : instr == DIV ? t1 / t2 : t1 % t2);
			res_dtype = DATA_INT;
		} else {
			if (res_dtype!=temp_dtype){
				if(instr==MUL) print_warning("type of left and right side of operand * don't match.");
				else print_warning("type of left and right side of operand / don't match.");
			}
			std::string new_res = gen_temp_var();
			element = {TEMP, "int", new_res, NONE};
			insert_to_quadruple_list(element);
			element = {instr, res, temp_var, new_res};
			insert_to_quadruple_list(element);
			res = new_res;
			res_dtype = DATA_INT;
		}
	}
}/* * / % */
void parse_exp4(std::string &res, _dtype &res_dtype) {
	std::string temp_var;
	_dtype temp_dtype;
	quadruple_element element{};
	_instruct instr;
	parse_exp3(res, res_dtype);
	while (tokens[curr_token].type == TOK_PLUS || tokens[curr_token].type == TOK_SUB) {
		instr = tokens[curr_token].type == TOK_PLUS ? ADD : SUB;
		match();
		parse_exp3(temp_var, temp_dtype);
		int t1, t2;
		if (is_const(res, t1) && is_const(temp_var, t2)) {
			res = std::to_string(instr == ADD ? t1 + t2 : t1 - t2);
			res_dtype = DATA_INT;
		} else {
			if (res_dtype!=temp_dtype){
				if(instr==ADD) print_warning("type of left and right side of operand + don't match.");
				else print_warning("type of left and right side of operand - don't match.");
			}
			std::string new_res = gen_temp_var();
			element = {TEMP, "int", new_res, NONE};
			insert_to_quadruple_list(element);
			element = {instr, res, temp_var, new_res};
			insert_to_quadruple_list(element);
			res = new_res;
			res_dtype = DATA_INT;
		}
	}
}/* + - */
void parse_exp5(std::string &res, _dtype &res_dtype) {
	std::string temp_var;
	_dtype temp_dtype;
	quadruple_element element{};
	_instruct instr;
	parse_exp4(res, res_dtype);
	while (tokens[curr_token].type == TOK_SHL || tokens[curr_token].type == TOK_SHR) {
		instr = tokens[curr_token].type == TOK_SHL ? SHL : SHR;
		match();
		parse_exp4(temp_var, temp_dtype);
		int t1, t2;
		if (is_const(res, t1) && is_const(temp_var, t2)) {
			res = std::to_string(instr == SHL ? ((unsigned) t1 << (unsigned) t2) : ((unsigned) t1 >> (unsigned) t2));
			res_dtype = DATA_INT;
		} else {
			if (temp_dtype!=DATA_INT){
				print_warning("the right part of shuffle operand should be int instead of "+dtype_convert_table_2[temp_dtype]);
			}
			std::string new_res = gen_temp_var();
			element = {TEMP, "int", new_res, NONE};
			insert_to_quadruple_list(element);
			element = {instr, res, temp_var, new_res};
			insert_to_quadruple_list(element);
			res = new_res;
			res_dtype = DATA_INT;
		}
	}
}/* << >> */
void parse_exp6(std::string &res, _dtype &res_dtype) {
	std::string temp_var;
	_dtype temp_dtype;
	quadruple_element element{};
	_instruct instr;
	parse_exp5(res, res_dtype);
	while (tokens[curr_token].type == TOK_GT || tokens[curr_token].type == TOK_GE ||
		   tokens[curr_token].type == TOK_LT || tokens[curr_token].type == TOK_LE) {
		switch (tokens[curr_token].type) {
			case TOK_GT:
				instr = GT;
				break;
			case TOK_GE:
				instr = GE;
				break;
			case TOK_LT:
				instr = LT;
				break;
			case TOK_LE:
				instr = LE;
				break;
			default:
				break;
		}
		match();
		parse_exp5(temp_var, temp_dtype);
		int t1, t2;
		if (is_const(res, t1) && is_const(temp_var, t2)) {
			switch (instr) {
				case GT:
					res = std::to_string((int) (t1 > t2));
					break;
				case GE:
					res = std::to_string((int) (t1 >= t2));
					break;
				case LT:
					res = std::to_string((int) (t1 < t2));
					break;
				case LE:
					res = std::to_string((int) (t1 <= t2));
					break;
				default:
					break;
			}
			res_dtype = DATA_INT;
		} else {
			if (res_dtype!=temp_dtype){
				if (instr==GT) print_warning("type of left and right side of operand > don't match.");
				else if (instr==GE) print_warning("type of left and right side of operand >= don't match.");
				else if (instr==LT) print_warning("type of left and right side of operand < don't match.");
				else print_warning("type of left and right side of operand <= don't match.");
			}
			std::string new_res = gen_temp_var();
			element = {TEMP, "int", new_res, NONE};
			insert_to_quadruple_list(element);
			element = {instr, res, temp_var, new_res};
			insert_to_quadruple_list(element);
			res = new_res;
			res_dtype = DATA_INT;
		}
	}
}/* > < >= <= */
void parse_exp7(std::string &res, _dtype &res_dtype) {
	std::string temp_var;
	_dtype temp_dtype;
	quadruple_element element{};
	_instruct instr;
	parse_exp6(res, res_dtype);
	while (tokens[curr_token].type == TOK_NE || tokens[curr_token].type == TOK_EQ) {
		instr = tokens[curr_token].type == TOK_NE ? NE : EQ;
		match();
		parse_exp6(temp_var, temp_dtype);
		int t1, t2;
		if (is_const(res, t1) && is_const(temp_var, t2)) {
			res = std::to_string((int) (instr == NE ? (t1 != t2) : (t1 == t2)));
			res_dtype = DATA_INT;
		} else {
			if (res_dtype!=temp_dtype){
				if(instr==EQ) print_warning("type of left and right side of operand == don't match.");
				else print_warning("type of left and right side of operand != don't match.");
			}
			std::string new_res = gen_temp_var();
			element = {TEMP, "int", new_res, NONE};
			insert_to_quadruple_list(element);
			element = {instr, res, temp_var, new_res};
			insert_to_quadruple_list(element);
			res = new_res;
			res_dtype = DATA_INT;
		}
	}
}/* == != */

void parse_exp85(std::string &res, _dtype &res_dtype) {
	std::string temp_var;
	_instruct instr;
	quadruple_element element{};
	bool flag = false;
	if (tokens[curr_token].type == TOK_BITNOT) {
		flag = true;
		instr = BITNOT;
		match();
	}
	parse_exp7(res, res_dtype);
	if (flag) {
		int t1;
		if (is_const(res, t1)) {
			res = std::to_string(!t1);
		} else {
			element = {instr, res, NONE, NONE};
			insert_to_quadruple_list(element);
		}
	}
}/* ~ */

void parse_exp8(std::string &res, _dtype &res_dtype) {
	std::string temp_var;
	_dtype temp_dtype;
	quadruple_element element{};
	parse_exp85(res, res_dtype);
	while (tokens[curr_token].type == TOK_BITAND) {
		match();
		parse_exp7(temp_var, temp_dtype);
		int t1, t2;
		if (is_const(res, t1) && is_const(temp_var, t2)) {
			res = std::to_string((unsigned) t1 & (unsigned) t2);
			res_dtype = DATA_INT;
		} else {
			if (res_dtype!=temp_dtype){
				print_warning("type of left and right side of operand & don't match.");
			}
			std::string new_res = gen_temp_var();
			element = {TEMP, "int", new_res, NONE};
			insert_to_quadruple_list(element);
			element = {BITAND, res, temp_var, new_res};
			insert_to_quadruple_list(element);
			res = new_res;
			res_dtype = DATA_INT;
		}
	}
}/* & */
void parse_exp9(std::string &res, _dtype &res_dtype) {
	std::string temp_var;
	_dtype temp_dtype;
	quadruple_element element{};
	parse_exp8(res, res_dtype);
	while (tokens[curr_token].type == TOK_BITXOR) {
		match();
		parse_exp8(temp_var, temp_dtype);
		int t1, t2;
		if (is_const(res, t1) && is_const(temp_var, t2)) {
			res = std::to_string((unsigned) t1 ^ (unsigned) t2);
			res_dtype = DATA_INT;
		} else {
			if (res_dtype!=temp_dtype){
				print_warning("type of left and right side of operand ^ don't match.");
			}
			std::string new_res = gen_temp_var();
			element = {TEMP, "int", new_res, NONE};
			insert_to_quadruple_list(element);
			element = {BITXOR, res, temp_var, new_res};
			insert_to_quadruple_list(element);
			res = new_res;
			res_dtype = DATA_INT;
		}
	}
}/* ^ */
void parse_exp10(std::string &res, _dtype &res_dtype) {
	std::string temp_var;
	_dtype temp_dtype;
	quadruple_element element{};
	parse_exp9(res, res_dtype);
	while (tokens[curr_token].type == TOK_BITOR) {
		match();
		parse_exp9(temp_var, temp_dtype);
		int t1, t2;
		if (is_const(res, t1) && is_const(temp_var, t2)) {
			res = std::to_string((unsigned) t1 | (unsigned) t2);
			res_dtype = DATA_INT;
		} else {
			if (res_dtype!=temp_dtype){
				print_warning("type of left and right side of operand | don't match.");
			}
			std::string new_res = gen_temp_var();
			element = {TEMP, "int", new_res, NONE};
			insert_to_quadruple_list(element);
			element = {BITOR, res, temp_var, new_res};
			insert_to_quadruple_list(element);
			res = new_res;
			res_dtype = DATA_INT;
		}
	}
}/* | */
void parse_exp11(std::string &res, _dtype &res_dtype) {
	std::string temp_var;
	_dtype temp_dtype;
	quadruple_element element{};
	parse_exp10(res, res_dtype);
	while (tokens[curr_token].type == TOK_LOGIAND) {
		match();
		parse_exp10(temp_var, temp_dtype);
		int t1, t2;
		if (is_const(res, t1) && is_const(temp_var, t2)) {
			res = std::to_string(t1 * t2);
			res_dtype = DATA_INT;
		} else {
			if (res_dtype!=temp_dtype){
				print_warning("type of left and right side of operand && don't match.");
			}
			std::string new_res = gen_temp_var();
			element = {TEMP, "int", new_res, NONE};
			insert_to_quadruple_list(element);
			element = {LOGIAND, res, temp_var, new_res};
			insert_to_quadruple_list(element);
			res = new_res;
			res_dtype = DATA_INT;
		}
	}
}/* && */
void parse_exp12(std::string &res, _dtype &res_dtype) {
	std::string temp_var;
	_dtype temp_dtype;
	quadruple_element element{};
	parse_exp11(res, res_dtype);
	while (tokens[curr_token].type == TOK_LOGIOR) {
		match();// ||
		parse_exp11(temp_var, temp_dtype);
		int t1, t2;
		if (is_const(res, t1) && is_const(temp_var, t2)) {
			res = std::to_string(t1 + t2);
			res_dtype = DATA_INT;
		} else {
			if (res_dtype!=temp_dtype){
				print_warning("type of left and right side of operand || don't match.");
			}
			std::string new_res = gen_temp_var();
			element = {TEMP, "int", new_res, NONE};
			insert_to_quadruple_list(element);
			element = {LOGIOR, res, temp_var, new_res};
			insert_to_quadruple_list(element);
			res = new_res;
			res_dtype = DATA_INT;
		}
	}
}/* || */
void parse_exp13(std::string &res, _dtype &res_dtype) {//not supported yet.
	parse_exp12(res, res_dtype);
}/* ? : */
void parse_exp14(std::string &res, _dtype &res_dtype) {//looks comma operand won't do anything...
	parse_exp13(res, res_dtype);
	while (tokens[curr_token].type == TOK_COMMA) {
		match();
		parse_exp13(res, res_dtype);
	}
}/* , */
