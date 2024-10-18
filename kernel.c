#include "console.h"

int main() {
	char* hello = "Hello World";
	
	clear_terminal();
	print_string(hello);

	while(1);
}
