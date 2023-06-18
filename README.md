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
1.This example demonstrates how to use the stringRotateLeft function to rotate the characters in a string to the left by a certain number of positions:

    ```c++
    const char *original = "abcdefg";
    char *rotated = stringRotateLeft(original, 2);
    
    if (rotated) 
    {
        printf("Original string: %s\n", original);
        printf("Rotated string (left by 2): %s\n", rotated);
        free(rotated);
    }
    ```

    
