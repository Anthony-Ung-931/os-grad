
void clear_terminal();
void print_character(char c);
void print_string(char* str);
void print_line(char* str);

typedef enum {
	BLACK = 0,
	BLUE,
	GREEN,
	CYAN,
	RED,
	PURPLE,
	BROWN,
	GRAY,
	DARK_GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_CYAN,
	LIGHT_RED,
	LIGHT_PURPLE,
	YELLOW,
	WHITE
} VGA_Color;
