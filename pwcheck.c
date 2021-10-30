/*
 *      pwcheck.c
 *  
 *      Password checking program
 *      IZP - 1st project
 * 
 *      Matyáš Strelec (xstrel03)
 *      10/2021
 */

#include <stdio.h>   // Header defining variables and functions for input / output
#include <stdlib.h>  // Header defining variables and functions for general functions, e.g. atoi()
#include <stdbool.h> // Header defining boolean types

/*
 * Check if given string contains only numbers 0-9
 */
bool IsNumber(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] < 48 || str[i] > 57)
        {
            return false;
        }
        i++;
    }
    return true;
}

/*
 * Check if given string contains a given character
 */
bool ContainsChar(char *str, char c)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == c)
        {
            return true;
        }
        i++;
    }
    return false;
}

/*
 * Return the number of characters of a given string (array of chars)
 */
int GetStringLength(char *str)
{
    int i = 0;
    while (str[i] != '\0') // Go through the array of chars until a null character (\0) comes up
    {
        i++;
    }
    return i - 1; // Return i-1 to account for newline character
}

/*
 * Compare two strings
 */

bool StringCompare(char *str1, char *str2)
{
    if (GetStringLength(str1) != GetStringLength(str2)) // If the length of both strings is not equal, they are not same
    {
        return false;
    }

    int i = 0;
    while (str1[i] != '\0') // Go through the array of chars until a null character (\0) comes up
    {
        if (str1[i] != str2[i]) // If the character on position i is not same in both string, they are not same
        {
            return false;
        }
        i++;
    }
    return true;
}

/*
 * Determine if a given string contains a lowercase letter (returns true) or doesn't (returns false)
 */

bool ContainsLowercase(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= 97 && str[i] <= 122) // Check if the decimal value of the character falls within the range of lowercase characters in ASCII
        {
            return true; // Return true if at least on lowercase letter is found
        }
        i++;
    }
    return false; // If none is found, return false
}

/*
 * Similar to ContainsLowercase(), but check for uppercase characters instead
 */
bool ContainsUppercase(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= 65 && str[i] <= 90)
        {
            return true;
        }
        i++;
    }
    return false;
}

/*
 * Similar to ContainsLowercase(), but check for numbers instead
 */
bool ContainsNumber(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= 48 && str[i] <= 57)
        {
            return true;
        }
        i++;
    }
    return false;
}

/*
 * Similar to ContainsLowercase(), but check for special characters instead
 */
bool ContainsSpecial(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if ((str[i] >= 32 && str[i] <= 47) || (str[i] >= 58 && str[i] <= 64) || (str[i] >= 91 && str[i] <= 96) || (str[i] >= 123 && str[i] <= 126))
        {
            return true;
        }
        i++;
    }
    return false;
}

/*
 * Check if the character on position pos in the string str is the same as the character on position pos-1
 */
