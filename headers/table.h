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

void insert(scope gol, std::string &ident, table_entry entry);

table_entry query(scope gol, std::string &ident);

#endif //CO_TABLE_H
