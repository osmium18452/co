#include "../headers/global.h"
#include "../headers/lex.h"

using std::cout;
using std::cin;
using std::endl;

std::unordered_set<char> blank_set({' ', '\t', '\v', '\f', '\n', '\r',});

std::unordered_set<char> symbol_set({
	',',';',
	'(',')','[',']','{','}','<','>',
	'+','-','*','/','%',
	'~','!',
	'=','&','^','|','\\',
	'?',':',
});

std::unordered_map<char, char> convert_table({
	{'a', '\a'},
	{'b', '\b'},
	{'t', '\t'},
	{'v', '\v'},
	{'f', '\f'},
	{'n', '\n'},
	{'r', '\r'},
	});

std::unordered_map<std::string, token_type> string_to_token({
	{"const",    TOK_CONST},
	{"signed",   TOK_SIGNED},   {"unsigned", TOK_UNSIGNED},
	{"void",     TOK_VOID},
	{"char",     TOK_CHAR},
	{"int",      TOK_INT},      {"short",    TOK_SHORT},    {"long",     TOK_LONG},
	{"float",    TOK_FLOAT},    {"double",   TOK_DOUBLE},
	{"if",       TOK_IF},       {"else",     TOK_ELSE},
	{"for",      TOK_FOR},      {"while",    TOK_WHILE},    {"do",       TOK_DO},
	{"return",   TOK_RETURN},
	{",",        TOK_COMMA},
	{";",        TOK_SEMICOLON},
	{"(",        TOK_LPARE},    {")",        TOK_RPARE},
	{"[",        TOK_LBRACKET}, {"]",        TOK_RBRACKET},
	{"{",        TOK_LBRACE},   {"}",        TOK_RBRACE},
	{"++",       TOK_INC},      {"--",       TOK_DEC},
	{"~",        TOK_BITNOT},   {"!",        TOK_LOGINOT},
	{"*",        TOK_MUL},      {"/",        TOK_DIV},      {"%",        TOK_MOD},
	{"+",        TOK_PLUS},     {"-",        TOK_SUB},
	{"<<",       TOK_SHL},      {">>",       TOK_SHR},
	{"<",        TOK_LT},       {">",        TOK_GT},
	{"<=",       TOK_LE},       {">=",       TOK_GE},
	{"==",       TOK_EQ},       {"!=",       TOK_NE},
	{"&",        TOK_BITAND},   {"^",        TOK_BITXOR},   {"|",        TOK_BITOR},
	{"&&",       TOK_LOGIAND},  {"||",       TOK_LOGIOR},
	{"?",        TOK_QM},       {":",        TOK_COLON},
	{"=",        TOK_ASSIGN},
                                                            });

