int main() {
	char *const VGA_BUFFER = (char *)0xb800;
	char* hello = "Hello World";
	
	char printChar;

	int offset = 0;

	while(printChar != '\0') {
		printChar = (char)*(hello + offset);
		VGA_BUFFER[offset] = printChar;
		offset += 2;
	}

}
