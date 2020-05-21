#ifndef CO_UTILS_H
#define CO_UTILS_H

#include "global.h"

void init_temp_var();
void init_temp_label();

std::string gen_temp_var();
std::string gen_temp_label();

bool is_const(const std::string &t, int &val);

#endif //CO_UTILS_H
