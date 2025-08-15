#include "tuple.h"
#include "canvas.h"

int tests_run = 0;
int tests_failed = 0;

void check(bool condition, const char* message) 
{
    // We always increment the number of tests run.
    tests_run++;

    if (condition) {
        // If the condition is true, we print a PASS message.
        printf("[PASS] %s\n", message);
    } else {
        // If it's false, we print a FAIL message...
        printf("[FAIL] %s\n", message);
        // ...and increment our failure counter.
        tests_failed++;
    }
}


int main(int argc, char **argv) 
{
	if (argc != 4) {
		fprintf(stderr, "Usage: %s <r> <g> <b>\n", argv[0]);
		return (EXIT_FAILURE);
	}

	t_tuple color = create_tuple(atof(argv[1]), 
								atof(argv[2]), 
								atof(argv[3]), 
								0);
								(void)color;
    test_color_operations();
    return (0);
}