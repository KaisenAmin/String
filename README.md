# CStringEnhancer

CStringEnhancer is a small C library that provides additional string manipulation functions. The functionalities provided include aligning strings (left, center, right), padding strings, shuffling strings, and more. This library is aimed at making string manipulation in C more versatile and easy.

## Features

- String Alignment:
  - Center align a string with a custom padding character.
  - Left align a string with a custom padding character.
  - Right align a string with a custom padding character.

- String Manipulation:
  - Shuffle the characters in a string.
  - Reverse a string.
  - Convert a string to uppercase.
  - Convert a string to lowercase.
  - Trim leading and trailing whitespace from a string.
  - Concatenate two strings.
  - Replace substrings in a string.
  - Rotate the characters in a string.
  - Transform a string to camel case, snake case, pascal case, or kebab case.

- String Information:
  - Calculate the length of a string.
  - Count the number of words in a string.
  - Count the number of digits in a string.
  - Count the occurrences of a specific character in a string.
  - Find the position of a character in a string.
  - Find the position of a substring in a string.
  - Compare two strings for equality.

- String Validation:
  - Check if a string is a palindrome.
  - Check if two strings are anagrams.
  - Check if a string is a rotation of another.
  - Check if a string is a rotation of a palindrome.
  - Check if a string is a rotation of an anagram.
  - Check if a string is a rotation of a substring.

- String Conversion:
  - Convert a string to an integer.
  - Convert a string to a floating-point number.

- Additional String Functions:
  - Perform string mapping, applying a function to each character in a string.
  - Perform string filtering, selecting characters from a string based on a condition.
  - Split a string into an array of substrings based on a delimiter.
  - encode and decode string in Base64

- Character Validation:
  - Check if a character is whitespace.
  - Check if a character is a digit.
  - Check if a character is a letter.
  - Check if a character is alphanumeric.
  - Check if a character is uppercase.
  - Check if a character is lowercase.
  - Check if a character is a punctuation mark.
  - Check if a character is a special character.
  - Check if a character is a vowel.
  - Check if a character is a consonant.

- Case Conversion:
  - Convert a character to uppercase.
  - Convert a character to lowercase.

- String Comparison:
  - Compare two strings for equality.

- These features aim to provide a comprehensive set of string manipulation functions to make working with strings in C more versatile and convenient.

## Getting Started

### Prerequisites

- A C compiler (e.g., gcc)

### Building

1. Clone the repository:

    ```sh
    git clone https://github.com/KaisenAmin/CStringEnhancer.git
    ```

2. Change to the project directory:

    ```sh
    cd CStringEnhancer
    ```

3. Compile the source code:

    ```sh
    gcc main.c String.c -o CStringEnhancer
    ```

### Usage

Run the compiled program:

```sh
./CStringEnhancer
```

### Example

1. This example demonstrates how to use the stringRotateLeft function to rotate the characters in a string to the left by a certain number of positions:

    ```c
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
    ```
2. These are some basic functions for strings:

   ```c
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
    ```

3. trim left and right:

    ```c
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
    ```
    
4. stringReplaceAll, stringSwapCase, stringTitleCase, stringIsEmpty:

   ```c
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
    ```
   
5. stringToBinary, stringFromBinary, stringRandom, stringCenter, stringLjust, stringRjust:

   ```c
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
    free(binary);
    free(original);
    free(randomStr);
    ```

6. stringShuffle:

   ```c
    const char *original = "hello";
    char *shuffled = stringShuffle(original);
    printf("Original string: %s\n", original);
    printf("Shuffled string: %s\n", shuffled);

    // Freeing the allocated memory
    free(shuffled);
    ```

7. stringInsert, stringRepeat, stringToInteger, stringToFloat:

   ```c
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
    ```

8. integerToString, floatToString:

   ```c
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
    ```
9. stringCamelCase, stringSnakeCase, stringPascalCase, stringKebabCase:

    ```c
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

    free(camelCase);
    free(snakeCase);
    free(pascalCase);
    free(kebabCase);
    free(originalSen);
    ```

10. stringCapitalize, stringJoin, stringSplit:

    ```c
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
    
    for (int i = 0; i < numTokens; i++) 
    {
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
    ```

11. stringMap:

    ```c
    #include <stdio.h>
    #include <stdlib.h>
    #include "String.h"


    char myToUpper(char c) 
    {
        return toUpperCase(c);
    }

    int main(int argc, char **argv)
    {
        const char *original = "hello";
        char *mapped = stringMap(original, myToUpper);

        printf("Mapped string: %s\n", mapped);

        free(mapped);

        getchar();
        return 0;
    }

    ```

12. stringFilter:

    ```c
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
    ```

13. stringEncodeB64, stringDecodeB64:
    ```c
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
    ```

    
