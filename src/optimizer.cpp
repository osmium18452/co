#include "../headers/global.h"
#include "../headers/optimizer.h"
#include "../headers/optimizer_func_def.h"
#include "../headers/x86.h"
#include "../headers/utils.h"

#define begin instr_table.begin()

extern std::vector<instr_table_element> instr_table;
extern std::vector<instr_table_element> optimized_instr_table;
extern std::string instr_convert_table[];

void optimize() {
	peephole();
}

void peephole() {
	int it = 0;
	while (it < instr_table.size()) {
		switch (instr_table[it].instr) {
			case _push_:
				if (it + 1 < instr_table.size() && instr_table[it + 1].instr == _pop_ &&
					instr_table[it].desc == instr_table[it + 1].desc) {
					/*cout << instr_convert_table[(begin + it)->instr] << " " << (begin + it)->desc << endl;
					cout << instr_convert_table[(begin + it + 1)->instr] << " " << (begin + it + 1)->desc << endl;*/
					instr_table.erase(begin + it, begin + it + 2);
					it--;
				} else it++;
				break;
			case _pop_:
				if (it + 1 < instr_table.size() && instr_table[it + 1].instr == _push_ &&
					instr_table[it].desc == instr_table[it + 1].desc) {
					/*cout << it + 18 << endl;
					cout << (begin + it)->instr << " " << instr_convert_table[(begin + it)->instr] << " "
						 << (begin + it)->desc
						 << endl;
					cout << (begin + it + 1)->instr << " " << instr_convert_table[(begin + it + 1)->instr] << " "
						 << (begin + it + 1)->desc << endl
						 << endl;*/
					instr_table.erase(begin + it, begin + it + 2);
					it--;
				} else it++;
				break;
			case _sub_:
				if (instr_table[it].src == "0" || instr_table[it].src == "dword 0") {
					instr_table.erase(begin + it, begin + it + 1);
				} else if (instr_table[it].src == "1" || instr_table[it].src == "dword 1") {
					instr_table[it] = instr_table_element{instr_table[it].ident, _dec_, instr_table[it].desc, NONE};
					it++;
				} else it++;
				break;
			case _add_:
				if (instr_table[it].src == "0" || instr_table[it].src == "dword 0") {
					instr_table.erase(begin + it, begin + it + 1);
				} else if (instr_table[it].src == "1" || instr_table[it].src == "dword 1") {
					instr_table[it] = instr_table_element{instr_table[it].ident, _inc_, instr_table[it].desc, NONE};
					it++;
				} else it++;
				break;
			case _mov_:
				if (instr_table[it].desc[0] == 'e' &&
					(instr_table[it].src == "0" || instr_table[it].src == "dword 0")) {
					instr_table[it] = instr_table_element{instr_table[it].ident, _xor_, instr_table[it].desc,
														  instr_table[it].desc};
					it++;
				} else if(instr_table[it].desc==instr_table[it].src){
					instr_table.erase(begin+it);
				} else it++;
				break;
			default:
				it++;
				break;
		}
	}
}