#include <stdio.h>
#include <stdlib.h>

#include "String.h"

int main(int argc, char **argv)
{
    const char* myName = "   Hello W156orld\nam36in";

    printf("The length of myName is %d\n", stringLength(myName));
    printf("The number of words in myName is %d\n", stringWordCount(myName));
    printf("The number of digits in myName is %d\n", stringDigitCount(myName));
    printf("The number of '6' in myName is %d\n", stringCharCount(myName, '6'));
    printf("The position of 'W' in myName is %d\n", stringFindChar(myName, 'W'));
    printf("The Position of 'W156' in myName is %d\n", stringFindString(myName, "W156"));
    printf("The String 'Hello' is %d\n", stringCompare(myName, "Hello W156orld\nam36in"));

    getchar();
    return 0;
}