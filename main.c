#include <stdio.h>
#include <stdlib.h>
#include "String.h"



bool is_vowel(char c) 
{
    return isVowel(c);
}

int main(int argc, char **argv)
{
    const char *original = "hello world";
    char *filtered = stringFilter(original, is_vowel);

    printf("Filtered string: %s\n", filtered);

    free(filtered);

    
    getchar();
    return 0;
}