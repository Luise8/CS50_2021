#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
// leading space markers and punctuation marks (?,!,.)
int spaces = 0;
int punctuation = 0;
int compute_letter(string text1);
int main(void)
{
    // Get input text
    string text = get_string("Text: ");
    // numbers of letters, words and sentences
    int letters = compute_letter(text);
    float words = spaces + 1;
    int sentences;
    if (punctuation == 0)
    {
        sentences = 1;
    }
    else
    {
        sentences = punctuation;
    }
    // Numbers of letters and sentences for 100 words
    float l = (letters * 100) / words;
    float s = (sentences * 100) / words;
    // Compute Grade
    int index = round((0.0588 * l) - (0.296 * s) - 15.8);
    // Print Grade
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index <= 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}
// Compute number of letters, spaces and punctuation (', ! and .), and return number of letters.
int compute_letter(string text1)
{
    int num_letter = 0;
    for (int i = 0, n = strlen(text1); i < n; i++)
    {
        if (text1[i] == '?' || text1[i] == '!' || text1[i] == '.')
        {
            punctuation++;
        }
        else if (isblank(text1[i]))
        {
            spaces++;
        }
        else if (isalpha(text1[i]))
        {
            num_letter++;
        }
    }
    return num_letter;
}
