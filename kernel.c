#include "console.h"
#include "tests.h"

/**
 * Flags for various internal tests
 */
const int flag_test_print_overflow = 0;
const int flag_test_preliminary_colors = 0;

void run_tests();

int main() {
	clear_terminal();

	char* str1= " HELLO ";
	char* str2 = " WORLD ";
	char* str3 = " TODAY ";
	
	print_line(str1);
	set_terminal_font_color(BLUE);
	print_line(str2);
	set_terminal_font_color(YELLOW);
	print_line(str3);
	print_character_with_color('A', GREEN);
	print_string_with_color(" BIG STRING", CYAN);
	print_line_with_color("A new line", BROWN);
	print_line_with_color(" is here", RED);

	print_line(str1);
	set_terminal_font_color(BLUE);
	print_line(str2);
	set_terminal_font_color(YELLOW);
	print_line(str3);
	print_character_with_color('A', GREEN);
	print_string_with_color(" BIG STRING", CYAN);
	print_line_with_color("A new line", BROWN);
	print_line_with_color(" is here", RED);
	
	print_line(str1);
	set_terminal_font_color(BLUE);
	print_line(str2);
	set_terminal_font_color(YELLOW);
	print_line(str3);
	print_character_with_color('A', GREEN);
	print_string_with_color(" BIG STRING", CYAN);
	print_line_with_color("A new line", BROWN);
	print_line_with_color(" is here", RED);

	print_line(str1);
	set_terminal_font_color(BLUE);
	print_line(str2);
	set_terminal_font_color(YELLOW);
	print_line(str3);
	print_character_with_color('A', GREEN);
	print_string_with_color(" BIG STRING", CYAN);
	print_line_with_color("A new line", BROWN);
	print_line_with_color(" is here", RED);
	
	print_line(str1);
	set_terminal_font_color(BLUE);
	print_line(str2);
	set_terminal_font_color(YELLOW);
	print_line(str3);
	print_character_with_color('A', GREEN);
	print_string_with_color(" BIG STRING", CYAN);
	print_line_with_color("A new line", BROWN);
	
	//print_line_with_color(" is here", RED);
	print_string_with_color(" is here", RED);

	run_tests();
	while(1);
}

void run_tests() {
	if(flag_test_print_overflow != 0) {
		test_print_overflow();
	}
	else if(flag_test_preliminary_colors != 0) {
		test_preliminary_colors();
	}
}
