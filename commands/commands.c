#include "console.h"
#include "dios_strings.h"

const char* HELP = "help";

void eval_command(char* command) {
	char* parsed_command = trim(command);
	print_line(parsed_command);
}
