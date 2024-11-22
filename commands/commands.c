#include "console.h"
#include "dios_strings.h"

const char* HELP = "help";
char* parsed_command;

/**
 * Only one argument is necessary for the color commands.
 */
char* tokens[2];

void help();
void bad_command();

/**
 * Most commands are small enough that I can provide them in this .c file.
 */
void eval_command(char* command) {
	char* parsed_command = trim(command);
	print_line(parsed_command);
	if(strcmp(parsed_command, HELP) == 0) {
		help();	
	}
	else {
		bad_command();
	}
}

void help() {
	print_line("List of Commands");
	print_line("    exit");
}

void bad_command() {
	print_line("Bad command. Type 'help' for a list of all commands.");
}
