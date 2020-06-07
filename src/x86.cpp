#include "../headers/x86.h"
#include "../headers/x86_func_def.h"
#include "../headers/quadruple.h"
#include "../headers/table.h"
#include "../headers/utils.h"

std::vector<std::string> instruct_table;
int ident;

void inc_ident() {
	ident += 4;
}

void dec_ident() {
	ident -= 4;
}

void insert_into_x86_table(const std::string &s) {
	std::string instr;
	for (auto i = 1; i < ident; i++) {
		instr += " ";
	}
	instruct_table.push_back(instr + s);
}

void translate_to_x86() {
	ident = 0;
	insert_into_x86_table("%include \"io.asm\"");
	gen_data_section();
	gen_bss_section();
	gen_text_section();
}

void gen_data_section() {
	insert_into_x86_table("section .data");
	inc_ident();
	gen_string_table();
	gen_global_table();
	dec_ident();
}

void gen_string_table() {
	for (const auto &i:string_table) {
		insert_into_x86_table(i.second + " db " + process_string(i.first) + ",00h");
	}
}

void print_x86_table(const std::string &file) {
	std::ostream x86_stream(NULL);
	std::filebuf buffer;
	buffer.open(file, std::ios::out);
	x86_stream.rdbuf(&buffer);
	for (const auto &i:instruct_table) {
		x86_stream << i << endl;
	}
}

void gen_start_code() {
	insert_into_x86_table("global _start");
	insert_into_x86_table("_start:");
	inc_ident();
	insert_into_x86_table("call main");
	insert_into_x86_table("call $quit");
	dec_ident();
}

void gen_global_table() {
	for (const auto &i:symbol_table[0]) {
		switch (i.second.itype) {
			case IDN_VAR:
				insert_into_x86_table("g_" + i.first + " dd 0");
				break;
			case IDN_ARRAY:
				insert_into_x86_table("g_" + i.first + " dd " + std::to_string(i.second.value) + " dup (0)");
				break;
			default:
				break;
		}
	}
}

void gen_text_section() {
	gen_start_code();
	for (auto iter=quadruple_list.begin();iter<quadruple_list.end();iter++) {
		switch (iter->instruct) {
			case VAR:
			case TEMP:
			case PARAM:
				continue;
			case FUNC:
				translate_func(iter);
				break;
			case END:
				gen_func_tail();
			default:
				break;
		}
	}
}

void gen_bss_section() {
	insert_into_x86_table("section .bss");
	inc_ident();
	insert_into_x86_table("?res resb 64");
	insert_into_x86_table("?res_read resb 4096");
	dec_ident();
}

void translate_func(const std::vector<quadruple_element>::iterator &iter){
	gen_func_head(iter);
	create_new_local_table();
	rebuild_symbol_table(iter);
	destroy_current_local_table();//todo: should not be here. move it to END.
}

void gen_func_head(const std::vector<quadruple_element>::iterator &iter){
	insert_into_x86_table(iter->b+":");
	inc_ident();
	insert_into_x86_table("push ebp");
	insert_into_x86_table("mov ebp,esp");
	insert_into_x86_table("push ebx");
}

void rebuild_symbol_table(const std::vector<quadruple_element>::iterator &iter){
	int num_of_var=0;
	for (auto i=iter;i->instruct!=END;i++){
		if (i->instruct==TEMP||i->instruct==VAR){
			if (!i->c.empty()){
				num_of_var+=stoi(i->c);
			} else {
				num_of_var++;
			}
		}
	}
}

void gen_func_tail(){
	insert_into_x86_table("pop ebx");
	insert_into_x86_table("leave");
	insert_into_x86_table("ret");
	dec_ident();
}

/*temp_size = i.c == NONE ? 1 : atoi(i.c.c_str());
				entry = {i.c == NONE ? IDN_VAR : IDN_ARRAY, i.a == "int" ? DATA_INT : DATA_CHAR, temp_size,
						 temp_size * (-INT_SIZE)};
				name__ = i.b;
				insert_to_symbol_table(scope::LOCAL, name__, entry);
				break;*/
/*entry = {i.c == NONE ? IDN_VAR : IDN_ARRAY, i.a == "int" ? DATA_INT : DATA_CHAR, 0, para_loc};
				para_loc+=INT_SIZE;
				name__ = i.b;
				insert_to_symbol_table(scope::LOCAL, name__, entry);
				break;*/