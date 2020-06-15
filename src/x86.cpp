#include "../headers/x86.h"
#include "../headers/x86_func_def.h"
#include "../headers/quadruple.h"
#include "../headers/table.h"
#include "../headers/reg.h"
#include "../headers/utils.h"

std::vector<std::string> x86_table;
std::vector<instr_table_element> instr_table;
std::vector<instr_table_element> optimized_instr_table;
int ident;
std::vector<quadruple_element>::iterator it;

std::string instr_convert_table[]{
	"mov",
	"pop", "push",
	"popa", "pusha",
	"lea",
	"cdq",
	"add", "sub", "imul", "idiv",
	"inc", "dec",
	"and", "not", "or", "xor",
	"shl", "shr",
	"cmp",
	"je", "jne", "jmp",
	"jg", "jl",
	"ja", "jb",
	"setl", "setle", "setg", "setge",
	"sete", "setne",
	"ret", "leave",
	"int",
	"",
	"call",
	"dd",
};

void print_x86_table(const std::string &file) {
	std::ostream x86_stream(nullptr);
	std::filebuf buffer;
	std::string space = " ";
	buffer.open(file, std::ios::out);
	x86_stream.rdbuf(&buffer);
	for (const auto &i:x86_table) {
		x86_stream << i << endl;
	}
	for (const auto &i:instr_table) {
		if (i.instr == _label_) {
			x86_stream << std::string(i.ident, ' ') << i.desc << ":" << endl;
		} else {

			x86_stream << std::string(i.ident, ' ') << instr_convert_table[i.instr] << " " << i.desc
			           << (i.src.empty() ? "" : " , ") << i.src
			           << endl;
		}
	}
}

void inc_ident() {
	ident += 4;
}

void dec_ident() {
	ident -= 4;
}

void insert_into_x86_table(instr instr, const std::string &desc, const std::string &src) {
	instr_table.emplace_back(instr_table_element{ident, instr, desc, src});
}

void insert_into_x86_table(instr instr, const std::string &desc) {
	instr_table.emplace_back(instr_table_element{ident, instr, desc, NONE});
}

void insert_into_x86_table(instr instr) {
	instr_table.emplace_back(instr_table_element{ident, instr, NONE, NONE});
}

void insert_into_x86_table(const std::string &s) {
	x86_table.push_back(std::string(ident,' ') + s);
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
	insert_into_x86_table("msg db \"hello world\",0ah,00h");
	insert_into_x86_table("rtn db 0ah,00h");
	for (const auto &i:string_table) {
		insert_into_x86_table(i.second + " db " + process_string(i.first) + ",00h");
	}
}

void gen_start_code() {
	insert_into_x86_table("section .text");
	insert_into_x86_table("global _start");
	insert_into_x86_table("_start:");
	inc_ident();
	insert_into_x86_table("mov esi,?res_read");
	insert_into_x86_table("xor edi,edi");
	insert_into_x86_table("mov byte [esi+edi],0ah");
	insert_into_x86_table("call main");
	insert_into_x86_table("call $quit");
	dec_ident();
}

