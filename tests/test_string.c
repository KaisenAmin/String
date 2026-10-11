#include "../String.h"

#include <limits.h>
#include <math.h>
#include <string.h>

static int checks = 0;
static int failures = 0;

#define CHECK(condition) check((condition), #condition, __LINE__)
#define CHECK_OWNED(actual, expected) checkOwned((actual), (expected), #actual, __LINE__)

static void check(bool ok, const char *expression, int line)
{
    checks++;
    if (!ok)
    {
        failures++;
        printf("FAIL line %d: %s\n", line, expression);
    }
}

static void checkOwned(char *actual, const char *expected, const char *expression, int line)
{
    bool ok = (actual == NULL && expected == NULL) || (actual && expected && strcmp(actual, expected) == 0);
    checks++;
    if (!ok)
    {
        failures++;
        printf("FAIL line %d: %s -> \"%s\", expected \"%s\"\n", line, expression,
               actual ? actual : "(null)", expected ? expected : "(null)");
    }
    free(actual);
}

static char upperChar(char c)
{
    return toUpperCase(c);
}

static bool vowelChar(char c)
{
    return isVowel(c);
}

static void testCharacterClasses(void)
{
    CHECK(isWhiteSpace(' ') && isWhiteSpace('\t') && isWhiteSpace('\n') && isWhiteSpace('\r'));
    CHECK(!isWhiteSpace('a'));
    CHECK(isDigit('0') && isDigit('9') && !isDigit('a'));
    CHECK(isLetter('a') && isLetter('Z') && !isLetter('1'));
    CHECK(isAlphaNumeric('a') && isAlphaNumeric('5') && !isAlphaNumeric('_'));
    CHECK(isUpperCase('A') && !isUpperCase('a'));
    CHECK(isLowerCase('a') && !isLowerCase('A'));
    CHECK(isPunctuation('.') && isPunctuation('-') && !isPunctuation('a') && !isPunctuation('\0'));
    CHECK(isSpecialChar('~') && isSpecialChar('\\') && !isSpecialChar('a') && !isSpecialChar('\0'));
    CHECK(isVowel('a') && isVowel('E') && !isVowel('b') && !isVowel('\0'));
    CHECK(isConsonant('f') && isConsonant('B') && !isConsonant('A') && !isConsonant('1'));
    CHECK(isPrintableChar('a') && !isPrintableChar('\n'));
    CHECK(toUpperCase('a') == 'A' && toUpperCase('A') == 'A' && toUpperCase('1') == '1');
    CHECK(toLowerCase('A') == 'a' && toLowerCase('a') == 'a' && toLowerCase('!') == '!');
}

static void testPredicates(void)
{
    CHECK(isPalindrome("abba") && isPalindrome("aba") && isPalindrome("") && !isPalindrome("abbd"));
    CHECK(isAnagram("abbd", "dbba") && isAnagram("Listen!", "!netsiL") && !isAnagram("abc", "abd"));
    CHECK(!isAnagram("abc", "ab") && isAnagram("", ""));
    CHECK(isSubString("Hello World", "World") && !isSubString("Hello", "Hello0"));
    CHECK(isRotation("Hello", "lloHe") && !isRotation("Hello", "olleH") && !isRotation("ab", "abc"));
    CHECK(isRotationOfPalindrome("abba") && isRotationOfPalindrome("aab") && !isRotationOfPalindrome("abc"));
    CHECK(isRotationOfAnagram("abc", "cab") && !isRotationOfAnagram("abc", "abd"));
    CHECK(isRotationOfSubString("abcde", "deab") && isRotationOfSubString("abcde", "cdeab"));
    CHECK(!isRotationOfSubString("abcde", "ace") && !isRotationOfSubString("ab", "abc"));
    CHECK(startsWithSubString("prefix-body", "prefix") && !startsWithSubString("pre", "prefix"));
    CHECK(stringStartsWith("hello", "he") && stringStartsWith("hello", "") && !stringStartsWith("he", "hello"));
    CHECK(stringEndsWith("hello", "llo") && !stringEndsWith("hello", "he") && !stringEndsWith("lo", "hello"));
    CHECK(stringContains("hello world", "o w") && !stringContains("hello", "z"));
    CHECK(stringIsNumeric("12345") && !stringIsNumeric("12a") && !stringIsNumeric(""));
    CHECK(stringIsAlpha("abcXYZ") && !stringIsAlpha("abc1"));
    CHECK(stringIsAlphaNumeric("abc123") && !stringIsAlphaNumeric("abc 123"));
    CHECK(stringIsPrintable("Hello, World!") && stringIsPrintable("") && !stringIsPrintable("a\tb"));
    CHECK(stringIsTitle("Hello World") && stringIsTitle("Hello. World") && !stringIsTitle("Hello world"));
    CHECK(!stringIsTitle("HEllo") && !stringIsTitle("") && !stringIsTitle("123"));
    CHECK(stringIsWhiteSpace(" \t\n") && !stringIsWhiteSpace(" a ") && !stringIsWhiteSpace(""));
    CHECK(stringIsUpperCase("HELLO WORLD 1") && !stringIsUpperCase("Hello") && !stringIsUpperCase("123"));
    CHECK(stringIsLowerCase("hello world 1") && !stringIsLowerCase("hEllo") && !stringIsLowerCase(""));
    CHECK(stringIsEmpty("") && stringIsEmpty(NULL) && !stringIsEmpty(" "));
}

