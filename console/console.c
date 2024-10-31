#include <stdint.h>
#include "console.h"

struct character {
	int8_t character;
	int8_t style;
};

const int VGA_WIDTH = 80;
const int VGA_HEIGHT = 25;

static struct character* const VGA_START = (struct character*)0xb8000;

const int8_t DEFAULT_CHARACTER = 0x20;
const int8_t DEFAULT_STYLE = (BLACK << 4) | GRAY;

static int terminal_pos = 0;
static int style = DEFAULT_STYLE;

static VGA_Color terminal_font_color = GRAY;
static VGA_Color terminal_background_color = BLACK;

static VGA_Color default_terminal_font = GRAY;
static VGA_Color default_terminal_background = BLACK;

void print_character(char c);
void clear_terminal();
void print_string(char* str);
void print_line(char* str);


void print_character(char c) {
	print_character_with_color(c, terminal_font_color);
}

void clear_terminal() {
	struct character* pos = (struct character*)(VGA_START);
	
	int i = 0;
	for(; i < VGA_WIDTH * VGA_HEIGHT; i++) {
		pos = (struct character*)(VGA_START+i);
		pos->character = DEFAULT_CHARACTER;
		pos->style = DEFAULT_STYLE;
	}
}

void print_string(char* str) {
	int i = 0;
	while(str[i] != '\0') {
		print_character(str[i]);
		i++;
	}
}

void print_line(char* str) {
	print_string(str);
	print_character('\n');
}

void set_terminal_font_color(VGA_Color color) {
	terminal_font_color = color;
}

void set_terminal_background_color(VGA_Color color) {
	terminal_background_color = color;
}

void print_character_with_color(char c, VGA_Color color) {
	struct character* pos = (struct character*)(VGA_START + terminal_pos);
	
	if(c != '\n') {
		pos->character = (int8_t) c;
		pos->style = (terminal_background_color << 4) | color;
		terminal_pos++;
	}
	else if(c == '\n') {
		terminal_pos /= 80;
		terminal_pos += 1;
		terminal_pos *= 80;
	}

	if(terminal_pos < 0 || terminal_pos >= VGA_WIDTH * VGA_HEIGHT) {
		clear_terminal();
		terminal_pos = 0;
	}
	
}
