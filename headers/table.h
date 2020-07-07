#ifndef CO_TABLE_H
#define CO_TABLE_H

#include "global.h"

/* identifier type */
enum _itype {
	IDN_CONST, IDN_VAR, IDN_ARRAY, IDN_FUNCTION,
};

/* data type */
enum _dtype {
	DATA_INT,
	DATA_CHAR, DATA_VOID,
};

enum scope {
	GLOBAL, LOCAL,
};

/*
 * _itype stand for the type of the identifier
 * _dtype stand for the data type of the identifier
 * value stand for the size of the array or the value of constant
 * address is used to assign an memory address for each variable,only used in the quadruple to x86 process
 */
enum _table_level{
	g,l,
};

struct table_entry {
	_itype itype;
	_dtype dtype;
	int value;
	int address;
	_table_level table_level;
};


extern std::vector<std::unordered_map<std::string, table_entry>> symbol_table;
extern std::string itype_convert_table[];
extern std::string dtype_convert_table[];
extern int local_symbol_table_level;
extern std::unordered_map<std::string,std::string> string_table;

bool insert_to_string_table(const std::string &s, std::string &slabel);

bool query_string_table(const std::string &s, std::string &label);

void init_string_table();

void print_string_table(const std::string &file);

void init_symbol_table();

void create_new_local_table();

void create_new_local_table_2();

void destroy_current_local_table();

void destroy_current_local_table_2();

bool insert_to_symbol_table(scope gol, std::string &ident, table_entry &entry);

bool query_symbol_table(const std::string &ident,table_entry &entry);

void print_symbol_table(std::string &file,int which_table,bool append);

int allocate_a_param_table();

void init_param_table();

void insert_to_para_table(const int para_table_num,const _dtype dtype);

std::vector<_dtype> get_para_table(const int para_table_num);

void print_para_table(std::string &file, int which_table, bool append);

void init_local_symbol_table();


#endif //CO_TABLE_H