static void testCounting(void)
{
    const char *name = "   Hello W156orld\nam36in";
    CHECK(stringLength(name) == 24 && stringLength("") == 0 && stringLength(NULL) == 0);
    CHECK(stringWordCount(name) == 3 && stringWordCount("   ") == 0 && stringWordCount("one") == 1);
    CHECK(stringDigitCount(name) == 5);
    CHECK(stringCharCount(name, '6') == 2 && stringCharCount(name, 'z') == 0);
    CHECK(stringFindChar(name, 'W') == 9 && stringFindChar(name, 'z') == -1 && stringFindChar(name, '\0') == -1);
    CHECK(stringFindString(name, "W156") == 9 && stringFindString(name, "nope") == -1);
    CHECK(stringCountSubstrings("hello world, hello!", "hello") == 2);
    CHECK(stringCountSubstrings("aaaa", "aa") == 2 && stringCountSubstrings("abc", "") == 0);
    CHECK(stringCompare("abc", "abc") == 1 && stringCompare("abc", "abd") == 0 && stringCompare("ab", "abc") == 0);
}

static void testNumberConversions(void)
{
    CHECK(stringToInteger("-12345") == -12345 && stringToInteger("+42") == 42 && stringToInteger("0") == 0);
    CHECK(stringToInteger("12a") == 0 && stringToInteger("") == 0 && stringToInteger("-") == 0);
    CHECK(stringToInteger("2147483647") == INT_MAX && stringToInteger("-2147483648") == INT_MIN);
    CHECK(stringToInteger("99999999999999999999") == INT_MAX);
    CHECK(fabsf(stringToFloat("3.14159") - 3.14159f) < 1e-6f);
    CHECK(fabsf(stringToFloat("-0.5") + 0.5f) < 1e-6f && stringToFloat("1.2.3") == 0.0f && stringToFloat(".") == 0.0f);
    CHECK_OWNED(integerToString(-12345), "-12345");
    CHECK_OWNED(integerToString(0), "0");
    CHECK_OWNED(integerToString(INT_MIN), "-2147483648");
    CHECK_OWNED(floatToString(3.1415926535f, 6), "3.141593");
    CHECK_OWNED(floatToString(-0.25f, 2), "-0.25");
    CHECK_OWNED(floatToString(2.75f, 0), "3");
    CHECK_OWNED(floatToString(1.5f, 12), "1.500000000000");
}

