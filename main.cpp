#include "headers/global.h"
#include "headers/readfile.h"

using std::cout;
using std::cin;

int main() {
	std::string s;
	std::string file = "../testfiles/in.txt";
	s = readfile(file);
	cout << s << std::endl;
	return 0;
}
