#include <stdio.h>
#include <stdlib.h>
#include "String.h"


int main(int argc, char **argv)
{
    const char *hexString = "1A3F";
    const char *octString = "1507";

    char *binaryFromHex = stringHexToBinary(hexString);
    char *binaryFromOct = stringOctToBinary(octString);

    printf("Hexadecimal String: %s\n", hexString);
    printf("Binary Representation from Hex: %s\n", binaryFromHex);

    printf("Octal String: %s\n", octString);
    printf("Binary Representation from Octal: %s\n", binaryFromOct);

    // Free the dynamically allocated memory
    free(binaryFromHex);
    free(binaryFromOct);

    getchar();
    return 0;
}