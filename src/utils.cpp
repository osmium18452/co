#include "../headers/global.h"
#include "../headers/utils.h"

int temp_var_num;
int temp_label_num;

bool is_const(const std::string &t, int &val) {
	if (t[0] == '\'') {
		val = t[1];
		return true;
	} else if (std::isdigit(t[0])) {
		val = std::stoi(t);
		return true;
	} else if (t[0] == '-' && isdigit(t[1])) {
		val = std::stoi(t);
		return true;
	} else return false;
}

void init_temp_var() {
	temp_var_num = 0;
}

void init_temp_label() {
	temp_label_num = 0;
}

std::string gen_temp_var() {
	std::string temp_var = "$temp_";
	temp_var += std::to_string(temp_var_num);
	return temp_var;
}

std::string gen_temp_label() {
	std::string temp_label = "$label_";
	temp_label += std::to_string(temp_label_num);
	return temp_label;
}