
const int VGA_WIDTH = 80;
const int VGA_HEIGHT = 25;

static const struct character* VGA_START = (struct character*)0xb8000;

const char DEFAULT_CHARACTER = 0x20;
const char DEFAULT_STYLE = (0x0 << 4) | (0x08);

static int terminal_pos = 0;
static int style = DEFAULT_STYLE;

struct character {
	char character;
	char style;
};


void print_character(char c) {
	struct character* pos = VGA_START + terminal_pos;
	
	pos->character = (char) c;
	pos->style = DEFAULT_STYLE;
	
	terminal_pos++;
}

void clear_terminal() {	
	int i = 0;
	for(; i < VGA_WIDTH * VGA_HEIGHT; i++) {
		print_character(DEFAULT_CHARACTER);
	}
	terminal_pos = 0;
}

void print_string(char* str) {
	int i = 0;
	while(str[i] != '\0') {
		print_character(str[i]);
	}
}

void print_line(char* str) {

}
