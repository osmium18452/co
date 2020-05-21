#include "../headers/global.h"
#include "../headers/expression.h"
#include "../headers/expression_func_def.h"

int temp_var_num;

void init_temp_var(){
	temp_var_num=0;
}

std::string gen_temp_var(){
	std::string temp_var="$temp_";
	temp_var+=std::to_string(temp_var_num);
	return temp_var;
}

void expression(){

}
void parse_factor(std::string &res, dtype &dtype){

}
/*factor:   identifier
 *          immidiate number
 *          func call (with return value)
 *          array read
 */
void parse_exp1(std::string &res, dtype &dtype){

}/* (backward) ++ -- */
void parse_exp2(std::string &res, dtype &dtype){

}/* (frontward) ++ -- + - !*/
void parse_exp3(std::string &res, dtype &dtype){

}/* * / % */
void parse_exp4(std::string &res, dtype &dtype){

}/* + - */
void parse_exp5(std::string &res, dtype &dtype){

}/* << >> */
void parse_exp6(std::string &res, dtype &dtype){

}/* > < >= <= */
void parse_exp7(std::string &res, dtype &dtype){

}/* == != */
void parse_exp8(std::string &res, dtype &dtype){

}/* & */
void parse_exp9(std::string &res, dtype &dtype){

}/* ^ */
void parse_exp10(std::string &res, dtype &dtype){

}/* | */
void parse_exp11(std::string &res, dtype &dtype){

}/* && */
void parse_exp12(std::string &res, dtype &dtype){

}/* || */
void parse_exp13(std::string &res, dtype &dtype){

}/* ? : */
void parse_exp14(std::string &res, dtype &dtype){

}/* = */
void parse_exp15(std::string &res, dtype &dtype){

}/* , */