static void testTransformations(void)
{
    char buffer[32];
    CHECK(stringCopy(buffer, "copy me") == buffer && strcmp(buffer, "copy me") == 0);
    CHECK_OWNED(stringReverse("abcdef"), "fedcba");
    CHECK_OWNED(stringReverse(""), "");
    CHECK_OWNED(stringToUpper("Hello, World 1"), "HELLO, WORLD 1");
    CHECK_OWNED(stringToLower("Hello, World 1"), "hello, world 1");
    CHECK_OWNED(stringTrim("  \t hello world \n "), "hello world");
    CHECK_OWNED(stringTrim("    "), "");
    CHECK_OWNED(stringTrimLeft("    Hello, World!"), "Hello, World!");
    CHECK_OWNED(stringTrimRight("Goodbye, World!    "), "Goodbye, World!");
    CHECK_OWNED(stringConcat("foo", "bar"), "foobar");
    CHECK_OWNED(stringSubString("hello", 1, 3), "ell");
    CHECK_OWNED(stringSubString("hello", 0, 10), "hello");
    CHECK_OWNED(stringSubString("hello", 5, 5), "");
    CHECK_OWNED(stringSubString("hello", 3, 1), NULL);
    CHECK_OWNED(stringSubString("hello", 6, 7), NULL);
    CHECK_OWNED(stringReplace("one two one", "one", "1"), "1 two one");
    CHECK_OWNED(stringReplace("abc", "x", "y"), "abc");
    CHECK_OWNED(stringReplace("abc", "", "y"), "abc");
    CHECK_OWNED(stringReplaceAll("This is an example", "is", "IS"), "ThIS IS an example");
    CHECK_OWNED(stringReplaceAll("aaa", "a", "bb"), "bbbbbb");
    CHECK_OWNED(stringReplaceAll("abc", "", "x"), "abc");
    CHECK_OWNED(stringRemove("one two one", "one"), " two one");
    CHECK_OWNED(stringRemoveAll("one two one", "one"), " two ");
    CHECK_OWNED(stringRemoveAll("abc", ""), "abc");
    CHECK_OWNED(stringRotateLeft("abcdefg", 2), "cdefgab");
    CHECK_OWNED(stringRotateRight("abcdefg", 2), "fgabcde");
    CHECK_OWNED(stringRotate("abcdefg", -9), "cdefgab");
    CHECK_OWNED(stringRotate("", 3), "");
    CHECK_OWNED(stringRotateLeft("abc", INT_MIN), "bca");
    CHECK_OWNED(stringInsert("hello world, hello!", "INSERTED ", 6), "hello INSERTED world, hello!");
    CHECK_OWNED(stringInsert("abc", "X", 3), "abcX");
    CHECK_OWNED(stringInsert("abc", "X", 4), NULL);
    CHECK_OWNED(stringRepeat("hello", 3), "hellohellohello");
    CHECK_OWNED(stringRepeat("hello", 0), "");
    CHECK_OWNED(stringRepeat("hello", -2), "");
    CHECK_OWNED(stringSwapCase("ThIs Is a TeSt 1"), "tHiS iS A tEsT 1");
    CHECK_OWNED(stringTitleCase("this is a TITLE case. example!"), "This Is A Title Case. Example!");
    CHECK_OWNED(stringCapitalize("hello world! this is an example string."), "Hello World! This Is An Example String.");
    CHECK_OWNED(stringCapitalize("  two  spaces"), "  Two  Spaces");
    CHECK_OWNED(stringCommonPrefix("interstellar", "internet"), "inter");
    CHECK_OWNED(stringCommonPrefix("abc", "xyz"), "");
    CHECK_OWNED(stringCommonSuffix("walking", "talking"), "alking");
    CHECK_OWNED(stringCommonSuffix("abc", "xyz"), "");
    CHECK_OWNED(stringSort("bd156caef"), "156abcdef");
    CHECK_OWNED(stringSort(""), "");
}

static void testCaseStyles(void)
{
    const char *sentence = "this is a sample string";
    CHECK_OWNED(stringCamelCase(sentence), "thisIsASampleString");
    CHECK_OWNED(stringPascalCase(sentence), "ThisIsASampleString");
    CHECK_OWNED(stringSnakeCase(sentence), "this_is_a_sample_string");
    CHECK_OWNED(stringKebabCase(sentence), "this-is-a-sample-string");
    CHECK_OWNED(stringCamelCase("  Hello   WORLD  "), "helloWorld");
    CHECK_OWNED(stringSnakeCase("  Hello   World-wide  "), "hello_world_wide");
    CHECK_OWNED(stringKebabCase("snake_case_input"), "snake-case-input");
    CHECK_OWNED(stringPascalCase(""), "");
}

static void testAlignment(void)
{
    CHECK_OWNED(stringCenter("hello", 20, '-'), "-------hello--------");
    CHECK_OWNED(stringLjust("hello", 10, '-'), "hello-----");
    CHECK_OWNED(stringRjust("hello", 10, '-'), "-----hello");
    CHECK_OWNED(stringLjust("hello", 3, '-'), "hello");
    CHECK_OWNED(stringRjust("hello", 3, '-'), "hello");
    CHECK_OWNED(stringCenter("hello", -1, '-'), "hello");
    CHECK_OWNED(stringPaddingLeft("42", '0', 5), "00042");
    CHECK_OWNED(stringPaddingRight("42", '.', 5), "42...");
    CHECK_OWNED(stringPaddingLeft("12345", '0', 3), "12345");
    CHECK_OWNED(stringExpandTabs("This\tis\ta\tstring", 8), "This    is      a       string");
    CHECK_OWNED(stringExpandTabs("a\tb\nab\tc", 4), "a   b\nab  c");
    CHECK_OWNED(stringExpandTabs("a\tb", 0), "ab");
    CHECK_OWNED(stringExpandTabs("a\tb", -1), NULL);
}

