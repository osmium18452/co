#include "../headers/x86.h"
#include "../headers/x86_func_def.h"
#include "../headers/quadruple.h"
#include "../headers/table.h"
#include "../headers/utils.h"

std::vector<std::string> instruct_table;
int ident;

void inc_ident(){
	ident+=4;
}

void dec_ident(){
	ident-=4;
}

void insert_into_x86_table(const std::string &s){
	std::string instr;
	for (auto i=1;i<ident;i++){
		instr+=" ";
	}
	instruct_table.push_back(instr+s);
}

void translate_to_x86() {
	ident=0;
	insert_into_x86_table("%include io.asm");
	gen_data_section();
	/*for (const auto &i : quadruple_list) {
		switch (i.instruct) {
			case VAR:
			case PARAM:
			case FUNC:
			case ASSIGN:
			case ADD:
			case SUB:
			case MUL:
			case DIV:
			case MOD:
			case CMP:
			case JE:
			case JNE:
			case JMP:
			case JA:
			case JB:
			case SWJMP:
			case END:
			case PRINT:
			case SCAN:
			case COMMA:
			case LABEL:
			case LOGIAND:
			case LOGIOR:
			case TEMP:
			case BITAND:
			case BITOR:
			case BITXOR:
			case NE:
			case EQ:
			case SHL:
			case SHR:
			case LT:
			case LE:
			case GT:
			case GE:
			case INC:
			case DEC:
			case NOT:
			case REVERSE:
			case PUSH:
			case POP:
			case CALL:
			case RET:
			case GETRET:
			case RDARR:
			case WRARR:
			case KASE_ITEM:
			case CREATE_TABLE:
			case DESTROY_TABLE:
			default:
				break;
		}
	}*/
}

void gen_data_section(){
	insert_into_x86_table("section .data");
	inc_ident();
	gen_string_table();
	gen_global_table();
	dec_ident();
	gen_start_code();
}

void gen_string_table(){
	for (const auto &i:string_table){
		insert_into_x86_table(i.second+" db "+process_string(i.first)+",00h");
	}
}

void print_x86_table(const std::string &file){
	std::ostream x86_stream(NULL);
	std::filebuf buffer;
	buffer.open(file,std::ios::out);
	x86_stream.rdbuf(&buffer);
	for (const auto &i:instruct_table){
		x86_stream<<i<<endl;
	}
}

void gen_start_code(){
	insert_into_x86_table("global _start");
	insert_into_x86_table("_start:");
	inc_ident();
	insert_into_x86_table("jmp main");
	dec_ident();
}

void gen_global_table(){

}
