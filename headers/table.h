#ifndef CO_TABLE_H
#define CO_TABLE_H

#include "global.h"

/* identifier type */
enum itype {
	IDN_CONST, IDN_VAR, IDN_ARRAY, IDN_FUNCTION,
};

/* data type */
enum dtype {
	DATA_INT,
	DATA_CHAR, DATA_VOID,
};

enum scope {
	GLOBAL, LOCAL,
};

/*
 * itype stand for the type of the identifier
 * dtype stand for the data type of the identifier
 * value stand for the size of the array or the value of constant
 * address is used to assign an memory address for each variable,only used in the quadruple to x86 process
 */
struct table_entry {
	itype itype;
	dtype dtype;
	int value;
	int address;
};

extern std::vector<std::unordered_map<std::string, table_entry>> symbol_table;
extern std::string itype_convert_table[];
extern std::string dtype_convert_table[];
extern int local_symbol_table_level;

void init_symbol_table();

void create_new_local_table();

void destroy_current_local_table();

void insert_to_symbol_table(scope gol, std::string &ident, table_entry entry);

table_entry query_symbol_table(std::string &ident);

void print_symbol_table(std::string &file,int which_table,bool append);

#endif //CO_TABLE_H
