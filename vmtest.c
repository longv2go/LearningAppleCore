#include <stdlib.h>

int global_j;
const int ci = 24;
int main(int argc, char const *argv[])
{
	int local_stack = 0;
	char *const_data = "This data is constant";
	char *tiny = malloc(32);
	char *small = malloc(2 * 1024);
	char *large = malloc(1024 * 1024);

	printf("Text is %p\n", main);
	printf("Global Data is %p\n", &global_j);
	printf("Local (stack) is %p\n", &local_stack);
	printf("Constant data is %p\n", &ci);
	printf("Hardcodeed string (also constant) are at %p\n", const_data);

	printf("Tiny alloc from %p\n", tiny);
	printf("Small alloc from %p\n", small);
	printf("Large alloc from \n", large);
	printf("Malloc (i.e. libSystem) is at %p\n", malloc);

	sleep(100);
	return 0;
}