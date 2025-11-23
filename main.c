#include "includes/malloc.h"

int main() {
    char *toto = malloc(10);

    free(toto);
}