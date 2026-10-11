#include "String.h"

int main(void)
{
    const char *original = "this is a sample string";

    char *camel = stringCamelCase(original);
    char *snake = stringSnakeCase(original);
    char *centered = stringCenter("hello", 20, '-');
    char *sorted = stringSort("bd156caef");
    char *replaced = stringReplaceAll(original, "is", "IS");

    printf("Original: %s\n", original);
    printf("Camel case: %s\n", camel);
    printf("Snake case: %s\n", snake);
    printf("Centered: %s\n", centered);
    printf("Sorted: %s\n", sorted);
    printf("Replaced: %s\n", replaced);
    printf("Word count: %d\n", stringWordCount(original));

    free(camel);
    free(snake);
    free(centered);
    free(sorted);
    free(replaced);
    return 0;
}
