#include "console.h"
#include "tests.h"
#include "keyboard.h"
#include "portmap.h"
#include "kernel_config.h"

/**
 * Flags for various internal tests
 */
const int flag_test_print_overflow = 0;
const int flag_test_preliminary_colors = 0;

void run_tests();

void write_character(uint8_t c);
char* read_command();
void clear_command_buffer();

/* Max command size, including the null byte */
uint8_t command_buffer[MAX_COMMAND_LENGTH];
uint8_t buffer_pos = 0;

int main() {
	
	clear_terminal();
	uint8_t byte;
	while(1) {
		clear_command_buffer();
		print_prompt();
		
		uint8_t done = 0;
		/* I cannot recreate this behavior inside a method. */
		while(!done) {
			while(byte = scan()) {
				print_character(charmap[byte]);
				write_character(charmap[byte]);
				if(charmap[byte] == '\n') {
					done = 1;
				}		
			}
		}
		print_line(command_buffer);
	}

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

char* read_command() {
	char* command = (char*)0;
	uint8_t byte = 0;
	while(byte = scan()) {
		print_character(charmap[byte]);
		if(byte == '\n') {
			print_character('*');
			return command;
		}		
	}
}

void clear_command_buffer() {
	for(int i = 0; i < MAX_COMMAND_LENGTH; i++) {
		command_buffer[i] = 0;
	}
	buffer_pos = 0;
}

void write_character(uint8_t c) {
	if((buffer_pos >= 0) && (buffer_pos < (MAX_COMMAND_LENGTH - 1))) {
		if(c != '\n') {
			command_buffer[buffer_pos] = c;
		}
		else {
			command_buffer[buffer_pos] = 0;
		}
		buffer_pos++;
	}
}