void gen_global_table() {
	for (const auto &i:symbol_table[0]) {
		switch (i.second.itype) {
			case IDN_VAR:
				insert_into_x86_table("g_" + i.first + " dd " + std::to_string(i.second.value));
				break;
			case IDN_ARRAY:
				insert_into_x86_table("g_" + i.first + " times " + std::to_string(i.second.value) + " dd 0");
				break;
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

void gen_text_section() {
	gen_start_code();
	it = quadruple_list.begin();
	while (it != quadruple_list.end()) {
		translate_func();
	}
}

void translate_push() {
	write_the_reg_back(EAX);
	change_reg_table_unit(EAX, NONE);
	insert_into_x86_table(_mov_, "eax", where_is_the_var(it->b));
	insert_into_x86_table(_push_, "eax");


}

void translate_label() {
	
	insert_into_x86_table(_label_, it->a);
}

void translate_call() {
	insert_into_x86_table(_call_, it->a);
	
}

void translate_restore_reg() {
	
	insert_into_x86_table(_pop_, "edx");
	insert_into_x86_table(_pop_, "ecx");
	insert_into_x86_table(_pop_, "eax");
	reg_table[EAX].var = save_reg_table_var_table[EAX];
	reg_table[EBX].var = save_reg_table_var_table[EBX];
	reg_table[ECX].var = save_reg_table_var_table[ECX];
	reg_table[EDX].var = save_reg_table_var_table[EDX];
}

void translate_save_reg() {
	
	insert_into_x86_table(_push_, "eax");
	insert_into_x86_table(_push_, "ecx");
	insert_into_x86_table(_push_, "edx");
	save_reg_table_var_table[EAX] = reg_table[EAX].var;
	save_reg_table_var_table[EBX] = reg_table[EBX].var;
	save_reg_table_var_table[ECX] = reg_table[ECX].var;
	save_reg_table_var_table[EDX] = reg_table[EDX].var;
}

void translate_restore_stack() {
	insert_into_x86_table(_add_, "esp", std::to_string(std::stoi(it->a) * INT_SIZE));
	
}

void translate_func() {
	int curr_var_num = 0;
	int curr_param_num = 1;
	gen_func_head();
	calc_func_stack_size();
	while (it->instruct != END) {
		switch (it->instruct) {
			case PARAM:
				translate_param(&curr_param_num);
				break;
			case VAR:
			case TEMP:
				translate_var_def(&curr_var_num);
				break;
			case CREATE_TABLE:
				flush_the_regs();
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
			case ADD:
				translate_add();
				break;
			case SUB:
				translate_sub();
				break;
			case MUL:
				translate_mul();
				break;
			case DIV:
			case MOD:
				translate_div_mod();
				break;
			case PRINT:
				translate_print();
				break;
			case RET:
				translate_ret();
				break;
			case INC:
				translate_inc();
				break;
			case DEC:
				translate_dec();
				break;
			case BITAND:
				translate_bitand();
				break;
			case BITOR:
				translate_bitor();
				break;
			case BITXOR:
				translate_bitxor();
				break;
			case BITNOT:
				translate_bitnot();
				break;
			case CMP:
				translate_cmp();
				break;
			case SHL:
				translate_shl();
				break;
			case SHR:
				translate_shr();
				break;
			case RDARR:
				translate_rdarr();
				break;
			case WRARR:
				translate_wrarr();
				break;
			case FLUSH_REGTABLE:
				flush_reg_table();
				break;
			case FLUSH_REG:
				flush_the_regs();
				break;
			case SCAN:
				translate_scan();
				break;
			case LOGIAND:
				translate_logiand();
				break;
			case LOGIOR:
				translate_logior();
				break;
			case GE:
				translate_ge();
				break;
			case GT:
				translate_gt();
				break;
			case LE:
				translate_le();
				break;
			case LT:
				translate_lt();
				break;
			case EQ:
				translate_eq();
				break;
			case NE:
				translate_ne();
				break;
			case NOT:
				translate_not();
				break;
			case KASE_ITEM:
				translate_kase_item();
				break;
			case SWJMP:
				translate_swjmp();
				break;
			default:
				break;
		}
		it++;
	}
	gen_func_tail();
}

void translate_kase_item() {
	insert_into_x86_table(_dd_, it->a);
	
}

void translate_swjmp() {
	regs vara = where_is_the_var_2(it->a);
	if (vara > 4) {
		std::string rega = give_me_a_reg(it->a);
		
		insert_into_x86_table(_mov_, rega, tell_me_the_address(it->a));
		insert_into_x86_table(_jmp_, "[" + rega + "*4" + "+" + it->b + "]");
	} else {
		
		insert_into_x86_table(_jmp_, "[" + regs_convert_table[vara] + "*4" + "+" + it->b + "]");
	}
}



void translate_logiand() {
	std::string true_label = gen_temp_label("x86_true_logiand");
	std::string false_label = gen_temp_label("x86_false_logiand");
	std::string end_label = gen_temp_label("x86_end_logiand");
	regs varc = where_is_the_var_2(it->c);
	if (varc < 4) {
		change_reg_table_unit(varc, NONE);
	}
	write_the_reg_back(EAX);
	change_reg_table_unit(EAX, NONE);
	
	insert_into_x86_table(_cmp_, where_is_the_var(it->a), "0");
	insert_into_x86_table(_je_, false_label);
	insert_into_x86_table(_cmp_, where_is_the_var(it->b), "0");
	insert_into_x86_table(_je_, false_label);
	insert_into_x86_table(_label_, true_label);
	insert_into_x86_table(_mov_, "eax", "1");
	insert_into_x86_table(_jmp_, end_label);
	insert_into_x86_table(_label_, false_label);
	insert_into_x86_table(_xor_, "eax", "eax");
	insert_into_x86_table(_label_, end_label);
	change_reg_table_unit(EAX, it->c);
}

void translate_logior() {
	std::string true_label = gen_temp_label("x86_true_logioir");
	std::string false_label = gen_temp_label("x86_false_logioir");
	std::string end_label = gen_temp_label("x86_end_logioir");
	regs varc = where_is_the_var_2(it->c);
	if (varc < 4) {
		change_reg_table_unit(varc, NONE);
	}
	write_the_reg_back(EAX);
	change_reg_table_unit(EAX, NONE);
	
	insert_into_x86_table(_cmp_, where_is_the_var(it->a), "0");
	insert_into_x86_table(_ja_, true_label);
	insert_into_x86_table(_cmp_, where_is_the_var(it->b), "0");
	insert_into_x86_table(_ja_, true_label);
	insert_into_x86_table(_label_, false_label);
	insert_into_x86_table(_xor_, "eax", "eax");
	insert_into_x86_table(_jmp_, end_label);
	insert_into_x86_table(_label_, true_label);
	insert_into_x86_table(_mov_, "eax", "1");
	insert_into_x86_table(_label_, end_label);
	change_reg_table_unit(EAX, it->c);
}

void translate_ne() {
	std::string equal_label = gen_temp_label("x86_ne_equal");
	std::string end_label = gen_temp_label("x86_ne_end");
	regs varc = where_is_the_var_2(it->c);
	if (varc < 4) {
		change_reg_table_unit(varc, NONE);
	}
	write_the_reg_back(EAX);
	change_reg_table_unit(EAX, NONE);
	regs vara = where_is_the_var_2(it->a), varb = where_is_the_var_2(it->b);
	bool flag = false;
	if (vara == MEM && varb == MEM) {
		flag = true;
		
		insert_into_x86_table(_mov_, "eax", where_is_the_var(it->a));
	}
	
	insert_into_x86_table(_cmp_, (flag ? "eax" : where_is_the_var(it->a)), where_is_the_var(it->b));
	insert_into_x86_table(_setne_, "al");
	insert_into_x86_table(_and_, "eax", "000000ffh");
	change_reg_table_unit(EAX, it->c);
}

void translate_eq() {
	std::string equal_label = gen_temp_label("x86_ne_equal");
	std::string end_label = gen_temp_label("x86_ne_end");
	regs varc = where_is_the_var_2(it->c);
	if (varc < 4) {
		change_reg_table_unit(varc, NONE);
	}
	write_the_reg_back(EAX);
	change_reg_table_unit(EAX, NONE);
	regs vara = where_is_the_var_2(it->a), varb = where_is_the_var_2(it->b);
	bool flag = false;
	if (vara == MEM && varb == MEM) {
		flag = true;
		
		insert_into_x86_table(_mov_, "eax", where_is_the_var(it->a));
	}
	
	insert_into_x86_table(_cmp_, (flag ? "eax" : where_is_the_var(it->a)), where_is_the_var(it->b));
	insert_into_x86_table(_sete_, "al");
	insert_into_x86_table(_and_, "eax", "000000ffh");
	change_reg_table_unit(EAX, it->c);
}

void translate_le() {
	std::string true_label = gen_temp_label("x86_true_le");
	std::string end_label = gen_temp_label("x86_end_le");
	regs varc = where_is_the_var_2(it->c);
	if (varc < 4) {
		change_reg_table_unit(varc, NONE);
	}
	write_the_reg_back(EAX);
	change_reg_table_unit(EAX, NONE);
	regs vara = where_is_the_var_2(it->a), varb = where_is_the_var_2(it->b);
	bool flag = false;
	if (vara == MEM && varb == MEM) {
		flag = true;
		
		insert_into_x86_table(_mov_, "eax", where_is_the_var(it->a));
	}
	
	insert_into_x86_table(_cmp_, (flag ? "eax" : where_is_the_var(it->a)), where_is_the_var(it->b));
	insert_into_x86_table(_setle_, "al");
	insert_into_x86_table(_and_, "eax", "000000ffh");
	change_reg_table_unit(EAX, it->c);
}

void translate_lt() {
	std::string true_label = gen_temp_label("x86_true_lt");
	std::string end_label = gen_temp_label("x86_end_lt");
	regs varc = where_is_the_var_2(it->c);
	if (varc < 4) {
		change_reg_table_unit(varc, NONE);
	}
	write_the_reg_back(EAX);
	change_reg_table_unit(EAX, NONE);
	regs vara = where_is_the_var_2(it->a), varb = where_is_the_var_2(it->b);
	bool flag = false;
	if (vara == MEM && varb == MEM) {
		flag = true;
		
		insert_into_x86_table(_mov_, "eax", where_is_the_var(it->a));
	}
	
	insert_into_x86_table(_cmp_, (flag ? "eax" : where_is_the_var(it->a)), where_is_the_var(it->b));
	insert_into_x86_table(_setl_, "al");
	insert_into_x86_table(_and_, "eax", "000000ffh");
	change_reg_table_unit(EAX, it->c);
}

void translate_gt() {
	std::string true_label = gen_temp_label("x86_true_gt");
	std::string end_label = gen_temp_label("x86_end_gt");
	regs varc = where_is_the_var_2(it->c);
	if (varc < 4) {
		change_reg_table_unit(varc, NONE);
	}
	write_the_reg_back(EAX);
	change_reg_table_unit(EAX, NONE);
	regs vara = where_is_the_var_2(it->a), varb = where_is_the_var_2(it->b);
	bool flag = false;
	if (vara == MEM && varb == MEM) {
		flag = true;
		
		insert_into_x86_table(_mov_, "eax", where_is_the_var(it->a));
	}
	
	insert_into_x86_table(_cmp_, (flag ? "eax" : where_is_the_var(it->a)), where_is_the_var(it->b));
	insert_into_x86_table(_setg_, "al");
	insert_into_x86_table(_and_, "eax", "000000ffh");
	change_reg_table_unit(EAX, it->c);
}

void translate_ge() {
	std::string true_label = gen_temp_label("x86_true_ge");
	std::string end_label = gen_temp_label("x86_end_ge");
	regs varc = where_is_the_var_2(it->c);
	if (varc < 4) {
		change_reg_table_unit(varc, NONE);
	}
	write_the_reg_back(EAX);
	change_reg_table_unit(EAX, NONE);
	regs vara = where_is_the_var_2(it->a), varb = where_is_the_var_2(it->b);
	bool flag = false;
	if (vara == MEM && varb == MEM) {
		flag = true;
		
		insert_into_x86_table(_mov_, "eax", where_is_the_var(it->a));
	}
	
	insert_into_x86_table(_cmp_, (flag ? "eax" : where_is_the_var(it->a)), where_is_the_var(it->b));
	insert_into_x86_table(_setge_, "al");
	insert_into_x86_table(_and_, "eax", "000000ffh");
	change_reg_table_unit(EAX, it->c);
}

void translate_not() {
	std::string equal_label = gen_temp_label("x86_not_equal");
	std::string end_label = gen_temp_label("x86_not_end");
	regs varc = where_is_the_var_2(it->b);
	if (varc < 4) {
		change_reg_table_unit(varc, NONE);
	}
	write_the_reg_back(EAX);
	change_reg_table_unit(EAX, NONE);
	
	insert_into_x86_table(_cmp_, where_is_the_var(it->a), "0");
	insert_into_x86_table(_sete_, "al");
	insert_into_x86_table(_and_, "eax", "000000ffh");
	change_reg_table_unit(EAX, it->b);
}



void translate_scan() {
	if (it->a == "int") {
		
		insert_into_x86_table(_call_, "$scan_int");
		insert_into_x86_table(_mov_, tell_me_the_address(it->b), "eax");
	} else if (it->a == "char") {
		
		insert_into_x86_table(_call_, "$scan_char");
		insert_into_x86_table(_mov_, tell_me_the_address(it->b), "eax");
	} else if (it->a == "string") {
		
		insert_into_x86_table(_lea_, "eax", tell_me_the_address(it->b));
		insert_into_x86_table(_push_, "eax");
		insert_into_x86_table(_call_, "$scan_string");
		insert_into_x86_table(_pop_, "eax");
	}
}

void translate_rdarr() {
	
	insert_into_x86_table(_push_, "esi");
	insert_into_x86_table(_push_, "edi");
	insert_into_x86_table(_lea_, "esi", lea_where_is_the_var(it->a));
	insert_into_x86_table(_mov_, "edi", where_is_the_var(it->b));
	insert_into_x86_table(_shl_, "edi", "2");
	regs varc = where_is_the_var_2(it->c);
	if (varc < 4) {
		
		insert_into_x86_table(_mov_, regs_convert_table[varc], "[esi+edi]");
	} else {
		
		insert_into_x86_table(_mov_, give_me_a_reg(it->c), "[esi+edi]");
	}
	
	insert_into_x86_table(_pop_, "edi");
	insert_into_x86_table(_pop_, "esi");
}

void translate_wrarr() {
	
	insert_into_x86_table(_push_, "esi");
	insert_into_x86_table(_push_, "edi");
	insert_into_x86_table(_lea_, "esi", lea_where_is_the_var(it->a));
	insert_into_x86_table(_mov_, "edi", where_is_the_var(it->b));
	insert_into_x86_table(_shl_, "edi", "2");
	regs varc = where_is_the_var_2(it->c);
	if (varc < 4) {
		insert_into_x86_table(_mov_, "[esi+edi]", regs_convert_table[varc]);
	} else if (varc == IMM) {
		
		insert_into_x86_table(_mov_, "dword [esi+edi]", it->c);
	} else {
		std::string addressofc = give_me_a_reg(it->c);
		
		insert_into_x86_table(_mov_, addressofc, tell_me_the_address(it->c));
		insert_into_x86_table(_mov_, "[esi+edi]", give_me_a_reg(it->c));
	}
	
	insert_into_x86_table(_pop_, "edi");
	insert_into_x86_table(_pop_, "esi");
}

void translate_shl() {
	regs varb = where_is_the_var_2(it->b);
	if (varb != ECX) {
		write_the_reg_back(ECX);
		change_reg_table_unit(ECX, NONE);
		
		insert_into_x86_table(_mov_, "ecx", where_is_the_var(it->b));
	}
	regs varc, reg;
	varc = where_is_the_var_2(it->c);
	if (varc < 4) {
		reg = varc;
		
		insert_into_x86_table(_mov_, regs_convert_table[reg], where_is_the_var(it->a));
	} else {
		reg = allocate_a_reg();
		
		insert_into_x86_table(_mov_, regs_convert_table[reg], where_is_the_var(it->a));
	}
	
	insert_into_x86_table(_shl_, regs_convert_table[reg], "cl");
	change_reg_table_unit(reg, it->c);
}

void translate_shr() {
	regs varb = where_is_the_var_2(it->b);
	if (varb != ECX) {
		write_the_reg_back(ECX);
		change_reg_table_unit(ECX, NONE);
		
		insert_into_x86_table(_mov_, "ecx", where_is_the_var(it->b));
	}
	regs varc, reg;
	varc = where_is_the_var_2(it->c);
	if (varc < 4) {
		reg = varc;
		
		insert_into_x86_table(_mov_, regs_convert_table[reg], where_is_the_var(it->a));
	} else {
		reg = allocate_a_reg();
		
		insert_into_x86_table(_mov_, regs_convert_table[reg], where_is_the_var(it->a));
	}
	
	insert_into_x86_table(_shr_, regs_convert_table[reg], "cl");
	change_reg_table_unit(reg, it->c);
}

void translate_cmp() {
	
	insert_into_x86_table(_cmp_, where_is_the_var(it->a), where_is_the_var(it->b));
}

void translate_bitnot() {
	
	insert_into_x86_table(_not_, where_is_the_var(it->a));
}

void translate_bitand() {
	regs varc, reg;
	varc = where_is_the_var_2(it->c);
	if (varc < 4) {
		reg = varc;
		
		insert_into_x86_table(_mov_, regs_convert_table[reg], where_is_the_var(it->a));
	} else {
		reg = allocate_a_reg();
		
		insert_into_x86_table(_mov_, regs_convert_table[reg], where_is_the_var(it->a));
	}
	
	insert_into_x86_table(_and_, regs_convert_table[reg], where_is_the_var(it->b));
	change_reg_table_unit(reg, it->c);
}

void translate_bitor() {
	regs varc, reg;
	varc = where_is_the_var_2(it->c);
	if (varc < 4) {
		reg = varc;
		
		insert_into_x86_table(_mov_, regs_convert_table[reg], where_is_the_var(it->a));
	} else {
		reg = allocate_a_reg();
		
		insert_into_x86_table(_mov_, regs_convert_table[reg], where_is_the_var(it->a));
	}
	
	insert_into_x86_table(_or_, regs_convert_table[reg], where_is_the_var(it->b));
	change_reg_table_unit(reg, it->c);
}

void translate_bitxor() {
	regs varc, reg;
	varc = where_is_the_var_2(it->c);
	if (varc < 4) {
		reg = varc;
		
		insert_into_x86_table(_mov_, regs_convert_table[reg], where_is_the_var(it->a));
	} else {
		reg = allocate_a_reg();
		
		insert_into_x86_table(_mov_, regs_convert_table[reg], where_is_the_var(it->a));
	}
	
	insert_into_x86_table(_xor_, regs_convert_table[reg], where_is_the_var(it->b));
	change_reg_table_unit(reg, it->c);
}

void translate_inc() {
	
	insert_into_x86_table(_inc_, where_is_the_var(it->a));
}

void translate_dec() {
	
	insert_into_x86_table(_dec_, where_is_the_var(it->a));
}

void translate_ret() {
	if (it->a.empty()) {
		
		insert_into_x86_table(_pop_, "ebx");
		insert_into_x86_table(_leave_);
		insert_into_x86_table(_ret_);
	} else {
		
		insert_into_x86_table(_mov_, "eax", where_is_the_var(it->a));
	}
}

void translate_print() {
	if (it->a == "int") {
		
		insert_into_x86_table(_mov_, "eax", where_is_the_var(it->b));
		insert_into_x86_table(_push_, "eax");
		insert_into_x86_table(_call_, "$print_int");
	} else if (it->a == "char") {
		
		insert_into_x86_table(_mov_, "eax", (it->b[0] == '\'' ? it->b : where_is_the_var(it->b)));
		insert_into_x86_table(_push_, "eax");
		insert_into_x86_table(_call_, "$print_char");
	} else if (it->a == "string") {
		std::string itbadd;
		bool has_bracket = true;
		if (it->b[0] == '?') itbadd = it->b, has_bracket = false;
		else itbadd = tell_me_the_address(it->b);
		if (has_bracket) insert_into_x86_table(_lea_, "eax", itbadd);
		else insert_into_x86_table(_mov_, "eax", itbadd);
		
		insert_into_x86_table(_push_, "eax");
		insert_into_x86_table(_call_, "$print_str");
	} else if (it->a == "const") {
		insert_into_x86_table(_push_, "dword " + it->b);
		insert_into_x86_table(_call_, "$print_int");
	}
	insert_into_x86_table(_pop_, "eax");
}

void translate_sub() {
	regs varc, reg;
	varc = where_is_the_var_2(it->c);
	if (varc < 4) {
		reg = varc;
		
		insert_into_x86_table(_mov_, regs_convert_table[reg], where_is_the_var(it->a));
	} else {
		reg = allocate_a_reg();
		
		insert_into_x86_table(_mov_, regs_convert_table[reg], where_is_the_var(it->a));
	}
	
	insert_into_x86_table(_sub_, regs_convert_table[reg], where_is_the_var(it->b));
	change_reg_table_unit(reg, it->c);
}

void translate_mul() {
	regs varc, reg;
	varc = where_is_the_var_2(it->c);
	if (varc < 4) {
		reg = varc;
		
		insert_into_x86_table(_mov_, regs_convert_table[reg], where_is_the_var(it->a));
	} else {
		reg = allocate_a_reg();
		
		insert_into_x86_table(_mov_, regs_convert_table[reg], where_is_the_var(it->a));
	}
	
	insert_into_x86_table(_imul_, regs_convert_table[reg], where_is_the_var(it->b));
	change_reg_table_unit(reg, it->c);
}

void translate_div_mod() {
	regs varc = where_is_the_var_2(it->c), varb = where_is_the_var_2(it->b);
	if (varb == IMM) {
		write_the_reg_back(ECX);
		change_reg_table_unit(ECX, NONE);
		
		insert_into_x86_table(_mov_, "ecx", it->b);
	}
	if (varc < 4) {
		write_the_reg_back(varc);
		change_reg_table_unit(varc, NONE);
	}
	write_the_reg_back(EAX);
	write_the_reg_back(EDX);
	
	insert_into_x86_table(_mov_, "eax", where_is_the_var(it->a));
	if (it->instruct == DIV) {
		change_reg_table_unit(EAX, it->c);
		change_reg_table_unit(EDX, NONE);
	} else {
		change_reg_table_unit(EAX, NONE);
		change_reg_table_unit(EDX, it->c);
	}
	
	insert_into_x86_table(_cdq_);

	if (varb == IMM) insert_into_x86_table(_idiv_, "ecx");
	else insert_into_x86_table(_idiv_,
	                                                                                        where_is_the_var(it->b));
}

void translate_add() {
	regs varc, reg;
	varc = where_is_the_var_2(it->c);
	if (varc < 4) {
		reg = varc;
		
		insert_into_x86_table(_mov_, regs_convert_table[reg], where_is_the_var(it->a));
	} else {
		reg = allocate_a_reg();
		
		insert_into_x86_table(_mov_, regs_convert_table[reg], where_is_the_var(it->a));
	}
	
	insert_into_x86_table(_add_, regs_convert_table[reg], where_is_the_var(it->b));
	change_reg_table_unit(reg, it->c);
}

void translate_assign() {
	regs var1, var2;
	if (is_num(it->a)) {
		
		insert_into_x86_table(_mov_, where_to_write_the_var(it->b), "dword " + it->a);
	} else {
		var1 = where_is_the_var_2(it->a);
		var2 = where_is_the_var_2(it->b);
		if (var1 == MEM && var2 == MEM)
			
			insert_into_x86_table(_mov_, give_me_a_reg(it->a), tell_me_the_address(it->a));
		
		insert_into_x86_table(_mov_, where_to_write_the_var(it->b), where_is_the_var(it->a));
	}
}

void translate_je() {
	
	insert_into_x86_table(_je_, it->a);
}

void translate_jmp() {
	
	insert_into_x86_table(_jmp_, it->a);
}

void translate_ja() {
	
	insert_into_x86_table(_jg_, it->a);
}

void translate_jb() {
	
	insert_into_x86_table(_jl_, it->a);
}

void translate_getret() {
	
	insert_into_x86_table(_mov_, where_to_write_the_var(it->a), "eax");
}

void translate_param(int *curr_param_num) {
	(*curr_param_num)++;
	table_entry entry{IDN_VAR, it->a == "int" ? DATA_INT : DATA_CHAR, 0, (*curr_param_num) * INT_SIZE, l};
	insert_to_symbol_table(LOCAL, it->b, entry);
}

void translate_var_def(int *curr_var_num) {
	if (it->c.empty())(*curr_var_num)++;
	else (*curr_var_num) += std::stoi(it->c);
	table_entry entry{it->c.empty() ? IDN_VAR : IDN_ARRAY, it->a == "int" ? DATA_INT : DATA_CHAR, 0,
	                  -(*curr_var_num) * INT_SIZE, l};
	insert_to_symbol_table(LOCAL, it->b, entry);
}

void gen_func_head() {
	
	insert_into_x86_table(_label_, it->b);
	it++;
	inc_ident();
	
	insert_into_x86_table(_push_, "ebp");
	insert_into_x86_table(_mov_, "ebp", "esp");
	insert_into_x86_table(_push_, "ebx");
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
	
	insert_into_x86_table(_sub_, "esp", std::to_string(num_of_var * INT_SIZE));
}

void gen_func_tail() {
	
	insert_into_x86_table(_pop_, "ebx");
	insert_into_x86_table(_leave_);
	insert_into_x86_table(_ret_);
	it++;
	dec_ident();
}
