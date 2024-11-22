#include "console.h"
#include "dios_strings.h"

const char* HELP = "help";

void help();


/**
 * Most commands are small enough that I can provide them in this .c file.
 */
void eval_command(char* command) {
	char* parsed_command = trim(command);
	print_line(parsed_command);
	if(strcmp(parsed_command, HELP) == 0) {
		help();	
	}
}

void help() {
	print_line("List of Commands");
}
