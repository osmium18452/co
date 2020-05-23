#ifndef CO_SDT_H
#define CO_SDT_H

#include "global.h"

struct kase_table{
	int kase_num;
	std::string kase_label;
	bool operator < (const kase_table &kaseT) const {
		return this->kase_num<kaseT.kase_num;
	}
};

extern int curr_token;

void parse_program();


#endif //CO_SDT_H
