#include "String.h"

#include <limits.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

typedef enum
{
    ALIGN_LEFT,
    ALIGN_CENTER,
    ALIGN_RIGHT
} Alignment;

static const char base64Table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const char hexDigits[] = "0123456789abcdef";
static const char *const hexToBin[] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111",
                                       "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};

static char *allocString(size_t length)
{
    char *result = malloc(length + 1);
    if (result)
    {
        result[length] = '\0';
    }
    return result;
}

static char *copyRange(const char *src, size_t length)
{
    char *result = allocString(length);
    if (result)
    {
        memcpy(result, src, length);
    }
    return result;
}

static char *copyOf(const char *str)
{
    return str ? copyRange(str, strlen(str)) : NULL;
}

static void seedRandomOnce(void)
{
    static bool seeded = false;
    if (!seeded)
    {
        srand((unsigned int)time(NULL));
        seeded = true;
    }
}

static bool isWordSeparator(char c)
{
    return isWhiteSpace(c) || c == '_' || c == '-';
}

static bool isTitleBoundary(char c)
{
    return isWhiteSpace(c) || c == '.' || c == '!' || c == '?';
}

static bool containsChar(const char *set, char c)
{
    return c != '\0' && strchr(set, c) != NULL;
}

static bool allChars(const char *str, bool (*predicate)(char))
{
    if (!str || *str == '\0')
    {
        return false;
    }
    for (; *str; str++)
    {
        if (!predicate(*str))
        {
            return false;
        }
    }
    return true;
}

static bool onlyCase(const char *str, bool (*wanted)(char), bool (*unwanted)(char))
{
    if (!str)
    {
        return false;
    }
    bool found = false;
    for (; *str; str++)
    {
        if (unwanted(*str))
        {
            return false;
        }
        found = found || wanted(*str);
    }
    return found;
}

static bool containedInDoubled(const char *str, const char *subStr)
{
    size_t length = strlen(str);
    char *doubled = allocString(length * 2);
    if (!doubled)
    {
        return false;
    }
    memcpy(doubled, str, length);
    memcpy(doubled + length, str, length);
    bool found = strstr(doubled, subStr) != NULL;
    free(doubled);
    return found;
}

static char *trimSides(const char *str, bool left, bool right)
{
    if (!str)
    {
        return NULL;
    }
    const char *start = str;
    const char *end = str + strlen(str);
    while (left && start < end && isWhiteSpace(*start))
    {
        start++;
    }
    while (right && end > start && isWhiteSpace(end[-1]))
    {
        end--;
    }
    return copyRange(start, (size_t)(end - start));
}

static char *rotate(const char *str, long long shiftRight)
{
    if (!str)
    {
        return NULL;
    }
    size_t length = strlen(str);
    char *rotated = allocString(length);
    if (!rotated || length == 0)
    {
        return rotated;
    }
    long long size = (long long)length;
    size_t shift = (size_t)(((shiftRight % size) + size) % size);
    memcpy(rotated, str + length - shift, shift);
    memcpy(rotated + shift, str, length - shift);
    return rotated;
}

static char *convertCase(const char *str, char separator, bool upperFirstWord, bool upperOtherWords)
{
    if (!str)
    {
        return NULL;
    }
    char *result = allocString(strlen(str));
    if (!result)
    {
        return NULL;
    }
    size_t length = 0;
    size_t words = 0;
    while (*str)
    {
        while (*str && isWordSeparator(*str))
        {
            str++;
        }
        if (*str == '\0')
        {
            break;
        }
        if (words > 0 && separator != '\0')
        {
            result[length++] = separator;
        }
        bool upper = words == 0 ? upperFirstWord : upperOtherWords;
        result[length++] = upper ? toUpperCase(*str) : toLowerCase(*str);
        str++;
        while (*str && !isWordSeparator(*str))
        {
            result[length++] = toLowerCase(*str++);
        }
        words++;
    }
    result[length] = '\0';
    return result;
}

