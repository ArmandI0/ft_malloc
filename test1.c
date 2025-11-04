#include <stdlib.h>

int main() {

	char *a = malloc(73);
	free(a + 5);


    return 0;
}