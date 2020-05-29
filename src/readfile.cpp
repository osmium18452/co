#include "../headers/readfile.h"

std::string readfile(const std::string &file) {
	std::string ret;
	freopen(file.c_str(), "r", stdin);
	char c = (char) getchar();
	while (c != EOF) {
		if (c == '\n' || c == '\r') ret += c=='\n'?c:' ';
		else ret += c;
		c = (char) getchar();
	}
	ret+='$';
	return ret;
}
