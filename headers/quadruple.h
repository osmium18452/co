#ifndef CO_QUADRUPLE_H
#define CO_QUADRUPLE_H

#include "global.h"

enum instruct{

};

struct quadruple_element{
	instruct instruct;
	std::string a;
	std::string b;
	std::string c;
};

void gen_quadruple(instruct instruct,std::string a, std::string b, std::string c);

extern std::vector<quadruple_element> quadruple_list;

#endif //CO_QUADRUPLE_H
