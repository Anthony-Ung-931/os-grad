#include "console.h"
#include "tests.h"

const int flag_test_print_overflow = 0;
const int flag_test_preliminary_colors = 1;

int main() {

	if(flag_test_print_overflow != 0) {
		test_print_overflow();
	}

	if(flag_test_preliminary_colors != 0) {
		test_preliminary_colors();
	}

	while(1);
}
