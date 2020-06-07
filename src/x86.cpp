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
	insert_into_x86_table("jmp main");
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
	int para_loc = 8;
	int temp_size;
	std::string name__;
	table_entry entry{};
	gen_start_code();
	for (const auto &i : quadruple_list) {
		switch (i.instruct) {
			case VAR:
				temp_size = i.c == NONE ? 1 : atoi(i.c.c_str());
				entry = {i.c == NONE ? IDN_VAR : IDN_ARRAY, i.a == "int" ? DATA_INT : DATA_CHAR, temp_size,
						 temp_size * (-INT_SIZE)};
				name__ = i.b;
				insert_to_symbol_table(scope::LOCAL, name__, entry);
				break;
			case TEMP:
			case PARAM:
				entry = {i.c == NONE ? IDN_VAR : IDN_ARRAY, i.a == "int" ? DATA_INT : DATA_CHAR, 0, para_loc+INT_SIZE};
				para_loc+=4;
				name__ = i.b;
				insert_to_symbol_table(scope::LOCAL, name__, entry);
				break;

		}
	}
}

void gen_bss_section() {
	insert_into_x86_table("section .bss");
	insert_into_x86_table("?res resb 64");
	insert_into_x86_table("?res_read resb 4096");
}