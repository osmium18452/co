#include "../headers/x86.h"
#include "../headers/x86_func_def.h"
#include "../headers/quadruple.h"
#include "../headers/table.h"
#include "../headers/reg.h"
#include "../headers/utils.h"

std::vector<std::string> instruct_table;
int ident;
std::vector<quadruple_element>::iterator it;

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
	it = quadruple_list.begin();
	while (it != quadruple_list.end()) {
		translate_func();
	}
	/*for (auto iter = quadruple_list.begin(); iter < quadruple_list.end(); iter++) {
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
				break;
			case RESTORE_STACK:
				translate_restore_stack(iter);
				break;
			case SAVE_REG:
				translate_save_reg();
				break;
			case RESTORE_REG:
				translate_restore_reg();
				break;
			case CALL:
				cout << "call " << iter->a << endl;
				translate_call(iter);
				break;
			case LABEL:
				translate_label(iter);
				break;
			case PUSH:
				translate_push(iter);
				break;
			default:
				break;
		}
	}*/
}

void translate_push() {
	insert_into_x86_table("mov eax," + tell_me_the_address(it->b));
	insert_into_x86_table("push eax");
}

void translate_label() {
	insert_into_x86_table(it->a + ":");
}

void translate_call() {
	insert_into_x86_table("call " + it->a);
}

void translate_restore_reg() {
	insert_into_x86_table("pop eax");
	insert_into_x86_table("pop ecx");
	insert_into_x86_table("pop edx");
}

void translate_save_reg() {
	insert_into_x86_table("push edx");
	insert_into_x86_table("push ecx");
	insert_into_x86_table("push eax");
}

void translate_restore_stack() {
//	cout<<iter->a<<endl;
	insert_into_x86_table("add esp," + std::to_string(std::stoi(it->a) * INT_SIZE));
}

void gen_bss_section() {
	insert_into_x86_table("section .bss");
	inc_ident();
	insert_into_x86_table("?res resb 64");
	insert_into_x86_table("?res_read resb 4096");
	dec_ident();
}

void translate_func() {
	int curr_var_num = 0;
	int curr_param_num = 0;
	gen_func_head();
	calc_func_stack_size();
	while (it->instruct != END) {
//		cout<<it-quadruple_list.begin()<<" "<<instruct_convert_table[it->instruct]<<endl;
		switch (it->instruct) {
			case PARAM:
				translate_param(&curr_param_num);
				break;
			case VAR:
			case TEMP:
				translate_var_def(&curr_var_num);
				break;
			case CREATE_TABLE:
				create_new_local_table_2();
				break;
			case DESTROY_TABLE:
				flush_the_regs();
				destroy_current_local_table_2();
				break;
			case RESTORE_REG:
				translate_restore_reg();
				break;
			case SAVE_REG:
				translate_save_reg();
				break;
			case RESTORE_STACK:
				translate_restore_stack();
				break;
			case CALL:
				translate_call();
				break;
			case LABEL:
				translate_label();
				break;
			case PUSH:
				translate_push();
				break;
			case GETRET:
				translate_getret();
				break;
			case JE:
				translate_je();
				break;
			case JA:
				translate_ja();
				break;
			case JB:
				translate_jb();
				break;
			case JMP:
				translate_jmp();
				break;
			case ASSIGN:
				translate_assign();
				break;
				/*notice: in our compiler, we don't support unsigned numbers. so the ja and jb here stand for the jg and jl*/
			default:
				break;
		}
		it++;
	}
	gen_func_tail();
}

void translate_assign(){
	regs var1,var2;
	if (is_num(it->a)){
		insert_into_x86_table("mov "+where_to_write_the_var(it->b)+","+it->a);
	} else {
		var1=where_is_the_var_2(it->a);
		var2=where_is_the_var_2(it->b);
		if (var1==MEM&&var2==MEM) insert_into_x86_table("mov "+give_me_a_reg(it->a)+","+tell_me_the_address(it->a));
		insert_into_x86_table("mov "+where_to_write_the_var(it->b)+","+where_is_the_var(it->a));
	}
}

void translate_je(){
	insert_into_x86_table("je "+it->a);
}

void translate_jmp(){
	insert_into_x86_table("jmp "+it->a);
}

void translate_ja(){
	insert_into_x86_table("jg "+it->a);
}

void translate_jb(){
	insert_into_x86_table("jl "+it->a);
}

void translate_getret() {
	insert_into_x86_table("mov " + where_to_write_the_var(it->a) + ", eax");
}

void translate_param(int *curr_param_num) {
	(*curr_param_num)++;
	table_entry entry{IDN_VAR, it->a == "int" ? DATA_INT : DATA_CHAR, 0, -(*curr_param_num) * INT_SIZE, l};
	insert_to_symbol_table(LOCAL, it->b, entry);
}

void translate_var_def(int *curr_var_num) {
	if (it->c.empty())(*curr_var_num)++;
	else (*curr_var_num) += std::stoi(it->c);
	table_entry entry{it->c.empty() ? IDN_VAR : IDN_ARRAY, it->a == "int" ? DATA_INT : DATA_CHAR, 0,
					  -(*curr_var_num) * INT_SIZE, l};
	insert_to_symbol_table(LOCAL, it->b, entry);;
}

void gen_func_head() {
	insert_into_x86_table(it->b + ":");
	it++;
	inc_ident();
	insert_into_x86_table("push ebp");
	insert_into_x86_table("mov ebp,esp");
	insert_into_x86_table("push ebx");
}

void calc_func_stack_size() {
	int num_of_var = 0;
	for (auto i = it; i->instruct != END; i++) {
		if (i->instruct == TEMP || i->instruct == VAR) {
			if (!i->c.empty()) {
				num_of_var += stoi(i->c);
			} else {
				num_of_var++;
			}
		}
	}
	insert_into_x86_table("sub esp," + std::to_string(num_of_var * INT_SIZE));
}

void gen_func_tail() {
	insert_into_x86_table("pop ebx");
	insert_into_x86_table("leave");
	insert_into_x86_table("ret");
	it++;
	dec_ident();
}