static char *replaceOccurrences(const char *str, const char *oldSubStr, const char *newSubStr, bool all)
{
    if (!str || !oldSubStr || !newSubStr)
    {
        return NULL;
    }
    size_t oldLength = strlen(oldSubStr);
    if (oldLength == 0)
    {
        return copyOf(str);
    }
    size_t newLength = strlen(newSubStr);
    size_t count = 0;
    for (const char *match = strstr(str, oldSubStr); match; match = all ? strstr(match + oldLength, oldSubStr) : NULL)
    {
        count++;
    }
    char *result = allocString(strlen(str) - count * oldLength + count * newLength);
    if (!result)
    {
        return NULL;
    }
    char *out = result;
    const char *cursor = str;
    for (size_t i = 0; i < count; i++)
    {
        const char *match = strstr(cursor, oldSubStr);
        size_t prefixLength = (size_t)(match - cursor);
        memcpy(out, cursor, prefixLength);
        memcpy(out + prefixLength, newSubStr, newLength);
        out += prefixLength + newLength;
        cursor = match + oldLength;
    }
    strcpy(out, cursor);
    return result;
}

static char *pad(const char *str, int width, char fillChar, Alignment alignment)
{
    if (!str)
    {
        return NULL;
    }
    size_t length = strlen(str);
    if (width < 0 || (size_t)width <= length)
    {
        return copyOf(str);
    }
    size_t padding = (size_t)width - length;
    size_t left = alignment == ALIGN_LEFT ? 0 : alignment == ALIGN_RIGHT ? padding : padding / 2;
    char *result = allocString((size_t)width);
    if (result)
    {
        memset(result, fillChar, (size_t)width);
        memcpy(result + left, str, length);
    }
    return result;
}

static char *digitsToBinary(const char *digits, int base)
{
    if (!digits)
    {
        return NULL;
    }
    size_t bitsPerDigit = base == 16 ? 4 : 3;
    size_t length = strlen(digits);
    char *binary = allocString(length * bitsPerDigit);
    if (!binary)
    {
        return NULL;
    }
    for (size_t i = 0; i < length; i++)
    {
        char c = toLowerCase(digits[i]);
        const char *position = containsChar(hexDigits, c) ? strchr(hexDigits, c) : NULL;
        int value = position ? (int)(position - hexDigits) : base;
        if (value >= base)
        {
            free(binary);
            return NULL;
        }
        memcpy(binary + i * bitsPerDigit, hexToBin[value] + 4 - bitsPerDigit, bitsPerDigit);
    }
    return binary;
}

static size_t expandTabsInto(const char *str, size_t tabSize, char *out)
{
    size_t length = 0;
    size_t column = 0;
    for (; *str; str++)
    {
        if (*str == '\t')
        {
            size_t spaces = tabSize > 0 ? tabSize - column % tabSize : 0;
            if (out)
            {
                memset(out + length, ' ', spaces);
            }
            length += spaces;
            column += spaces;
        }
        else
        {
            if (out)
            {
                out[length] = *str;
            }
            length++;
            column = (*str == '\n' || *str == '\r') ? 0 : column + 1;
        }
    }
    return length;
}

static int base64Value(char c)
{
    if (isUpperCase(c))
    {
        return c - 'A';
    }
    if (isLowerCase(c))
    {
        return c - 'a' + 26;
    }
    if (isDigit(c))
    {
        return c - '0' + 52;
    }
    if (c == '+')
    {
        return 62;
    }
    return c == '/' ? 63 : -1;
}

static char swapCase(char c)
{
    return isUpperCase(c) ? toLowerCase(c) : toUpperCase(c);
}

bool isWhiteSpace(char c)
{
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f';
}

bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}

bool isLetter(char c)
{
    return isUpperCase(c) || isLowerCase(c);
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
    return containsChar(".,?!:;-", c);
}

bool isSpecialChar(char c)
{
    return containsChar("~`!@#$%^&*()_+={}[]|\\:;\"'<>,.?/", c);
}

bool isVowel(char c)
{
    return containsChar("aeiouAEIOU", c);
}

bool isConsonant(char c)
{
    return isLetter(c) && !isVowel(c);
}

bool isPrintableChar(char c)
{
    return c >= 32 && c <= 126;
}

bool isPalindrome(const char *str)
{
    if (!str)
    {
        return false;
    }
    size_t length = strlen(str);
    for (size_t i = 0; i < length / 2; i++)
    {
        if (str[i] != str[length - 1 - i])
        {
            return false;
        }
    }
    return true;
}

