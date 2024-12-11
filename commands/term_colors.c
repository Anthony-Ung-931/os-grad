#include "console.h"
#include "dios_strings.h"

const char* LIST = "list";

/**
 * This cannot be constant because I get compiler warnings.
 */
char* colors[] = { 
	"BLACK",
	"BLUE",
	"GREEN",
	"CYAN",
	"RED",
	"PURPLE",
	"BROWN",
	"GRAY",
	"DARK GRAY",
	"LIGHT BLUE",
	"LIGHT GREEN",
	"LIGHT CYAN",
	"LIGHT RED",
	"LIGHT PURPLE",
	"YELLOW",
	"WHITE",
	(char*)(0)
};

void list();

void set_text_color(char** args) {
	if(!(args[1])) {
		print_line("You did not specify which color to change to.");
		print_line("call $ set-text-color list to see a list of colors");
		return;
	}

	print_line(args[1]);

	if(strcmp(args[1], LIST) == 0) {
		list();
	}
}

void list() {
	clear_terminal();
	print_line("This is a list of all colors:");
	int i = 0;
	while(colors[i] != (char*)(0)) {
		print_character('\t');
		print_line(colors[i]);
		i++;
	}
}
