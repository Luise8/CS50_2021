#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
int check_only_letters(string letters1);
int check_complete_alphabet(string letters2);
string key_tolower(string key_all);
string encryptor(string message, string key);
int main(int argc, string argv[])
{
    // Check that only one argument was entered as the key
    int check_two;
    int check_three;
    string key; // variable that will be used for the future  
    if (argc == 2)
    {
        // Start the next verification by entering the key in the single letter verification function
        check_two = check_only_letters(argv[1]);
        check_three = check_complete_alphabet(argv[1]);
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // Check that all key (in lower) is letters. In this case, assign the argv[1] in lowercase to key variable  
    if (check_two == 0 && check_three == 2847) // 2847 is value alphabet in lower. 
    {
        key = key_tolower(argv[1]);
    }
    else
    {
        printf("The key must contain 26 different alphabetic characters\n");
        return 1;
    }
    // Get text to cipher
    string plaintext = get_string("plaintext: ");
    // Converts plain text to cipher text and print
    string ciphertext = encryptor(plaintext, key); 
    // Print ciphertext
    printf("ciphertext: ");
    printf("%s\n", ciphertext);
    return 0;

}
// Check that all key are letters and return 0 if is true
int check_only_letters(string letters1)
{
    int check1 = strlen(letters1);
    for (int i = 0, n = strlen(letters1); i < n; i++)
    {
        if (isalpha(letters1[i]))
        {
            check1--;
            
        }
        else
        {
            check1++;
        }
    }
    return check1;
}
// Check that key contain 26 different alphabetic characters (a-z). Return 2847 (value of all letters in lowercase)
int check_complete_alphabet(string letters2)
{
    int check2 = 0;
    for (int i = 0, n = 26; i < n; i++)
    {
        check2 += tolower(letters2[i]); //Convert all letters in lowercase for a more easy calculate.
    }
    return check2;
}
// Convert all letters of key in lowercase for a more easy process afterword
string key_tolower(string key_all)
{
    string key_lower = key_all;
    for (int i = 0, n = 26; i < n; i++)
    {
        key_lower[i] = tolower(key_all[i]); 
    }
    return key_lower;
}
// Message encryptor
string encryptor(string message, string key)
{
    string encrypted_message = message;
    for (int i = 0, n = strlen(message); i < n; i++)
    {
        if (islower(message[i]))
        {
            int k = message[i] - 97; // Number of the letter of message in the key lowercase
            encrypted_message[i] = key[k]; // Substitution of the letter of the message by the letter of the key
        }
        else if (isupper(message[i]))
        {
            int k = message[i] - 65; // Number of the letter of message in the key for upper
            encrypted_message[i] = toupper(key[k]); 
        }
        else
        {
            encrypted_message[i] = message[i]; // In case of a non-alphabetic character
        }
    } 
    return encrypted_message;
}
