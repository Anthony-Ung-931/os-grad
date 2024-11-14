#include <stdint.h>
#include "console.h"
#include "portmap.h"

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
static void update_cursor();

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
	update_cursor();
}

/**
 * McKee says it is OK for now if I simply shift up and have the first line
 * be perminantly lost.
 */
void shift_up() {
	struct character* current_pos = (struct character*)(VGA_START);
	struct character* old_pos = (struct character*)(VGA_START);

	int i = 0;
	for(; i < VGA_WIDTH * (VGA_HEIGHT - 1); i++) {
		current_pos = (struct character*)(VGA_START+i);
		old_pos = (struct character*)(VGA_START+VGA_WIDTH+i);

		current_pos->character = old_pos->character;
		current_pos->style = old_pos->style;
	}
	for(; i < VGA_WIDTH * VGA_HEIGHT; i++) {
		current_pos = (struct character*)(VGA_START+i);
		current_pos->character = DEFAULT_CHARACTER;
		current_pos->style = DEFAULT_STYLE;
	}

	terminal_pos = VGA_WIDTH * (VGA_HEIGHT - 1);
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

	/**
	 *	McKee says it is OK if I am checking for out of bounds.
	 *	He suggests that I shift everything up first and that he is
	 *		OK if I lose the first line of output.
	 */
	if(terminal_pos < 0 || terminal_pos >= VGA_WIDTH * (VGA_HEIGHT + 1)) {
		clear_terminal();
		terminal_pos = 0;
	}
	else if(terminal_pos >= VGA_WIDTH * VGA_HEIGHT) {
		shift_up();
	}
	update_cursor();
}

void print_string_with_color(char* str, VGA_Color color) {
	int i = 0;
	while(str[i] != '\0') {
		print_character_with_color(str[i], color);
		i++;
	}
	
}

void print_line_with_color(char* str, VGA_Color color) {
	print_string_with_color(str, color);
	print_character('\n');
}

static void update_cursor() {
	uint16_t cursor_pos = terminal_pos;
	outb(0x3d4, 0x0f);
	outb(0x3d5, (uint8_t)(cursor_pos));
	outb(0x3d4, 0x0e);
	outb(0x3d5, (uint8_t)(cursor_pos >> 8));
}
