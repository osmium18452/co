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
	'=','&','^','|',
	'\\','\'','\"',
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
	{"+=",       TOK_ADDASS},   {"-=",       TOK_SUBASS},
	{"*=",       TOK_MULASS},   {"/=",       TOK_DIVASS},   {"%=",       TOK_MODASS},
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
/*----------------------------------------numbers------------------------------------------*/
			case STAT_INT:
				if (isdigit(s[right])) {
					right++;
					state = STAT_INT;
				} else if (s[right] == '.') {
					right++;
					state = STAT_DBL;
				} else if (s[right] == 'u') {
					right++;
					state = STAT_UINT;
				} else if (s[right] == 'l') {
					right++;
					state = STAT_LONG;
				} else if (s[right] == 's') {
					right++;
					state = STAT_SHORT;
				} else if (s[right] == 'f') {
					right++;
					token tmp;
					tmp.type = TOK_FLOATCONST;
					tmp.floatval = (float) atof(s.substr(left, right - left-1).c_str());
					tokens.push_back(tmp);
					token_num++;
					state = STAT_START;
				}else if (s[right] == 'd') {
					right++;
					token tmp;
					tmp.type = TOK_DOUBLECONST;
					tmp.doubleval = atof(s.substr(left, right - left-1).c_str());
					tokens.push_back(tmp);
					token_num++;
					state = STAT_START;
				} else {
					token tmp;
					tmp.type = TOK_INTCONST;
					tmp.intval = atoi(s.substr(left, right - left).c_str());
					tokens.push_back(tmp);
					token_num++;
					state = STAT_START;
				}
				break;
			case STAT_UINT:
				if (s[right] == 'l') {
					right++;
					state = STAT_ULONG;
				} else if (s[right] == 's') {
					right++;
					state = STAT_USHORT;
				} else {
					token tmp;
					tmp.type = TOK_UINTCONST;
					tmp.uintval = (unsigned int) atoll(s.substr(left, right - left - 1).c_str());
					tokens.push_back(tmp);
					token_num++;
					state = STAT_START;
				}
				break;
			case STAT_ULONG:
				if (true) {
					token tmp;
					tmp.type = TOK_ULONGCONST;
					tmp.ullval = strtoull(s.substr(left, right - left - 2).c_str(), NULL, 10);
					tokens.push_back(tmp);
					token_num++;
					state = STAT_START;
				}
				break;
			case STAT_LONG:
				if (true) {
					token tmp;
					tmp.type = TOK_LONGCONST;
					tmp.llval = strtoll(s.substr(left, right - left - 1).c_str(), NULL, 10);
					tokens.push_back(tmp);
					token_num++;
					state = STAT_START;
				}
				break;
			case STAT_SHORT:
				if (true) {
					token tmp;
					tmp.type = TOK_SHORTCONST;
					tmp.shortval = (short) strtoll(s.substr(left, right - left - 1).c_str(), NULL, 10);
					tokens.push_back(tmp);
					token_num++;
					state = STAT_START;
				}
				break;
			case STAT_USHORT:
				if (true) {
					token tmp;
					tmp.type = TOK_USHORTCONST;
					tmp.ushortval = (unsigned short) strtoll(s.substr(left, right - left - 2).c_str(), NULL, 10);
					tokens.push_back(tmp);
					token_num++;
					state = STAT_START;
				}
				break;
			case STAT_DBL:
				if (isdigit(s[right])) {
					right++;
					state = STAT_DBL;
				} else if (s[right] == 'f') {
					right++;
					state = STAT_FLT;
				} else {
					token tmp;
					tmp.type = TOK_DOUBLECONST;
					tmp.doubleval = atof(s.substr(left, right - left).c_str());
					tokens.push_back(tmp);
					token_num++;
					state = STAT_START;
				}
				break;
			case STAT_FLT:
				if (true) {
					token tmp;
					tmp.type = TOK_FLOATCONST;
					tmp.floatval = (float) atof(s.substr(left, right - left-1).c_str());
					tokens.push_back(tmp);
					token_num++;
					state = STAT_START;
				}
				break;
