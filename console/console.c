#include <stdint.h>

struct character {
	int8_t character;
	int8_t style;
};

const int VGA_WIDTH = 80;
const int VGA_HEIGHT = 25;

static struct character* const VGA_START = (struct character*)0xb8000;

const int8_t DEFAULT_CHARACTER = 0x20;
const int8_t DEFAULT_STYLE = 0x07;

static int terminal_pos = 0;
static int style = DEFAULT_STYLE;

void print_character(char c) {
	struct character* pos = (struct character*)(VGA_START + terminal_pos);
	
	pos->character = (int8_t) c;
	pos->style = DEFAULT_STYLE;
	
	terminal_pos++;
}

void clear_terminal() {	
	int i = 0;
	for(; i < VGA_WIDTH * VGA_HEIGHT; i++) {
		print_character((char) DEFAULT_CHARACTER);
	}
	terminal_pos = 0;
}

void print_string(char* str) {
	int i = 0;
	while(str[i] != '\0') {
		print_character(str[i]);
		i++;
	}
}

void print_line(char* str) {

}
