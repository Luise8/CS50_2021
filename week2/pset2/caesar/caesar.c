#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int check_only_digits(string digits);
int main(int argc, string argv[])
{
    // Check that only one argument was entered as the key
    int check_two;
    int key; // variable that will be used for the future conversion of the string to int of the key
    if (argc == 2)
    {
        // Start the next verification by entering the key in the single digit verification function
        check_two = check_only_digits(argv[1]);
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // Check that all key are digits. In this case, start converting string to int of key 
    if (check_two == 0)
    {
        key = atoi(argv[1]);
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // Get text to cipher
    string plaintext = get_string("plaintext: ");
    int ciphertext;
    int k = key % 26; // Key convert into 26 range (a-z)
    // Converts plain text to cipher text and print
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        ciphertext = plaintext[i] + k;
        // This case is aplicate when plaintext is a lower case letter and it is out of range when the key is added to it
        if (islower(plaintext[i]) && ciphertext > 122)
        {
            int difference = ((plaintext[i] + key) - 122) % 26;
            ciphertext = 96 + difference;
            printf("%c", ciphertext);
        }
        // This case is aplicate when plaintext is a capital letter and it is out of range when the key is added to it
        else if (isupper(plaintext[i]) && ciphertext > 90)
        {
            int difference = ((plaintext[i] + key) - 90) % 26;
            ciphertext = 64 + difference;
            printf("%c", ciphertext);
        }
        // This case is aplicate when plaintext is an any letter, but when the key is added it is still within the range (uppercase or lowercase)
        else if (isalpha(plaintext[i]))
        {
            printf("%c", ciphertext);
        }
        // This case is aplicate when plaintext is not a letter
        else
        {
            ciphertext = plaintext[i];
            printf("%c", ciphertext);
        }
    }
    printf("\n");
    return 0;

}
// Check that all key are digits and return 0 if is true
int check_only_digits(string digits)
{
    int check = strlen(digits);
    for (int i = 0, n = strlen(digits); i < n; i++)
    {
        if (isdigit(digits[i]))
        {
            check--;
            
        }
        else
        {
            check++;
        }
    }
    return check;
}