/*----------------------------------------character------------------------------------------*/
			case STAT_CHAR1:
				if (s[right] == '\\') {
					right++;
					state = STAT_CHAR4;
				} else {
					right++;
					state = STAT_CHAR2;
				}
				break;
			case STAT_CHAR2:
				if (true) {
					token tmp;
					tmp.type = TOK_CHARCONST;
					tmp.charval = s[right];
					tokens.push_back(tmp);
					token_num++;
					right++;
					state = STAT_CHAR3;
				}
				break;
			case STAT_CHAR3:
				state = STAT_START;
				break;
			case STAT_CHAR4:
				right++;
				state = STAT_CHAR5;
				break;
			case STAT_CHAR5:
				if (convert_table.find(s[right - 1]) == convert_table.end()) {
					token tmp;
					tmp.type = TOK_CHARCONST;
					tmp.charval = s[right - 1];
					tokens.push_back(tmp);
					token_num++;
				} else {
					token tmp;
					tmp.type = TOK_CHARCONST;
					tmp.charval = convert_table[s[right - 1]];
					tokens.push_back(tmp);
					token_num++;
				}
				right++;
				state = STAT_CHAR3;
				break;
/*----------------------------------------string------------------------------------------*/
			case STAT_STR1:
				if (s[right] == '\\') {
					right++;
					state = STAT_STR4;
				} else if (s[right] == '\"') {
					right++;
					state = STAT_STR3;
				} else {
					right++;
					state = STAT_STR2;
				}
				break;
			case STAT_STR2:
				if (s[right] == '\\') {
					right++;
					state = STAT_STR4;
				} else if (s[right] == '\"') {
					right++;
					state = STAT_STR3;
				} else {
					right++;
					state = STAT_STR2;
				}
				break;
			case STAT_STR3:
				if (true) {
					token tmp;
					tmp.type = TOK_STRINGCONST;
					std::string tmps;
					for (int i=left+1;i<right-1;i++){
						if (s[i]!='\\') tmps+=s[i];
						else {
							i++;
							if (convert_table.find(s[i])==convert_table.end()) tmps+=s[i];
							else tmps+=convert_table[s[i]];
						}
					}
					tmp.stringval=tmps;
					tokens.push_back(tmp);
					token_num++;
					state=STAT_START;
				}
				break;
			case STAT_STR4:
				if (true) {
					right++;
					state = STAT_STR2;
				}
				break;
