#include "../headers/global.h"
#include "../headers/optimizer.h"
#include "../headers/optimizer_func_def.h"
#include "../headers/x86.h"

extern std::vector<instr_table_element> instr_table;

void optimize() {
	peelhole();
}

void peelhole() {
	int it = 0;
	while (it < instr_table.size()) {
		switch (instr_table[it].instr) {
			case _push_:
				if (it + 1 < instr_table.size() && instr_table[it + 1].instr == _pop_ &&
				    instr_table[it].desc == instr_table[it + 1].desc) {
					instr_table.erase(instr_table.begin() + it, instr_table.begin() + it + 2);
				}
				break;
				case _pop
			default:
				it++;
				break;
		}
	}
}