bool isAnagram(const char *str1, const char *str2)
{
    if (!str1 || !str2 || strlen(str1) != strlen(str2))
    {
        return false;
    }
    int counts[UCHAR_MAX + 1] = {0};
    for (; *str1; str1++, str2++)
    {
        counts[(unsigned char)*str1]++;
        counts[(unsigned char)*str2]--;
    }
    for (int i = 0; i <= UCHAR_MAX; i++)
    {
        if (counts[i] != 0)
        {
            return false;
        }
    }
    return true;
}

bool isSubString(const char *str, const char *subStr)
{
    return str && subStr && strstr(str, subStr) != NULL;
}

bool isRotation(const char *str1, const char *str2)
{
    return str1 && str2 && strlen(str1) == strlen(str2) && containedInDoubled(str1, str2);
}

bool isRotationOfPalindrome(const char *str)
{
    if (!str)
    {
        return false;
    }
    size_t length = strlen(str);
    if (length == 0)
    {
        return true;
    }
    for (size_t shift = 0; shift < length; shift++)
    {
        bool palindrome = true;
        for (size_t i = 0; i < length / 2 && palindrome; i++)
        {
            palindrome = str[(shift + i) % length] == str[(shift + length - 1 - i) % length];
        }
        if (palindrome)
        {
            return true;
        }
    }
    return false;
}

bool isRotationOfAnagram(const char *str1, const char *str2)
{
    return isAnagram(str1, str2);
}

bool isRotationOfSubString(const char *str1, const char *str2)
{
    return str1 && str2 && strlen(str2) <= strlen(str1) && containedInDoubled(str1, str2);
}

bool startsWithSubString(const char *str, const char *subStr)
{
    return stringStartsWith(str, subStr);
}

bool stringIsNumeric(const char *str)
{
    return allChars(str, isDigit);
}

bool stringIsAlpha(const char *str)
{
    return allChars(str, isLetter);
}

bool stringIsAlphaNumeric(const char *str)
{
    return allChars(str, isAlphaNumeric);
}

bool stringIsPrintable(const char *str)
{
    return str && (*str == '\0' || allChars(str, isPrintableChar));
}

bool stringIsTitle(const char *str)
{
    if (!str)
    {
        return false;
    }
    bool atWordStart = true;
    bool hasLetter = false;
    for (; *str; str++)
    {
        if (isLetter(*str))
        {
            if (atWordStart ? !isUpperCase(*str) : !isLowerCase(*str))
            {
                return false;
            }
            atWordStart = false;
            hasLetter = true;
        }
        else if (isTitleBoundary(*str))
        {
            atWordStart = true;
        }
    }
    return hasLetter;
}

bool stringIsWhiteSpace(const char *str)
{
    return allChars(str, isWhiteSpace);
}

bool stringIsUpperCase(const char *str)
{
    return onlyCase(str, isUpperCase, isLowerCase);
}

bool stringIsLowerCase(const char *str)
{
    return onlyCase(str, isLowerCase, isUpperCase);
}

bool stringIsEmpty(const char *str)
{
    return str == NULL || str[0] == '\0';
}

bool stringStartsWith(const char *str, const char *prefix)
{
    return str && prefix && strncmp(str, prefix, strlen(prefix)) == 0;
}

bool stringEndsWith(const char *str, const char *suffix)
{
    if (!str || !suffix)
    {
        return false;
    }
    size_t length = strlen(str);
    size_t suffixLength = strlen(suffix);
    return suffixLength <= length && memcmp(str + length - suffixLength, suffix, suffixLength) == 0;
}

bool stringContains(const char *str, const char *subStr)
{
    return isSubString(str, subStr);
}

int stringLength(const char *str)
{
    return str ? (int)strlen(str) : 0;
}

int stringWordCount(const char *str)
{
    int count = 0;
    bool inWord = false;
    for (; str && *str; str++)
    {
        if (isWhiteSpace(*str))
        {
            inWord = false;
        }
        else if (!inWord)
        {
            inWord = true;
            count++;
        }
    }
    return count;
}

int stringDigitCount(const char *str)
{
    int count = 0;
    for (; str && *str; str++)
    {
        count += isDigit(*str);
    }
    return count;
}

int stringCharCount(const char *str, char c)
{
    int count = 0;
    for (; str && *str; str++)
    {
        count += *str == c;
    }
    return count;
}

int stringFindChar(const char *str, char c)
{
    const char *found = (str && c != '\0') ? strchr(str, c) : NULL;
    return found ? (int)(found - str) : -1;
}

