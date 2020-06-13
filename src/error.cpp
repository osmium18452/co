#include "../headers/global.h"
#include "../headers/error.h"

int warnings, errors;

void print_error(const std::string &message) {
	cout << "error (" << curr_line_num << "):" << message << endl;
	errors++;
}

void print_warning(const std::string &message) {
	cout << "waring (" << curr_line_num << "):" << message << endl;
	warnings++;
}

void init_error_warning_handler() {
	warnings = 0;
	errors = 0;
	has_main_func=false;
}

void error_warning_handler_summary(){
	cout << "compilation complete. " << warnings << " warning(s), " << errors << " error(s)." << endl;
}