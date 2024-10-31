#include "console.h"
#include "tests.h"

/**
 * Flags for various internal tests
 */
const int flag_test_print_overflow = 0;
const int flag_test_preliminary_colors = 0;

void run_tests();

int main() {
	run_tests();
	while(1);
}

void run_tests() {
	if(flag_test_print_overflow != 0) {
		test_print_overflow();
	}

	if(flag_test_preliminary_colors != 0) {
		test_preliminary_colors();
	}

}
