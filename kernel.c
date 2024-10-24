#include "console.h"
#include "tests.h"

/*	I use this flag to control whether to execute a function that will
 *		make my terminal position out of bounds.
 */
int test_print_overflow_flag = 0;

int main() {
	char* hello = "Hello World";
	char* test_str = "Called after print_line()";

	char* evil_string = "Hello World \\n\nAgain";

	clear_terminal();
	print_string(hello);
	print_character('\n');

	print_line(hello);
	print_string(test_str);

	print_character('\n');

	print_string(evil_string);

	if(test_print_overflow_flag) {
		test_print_overflow();
	}

	while(1);
}