int stringFindString(const char *str, const char *subStr)
{
    const char *found = (str && subStr) ? strstr(str, subStr) : NULL;
    return found ? (int)(found - str) : -1;
}

int stringCountSubstrings(const char *str, const char *subStr)
{
    if (!str || !subStr || *subStr == '\0')
    {
        return 0;
    }
    size_t subLength = strlen(subStr);
    int count = 0;
    for (const char *match = strstr(str, subStr); match; match = strstr(match + subLength, subStr))
    {
        count++;
    }
    return count;
}

int stringToInteger(const char *str)
{
    if (!str)
    {
        return 0;
    }
    int sign = 1;
    if (*str == '-' || *str == '+')
    {
        sign = *str == '-' ? -1 : 1;
        str++;
    }
    if (*str == '\0')
    {
        return 0;
    }
    long long value = 0;
    for (; *str; str++)
    {
        if (!isDigit(*str))
        {
            return 0;
        }
        if (value <= (long long)INT_MAX + 1)
        {
            value = value * 10 + (*str - '0');
        }
    }
    value *= sign;
    if (value > INT_MAX)
    {
        return INT_MAX;
    }
    return value < INT_MIN ? INT_MIN : (int)value;
}

int stringCompare(const char *str1, const char *str2)
{
    return str1 && str2 && strcmp(str1, str2) == 0;
}

float stringToFloat(const char *str)
{
    if (!str)
    {
        return 0.0f;
    }
    double sign = 1.0;
    if (*str == '-' || *str == '+')
    {
        sign = *str == '-' ? -1.0 : 1.0;
        str++;
    }
    double result = 0.0;
    double scale = 1.0;
    bool seenDot = false;
    bool seenDigit = false;
    for (; *str; str++)
    {
        if (*str == '.' && !seenDot)
        {
            seenDot = true;
        }
        else if (isDigit(*str))
        {
            seenDigit = true;
            if (seenDot)
            {
                scale /= 10.0;
                result += (*str - '0') * scale;
            }
            else
            {
                result = result * 10.0 + (*str - '0');
            }
        }
        else
        {
            return 0.0f;
        }
    }
    return seenDigit ? (float)(sign * result) : 0.0f;
}

char toUpperCase(char c)
{
    return isLowerCase(c) ? (char)(c - 'a' + 'A') : c;
}

char toLowerCase(char c)
{
    return isUpperCase(c) ? (char)(c - 'A' + 'a') : c;
}

char *stringCopy(char *dest, const char *src)
{
    if (dest && src)
    {
        strcpy(dest, src);
    }
    return dest;
}

char *stringReverse(const char *str)
{
    if (!str)
    {
        return NULL;
    }
    size_t length = strlen(str);
    char *reversed = allocString(length);
    for (size_t i = 0; reversed && i < length; i++)
    {
        reversed[i] = str[length - 1 - i];
    }
    return reversed;
}

char *stringToUpper(const char *str)
{
    return stringMap(str, toUpperCase);
}

char *stringToLower(const char *str)
{
    return stringMap(str, toLowerCase);
}

char *stringTrim(const char *str)
{
    return trimSides(str, true, true);
}

char *stringTrimLeft(const char *str)
{
    return trimSides(str, true, false);
}

char *stringTrimRight(const char *str)
{
    return trimSides(str, false, true);
}

char *stringConcat(const char *str1, const char *str2)
{
    if (!str1 || !str2)
    {
        return NULL;
    }
    size_t length1 = strlen(str1);
    size_t length2 = strlen(str2);
    char *result = allocString(length1 + length2);
    if (result)
    {
        memcpy(result, str1, length1);
        memcpy(result + length1, str2, length2);
    }
    return result;
}

char *stringSubString(const char *str, int start, int end)
{
    if (!str || start < 0 || end < start)
    {
        return NULL;
    }
    size_t length = strlen(str);
    if ((size_t)start > length)
    {
        return NULL;
    }
    size_t last = (size_t)end < length ? (size_t)end + 1 : length;
    return copyRange(str + start, last - (size_t)start);
}

char *stringReplace(const char *str, const char *subStr, const char *newSubStr)
{
    return replaceOccurrences(str, subStr, newSubStr, false);
}

