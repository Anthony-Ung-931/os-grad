#include "console.h"

int main() {
	char *const VGA_BUFFER = (char *)0xb8000;
	char* hello = "Hello World";
	
	char printChar = (char)1;

	int offset = 0;

	clear_terminal();

	while(printChar != '\0') {
		printChar = (char)*(hello + offset);
		VGA_BUFFER[2 * offset] = printChar;
		offset += 1;
	}

}
