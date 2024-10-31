#include "console.h"

void test_print_overflow() {
	for(int i = 0; i < 30; i++) {
		print_character('\n');
	}
}

void test_preliminary_colors() {
	set_terminal_font_color(CYAN);
	
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
}
