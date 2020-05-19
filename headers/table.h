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

extern std::unordered_map<std::string, table_entry> global_symbol_table;
extern std::unordered_map<std::string, table_entry> local_symbol_table;
extern std::string itype_convert_table[];
extern std::string dtype_convert_table[];

void insert_to_symbol_table(scope gol, std::string &ident, table_entry entry);

table_entry query(scope gol, std::string &ident);

#endif //CO_TABLE_H
