#include <stdio.h>
#include <stdlib.h>
#include "String.h"


int main(int argc, char **argv)
{
    const char *original = "Hello, World!";
    char encoded[256];
    char decoded[256];

    // Encode the string
    stringEncodeB64(original, encoded);
    printf("Encoded string: %s\n", encoded);

    // Decode the string
    stringDecodeB64(encoded, decoded);
    printf("Decoded string: %s\n", decoded);

    getchar();
    return 0;
}