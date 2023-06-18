#include "String.h"

char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

bool isWhiteSpace(char c) 
{
    return c == ' ' || c == '\t' || c == '\n';
}

bool isDigit(char c) 
{
    return c >= '0' && c <= '9';
}

bool isLetter(char c) 
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isAlphaNumeric(char c) 
{
    return isDigit(c) || isLetter(c);
}

bool isUpperCase(char c) 
{
    return c >= 'A' && c <= 'Z';
}

bool isLowerCase(char c) 
{
    return c >= 'a' && c <= 'z';
}

bool isPunctuation(char c) 
{
    return c == '.' || c == ',' || c == '?' || c == '!' || c == ':' || c == ';' || c == '-';
}

bool isSpecialChar(char c) 
{
    return c == '~' || c == '`' || c == '!' || c == '@' || c == '#' || c == '$' || c == '%' || c == '^' || c == '&' || c == '*' || c == '(' || c == ')' || c == '_' || c == '+' || c == '=' || c == '{' || c == '}' || c == '[' || c == ']' || c == '|' || c == '\\' || c == ':' || c == ';' || c == '"' || c == '\'' || c == '<' || c == '>' || c == ',' || c == '.' || c == '?' || c == '/';
}

bool isVowel(char c) 
{
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

bool isConsonant(char c) 
{
    return isLetter(c) && !isVowel(c);
}

bool isPalindrome(const char *str) 
{
    int length = stringLength(str);
    const char *end = str + length - 1;
    while (end > str) 
    {
        if (*end != *str) 
        {
            return false;
        }
        end--;
        str++;
    }
    return true;
}

bool isAnagram(const char *str1, const char *str2)
{
    int length1 = stringLength(str1);
    int length2 = stringLength(str2);
    if (length1 != length2)
    {
        return false;
    }
    int *count1 = (int*)calloc(26, sizeof(int));
    int *count2 = (int*)calloc(26, sizeof(int));
    while (*str1 != '\0')
    {
        count1[*str1 - 'a']++;
        count2[*str2 - 'a']++;
        str1++;
        str2++;
    }
    for (int i = 0; i < 26; i++)
    {
        if (count1[i] != count2[i])
        {
            return false;
        }
    }
    return true;
}

bool isSubString(const char *str, const char *subStr)
{
    while (*str != '\0')
    {
        if (*str == *subStr)
        {
            const char *tempStr = str;
            const char *tempSubStr = subStr;
            while (*tempSubStr != '\0')
            {
                if (*tempStr != *tempSubStr)
                {
                    break;
                }
                tempStr++;
                tempSubStr++;
            }
            if (*tempSubStr == '\0')
            {
                return true;
            }
        }
        str++;
    }
    return false;
}

bool isRotationOfPalindrome(const char *str) 
{
    int length = stringLength(str);
    char *temp = (char*)malloc(length * 2 + 1);

    for (int i = 0; i < length; i++) 
    {
        stringCopy(temp, str + i);
        stringCopy(temp + length - i, str);

        if (isPalindrome(temp)) 
        {
            free(temp);
            return true;
        }
    }

    free(temp);
    return false;
}

bool isRotation(const char *str1, const char *str2)
{
    int length1 = stringLength(str1);
    int length2 = stringLength(str2);
    if (length1 != length2) 
    {
        return false;
    }

    char *temp = (char*)malloc(length1 * 2 + 1);
    stringCopy(temp, str1);
    stringCopy(temp + length1, str1);
    temp[length1 * 2] = '\0';
    bool result = isSubString(temp, str2);
    free(temp);
    return result;
}

bool isRotationOfAnagram(const char *str1, const char *str2) 
{
    int length1 = stringLength(str1);
    int length2 = stringLength(str2);
    if (length1 != length2) 
    {
        return false;
    }

    char *temp = (char*)malloc(length1 * 2 + 1);
    stringCopy(temp, str1);
    stringCopy(temp + length1, str1);
    temp[length1 * 2] = '\0';
    bool result = isAnagram(temp, str2);
    free(temp);
    return result;
}

bool isRotationOfSubString(const char *str1, const char *str2)
{
    int length1 = stringLength(str1);
    int length2 = stringLength(str2);
    if (length1 != length2)
    {
        return false;
    }

    char *temp = (char*)malloc(length1 * 2 + 1);
    stringCopy(temp, str1);
    stringCopy(temp + length1, str1);
    temp[length1 * 2] = '\0';
    bool result = isSubString(temp, str2);
    free(temp);
    return result;
}

bool isPrintableChar(char c) 
{
    return c >= 32 && c <= 126;
}

bool startsWithSubString(const char *str, const char *subStr)
{
    while (*subStr) 
    {
        if (*str != *subStr) 
        {
            return false;
        }
        str++;
        subStr++;
    }
    return true;
}

bool stringIsNumeric(const char *str) 
{
    while (*str) 
    {
        if (!isDigit(*str)) 
        {
            return false;
        }
        str++;
    }
    return true;
}

bool stringIsAlpha(const char *str) 
{
    while (*str) 
    {
        if (!isLetter(*str)) 
        {
            return false;
        }
        str++;
    }
    return true;
}

bool stringIsAlphaNumeric(const char *str) 
{
    while (*str) 
    {
        if (!isLetter(*str) && !isDigit(*str)) 
        {
            return false;
        }
        str++;
    }
    return true;
}

bool stringIsPrintable(const char *str) 
{
    while (*str) {
        if (!isPrintableChar(*str)) {
            return false;
        }
        str++;
    }
    return true;
}

bool stringIsTitle(const char *str) 
{
    bool newWord = true;
    while (*str) {
        if (isWhiteSpace(*str)) 
        {
            newWord = true;
        } else if (newWord && isLowerCase(*str)) 
        {
            return false;
        } 
        else if (!newWord && isUpperCase(*str)) 
        {
            return false;
        }
        newWord = false;
        str++;
    }
    return true;
}

bool stringIsWhiteSpace(const char *str) 
{
    while (*str) 
    {
        if (!isWhiteSpace(*str)) 
        {
            return false;
        }
        str++;
    }
    return true;
}

bool stringIsUpperCase(const char *str) 
{
    while (*str) 
    {
        if (!isUpperCase(*str)) 
        {
            return false;
        }
        str++;
    }
    return true;
}

bool stringIsLowerCase(const char *str) 
{
    while (*str) 
    {
        if (!isLowerCase(*str)) 
        {
            return false;
        }
        str++;
    }
    return true;
}

bool stringIsEmpty(const char *str) 
{
    // A string is considered empty if it's NULL or the first character is the null terminator
    return str == NULL || str[0] == '\0';
}

char toUpperCase(char c) 
{
    if (isLowerCase(c)) 
    {
        return c - 32;
    }
    return c;
}

char toLowerCase(char c) 
{
    if (isUpperCase(c)) 
    {
        return c + 32;
    }
    return c;
}

int stringLength(const char *str)
{
    int length = 0;
    while (*str != '\0')
    {
        length++;
        str++;
    }
    return length;
}

int stringWordCount(const char* str)
{
    int wordCount = 0;
    int inWord = 0;
    while (*str != '\0')
    {
        if (*str == ' ' || *str == '\t' || *str == '\n')
        {
            inWord = 0;
        }
        else if (inWord == 0)
        {
            inWord = 1;
            wordCount++;
        }
        str++;
    }
    return wordCount;
}

int stringDigitCount(const char* str)
{
    int digitCount = 0;
    while (*str != '\0')
    {
        if (*str >= '0' && *str <= '9')
        {
            digitCount++;
        }
        str++;
    }
    return digitCount;
}

int stringCharCount(const char* str, char c)
{
    int charCount = 0;
    while (*str != '\0')
    {
        if (*str == c)
        {
            charCount++;
        }
        str++;
    }
    return charCount;
}

int stringFindChar(const char* str, char c)
{
    int index = 0;
    while (*str != '\0')
    {
        if (*str == c)
        {
            return index;
        }
        index++;
        str++;
    }
    return -1;
}

int stringFindString(const char *str, const char *subStr)
{
    int index = 0;
    while (*str != '\0')
    {
        if (*str == *subStr)
        {
            const char *tempStr = str;
            const char *tempSubStr = subStr;
            while (*tempSubStr != '\0')
            {
                if (*tempStr != *tempSubStr)
                {
                    break;
                }
                tempStr++;
                tempSubStr++;
            }
            if (*tempSubStr == '\0')
            {
                return index;
            }
        }
        index++;
        str++;
    }
    return -1;
}

int stringCompare(const char *str1, const char *str2)
{
    while (*str1 != '\0' && *str2 != '\0')
    {
        if (*str1 != *str2)
        {
            return 0;
        }
        str1++;
        str2++;
    }
    if (*str1 == '\0' && *str2 == '\0')
    {
        return 1;
    }
    return 0;
}

char* stringCopy(char *dest, const char *src)
{
    char *temp = dest;
    while (*src != '\0')
    {
        *temp = *src;
        temp++;
        src++;
    }
    *temp = '\0';
    
    return dest; // Return the destination pointer
}

char* stringReverse(const char *str) 
{
    int length = stringLength(str);
    char *reversed = (char*)malloc(length + 1);
    char *temp = reversed;

    str = str + length - 1; // Point to the end of the input string

    while (length > 0) 
    {
        *temp = *str;
        temp++;
        str--;
        length--;
    }
    *temp = '\0';

    return reversed;
}

char* stringToUpper(const char *str)
{
    int length = stringLength(str);
    char *upper = (char*)malloc(length + 1);
    char *temp = upper;

    while (*str != '\0')
    {
        if (*str >= 'a' && *str <= 'z')
        {
            *temp = *str - 32;
        }
        else
        {
            *temp = *str;
        }
        temp++;
        str++;
    }
    *temp = '\0';

    return upper;
}

char* stringToLower(const char *str)
{
    int length = stringLength(str);
    char *lower = (char*)malloc(length + 1);
    char *temp = lower;

    while (*str != '\0')
    {
        if (*str >= 'A' && *str <= 'Z')
        {
            *temp = *str + 32;
        }
        else
        {
            *temp = *str;
        }
        temp++;
        str++;
    }
    *temp = '\0';

    return lower;
}

char* stringTrim(const char *str) 
{
    // Find the start of the trimmed string
    while (isWhiteSpace(*str)) 
    {
        str++;
    }
    
    // Find the end of the trimmed string
    const char *end = str + stringLength(str) - 1;
    while (end > str && isWhiteSpace(*end)) 
    {
        end--;
    }
    
    // Allocate memory for the trimmed string
    int trimmed_length = end - str + 1;
    char *trimmed = (char*)malloc(trimmed_length + 1);
    
    // Copy the characters
    char *temp = trimmed;
    while (str <= end) 
    {
        *temp++ = *str++;
    }
    *temp = '\0';

    return trimmed;
}

char* stringConcat(const char *str1, const char *str2)
{
    int length1 = stringLength(str1);
    int length2 = stringLength(str2);
    char *concat = (char*)malloc(length1 + length2 + 1);
    char *temp = concat;

    while (*str1 != '\0')
    {
        *temp = *str1;
        temp++;
        str1++;
    }
    while (*str2 != '\0')
    {
        *temp = *str2;
        temp++;
        str2++;
    }
    *temp = '\0';

    return concat;
}

char* stringSubString(const char *str, int start, int end)
{
    int length = stringLength(str);
    if (start < 0 || start > length || end < 0 || end > length || start > end)
    {
        return NULL;
    }
    char *subStr = (char*)malloc(end - start + 1);
    char *temp = subStr;
    str = str + start;
    while (start <= end)
    {
        *temp = *str;
        temp++;
        str++;
        start++;
    }
    *temp = '\0';

    return subStr;
}

char* stringReplace(const char *str, const char *subStr, const char *newSubStr) 
{
    int length = stringLength(str);
    int subStrLength = stringLength(subStr);
    int newSubStrLength = stringLength(newSubStr);
    int index = stringFindString(str, subStr);
    
    if (index == -1) 
    {
        return NULL;
    }

    const char *originalStr = str; // Keep track of the start of the original string

    char *replaced = (char*)malloc(length - subStrLength + newSubStrLength + 1);
    char *temp = replaced;
    
    while (*str != '\0') 
    {
        if (str == originalStr + index) 
        {
            stringCopy(temp, newSubStr);
            temp += newSubStrLength;
            str += subStrLength;
        } else 
        {
            *temp = *str;
            temp++;
            str++;
        }
    }
    
    *temp = '\0';

    return replaced;
}

char* stringRotate(const char *str, int n) 
{
    int length = stringLength(str);
    
    if (length == 0)
    {
        return NULL;
    }

    // Normalize n to be between 0 and length - 1
    n = ((n % length) + length) % length;

    char *rotated = (char*)malloc(length + 1);
    
    // Copy the last n characters
    memcpy(rotated, str + length - n, n);
    
    // Copy the first length - n characters
    memcpy(rotated + n, str, length - n);

    rotated[length] = '\0';

    return rotated;
}

char* stringRotateLeft(const char *str, int n) 
{
    int length = stringLength(str);
    
    if (length == 0) 
    {
        return NULL;
    }

    // Normalize n to be between 0 and length - 1
    n = ((n % length) + length) % length;

    char *rotated = (char*)malloc(length + 1);
    
    // Copy the substring starting from n to the end
    memcpy(rotated, str + n, length - n);
    
    // Copy the first n characters to the end of the new string
    memcpy(rotated + length - n, str, n);

    rotated[length] = '\0';

    return rotated;
}

char* stringRotateRight(const char *str, int n) 
{
    int length = stringLength(str);
    
    if (length == 0) 
    {
        return NULL;
    }

    // Normalize n to be between 0 and length - 1
    n = ((n % length) + length) % length;

    char *rotated = (char*)malloc(length + 1);
    
    // Copy the last n characters to the beginning
    memcpy(rotated, str + length - n, n);
    
    // Copy the first length - n characters to the end
    memcpy(rotated + n, str, length - n);

    rotated[length] = '\0';

    return rotated;
}


char* stringCamelCase(const char *str) 
{
    int length = stringLength(str);
    char *camelCase = (char*)malloc(length + 1);
    int i = 0, j = 0;
    int newWord = 1;

    while (i < length) 
    {
        if (isWhiteSpace(str[i])) 
        {
            newWord = 1;
        } 
        else 
        {
            if (newWord) 
            {
                camelCase[j++] = toUpperCase(str[i]);
            } 
            else 
            {
                camelCase[j++] = toLowerCase(str[i]);
            }
            newWord = 0;
        }
        i++;
    }
    camelCase[j] = '\0';
    return camelCase;
}

char* stringSnakeCase(const char *str) 
{
    int length = stringLength(str);
    char *snakeCase = (char*)malloc(length + 1);
    int i = 0, j = 0;

    while (i < length) 
    {
        if (isWhiteSpace(str[i])) 
        {
            snakeCase[j++] = '_';
        } 
        else 
        {
            snakeCase[j++] = toLowerCase(str[i]);
        }
        i++;
    }
    snakeCase[j] = '\0';
    return snakeCase;
}

char* stringPascalCase(const char *str) {
    int length = stringLength(str);
    char *pascalCase = (char*)malloc(length + 1);
    int i = 0, j = 0;
    int newWord = 1;

    while (i < length) 
    {
        if (isWhiteSpace(str[i])) 
        {
            newWord = 1;
        } 
        else 
        {
            if (newWord) 
            {
                pascalCase[j++] = toUpperCase(str[i]);
            } else 
            {
                pascalCase[j++] = toLowerCase(str[i]);
            }
            newWord = 0;
        }
        i++;
    }
    pascalCase[j] = '\0';
    return pascalCase;
}

char* stringKebabCase(const char *str) 
{
    int length = stringLength(str);
    char *kebabCase = (char*)malloc(length + 1);
    int i = 0, j = 0;

    while (i < length) 
    {
        if (isWhiteSpace(str[i])) 
        {
            kebabCase[j++] = '-';
        } 
        else 
        {
            kebabCase[j++] = toLowerCase(str[i]);
        }
        i++;
    }
    kebabCase[j] = '\0';
    return kebabCase;
}

int stringCountSubstrings(const char *str, const char *subStr) 
{
    int count = 0;
    int strLength = stringLength(str);
    int subStrLength = stringLength(subStr);
    
    for (int i = 0; i <= strLength - subStrLength; i++) 
    {
        int j;
        for (j = 0; j < subStrLength; j++) 
        {
            if (str[i + j] != subStr[j]) 
            {
                break;
            }
        }
        if (j == subStrLength)
        {
            count++;
            i += subStrLength - 1;
        }
    }
    return count;
}

char* stringInsert(const char *str, const char *subStr, int pos) 
{
    char *left = stringSubString(str, 0, pos);
    char *right = stringSubString(str, pos, stringLength(str));
    
    char *leftConcat = stringConcat(left, subStr);
    char *result = stringConcat(leftConcat, right);
    
    free(left);
    free(right);
    free(leftConcat);
    
    return result;
}

char* stringRepeat(const char *str, int times) 
{
    char *result = (char *)malloc(stringLength(str) * times + 1);
    result[0] = '\0';
    
    for (int i = 0; i < times; i++) 
    {
        char *temp = stringConcat(result, str);
        strcpy(result, temp);
        free(temp);
    }
    
    return result;
}

int stringToInteger(const char *str) 
{
    int result = 0;
    int sign = 1;
    
    if (*str == '-') 
    {
        sign = -1;
        str++;
    }
    
    while (*str) 
    {
        if (!isDigit(*str)) 
        {
            return 0; // Invalid character in the string
        }
        result = result * 10 + (*str - '0');
        str++;
    }
    
    return sign * result;
}

float stringToFloat(const char *str)
{
    float result = 0.0;
    float sign = 1.0;
    float decimalPlace = 0.1;
    bool isDecimal = false;
    
    if (*str == '-')
    {
        sign = -1.0;
        str++;
    }
    
    while (*str)
    {
        if (*str == '.')
        {
            isDecimal = true;
        }
        else if (isDigit(*str))
        {
            int digit = *str - '0';
            if (isDecimal)
            {
                result += digit * decimalPlace;
                decimalPlace /= 10.0;
            }
            else
            {
                result = result * 10.0 + digit;
            }
        }
        else
        {
            return 0.0; // Invalid character in string
        }
        str++;
    }
    
    return result * sign;
}

char* integerToString(int value)
{
    char buffer[12]; // Buffer to hold the string representation
    int i = 0;
    int sign = 1;
    
    if (value < 0)
    {
        sign = -1;
        value = -value;
    }
    
    do
    {
        buffer[i++] = (value % 10) + '0';
        value /= 10;
    } while (value > 0);
    
    if (sign < 0)
    {
        buffer[i++] = '-';
    }
    
    buffer[i] = '\0';
    
    // Reverse the buffer into the result
    char *result = (char*)malloc(i + 1);
    for (int j = 0; j < i; j++)
    {
        result[j] = buffer[i - j - 1];
    }
    result[i] = '\0';
    
    return result;
}

char* floatToString(float value, int precision)
{
    int intPart = (int)value;
    float decimalPart = value - intPart;
    
    // Convert the integer part
    char* intStr = integerToString(intPart);
    int intStrLen = stringLength(intStr);
    
    // Convert the decimal part
    char decimalStr[10];
    for (int i = 0; i < precision; i++)
    {
        decimalPart *= 10;
        decimalStr[i] = (int)decimalPart + '0';
        decimalPart -= (int)decimalPart;
    }
    decimalStr[precision] = '\0';

    // Combine both parts
    char* result = (char*)malloc(intStrLen + precision + 2);
    stringCopy(result, intStr);
    result[intStrLen] = '.';
    stringCopy(result + intStrLen + 1, decimalStr);
    
    free(intStr);
    
    return result;
}

bool stringStartsWith(const char *str, const char *prefix) 
{
    int strLength = stringLength(str);
    int prefixLength = stringLength(prefix);

    if (prefixLength > strLength) 
    {
        return false;
    }

    for (int i = 0; i < prefixLength; i++) 
    {
        if (str[i] != prefix[i]) 
        {
            return false;
        }
    }

    return true;
}

bool stringEndsWith(const char *str, const char *suffix) 
{
    int strLength = stringLength(str);
    int suffixLength = stringLength(suffix);

    if (suffixLength > strLength) 
    {
        return false;
    }

    for (int i = 0; i < suffixLength; i++) 
    {
        if (str[strLength - suffixLength + i] != suffix[i]) 
        {
            return false;
        }
    }

    return true;
}

char* stringRemove(const char *str, const char *toRemove)
{
    int strLength = stringLength(str);
    int toRemoveLength = stringLength(toRemove);
    char *result = (char*)malloc(strLength + 1);
    int j = 0;

    for (int i = 0; i < strLength;) 
    {
        bool isMatch = true;
        for (int k = 0; k < toRemoveLength; k++) 
        {
            if (str[i + k] != toRemove[k]) 
            {
                isMatch = false;
                break;
            }
        }
        
        if (isMatch) 
        {
            i += toRemoveLength;
        } 
        else 
        {
            result[j++] = str[i++];
        }
    }

    result[j] = '\0';

    return result;
}

char* stringRemoveAll(const char *str, const char *toRemove) 
{
    int strLength = stringLength(str);
    int toRemoveLength = stringLength(toRemove);

    char *result = (char*)malloc(strLength + 1);
    int j = 0, i = 0;

    while (i < strLength) 
    {
        bool isMatch = true;

        // Check if the substring to remove matches at the current position
        for (int k = 0; k < toRemoveLength; k++) 
        {
            if (str[i + k] != toRemove[k] || i + k >= strLength) 
            {
                isMatch = false;
                break;
            }
        }

        // If it matches, skip the characters in the substring to remove
        if (isMatch) 
        {
            i += toRemoveLength;
        } else 
        {
            // If it doesn't match, copy the current character to the result
            result[j++] = str[i++];
        }
    }

    // Null terminate the result string
    result[j] = '\0';

    return result;
}

char* stringCapitalize(const char *str) 
{
    int length = stringLength(str);
    char *capitalized = (char*)malloc(length + 1);
    int i = 0;
    bool newWord = true;

    while (i < length) 
    {
        if (isWhiteSpace(str[i])) 
        {
            newWord = true;
        } 
        else 
        {
            if (newWord) 
            {
                capitalized[i] = toUpperCase(str[i]);
            } 
            else 
            {
                capitalized[i] = str[i];
            }
            newWord = false;
        }
        i++;
    }
    capitalized[length] = '\0';
    return capitalized;
}

char** stringSplit(const char *str, char delimiter, int *numTokens) 
{
    int length = stringLength(str);
    *numTokens = 1;

    for (int i = 0; i < length; i++) 
    {
        if (str[i] == delimiter) 
        {
            (*numTokens)++;
        }
    }

    char **tokens = (char**)malloc((*numTokens) * sizeof(char*));
    int tokenStart = 0;
    int tokenIndex = 0;

    for (int i = 0; i <= length; i++) 
    {
        if (str[i] == delimiter || str[i] == '\0') 
        {
            int tokenLength = i - tokenStart;
            tokens[tokenIndex] = (char*)malloc(tokenLength + 1);
            for (int j = 0; j < tokenLength; j++) 
            {
                tokens[tokenIndex][j] = str[tokenStart + j];
            }
            tokens[tokenIndex][tokenLength] = '\0';
            tokenIndex++;
            tokenStart = i + 1;
        }
    }

    return tokens;
}

char* stringJoin(char **strings, int numStrings, const char *delimiter) 
{
    int delimiterLength = stringLength(delimiter);
    int totalLength = 0;

    for (int i = 0; i < numStrings; i++) 
    {
        totalLength += stringLength(strings[i]);
        if (i < numStrings - 1) 
        {
            totalLength += delimiterLength;
        }
    }

    char *joined = (char*)malloc(totalLength + 1);
    int index = 0;

    for (int i = 0; i < numStrings; i++) 
    {
        int currentLength = stringLength(strings[i]);
        stringCopy(joined + index, strings[i]);
        index += currentLength;
        if (i < numStrings - 1) 
        {
            stringCopy(joined + index, delimiter);
            index += delimiterLength;
        }
    }

    joined[totalLength] = '\0';
    return joined;
}

char* stringPaddingLeft(const char *str, char paddingChar, int totalLength) 
{
    int length = stringLength(str);
    if (length >= totalLength) 
    {
        return stringCopy((char*)malloc(length + 1), str);
    }

    char *padded = (char*)malloc(totalLength + 1);
    int padding = totalLength - length;

    for (int i = 0; i < padding; i++) 
    {
        padded[i] = paddingChar;
    }

    stringCopy(padded + padding, str);
    return padded;
}

char* stringPaddingRight(const char *str, char paddingChar, int totalLength) 
{
    int length = stringLength(str);
    if (length >= totalLength) 
    {
        return stringCopy((char*)malloc(length + 1), str);
    }

    char *padded = (char*)malloc(totalLength + 1);
    stringCopy(padded, str);

    for (int i = length; i < totalLength; i++) 
    {
        padded[i] = paddingChar;
    }

    padded[totalLength] = '\0';
    return padded;
}

char* stringTrimLeft(const char *str) 
{
    if (str == NULL) {
        return NULL;
    }

    // Find the index of the first non-whitespace character
    int startIndex = 0;
    while (str[startIndex] != '\0' && isWhiteSpace(str[startIndex])) 
    {
        startIndex++;
    }

    // Calculate the length of the new string
    int newLength = stringLength(str) - startIndex;

    // Allocate memory for the new string
    char *trimmed = (char*)malloc(newLength + 1);

    // Copy the characters after the whitespace to the new string
    stringCopy(trimmed, str + startIndex);

    return trimmed;
}

char* stringTrimRight(const char *str) 
{
    if (str == NULL) 
    {
        return NULL;
    }

    int length = stringLength(str);

    // Find the index of the last non-whitespace character
    int endIndex = length - 1;
    while (endIndex >= 0 && isWhiteSpace(str[endIndex])) 
    {
        endIndex--;
    }

    // Calculate the length of the new string
    int newLength = endIndex + 1;

    // Allocate memory for the new string
    char *trimmed = (char*)malloc(newLength + 1);

    // Copy characters up to the last non-whitespace character
    for (int i = 0; i < newLength; i++) 
    {
        trimmed[i] = str[i];
    }
    trimmed[newLength] = '\0';

    return trimmed;
}

char* stringSwapCase(const char *str) 
{
    int length = stringLength(str);
    char *result = (char *)malloc(length + 1);

    for (int i = 0; i < length; i++) 
    {
        if (isUpperCase(str[i])) 
        {
            result[i] = toLowerCase(str[i]);
        } 
        else if (isLowerCase(str[i])) 
        {
            result[i] = toUpperCase(str[i]);
        } 
        else 
        {
            result[i] = str[i];
        }
    }
    result[length] = '\0';
    return result;
}

char* stringTitleCase(const char *str) 
{
    int length = stringLength(str);
    char *result = (char *)malloc(length + 1);
    bool newWord = true;

    for (int i = 0; i < length; i++) 
    {
        // Only letters that are at the beginning of a word are capitalized
        if (newWord && isLetter(str[i])) 
        {
            result[i] = toUpperCase(str[i]);
            newWord = false;
        } 
        else if (isLetter(str[i])) 
        {
            result[i] = toLowerCase(str[i]);
        } 
        else 
        {
            result[i] = str[i];
            if (str[i] == ' ' || str[i] == '.' || str[i] == '!' || str[i] == '?') 
            {
                newWord = true;
            }
        }
    }
    result[length] = '\0';
    return result;
}

char* stringReplaceAll(const char *str, const char *oldSubStr, const char *newSubStr) 
{
    int i, count = 0;
    int newSubStrLength = stringLength(newSubStr);
    int oldSubStrLength = stringLength(oldSubStr);
    
    // Counting the number of times oldSubStr occurs in the str
    for (i = 0; str[i] != '\0'; i++) 
    {
        if (startsWithSubString(&str[i], oldSubStr)) 
        {
            count++;
            // Jumping to index after the old substring
            i += oldSubStrLength - 1;
        }
    }
    
    // Making new string of necessary length
    char *result = (char *)malloc(i + count * (newSubStrLength - oldSubStrLength) + 1);

    i = 0;
    while (*str) 
    {
        // Compare substring with oldSubStr
        if (startsWithSubString(str, oldSubStr)) 
        {
            stringCopy(&result[i], newSubStr);
            i += newSubStrLength;
            str += oldSubStrLength;
        } 
        else 
        {
            result[i++] = *str++;
        }
    }

    result[i] = '\0';
    return result;
}

char* stringCommonPrefix(const char *str1, const char *str2) 
{
    int length = 0;
    
    // Find the length of the common prefix
    while (str1[length] && str2[length] && str1[length] == str2[length]) 
    {
        length++;
    }
    
    // Create the result string
    char *commonPrefix = (char *)malloc(length + 1);
    for (int i = 0; i < length; i++) 
    {
        commonPrefix[i] = str1[i];
    }
    commonPrefix[length] = '\0';
    
    return commonPrefix;
}

char* stringCommonSuffix(const char *str1, const char *str2) 
{
    int length1 = stringLength(str1);
    int length2 = stringLength(str2);
    int commonLength = 0;
    
    // Find the length of the common suffix
    while (commonLength < length1 && commonLength < length2 &&
           str1[length1 - commonLength - 1] == str2[length2 - commonLength - 1]) 
    {
        commonLength++;
    }
    
    // Create the result string
    char *commonSuffix = (char *)malloc(commonLength + 1);
    for (int i = 0; i < commonLength; i++) 
    {
        commonSuffix[i] = str1[length1 - commonLength + i];
    }
    commonSuffix[commonLength] = '\0';
    
    return commonSuffix;
}

bool stringContains(const char *str, const char *subStr) 
{
    while (*str) 
    {
        const char *a = str;
        const char *b = subStr;
        while (*a && *b && (*a == *b)) 
        {
            a++;
            b++;
        }
        if (!*b) 
        {
            return true;
        }
        str++;
    }
    return false;
}

char* stringToBinary(const char *str) 
{
    if (str == NULL) 
    {
        return NULL;
    }

    int length = stringLength(str);
    char *binaryStr = (char *)malloc(8 * length + 1); // 8 bits per character
    binaryStr[8 * length] = '\0'; // Null-terminator

    for (int i = 0; i < length; i++) 
    {
        char c = str[i];
        for (int j = 7; j >= 0; j--) 
        {
            binaryStr[i * 8 + (7 - j)] = (c & (1 << j)) ? '1' : '0';
        }
    }
    return binaryStr;
}

char* stringFromBinary(const char *binaryStr) 
{
    if (binaryStr == NULL || strlen(binaryStr) % 8 != 0) 
    {
        return NULL;
    }

    int length = strlen(binaryStr);
    char *str = (char *)malloc(length / 8 + 1);
    str[length / 8] = '\0'; // Null-terminator

    for (int i = 0; i < length; i += 8) 
    {
        char c = 0;
        for (int j = 0; j < 8; j++) 
        {
            c = c << 1;
            c |= (binaryStr[i + j] == '1') ? 1 : 0;
        }
        str[i / 8] = c;
    }
    return str;
}

char* stringRandom(int length) 
{
    if (length <= 0) 
    {
        return NULL;
    }

    char *str = (char *)malloc(length + 1);
    str[length] = '\0'; // Null-terminator

    srand(time(NULL)); // Seed the random number generator
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    for (int i = 0; i < length; i++) 
    {
        int index = rand() % (sizeof(charset) - 1);
        str[i] = charset[index];
    }
    return str;
}

char* stringCenter(const char *str, int width, char fillChar) 
{
    if (!str || width < 0) 
    {
        return NULL;
    }

    int strLen = 0;
    while (str[strLen]) 
    {
        strLen++;
    }

    int padding = width - strLen;
    if (padding <= 0) 
    {
        char *result = (char *)malloc(strLen + 1);
        for (int i = 0; i < strLen; i++) {
            result[i] = str[i];
        }
        result[strLen] = '\0';
        return result;
    }

    int leftPadding = padding / 2;

    char *result = (char *)malloc(width + 1);
    for (int i = 0; i < width; i++) {
        result[i] = (i < leftPadding || i >= leftPadding + strLen) ? fillChar : str[i - leftPadding];
    }
    result[width] = '\0';

    return result;
}

char* stringLjust(const char *str, int width, char fillChar)
{
    if (!str || width < 0) 
    {
        return NULL;
    }

    int strLen = 0;
    while (str[strLen]) 
    {
        strLen++;
    }

    char *result = (char *)malloc(width + 1);
    for (int i = 0; i < width; i++) 
    {
        result[i] = (i < strLen) ? str[i] : fillChar;
    }
    result[width] = '\0';

    return result;
}

char* stringRjust(const char *str, int width, char fillChar) 
{
    if (!str || width < 0) 
    {
        return NULL;
    }

    int strLen = 0;
    while (str[strLen]) 
    {
        strLen++;
    }

    int padding = width - strLen;

    char *result = (char *)malloc(width + 1);
    for (int i = 0; i < width; i++) 
    {
        result[i] = (i < padding) ? fillChar : str[i - padding];
    }
    result[width] = '\0';

    return result;
}

char* stringShuffle(const char *str) 
{
    if (str == NULL) 
    {
        return NULL;
    }
    
    int strLen = stringLength(str);
    
    // Copy the original string so that we don't modify it
    char *shuffled = (char *)malloc(strLen + 1);
    stringCopy(shuffled, str);
    
    // Seed the random number generator
    srand(time(NULL));
    
    // Fisher-Yates shuffle algorithm
    for (int i = strLen - 1; i > 0; i--) 
    {
        int j = rand() % (i + 1);
        char temp = shuffled[i];
        shuffled[i] = shuffled[j];
        shuffled[j] = temp;
        
    }
    
    return shuffled;
}

char* stringToHex(const char *str) 
{
    if (!str) 
    {
        return NULL;
    }

    int length = stringLength(str);
    char *hexString = malloc(length * 2 + 1);

    for (int i = 0; i < length; i++) 
    {
        sprintf(hexString + i * 2, "%02x", (unsigned char)str[i]);
    }

    hexString[length * 2] = '\0';
    return hexString;
}

char* stringToOct(const char *str) 
{
    if (!str) 
    {
        return NULL;
    }

    int length = stringLength(str);
    char *octString = malloc(length * 4 + 1);
    char buffer[4];

    octString[0] = '\0';

    for (int i = 0; i < length; i++) 
    {
        sprintf(buffer, "%03o", (unsigned char)str[i]);
        strcat(octString, buffer);
    }

    return octString;
}

char* stringHexToBinary(const char *hexStr)
{
    if (!hexStr) 
    {
        return NULL;
    }

    const char *hexToBin[] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111",
                              "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
    
    int length = strlen(hexStr);
    char *binary = (char *) malloc(length * 4 + 1);
    binary[0] = '\0';
    
    for (int i = 0; i < length; i++) 
    {
        int value;
        if ('0' <= hexStr[i] && hexStr[i] <= '9') 
        {
            value = hexStr[i] - '0';
        } else if ('a' <= hexStr[i] && hexStr[i] <= 'f') 
        {
            value = hexStr[i] - 'a' + 10;
        } else if ('A' <= hexStr[i] && hexStr[i] <= 'F') 
        {
            value = hexStr[i] - 'A' + 10;
        } 
        else 
        {
            free(binary);
            return NULL; // Invalid character in hex string
        }
        strcat(binary, hexToBin[value]);
    }
    
    return binary;
}

char* stringOctToBinary(const char *octStr) 
{
    if (!octStr) 
    {
        return NULL;
    }

    const char *octToBin[] = {"000", "001", "010", "011", "100", "101", "110", "111"};
    
    int length = strlen(octStr);
    char *binary = (char *) malloc(length * 3 + 1);
    binary[0] = '\0';
    
    for (int i = 0; i < length; i++) 
    {
        int value;
        if ('0' <= octStr[i] && octStr[i] <= '7') 
        {
            value = octStr[i] - '0';
        } 
        else 
        {
            free(binary);
            return NULL; // Invalid character in octal string
        }
        strcat(binary, octToBin[value]);
    }
    
    return binary;
}

char* stringMap(const char *str, char (*function)(char)) 
{
    if (!str || !function) 
    {
        return NULL;
    }

    int len = stringLength(str);
    char *new_str = (char *) malloc(len + 1);
    
    for (int i = 0; i < len; i++) 
    {
        new_str[i] = function(str[i]);
    }
    
    new_str[len] = '\0';
    return new_str;
}

char* stringFilter(const char *str, bool (*condition)(char)) 
{
    if (!str || !condition) 
    {
        return NULL;
    }
    
    int len = stringLength(str);
    char *new_str = (char *) malloc(len + 1);
    
    int j = 0;
    for (int i = 0; i < len; i++) 
    {
        if (condition(str[i])) 
        {
            new_str[j++] = str[i];
        }
    }
    
    new_str[j] = '\0';
    return new_str;
}

char* stringExpandTabs(const char *str, int tabSize) 
{
    if (str == NULL || tabSize < 0) 
    {
        return NULL;
    }

    int expandedLength = 0;
    for (int i = 0; str[i] != '\0'; i++) 
    {
        if (str[i] == '\t') {
            expandedLength += tabSize;
        } else {
            expandedLength++;
        }
    }

    char *expandedStr = (char*)malloc(expandedLength + 1);
    int index = 0;

    for (int i = 0; str[i] != '\0'; i++) 
    {
        if (str[i] == '\t') {
            for (int j = 0; j < tabSize; j++) 
            {
                expandedStr[index++] = ' ';
            }
        } 
        else 
        {
            expandedStr[index++] = str[i];
        }
    }
    expandedStr[index] = '\0';
    
    return expandedStr;
}

void stringEncodeB64(const char *input, char *output) 
{
    int i, j, padding;
    uint32_t len = strlen(input);

    // Determine padding size
    padding = len % 3 == 0 ? 0 : 3 - len % 3;

    for (i = 0, j = 0; i < len; i += 3, j += 4) {
        int a = input[i];
        int b = i + 1 < len ? input[i + 1] : 0;
        int c = i + 2 < len ? input[i + 2] : 0;

        output[j] = base64_table[a >> 2];
        output[j + 1] = base64_table[((a & 3) << 4) | (b >> 4)];
        output[j + 2] = i + 1 < len ? base64_table[((b & 15) << 2) | (c >> 6)] : '=';
        output[j + 3] = i + 2 < len ? base64_table[c & 63] : '=';
    }

    output[(len + padding) / 3 * 4] = '\0';
}

void stringDecodeB64(const char *encoded, char *decoded_string) 
{
    uint32_t len_str = strlen(encoded);
    uint32_t k = 0;
    uint32_t num = 0;
    int count_bits = 0;

    for (uint32_t i = 0; i < len_str; i += 4) 
    {
        num = 0, count_bits = 0;
        for (int j = 0; j < 4; j++) {
            // Make space for 6 bits.
            if (encoded[i + j] != '=') 
            {
                num = num << 6;
                count_bits += 6;
            }

            if (encoded[i + j] >= 'A' && encoded[i + j] <= 'Z')
                num = num | (encoded[i + j] - 'A');

            else if (encoded[i + j] >= 'a' && encoded[i + j] <= 'z')
                num = num | (encoded[i + j] - 'a' + 26);

            else if (encoded[i + j] >= '0' && encoded[i + j] <= '9')
                num = num | (encoded[i + j] - '0' + 52);

            else if (encoded[i + j] == '+')
                num = num | 62;

            else if (encoded[i + j] == '/')
                num = num | 63;

            else 
            {
                num = num >> 2;
                count_bits -= 2;
            }
        }

        while (count_bits != 0) 
        {
            count_bits -= 8;
            decoded_string[k++] = (num >> count_bits) & 255;
        }
    }

    decoded_string[k] = '\0';
}

char* stringSort(const char *str) 
{
    if (str == NULL) 
    {
        return NULL;
    }
    
    int length = stringLength(str);
    
    // Allocate memory for the sorted string
    char *sortedStr = (char*) malloc(length + 1);
    
    // Copy the original string to sortedStr
    stringCopy(sortedStr, str);
    
    // Sort the characters in sortedStr using Bubble Sort
    for (int i = 0; i < length - 1; i++) 
    {
        for (int j = 0; j < length - i - 1; j++) 
        {
            if (sortedStr[j] > sortedStr[j + 1]) 
            {
                // Swap sortedStr[j] and sortedStr[j+1]
                char temp = sortedStr[j];
                sortedStr[j] = sortedStr[j + 1];
                sortedStr[j + 1] = temp;
            }
        }
    }
    
    // Null-terminate the sorted string
    sortedStr[length] = '\0';
    
    return sortedStr;
}
