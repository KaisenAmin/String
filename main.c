#include <stdio.h>
#include <stdlib.h>
#include "String.h"


int main(int argc, char **argv)
{
    const char *exampleString = "Hello";

    char *hexRepresentation = stringToHex(exampleString);
    char *octRepresentation = stringToOct(exampleString);

    printf("Original String: %s\n", exampleString);
    printf("Hexa decimal Representation: %s\n", hexRepresentation);
    printf("Octal Representation: %s\n", octRepresentation);

    // Free the dynamically allocated memory
    free(hexRepresentation);
    free(octRepresentation);

    getchar();
    return 0;
}