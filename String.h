#ifndef STRING_H_
#define STRING_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

bool isWhiteSpace(char c);
bool isDigit(char c);
bool isLetter(char c);
bool isAlphaNumeric(char c);
bool isUpperCase(char c);
bool isLowerCase(char c);
bool isPunctuation(char c);
bool isSpecialChar(char c);
bool isVowel(char c);
bool isConsonant(char c);
bool isPalindrome(const char *str);
bool isAnagram(const char *str1, const char *str2);
bool isSubString(const char *str, const char *subStr);
bool isRotation(const char *str1, const char *str2);
bool isRotationOfPalindrome(const char *str);
bool isRotationOfAnagram(const char *str1, const char *str2);
bool isRotationOfSubString(const char *str1, const char *str2);
bool isPrintableChar(char c);
bool startsWithSubString(const char *str, const char *subStr);
bool stringIsNumeric(const char *str);
bool stringIsAlpha(const char *str);
bool stringIsAlphaNumeric(const char *str);
bool stringIsPrintable(const char *str);
bool stringIsTitle(const char *str);
bool stringIsWhiteSpace(const char *str);
bool stringIsUpperCase(const char *str);
bool stringIsLowerCase(const char *str);
bool stringIsEmpty(const char *str);
bool stringStartsWith(const char *str, const char *prefix);
bool stringEndsWith(const char *str, const char *suffix);
bool stringContains(const char *str, const char *subStr);

int stringLength(const char *str);
int stringWordCount(const char *str);
int stringDigitCount(const char *str);
int stringCharCount(const char *str, char c);
int stringFindChar(const char *str, char c);
int stringFindString(const char *str, const char *subStr);
int stringCountSubstrings(const char *str, const char *subStr);
int stringToInteger(const char *str);
int stringCompare(const char *str1, const char *str2);
float stringToFloat(const char *str);

char toUpperCase(char c);
char toLowerCase(char c);

char* stringCopy(char *dest, const char *src);
char* stringReverse(const char *str);
char* stringToUpper(const char *str);
char* stringToLower(const char *str);
char* stringTrim(const char *str);
char* stringConcat(const char *str1, const char *str2);
char* stringSubString(const char *str, int start, int end);
char* stringReplace(const char *str, const char *subStr, const char *newSubStr);
char* stringRotate(const char *str, int n);
char* stringRotateLeft(const char *str, int n);
char* stringRotateRight(const char *str, int n);
char* stringCamelCase(const char *str);
char* stringSnakeCase(const char *str);
char* stringPascalCase(const char *str);
char* stringKebabCase(const char *str);
char* stringInsert(const char *str, const char *subStr, int pos);
char* stringRepeat(const char *str, int times);
char* integerToString(int value);
char* floatToString(float value, int precision);
char* stringRemove(const char *str, const char *toRemove);
char* stringRemoveAll(const char *str, const char *toRemove);
char* stringCapitalize(const char *str);
char* stringJoin(char **strings, int numStrings, const char *delimiter);
char* stringPaddingLeft(const char *str, char paddingChar, int totalLength);
char* stringPaddingRight(const char *str, char paddingChar, int totalLength);
char* stringTrimLeft(const char *str);
char* stringTrimRight(const char *str);
char* stringSwapCase(const char *str);
char* stringTitleCase(const char *str);
char* stringReplaceAll(const char *str, const char *oldSubStr, const char *newSubStr);
char* stringCommonPrefix(const char *str1, const char *str2);
char* stringCommonSuffix(const char *str1, const char *str2);
char* stringToBinary(const char *str);
char* stringFromBinary(const char *binaryStr);
char* stringRandom(int length);
char* stringCenter(const char *str, int width, char fillChar);
char* stringLjust(const char *str, int width, char fillChar);
char* stringRjust(const char *str, int width, char fillChar);
char* stringShuffle(const char *str);
char* stringToHex(const char *str); 
char* stringToOct(const char *str);
char* stringHexToBinary(const char *hexStr);
char* stringOctToBinary(const char *octStr);
char* stringMap(const char *str, char (*function)(char));
char* stringFilter(const char *str, bool (*function)(char));
char* stringExpandTabs(const char *str, int tabSize);
char* stringSort(const char *str);

char** stringSplit(const char *str, char delimiter, int *numTokens);

void stringEncodeB64(const char *input, char *output);
void stringDecodeB64(const char *encoded, char *decoded_string);

#endif 