/*----------------------------------------character------------------------------------------*/
			case STAT_SMBL:
				switch (s[right]) {
					case '+':
						right++;
						state=STAT_PLUS;
						break;
					case '-':
						right++;
						state=STAT_SUB;
						break;
					case '~':
						right++;
						state=STAT_BITNOT;
						break;
					case '!':
						right++;
						state=STAT_LOGINOT;
						break;
					case '*':
						right++;
						state=STAT_MUL;
						break;
					case '/':
						right++;
						state=STAT_DIV;
						break;
					case '%':
						right++;
						state=STAT_MOD;
						break;
					case '<':
						right++;
						state=STAT_LT;
						break;
					case '>':
						right++;
						state=STAT_GT;
						break;
					case '(':
						right++;
						state=STAT_LPARE;
						break;
					case ')':
						right++;
						state=STAT_RPARE;
						break;
					case '{':
						right++;
						state=STAT_LBRACE;
						break;
					case '}':
						right++;
						state=STAT_RBRACE;
						break;
					case '[':
						right++;
						state=STAT_LBRACKET;
						break;
					case ']':
						right++;
						state=STAT_RBRACKET;
						break;
					case '=':
						right++;
						state=STAT_ASGN;
						break;
					case '&':
						right++;
						state=STAT_BITAND;
						break;
					case '^':
						right++;
						state=STAT_XOR;
						break;
					case '|':
						right++;
						state=STAT_BITOR;
						break;
					case '?':
						right++;
						state=STAT_QM;
						break;
					case ':':
						right++;
						state=STAT_COLON;
						break;
					case ',':
						right++;
						state=STAT_COMMA;
						break;
					case ';':
						right++;
						state=STAT_SEMICOLON;
						break;
				}
				break;
			case STAT_PLUS:
				if (s[right]=='+'){
					right++;
					state=STAT_INCR;
				} else if (s[right]=='='){
					right++;
					state=STAT_ADDASS;
				} else {
					token tmp;
					tmp.type=TOK_PLUS;
					tokens.push_back(tmp);
					token_num++;
					state=STAT_START;
				}
				break;
			case STAT_INCR:
				if (true){
					token tmp;
					tmp.type=TOK_INC;
					tokens.push_back(tmp);
					token_num++;
					state=STAT_START;
				}
				break;
			case STAT_ADDASS:
				if (true){
					token tmp;
					tmp.type=TOK_ADDASS;
					tokens.push_back(tmp);
					token_num++;
					state=STAT_START;
				}
				break;
			case STAT_SUB:
				if (s[right]=='-'){
					right++;
					state=STAT_DECR;
				} else if (s[right]=='='){
					right++;
					state=STAT_SUBASS;
				} else {
					token tmp;
					tmp.type=TOK_SUB;
					tokens.push_back(tmp);
					token_num++;
					state=STAT_START;
				}
				break;
			case STAT_DECR:
				if (true){
					token tmp;
					tmp.type=TOK_DEC;
					tokens.push_back(tmp);
					token_num++;
					state=STAT_START;
				}
				break;
			case STAT_SUBASS:
				if (true){
					token tmp;
					tmp.type=TOK_SUBASS;
					tokens.push_back(tmp);
					token_num++;
					state=STAT_START;
				}
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
			case STAT_STR5:
				break;
			case STAT_MUL:
				if (s[right]=='='){
					right++;
					state=STAT_MULASS;
				} else {
					token tmp;
					tmp.type=TOK_MUL;
					tokens.push_back(tmp);
					token_num++;
					state=STAT_START;
				}
				break;
			case STAT_DIV:
				if (s[right]=='='){
					right++;
					state=STAT_DIVASS;
				} else {
					token tmp;
					tmp.type=TOK_DIV;
					tokens.push_back(tmp);
					token_num++;
					state=STAT_START;
				}
				break;
			case STAT_MOD:
				if (s[right]=='='){
					right++;
					state=STAT_MODASS;
				} else {
					token tmp;
					tmp.type=TOK_MOD;
					tokens.push_back(tmp);
					token_num++;
					state=STAT_START;
				}
				break;
			case STAT_MULASS:
				if (true){
					token tmp;
					tmp.type=TOK_MULASS;
					tokens.push_back(tmp);
					token_num++;
					state=STAT_START;
				}
				break;
			case STAT_DIVASS:
				if (true){
					token tmp;
					tmp.type=TOK_DIVASS;
					tokens.push_back(tmp);
					token_num++;
					state=STAT_START;
				}
				break;
			case STAT_MODASS:
				if (true){
					token tmp;
					tmp.type=TOK_MODASS;
					tokens.push_back(tmp);
					token_num++;
					state=STAT_START;
				}
				break;
			case STAT_COMMA:
				break;
			case STAT_SEMICOLON:
				break;
			case STAT_LPARE:
				break;
			case STAT_RPARE:
				break;
			case STAT_LBRACKET:
				break;
			case STAT_RBRACKET:
				break;
			case STAT_LBRACE:
				break;
			case STAT_RBRACE:
				break;
			case STAT_XOR:
				break;
			case STAT_QM:
				break;
			case STAT_COLON:
				break;
			case STAT_BITNOT:
				break;
			case STAT_LOGINOT:
				break;
			case STAT_BITAND:
				break;
			case STAT_BITOR:
				break;
		}
	}
	return token_num;
}