/* 	
 *  	I have to use a preprocessor directive to name this constant because
 * 		this constant needs to be used in an array size declaration.
 * */

#define MAX_COMMAND_LENGTH 64

/*
 *	I have to use a preprocessor directive for the console prompt
 *		because if I declare a const char, I get a compiler warning
 *		that my print_string call would discard the const qualifier.
 * */

#define CONSOLE_PROMPT "$ "

