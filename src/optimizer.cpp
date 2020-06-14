#include "../headers/global.h"
#include "../headers/optimizer.h"
#include "../headers/optimizer_func_def.h"
#include "../headers/x86.h"

extern std::vector<instr_table_element> instr_table;
extern std::vector<instr_table_element> optimized_instr_table;

void optimize() {
	peelhole();
}

void peelhole() {
	auto it=instr_table.begin();
	while (it<instr_table.end()){
		switch (it->instr) {
			case _push_:
				if (it+1<instr_table.end()&&it->instr==_pop_&&it->desc==(it+1)->desc){

				}
		}
	}
	while (it < instr_table.size()) {
		cout<<instr_table.size()<<" "<<it<<endl;
		switch (instr_table[it].instr) {
			case _push_:
				if (it + 1 < instr_table.size() && instr_table[it + 1].instr == _pop_ &&
				    instr_table[it].desc == instr_table[it + 1].desc) {
					instr_table.erase(instr_table.begin() + it, instr_table.begin() + it + 2);
				}
				break;
			case _pop_:
				if (it + 1 < instr_table.size() && instr_table[it + 1].instr == _push_ &&
				    instr_table[it].desc == instr_table[it + 1].desc) {
					instr_table.erase(instr_table.begin() + it, instr_table.begin() + it + 2);
				}
				break;
			default:
				it++;
				break;
		}
	}
}