char *stringReplaceAll(const char *str, const char *oldSubStr, const char *newSubStr)
{
    return replaceOccurrences(str, oldSubStr, newSubStr, true);
}

char *stringRemove(const char *str, const char *toRemove)
{
    return replaceOccurrences(str, toRemove, "", false);
}

char *stringRemoveAll(const char *str, const char *toRemove)
{
    return replaceOccurrences(str, toRemove, "", true);
}

char *stringRotate(const char *str, int n)
{
    return rotate(str, n);
}

char *stringRotateLeft(const char *str, int n)
{
    return rotate(str, -(long long)n);
}

char *stringRotateRight(const char *str, int n)
{
    return rotate(str, n);
}

char *stringCamelCase(const char *str)
{
    return convertCase(str, '\0', false, true);
}

char *stringPascalCase(const char *str)
{
    return convertCase(str, '\0', true, true);
}

char *stringSnakeCase(const char *str)
{
    return convertCase(str, '_', false, false);
}

char *stringKebabCase(const char *str)
{
    return convertCase(str, '-', false, false);
}

char *stringInsert(const char *str, const char *subStr, int pos)
{
    if (!str || !subStr || pos < 0 || (size_t)pos > strlen(str))
    {
        return NULL;
    }
    size_t length = strlen(str);
    size_t subLength = strlen(subStr);
    char *result = allocString(length + subLength);
    if (result)
    {
        memcpy(result, str, (size_t)pos);
        memcpy(result + pos, subStr, subLength);
        memcpy(result + pos + subLength, str + pos, length - (size_t)pos);
    }
    return result;
}

char *stringRepeat(const char *str, int times)
{
    if (!str)
    {
        return NULL;
    }
    size_t length = strlen(str);
    size_t count = times > 0 ? (size_t)times : 0;
    if (length > 0 && count > (SIZE_MAX - 1) / length)
    {
        return NULL;
    }
    char *result = allocString(length * count);
    for (size_t i = 0; result && i < count; i++)
    {
        memcpy(result + i * length, str, length);
    }
    return result;
}

char *integerToString(int value)
{
    char buffer[16];
    snprintf(buffer, sizeof buffer, "%d", value);
    return copyOf(buffer);
}

char *floatToString(float value, int precision)
{
    if (precision < 0)
    {
        precision = 0;
    }
    int length = snprintf(NULL, 0, "%.*f", precision, (double)value);
    if (length < 0)
    {
        return NULL;
    }
    char *result = allocString((size_t)length);
    if (result)
    {
        snprintf(result, (size_t)length + 1, "%.*f", precision, (double)value);
    }
    return result;
}

char *stringCapitalize(const char *str)
{
    char *result = copyOf(str);
    bool atWordStart = true;
    for (char *c = result; c && *c; c++)
    {
        if (isWhiteSpace(*c))
        {
            atWordStart = true;
        }
        else
        {
            if (atWordStart)
            {
                *c = toUpperCase(*c);
            }
            atWordStart = false;
        }
    }
    return result;
}

char **stringSplit(const char *str, char delimiter, int *numTokens)
{
    if (numTokens)
    {
        *numTokens = 0;
    }
    if (!str || !numTokens)
    {
        return NULL;
    }
    int count = stringCharCount(str, delimiter) + 1;
    char **tokens = malloc((size_t)count * sizeof *tokens);
    if (!tokens)
    {
        return NULL;
    }
    const char *start = str;
    for (int i = 0; i < count; i++)
    {
        const char *end = strchr(start, delimiter);
        if (!end)
        {
            end = start + strlen(start);
        }
        tokens[i] = copyRange(start, (size_t)(end - start));
        if (!tokens[i])
        {
            while (i-- > 0)
            {
                free(tokens[i]);
            }
            free(tokens);
            return NULL;
        }
        start = end + 1;
    }
    *numTokens = count;
    return tokens;
}

char *stringJoin(char **strings, int numStrings, const char *delimiter)
{
    if (!strings || numStrings < 0)
    {
        return NULL;
    }
    const char *separator = delimiter ? delimiter : "";
    size_t separatorLength = strlen(separator);
    size_t total = 0;
    for (int i = 0; i < numStrings; i++)
    {
        total += (strings[i] ? strlen(strings[i]) : 0) + (i > 0 ? separatorLength : 0);
    }
    char *joined = allocString(total);
    if (!joined)
    {
        return NULL;
    }
    char *out = joined;
    for (int i = 0; i < numStrings; i++)
    {
        if (i > 0)
        {
            memcpy(out, separator, separatorLength);
            out += separatorLength;
        }
        if (strings[i])
        {
            size_t length = strlen(strings[i]);
            memcpy(out, strings[i], length);
            out += length;
        }
    }
    return joined;
}

