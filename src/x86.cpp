#include "../headers/x86.h"
#include "../headers/x86_func_def.h"
#include "../headers/quadruple.h"

std::vector<instruct_table_item> instruct_table;

void translate_to_x86() {

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

void insert_to_instruction_table(const instruct_table_item &item) {
	instruct_table.push_back(item);
}

