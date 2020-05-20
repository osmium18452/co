#include "../headers/global.h"
#include "../headers/expression.h"

int temp_var_num;

void init_temp_var(){
	temp_var_num=0;
}

std::string gen_temp_var(){
	std::string temp_var="$temp_";
	temp_var+=std::to_string(temp_var_num);
	return temp_var;
}