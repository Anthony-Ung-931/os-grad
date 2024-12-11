#include "console.h"
#include "dios_strings.h"
#include "term_colors.h"

#include <stdint.h>

const char* HELP = "help";
const char* SET_TEXT_COLOR = "set-text-color";
const char* SET_BG_COLOR = "set-background-color";
const char* CLEAR = "clear";

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
	populate_tokens(command);

	if(strcmp(tokens[0], HELP) == 0) {
		help();	
	}
	else if(strcmp(tokens[0], SET_TEXT_COLOR) == 0) {
		set_text_color(tokens);
	}
	else if(strcmp(tokens[0], SET_BG_COLOR) == 0) {
		set_text_background_color(tokens);
	}
	else if(strcmp(tokens[0], CLEAR) == 0) {
		clear_terminal();
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


/**
 * This function as written now returns addresses to two empty strings.
 */
void populate_tokens(char* command) {
	parsed_command = trim(command);
	
	int num_tokens = 1;
	int len = str_len(parsed_command);
	int token_start = 0;

	int i = 0;

	tokens[0] = parsed_command;

	/**
	 * The command buffer will always contain two null_bytes at the end.
	 */
	while((i < len) && (num_tokens <= 2) && (parsed_command[i] != '\0')) {
		
		/* Handles more than one whitespace between args. */
		while(is_space(parsed_command[i])) {
			i++;
		}

		token_start = i;
		while((i < len) && (parsed_command[i] != '\0') && 
			(!is_space(parsed_command[i]))) {
			i++;
		}

		if(token_start < i) {
			parsed_command[i] = '\0';
			i++;

			tokens[(num_tokens - 1)] = &parsed_command[token_start];
			num_tokens++;
		}

	}

}

void help() {
	print_line("List of Commands");
	print_line("    help");
	print_line("    set-text-color [color: str]");
	print_line("    set-background-color [color: str]");
	print_line("    clear");
	print_line("    exit");
}

void bad_command() {
	print_line("Bad command. Type 'help' for a list of all commands.");
}