int get_token(std::string s, std::vector<token> &tokens, bool use_blank) {
	int left = 0, right = 0;
	state_type state = STAT_START;
	int len = s.length();
	int token_num = 0;
	while (right < len) {
		switch (state) {
			case STAT_START:
				if (isdigit(s[right])) {                                              //number const
					left = right;
					right++;
					state = STAT_INT;
				} else if (s[right] == '_' || isalpha(s[right])) {                   //identifier or reserved word
					left = right;
					right++;
					state = STAT_IDENT;
				} else if (s[right] == '\'') {                                     //char const
					left = right;
					right++;
					state = STAT_CHAR1;
				} else if (s[right] == '\"') {                                     //string const
					left = right;
					right++;
					state = STAT_STR1;
				} else if (blank_set.find(s[right]) != blank_set.end()) {  //blank
					left = right;
					right++;
					state = STAT_BLANK;
				} else if (symbol_set.find(s[right]) != symbol_set.end()) {           //symbols
					left = right;
					right++;
					state = STAT_SMBL;
				} else if (s[right] == '$') {
					right++;
					state = STAT_START;
				} else {
					/* simple error handler */
					cout << "unrecognizable character:" << s[right] << "**" << std::endl;
					return 0;
				}
				break;
			case STAT_BLANK:
				if (blank_set.find(s[right]) != blank_set.end()) {
					right++;
					state = STAT_BLANK;
				} else {
					token tmp;
					tmp.type = TOK_BLANK;
					if (use_blank) {
						tokens.push_back(tmp);
						token_num++;
					}
					state = STAT_START;
				}
				break;
/*---------------------------------keywords and identifiers---------------------------------*/
			case STAT_IDENT:
				if (s[right] == '_' || isalnum(s[right])) {
					right++;
					state = STAT_IDENT;
				} else {
					token tmp;
					tmp.stringval = s.substr(left, right - left);
					if (string_to_token.find(tmp.stringval) == string_to_token.end()) {
						tmp.type = TOK_IDENT;
					} else {
						tmp.type = string_to_token[tmp.stringval];
					}
					tokens.push_back(tmp);
					token_num++;
					state = STAT_START;
				}
				break;
/*----------------------------------------numbers-----------------------------------------*/
			case STAT_INT:
				if (isdigit(s[right])){
					right++;
					state=STAT_INT;
				} else if (s[right]=='.'){
					right++;
					state=STAT_FLT;
				} else if (s[right]=='u'){
					right++;
					state=STAT_UINT;
				} else if (s[right]=='l'){
					right++;
					state=STAT_LONG;
				} else if (s[right]=='s'){
					right++;
					state=STAT_SHORT;
				} else {
					token tmp;
					tmp.type=TOK_INTCONST;
					tmp.intval=atoi(s.substr(left,right-left).c_str());
					tokens.push_back(tmp);
					token_num++;
					state=STAT_START;
				}
				break;
			case STAT_UINT:
				if (s[right]=='l'){
					right++;
					state=STAT_ULONG;
				} else if(s[right]=='s'){
					right++;
					state=STAT_USHORT;
				} else {
					token tmp;
					tmp.type=TOK_UINTCONST;
					tmp.uintval=(unsigned int) atoll(s.substr(left,right-left-1).c_str());
					tokens.push_back(tmp);
					token_num++;
					state=STAT_START;
				}
				break;
			case STAT_ULONG:
				if (true){
					token tmp;
					tmp.type=TOK_ULONGCONST;
					tmp.ullval=strtoull(s.substr(left,right-left-2).c_str(),NULL,10);
					tokens.push_back(tmp);
					token_num++;
					state=STAT_START;
				}
				break;
			case STAT_LONG:
				if (true){
					token tmp;
					tmp.type=TOK_LONGCONST;
					tmp.llval=strtoll(s.substr(left,right-left-1).c_str(),NULL,10);
					tokens.push_back(tmp);
					token_num++;
					state=STAT_START;
				}
				break;
			case STAT_SHORT:
				if (true){
					token tmp;
					tmp.type=TOK_SHORTCONST;
					tmp.shortval=(short) strtoll(s.substr(left,right-left-1).c_str(),NULL,10);
					tokens.push_back(tmp);
					token_num++;
					state=STAT_START;
				}
				break;
			case STAT_USHORT:
				if (true){
					token tmp;
					tmp.type=TOK_USHORTCONST;
					tmp.ushortval=(unsigned short) strtoll(s.substr(left,right-left-2).c_str(),NULL,10);
					tokens.push_back(tmp);
					token_num++;
					state=STAT_START;
				}
				break;
			case STAT_DBL:
				break;
			case STAT_FLT:
				break;
			case STAT_CHAR1:
				break;
			case STAT_CHAR2:
				break;
			case STAT_CHAR3:
				break;
			case STAT_CHAR4:
				break;
			case STAT_CHAR5:
				break;
			case STAT_STR1:
				break;
			case STAT_STR2:
				break;
			case STAT_STR3:
				break;
			case STAT_STR4:
				break;
			case STAT_STR5:
				break;
			case STAT_SMBL:
				break;
			case STAT_PLUS:
				break;
			case STAT_INCR:
				break;
			case STAT_SUB:
				break;
			case STAT_DECR:
				break;
			case STAT_BAND:
				break;
			case STAT_AND:
				break;
			case STAT_BOR:
				break;
			case STAT_OR:
				break;
			case STAT_NOT:
				break;
			case STAT_NE:
				break;
			case STAT_ASGN:
				break;
			case STAT_EQ:
				break;
			case STAT_GT:
				break;
			case STAT_SR:
				break;
			case STAT_GE:
				break;
			case STAT_LT:
				break;
			case STAT_SL:
				break;
			case STAT_LE:
				break;
		}
	}
	return token_num;
}