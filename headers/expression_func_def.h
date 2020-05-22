#ifndef CO_EXPRESSION_FUNC_DEF_H
#define CO_EXPRESSION_FUNC_DEF_H

#include "global.h"
#include "table.h"

extern void parse_non_void_func_call(std::string &res, dtype &data_type, const std::string &id);
extern void parse_array_read(std::string &res, dtype &dtype, const std::string &id);

/*factor:   identifier
 *          immidiate number
 *          func call (with return value)
 *          array read
 */
void parse_factor(std::string &res, dtype &dtype);
void parse_exp1(std::string &res, dtype &res_dtype);/* (backward) ++ -- */
void parse_exp2(std::string &res, dtype &res_dtype);/* (frontward) ++ -- + - !*/
void parse_exp3(std::string &res, dtype &res_dtype);/* * / % */
void parse_exp4(std::string &res, dtype &res_dtype);/* + - */
void parse_exp5(std::string &res, dtype &res_dtype);/* << >> */
void parse_exp6(std::string &res, dtype &res_dtype);/* > < >= <= */
void parse_exp7(std::string &res, dtype &res_dtype);/* == != */
void parse_exp8(std::string &res, dtype &res_dtype);/* & */
void parse_exp9(std::string &res, dtype &res_dtype);/* ^ */
void parse_exp10(std::string &res, dtype &res_dtype);/* | */
void parse_exp11(std::string &res, dtype &res_dtype);/* && */
void parse_exp12(std::string &res, dtype &res_dtype);/* || */
void parse_exp13(std::string &res, dtype &res_dtype);/* ? : */
void parse_exp14(std::string &res, dtype &res_dtype);/* , */


#endif //CO_EXPRESSION_FUNC_DEF_H
