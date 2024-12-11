#include "console.h"
#include "dios_strings.h"

const char* LIST = "list";

/**
 * This cannot be constant because I get compiler warnings.
 */
char* colors[] = { 
	"black",
	"blue",
	"green",
	"cyan",
	"red",
	"purple",
	"brown",
	"gray",
	"dark-gray",
	"light-blue",
	"light-green",
	"light-cyan",
	"light-red",
	"light-purple",
	"yellow",
	"white",
	(char*)(0)
};

void list();
int find_color(char* arg);

void set_text_color(char** args) {
	if(!(args[1])) {
		print_line("You did not specify which color to change to.");
		print_line("call $ set-text-color list to see a list of colors");
		return;
	}

	int color = find_color(args[1]);

	if(color != -1) {
		set_terminal_font_color((VGA_Color)(color));
	}

	else if(strcmp(args[1], LIST) == 0) {
		list();
	}

	else {
		print_line("Please format your argument properly.");
		print_line("call $ set-text-color list to see a list of colors");
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

int find_color(char* arg) {
	int i = 0;
	int found = 0;
	while(colors[i] != (char*)(0)) {
		if(strcmp(arg, colors[i]) == 0) {
			return i;
		}
		i++;
	}
	return -1;
}
