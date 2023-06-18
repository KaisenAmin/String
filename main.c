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

    char* newName = (char*)malloc(stringLength(myName) + 1);
    stringCopy(newName, myName);

    printf("Copy myName to newName: %s\n", newName);
    printf("The reverse of this string is: %s\n", stringReverse(newName));
    printf("The upper case of this string is: %s\n", stringToUpper(newName));
    printf("The lower case of this string is: %s\n", stringToLower(newName));
    printf("The trim of this string is: %s\n", stringTrim(newName));
    printf("isWhiteSpace: %d\n", isWhiteSpace(' '));
    printf("isDigit: %d\n", isDigit('1'));
    printf("isLetter: %d\n", isLetter('a'));
    printf("isAlphaNumeric: %d\n", isAlphaNumeric('a'));
    printf("isUpperCase: %d\n", isUpperCase('A'));
    printf("isLowerCase: %d\n", isLowerCase('A'));
    printf("isPunctuation: %d\n", isPunctuation('.'));
    printf("isSpecialChar: %d\n", isSpecialChar('~'));
    printf("isVowel: %d\n", isVowel('f'));
    printf("isConsonant: %d\n", isConsonant('f'));
    printf("isPalindrome: %d\n", isPalindrome("abbd"));
    printf("isAnaGram: %d\n", isAnagram("abbd", "dbba"));
    printf("isSubString 'Hello' of %d\n", isSubString(myName, "Hello0"));
    printf("isRotation: %d\n", isRotation("Hello", "lloHe"));
    printf("isRotationOfPalindrome: %d\n", isRotationOfPalindrome("abba"));

    const char *str1 = "aacd";
    const char *str2 = "daca";
    printf("Is '%s' a rotation of an anagram of '%s'? %s\n", str2, str1, isRotationOfAnagram(str1, str2) ? "Yes" : "No");

    const char *str3 = "abcd";
    const char *str4 = "dcab";
    printf("Is '%s' a rotation of an anagram of '%s'? %s\n", str4, str3, isRotationOfAnagram(str3, str4) ? "Yes" : "No");

    printf("isRotationOfSubString: %d\n", isRotationOfSubString("Hello", "lloHe"));
    printf("Concat String 'Hello' and 'World': %s\n", stringConcat("Hello", myName));
    printf("SubString of 'Hello World': %s\n", stringSubString(myName, 0, 5));
    printf("Replace 'Hello' with 'Hi': %s\n", stringReplace(myName, "Hello", "Hi"));
    printf("Rotate 'Hello' by 2: %s\n", stringRotate("Hello", 2));

    const char *original = "abcdefg";
    char *rotated = stringRotateLeft(original, 2);
    
    if (rotated) 
    {
        printf("Original string: %s\n", original);
        printf("Rotated string (left by 2): %s\n", rotated);
        free(rotated);
    }

    const char *originalRight = "abcdefg";
    char *rotatedRight = stringRotateRight(original, 2);

    if (rotatedRight) 
    {
        printf("Original string: %s\n", originalRight);
        printf("Rotated string (right by 2): %s\n", rotatedRight);
        free(rotatedRight);
    }

    const char *originalSen = "this is a sample string";

    char *camelCase = stringCamelCase(originalSen);
    char *snakeCase = stringSnakeCase(originalSen);
    char *pascalCase = stringPascalCase(originalSen);
    char *kebabCase = stringKebabCase(originalSen);

    printf("Original: %s\n", originalSen);
    printf("Camel Case: %s\n", camelCase);
    printf("Snake Case: %s\n", snakeCase);
    printf("Pascal Case: %s\n", pascalCase);
    printf("Kebab Case: %s\n", kebabCase);

    const char *myString = "hello world, hello!";
    const char *subString = "hello";
    const char *insertString = "INSERTED ";
    
    printf("%s\n", myString);
    printf("Count of '%s' in '%s': %d\n", subString, myString, stringCountSubstrings(myString, subString));

    char *newString = stringInsert(myString, insertString, 6);
    printf("String after insertion: %s\n", newString);
    free(newString);

    char *repeatedString = stringRepeat(subString, 3);
    printf("Repeated string: %s\n", repeatedString);
    free(repeatedString);

    const char *intString = "-12345";
    printf("String to integer: %d\n", stringToInteger(intString));

    const char *floatStr = "3.14159";
    float floatValue = stringToFloat(floatStr);
    printf("Converted string \"%s\" to float: %f\n", floatStr, floatValue);

    // Example using integerToString
    int intValue = -12345;
    char *intStr = integerToString(intValue);
    printf("Converted integer %d to string: \"%s\"\n", intValue, intStr);

    // Example using floatToString
    float pi = 3.1415926535;
    int precision = 6;
    char *piStr = floatToString(pi, precision);
    printf("Converted float %f to string with precision %d: \"%s\"\n", pi, precision, piStr);

    // Free the dynamically allocated memory
    free(intStr);
    free(piStr);

    const char *myStringTest = "This is an example string";
    const char *prefix = "This";
    const char *suffix = "string1";
    const char *toRemove = "example ";

    printf("Does \"%s\" start with \"%s\"? %s\n", myStringTest, prefix, stringStartsWith(myStringTest, prefix) ? "Yes" : "No");
    printf("Does \"%s\" end with \"%s\"? %s\n", myStringTest, suffix, stringEndsWith(myStringTest, suffix) ? "Yes" : "No");

    char *removed = stringRemove(myStringTest, toRemove);
    printf("Original string: \"%s\"\n", myStringTest);
    printf("String with \"%s\" removed: \"%s\"\n", toRemove, removed);

    const char *myStringRmoveAll = "I love apples. Apples are great. Do you like apples?";
    const char *toRemoveAll = "apples";

    char *removedAll = stringRemoveAll(myStringRmoveAll, toRemoveAll);
    printf("Original string: \"%s\"\n", myStringRmoveAll);
    printf("String with \"%s\" removed: \"%s\"\n", toRemoveAll, removedAll);

    // Free dynamically allocated memory
    free(removedAll);
    free(removed);
    free(camelCase);
    free(snakeCase);
    free(pascalCase);
    free(kebabCase);
    free(newName);

    // paddinleft and write and join and split string 
    const char *str1 = "hello world! this is an example string.";
    char *capitalized = stringCapitalize(str1);
    printf("Original string: %s\n", str1);
    printf("Capitalized string: %s\n\n", capitalized);
    free(capitalized); // Don't forget to free memory

    // Example using stringSplit
    const char *str2 = "apple,banana,orange,grape";
    int numTokens;
    char **tokens = stringSplit(str2, ',', &numTokens);
    printf("Split string into tokens:\n");
    for (int i = 0; i < numTokens; i++) {
        printf("%s\n", tokens[i]);
        free(tokens[i]); // Free each token
    }
    free(tokens); // Free the array holding tokens
    printf("\n");

    // Example using stringJoin
    char *parts[] = {"This", "is", "a", "joined", "string"}; // Without const
    char *joined = stringJoin(parts, 5, " ");
    printf("Joined string: %s\n\n", joined);
    free(joined);// Don't forget to free memory

    // Example using stringPaddingLeft
    const char *str3 = "42";
    char *paddedLeft = stringPaddingLeft(str3, '0', 5);
    printf("Original string: %s\n", str3);
    printf("Padded left string: %s\n", paddedLeft);
    free(paddedLeft); // Don't forget to free memory


    // trim left and right
    const char *str1 = "    Hello, World!";
    const char *str2 = "Goodbye, World!    ";

    char *trimmedLeft = stringTrimLeft(str1);
    char *trimmedRight = stringTrimRight(str2);

    printf("Original String: '%s'\n", str1);
    printf("Left Trimmed: '%s'\n", trimmedLeft);

    printf("Original String: '%s'\n", str2);
    printf("Right Trimmed: '%s'\n", trimmedRight);

    free(trimmedLeft);
    free(trimmedRight);

    // Example for stringSwapCase stringTitleCase and stringReplaceAll
    const char *example1 = "ThIs Is a TeSt StrInG";
    char *swappedCase = stringSwapCase(example1);
    printf("Swap Case: %s\n", swappedCase);
    free(swappedCase);

    // Example for stringTitleCase
    const char *example2 = "this is a title case example";
    char *titleCase = stringTitleCase(example2);
    printf("Title Case: %s\n", titleCase);
    free(titleCase);

    // Example for stringReplaceAll
    const char *originalString = "This is an example string. Let's replace all occurrences of 'is' with 'IS'";
    char *replaced = stringReplaceAll(originalString, "is", "IS");
    printf("Replaced String: %s\n", replaced);
    free(replaced);

    const char *emptyString = "";
    const char *nonEmptyString = "hello@example.com";


    printf("Is empty string empty? %s\n", stringIsEmpty(emptyString) ? "Yes" : "No");
    printf("Is non-empty string empty? %s\n", stringIsEmpty(nonEmptyString) ? "Yes" : "No");


    // Testing the stringToBinary function
    char *binary = stringToBinary("ABCD");
    printf("Binary representation of 'ABCD': %s\n", binary);

    // Testing the stringFromBinary function
    char *original = stringFromBinary(binary);
    printf("Original string from binary: %s\n", original);

    // Testing the stringRandom function
    char *randomStr = stringRandom(10);
    printf("Random string: %s\n", randomStr);

    char *centered = stringCenter("hello", 20, '-');
    printf("Centered string: %s\n", centered);

    // Testing the stringLjust function
    char *ljust = stringLjust("hello", 20, '-');
    printf("Left-justified string: %s\n", ljust);

    // Testing the stringRjust function
    char *rjust = stringRjust("hello", 20, '-');
    printf("Right-justified string: %s\n", rjust);

    // Freeing the allocated memory
    free(centered);
    free(ljust);
    free(rjust);

    const char *original = "hello";
    char *shuffled = stringShuffle(original);
    printf("Original string: %s\n", original);
    printf("Shuffled string: %s\n", shuffled);

    // Freeing the allocated memory
    free(shuffled);
    

    // Freeing the allocated memory
    free(binary);
    free(original);
    free(randomStr);

    getchar();
    return 0;
}