bool CheckPrevious(char *str, int pos)
{
    if (pos == 0) // If the checked character in on index 0, there are no characters in the string in front of it, therefore there is no previous character
    {
        return false;
    }
    else if (str[pos] == str[pos - 1])
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
 * Check if a given string contains a sequence of same characters long at least prm long
 */
bool DoesntContainSequence(char *str, int prm)
{
    int maxSequenceLength = 0; // Store the length of the longest sequence of same characters in given string

    for (int i = 1; i < GetStringLength(str); i++) // For loop which goes through all characters of string, starting at index 1 (2nd character)
    {
        int thisSequenceLength = 1; // Store the length of the sequence of same characters for the current pass of the string
        int j = i;
        while (CheckPrevious(str, j)) // Go backwards from the current character in string, check if the previous character is the same
        {
            thisSequenceLength++; // For every pass, count the length of the current sequence
            j--;
        }

        if (thisSequenceLength > maxSequenceLength) // If the current sequence is longer than the one currently stored, replace it with the current one
        {
            maxSequenceLength = thisSequenceLength;
        }
    }

    return (maxSequenceLength < prm); // If the longest sequence maxSequenceLength in given string is shorter than prm, return true as the condition is fullfiled
}

/*
 * Check if a given string contains two same substrings at least prm characters long
 */
bool DoesntContainSubstring(char *str, int prm)
{
    for (int i = 0; str[i] != '\0'; i++) // Go through every character in the string
    {
        for (int j = i + 1; str[j] != '\0'; j++) // For every character in string, check the remaining characters
        {
            bool currentSubstring = true; // Store if current substring contains a subsequence

            for (int k = 0; k < prm; k++) // Compare two substrings, first starting at i, second at j, separated by k characters, at least prm number of passes
            {
                if (str[i + k] != str[j + k])
                {
                    currentSubstring = false;
                    break;
                }
            }

            if (currentSubstring)
            {
                return false;
            }
        }
    }
    return true; // If no substring longer than prm were found, return true as the condition was met
}

/*
 * Check the password str according to the security criteria specified by lvl (level) and prm (param) arguments
 */
bool CheckPassword(char *str, int lvl, int prm) //
{
    switch (lvl)
    {
    /*
     * Security level 1
     * Password contains at least one lowercase and uppercase letter
     */
    case 1:
        return (ContainsLowercase(str) && ContainsUppercase(str)); // Checks for validity of both conditions at once
        break;
    /*
     * Security level 2
     * Password contains characters from at least prm categories
     * Level 1 is also met
     */
    case 2:
        /*
         * If the condition is met, value of the ContainsX() function is true == 1. If at least prm conditions are met, returns true
         * In case when prm is bigger than 4, assume prm is 4 anyway
         */
        if (prm > 4)
        {
            return ((CheckPassword(str, 1, prm)) && (ContainsLowercase(str) + ContainsUppercase(str) + ContainsNumber(str) + ContainsSpecial(str) >= 4));
        }
        else
        {
            return ((CheckPassword(str, 1, prm)) && (ContainsLowercase(str) + ContainsUppercase(str) + ContainsNumber(str) + ContainsSpecial(str) >= prm));
        }
        break;
    /*
     * Security level 3
     * Password doesn't contain a sequence of same characters longer than prm
     * Levels 1 and 2 are also met
     */
    case 3:
        return ((CheckPassword(str, 2, prm)) && (DoesntContainSequence(str, prm)));
        break;
    /*
     * Security level 4
     * Password doesn't contain two same substrings longer than prm
     * Levels 1, 2, and 3 are also met
     */
    case 4:
        return ((CheckPassword(str, 3, prm)) && (DoesntContainSubstring(str, prm)));
        break;
    default:
        return false;
        break;
    }
}

int main(int argc, char *argv[])
{
    int maxLength = 102;   // Maximal length of one password is 100 characters, plus 2 characters to account for \n and \0
    char heslo[maxLength]; // Array of characters to temporarily store the password that is worked with

    int lvl = 1;
    int prm = 1;
    bool printStats = false;

    if (argc < 3 || argc > 4) // 2 or 3 arguments are expected
    {
        fprintf(stderr, "Chyba: neplatny pocet argumentu.\n");
        return -1;
    }

    if (IsNumber(argv[1])) // If parameter consists of numbers only
    {
        lvl = atoi(argv[1]); // Lvl integer stores security level, argv[] arguments are read as strings,the atoi() function converts them to integers
    }
    else
    {
        fprintf(stderr, "Chyba: level musi byt cele cislo v intervalu 1 - 4.\n");
        return -1;
    }

    if (IsNumber(argv[2])) // If parameter consists of numbers only
    {
        prm = atoi(argv[2]); // Prm integer stores the additional parameter
    }
    else
    {
        fprintf(stderr, "Chyba: param musi byt cele cislo v intervalu 1 - 4.\n");
        return -1;
    }

    if (lvl < 1 || lvl > 4) // Lvl arguement is expected to be a whole number in interval 1-4
    {
        fprintf(stderr, "Chyba: level musi byt cele cislo v intervalu 1 - 4.\n");
        if (prm < 1) // Prm arguement is expected to be a whole number bigger than 1
        {
            fprintf(stderr, "Chyba: param musi byt kladne cele cislo.\n");
        }
        return -1;
    }

    if (prm < 1) // Prm arguement is expected to be a whole number bigger than 1
    {
        fprintf(stderr, "Chyba: param musi byt kladne cele cislo.\n");
        return -1;
    }

    if (argc == 4 && StringCompare(argv[3], "--stats")) // If there are 3 arguements and the 3rd one is "--stats", print the statistics at the end of the program
    {
        printStats = true;
    }
    if (argc == 4 && !StringCompare(argv[3], "--stats"))
    {
        fprintf(stderr, "Chyba: treti argument je neplatny.\n");
        return -1;
    }

    // Store values for statistics
    int numberOfPasswords = 0;
    bool uniqueCharacters[256] = {false};
    int numberOfUniqueCharacters = 0;
    int minimalLength = 100;
    float lengthOfAll = 0;
    float averageLength = 0;

    while (fgets(heslo, maxLength, stdin)) // Go through all the passwords, line by line
    {
        numberOfPasswords++; // For every pass, raise the number of passwords

        if (!ContainsChar(heslo, '\n')) // If fgets didn't write a newline character, it means it read more than maximum length of password
        {
            fprintf(stderr, "Chyba: maximalni delka hesla je 100 znaku.\n");
            return -1;
        }

        /*
         * To store all unique characters, an array of booleans is used. If the password contains a character, the boolean on its ASCII position is marked true
         */
        for (int i = 0; heslo[i] != '\0' && heslo[i] != '\n'; i++)
        {
            uniqueCharacters[(int)heslo[i]] = true;
        }

        if (GetStringLength(heslo) < minimalLength) // Store the shortest password
        {
            minimalLength = GetStringLength(heslo);
        }

        lengthOfAll += GetStringLength(heslo); //  Add to the length of all characters

        if (CheckPassword(heslo, lvl, prm)) // Check the password by the specified criteria
        {
            printf("%s", heslo); // If conditions are met, print out the password
        }
    }

    for (int i = 0; i < 256; i++) // Count the unique characters by adding up all true values in the array
    {
        numberOfUniqueCharacters += uniqueCharacters[i];
    }

    averageLength = (lengthOfAll / numberOfPasswords); // Get the average length of all passwords

    if (printStats) // Prints the statistics at the end if enabled
    {
        printf("Statistika:\n");
        printf("Ruznych znaku: %d\n", numberOfUniqueCharacters);
        printf("Minimalni delka: %d\n", minimalLength);
        printf("Prumerna delka: %.1f\n", averageLength); // Average length is rounded up to one decimal point
    }

    return 0;
}