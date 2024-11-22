#include "console.h"
#include "dios_strings.h"

#include <stdint.h>

const char* HELP = "help";
char* parsed_command;

/**
 * Only one argument is necessary for the color commands.
 */
char* tokens[3];

void help();
void bad_command();
void clear_tokens();
void populate_tokens();

/**
 * Most commands are small enough that I can provide them in this .c file.
 * Exit is implemented from the eval loop because that is the only way I
 * 	can return from main.
 */
void eval_command(char* command) {
	clear_tokens();

	parsed_command = trim(command);
	print_line(parsed_command);
	
	populate_tokens();

	int i = 0;
	while(tokens[i] != 0) {
		print_line(tokens[i]);
		i++;
	}

	if(strcmp(parsed_command, HELP) == 0) {
		help();	
	}
	else {
		bad_command();
	}
}

void clear_tokens() {
	for(int i = 0; i < 3; i++) {
		tokens[i] = (char*)(0);
	}
}

void populate_tokens() {
	int i = 0;
	uint8_t double_null = 0;
	char* current_char = parsed_command;
	char* next_char = parsed_command + 1;

	/**
	 * The command buffer will always contain two null_bytes at the end.
	 */
	while(i < 2 && !double_null) {
		tokens[i] = current_char;
		while(!is_space(current_char) && (*current_char != '\0')) {
			current_char++;
			next_char++;
		}

		*current_char = '\0';
		if(*next_char == '\0') {
			double_null = 1;
		}
		i++;
	}

}

void help() {
	print_line("List of Commands");
	print_line("    exit");
}

void bad_command() {
	print_line("Bad command. Type 'help' for a list of all commands.");
}