static void testSplitJoin(void)
{
    int count = -1;
    char **tokens = stringSplit("apple,banana,,grape", ',', &count);
    CHECK(tokens != NULL && count == 4);
    if (tokens && count == 4)
    {
        CHECK(strcmp(tokens[0], "apple") == 0 && strcmp(tokens[1], "banana") == 0);
        CHECK(strcmp(tokens[2], "") == 0 && strcmp(tokens[3], "grape") == 0);
    }
    for (int i = 0; tokens && i < count; i++)
    {
        free(tokens[i]);
    }
    free(tokens);

    tokens = stringSplit("single", ',', &count);
    CHECK(tokens != NULL && count == 1 && strcmp(tokens[0], "single") == 0);
    free(tokens[0]);
    free(tokens);

    char *parts[] = {"This", "is", "a", "joined", "string"};
    CHECK_OWNED(stringJoin(parts, 5, " "), "This is a joined string");
    CHECK_OWNED(stringJoin(parts, 1, ", "), "This");
    CHECK_OWNED(stringJoin(parts, 0, ", "), "");
}

static void testEncodings(void)
{
    char *binary = stringToBinary("AB");
    CHECK(binary && strcmp(binary, "0100000101000010") == 0);
    CHECK_OWNED(stringFromBinary(binary), "AB");
    free(binary);
    CHECK_OWNED(stringToBinary("\xff"), "11111111");
    CHECK_OWNED(stringFromBinary("0100000"), NULL);
    CHECK_OWNED(stringFromBinary("0100000x"), NULL);
    CHECK_OWNED(stringToHex("Hello"), "48656c6c6f");
    CHECK_OWNED(stringToHex("\xff"), "ff");
    CHECK_OWNED(stringToOct("Hello"), "110145154154157");
    CHECK_OWNED(stringHexToBinary("1A3f"), "0001101000111111");
    CHECK_OWNED(stringHexToBinary("1G"), NULL);
    CHECK_OWNED(stringOctToBinary("1507"), "001101000111");
    CHECK_OWNED(stringOctToBinary("18"), NULL);

    const char *samples[] = {"", "f", "fo", "foo", "foob", "fooba", "foobar", "Hello, World!", "\xff\xfe\x80"};
    const char *expected[] = {"", "Zg==", "Zm8=", "Zm9v", "Zm9vYg==", "Zm9vYmE=", "Zm9vYmFy", "SGVsbG8sIFdvcmxkIQ==", "//6A"};
    for (size_t i = 0; i < sizeof samples / sizeof samples[0]; i++)
    {
        char encoded[64];
        char decoded[64];
        stringEncodeB64(samples[i], encoded);
        stringDecodeB64(encoded, decoded);
        CHECK(strcmp(encoded, expected[i]) == 0);
        CHECK(strcmp(decoded, samples[i]) == 0);
    }
}

static void testFunctional(void)
{
    CHECK_OWNED(stringMap("hello", upperChar), "HELLO");
    CHECK_OWNED(stringFilter("hello world", vowelChar), "eoo");
    CHECK_OWNED(stringMap(NULL, upperChar), NULL);
    CHECK_OWNED(stringFilter("abc", NULL), NULL);
}

static void testRandomness(void)
{
    char *randomString = stringRandom(32);
    CHECK(randomString && strlen(randomString) == 32 && stringIsAlphaNumeric(randomString));
    free(randomString);
    CHECK_OWNED(stringRandom(0), "");
    CHECK_OWNED(stringRandom(-1), NULL);

    const char *original = "hello world";
    char *shuffled = stringShuffle(original);
    CHECK(shuffled && isAnagram(original, shuffled));
    free(shuffled);
    CHECK_OWNED(stringShuffle(""), "");
}

int main(void)
{
    testCharacterClasses();
    testPredicates();
    testCounting();
    testNumberConversions();
    testTransformations();
    testCaseStyles();
    testAlignment();
    testSplitJoin();
    testEncodings();
    testFunctional();
    testRandomness();
    printf("%d checks, %d failures\n", checks, failures);
    return failures == 0 ? 0 : 1;
}
