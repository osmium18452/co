#ifndef CO_TABLE_H
#define CO_TABLE_H

#include "global.h"

/* identifier type */
enum itype {
	IDN_CONST, IDN_VAR, IDN_ARRAY, IDN_FUNCTION,
};

/* data type */
enum dtype {
	DATA_SHORT, DATA_INT, DATA_LONG,
	DATA_FLOAT, DATA_DOUBLE,
	DATA_CHAR, DATA_VOID,
};

enum gol {
	GLOBAL, LOCAL,
};

struct table_entry {
	itype itype;
	dtype dtype;
	LL value;
	LL address;
};

extern std::unordered_map<std::string, table_entry> global_symbol_table;
extern std::unordered_map<std::string, table_entry> local_symbol_table;
extern std::string itype_convert_table[];
extern std::string dtype_convert_table[];

void insert(gol gol, std::string &ident, table_entry entry);

table_entry query(gol gol, std::string &ident);

#endif //CO_TABLE_H
