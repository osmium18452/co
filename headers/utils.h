#ifndef CO_UTILS_H
#define CO_UTILS_H

#include "global.h"

void init_temp_var();
void init_temp_label();

std::string gen_temp_var();
std::string gen_temp_label();
std::string gen_temp_label(const std::string &name);
std::string process_string(const std::string &s);

bool is_const(const std::string &t, int &val);
bool is_num(const std::string &s);

#endif //CO_UTILS_H
