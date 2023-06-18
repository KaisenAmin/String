#include <stdio.h>
#include <stdlib.h>
#include "String.h"


int main(int argc, char **argv)
{
    const char *originalString = "bd156caef";

    // Sort the characters in the original string
    char *sortedString = stringSort(originalString);

    // Print the sorted string
    printf("Original String: %s\n", originalString);
    printf("Sorted String: %s\n", sortedString);

    // Free the dynamically allocated memory
    free(sortedString);

    getchar();
    return 0;
}