#include "console.h"

void test_print_overflow() {
	for(int i = 0; i < 30; i++) {
		print_character('\n');
	}
}
