# CStringEnhancer

CStringEnhancer is a small C library that provides additional string manipulation functions. The functionalities provided include aligning strings (left, center, right), padding strings, shuffling strings, and more. This library is aimed at making string manipulation in C more versatile and easy.

## Features

- Center align a string with a custom padding character.
- Left align a string with a custom padding character.
- Right align a string with a custom padding character.
- Shuffle the characters in a string.
- String Length Calculation
- String Copy
- Check if a string is Palindrome
- Check if two strings are Anagrams
- Check if a string is a rotation of another
- ... [Any other features you add]

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
4. stringReplaceAll, stringSwapCase, stringTitleCase, stringIsEmpty

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

    