char *stringPaddingLeft(const char *str, char paddingChar, int totalLength)
{
    return pad(str, totalLength, paddingChar, ALIGN_RIGHT);
}

char *stringPaddingRight(const char *str, char paddingChar, int totalLength)
{
    return pad(str, totalLength, paddingChar, ALIGN_LEFT);
}

char *stringCenter(const char *str, int width, char fillChar)
{
    return pad(str, width, fillChar, ALIGN_CENTER);
}

char *stringLjust(const char *str, int width, char fillChar)
{
    return pad(str, width, fillChar, ALIGN_LEFT);
}

char *stringRjust(const char *str, int width, char fillChar)
{
    return pad(str, width, fillChar, ALIGN_RIGHT);
}

char *stringSwapCase(const char *str)
{
    return stringMap(str, swapCase);
}

char *stringTitleCase(const char *str)
{
    char *result = copyOf(str);
    bool atWordStart = true;
    for (char *c = result; c && *c; c++)
    {
        if (isLetter(*c))
        {
            *c = atWordStart ? toUpperCase(*c) : toLowerCase(*c);
            atWordStart = false;
        }
        else if (isTitleBoundary(*c))
        {
            atWordStart = true;
        }
    }
    return result;
}

char *stringCommonPrefix(const char *str1, const char *str2)
{
    if (!str1 || !str2)
    {
        return NULL;
    }
    size_t length = 0;
    while (str1[length] && str1[length] == str2[length])
    {
        length++;
    }
    return copyRange(str1, length);
}

char *stringCommonSuffix(const char *str1, const char *str2)
{
    if (!str1 || !str2)
    {
        return NULL;
    }
    size_t length1 = strlen(str1);
    size_t length2 = strlen(str2);
    size_t common = 0;
    while (common < length1 && common < length2 && str1[length1 - 1 - common] == str2[length2 - 1 - common])
    {
        common++;
    }
    return copyRange(str1 + length1 - common, common);
}

char *stringToBinary(const char *str)
{
    if (!str)
    {
        return NULL;
    }
    size_t length = strlen(str);
    char *binary = allocString(length * 8);
    for (size_t i = 0; binary && i < length; i++)
    {
        unsigned char c = (unsigned char)str[i];
        for (int bit = 0; bit < 8; bit++)
        {
            binary[i * 8 + (size_t)bit] = (c & (0x80 >> bit)) ? '1' : '0';
        }
    }
    return binary;
}

char *stringFromBinary(const char *binaryStr)
{
    if (!binaryStr || strlen(binaryStr) % 8 != 0 || binaryStr[strspn(binaryStr, "01")] != '\0')
    {
        return NULL;
    }
    size_t length = strlen(binaryStr) / 8;
    char *str = allocString(length);
    for (size_t i = 0; str && i < length; i++)
    {
        unsigned char c = 0;
        for (int bit = 0; bit < 8; bit++)
        {
            c = (unsigned char)((c << 1) | (binaryStr[i * 8 + (size_t)bit] == '1'));
        }
        str[i] = (char)c;
    }
    return str;
}

char *stringRandom(int length)
{
    if (length < 0)
    {
        return NULL;
    }
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    seedRandomOnce();
    char *str = allocString((size_t)length);
    for (int i = 0; str && i < length; i++)
    {
        str[i] = charset[rand() % (int)(sizeof charset - 1)];
    }
    return str;
}

char *stringShuffle(const char *str)
{
    char *shuffled = copyOf(str);
    if (!shuffled)
    {
        return NULL;
    }
    seedRandomOnce();
    for (size_t i = strlen(shuffled); i > 1; i--)
    {
        size_t j = (size_t)rand() % i;
        char temp = shuffled[i - 1];
        shuffled[i - 1] = shuffled[j];
        shuffled[j] = temp;
    }
    return shuffled;
}

char *stringToHex(const char *str)
{
    if (!str)
    {
        return NULL;
    }
    size_t length = strlen(str);
    char *hex = allocString(length * 2);
    for (size_t i = 0; hex && i < length; i++)
    {
        unsigned char c = (unsigned char)str[i];
        hex[i * 2] = hexDigits[c >> 4];
        hex[i * 2 + 1] = hexDigits[c & 0x0F];
    }
    return hex;
}

char *stringToOct(const char *str)
{
    if (!str)
    {
        return NULL;
    }
    size_t length = strlen(str);
    char *oct = allocString(length * 3);
    for (size_t i = 0; oct && i < length; i++)
    {
        unsigned char c = (unsigned char)str[i];
        oct[i * 3] = (char)('0' + (c >> 6));
        oct[i * 3 + 1] = (char)('0' + ((c >> 3) & 7));
        oct[i * 3 + 2] = (char)('0' + (c & 7));
    }
    return oct;
}

char *stringHexToBinary(const char *hexStr)
{
    return digitsToBinary(hexStr, 16);
}

char *stringOctToBinary(const char *octStr)
{
    return digitsToBinary(octStr, 8);
}

char *stringMap(const char *str, char (*function)(char))
{
    if (!str || !function)
    {
        return NULL;
    }
    size_t length = strlen(str);
    char *mapped = allocString(length);
    for (size_t i = 0; mapped && i < length; i++)
    {
        mapped[i] = function(str[i]);
    }
    return mapped;
}

char *stringFilter(const char *str, bool (*function)(char))
{
    if (!str || !function)
    {
        return NULL;
    }
    char *filtered = allocString(strlen(str));
    if (!filtered)
    {
        return NULL;
    }
    size_t length = 0;
    for (; *str; str++)
    {
        if (function(*str))
        {
            filtered[length++] = *str;
        }
    }
    filtered[length] = '\0';
    return filtered;
}

char *stringExpandTabs(const char *str, int tabSize)
{
    if (!str || tabSize < 0)
    {
        return NULL;
    }
    char *expanded = allocString(expandTabsInto(str, (size_t)tabSize, NULL));
    if (expanded)
    {
        expandTabsInto(str, (size_t)tabSize, expanded);
    }
    return expanded;
}

char *stringSort(const char *str)
{
    if (!str)
    {
        return NULL;
    }
    size_t counts[UCHAR_MAX + 1] = {0};
    size_t length = 0;
    for (const unsigned char *c = (const unsigned char *)str; *c; c++, length++)
    {
        counts[*c]++;
    }
    char *sorted = allocString(length);
    size_t index = 0;
    for (int c = 1; sorted && c <= UCHAR_MAX; c++)
    {
        memset(sorted + index, c, counts[c]);
        index += counts[c];
    }
    return sorted;
}

void stringEncodeB64(const char *input, char *output)
{
    if (!input || !output)
    {
        return;
    }
    const unsigned char *bytes = (const unsigned char *)input;
    size_t length = strlen(input);
    size_t out = 0;
    for (size_t i = 0; i < length; i += 3)
    {
        unsigned long triple = (unsigned long)bytes[i] << 16;
        triple |= i + 1 < length ? (unsigned long)bytes[i + 1] << 8 : 0;
        triple |= i + 2 < length ? (unsigned long)bytes[i + 2] : 0;
        output[out++] = base64Table[(triple >> 18) & 63];
        output[out++] = base64Table[(triple >> 12) & 63];
        output[out++] = i + 1 < length ? base64Table[(triple >> 6) & 63] : '=';
        output[out++] = i + 2 < length ? base64Table[triple & 63] : '=';
    }
    output[out] = '\0';
}

void stringDecodeB64(const char *encoded, char *decoded_string)
{
    if (!encoded || !decoded_string)
    {
        return;
    }
    unsigned long buffer = 0;
    int bits = 0;
    size_t length = 0;
    for (; *encoded && *encoded != '='; encoded++)
    {
        int value = base64Value(*encoded);
        if (value < 0)
        {
            continue;
        }
        buffer = ((buffer << 6) | (unsigned long)value) & 0xFFFFFF;
        bits += 6;
        if (bits >= 8)
        {
            bits -= 8;
            decoded_string[length++] = (char)((buffer >> bits) & 0xFF);
        }
    }
    decoded_string[length] = '\0';
}
