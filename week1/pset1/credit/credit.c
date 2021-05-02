#include <cs50.h>
#include <stdio.h>
int main(void)
{
    //number will save the entered number
    //regressive will be used to count the digits to lentgh, counting down to 0
    //modall will save the Mod needed to capture all digits of number
    //length will save the length of number. Example: 111 = 3
    //penultimate will save the sum of the digits interleaved by one, starting from the penultimate and multiplied by 2 and added
    //last will save the sum of the other digits
    long number;
    long regressive;
    long verification;
    int length;
    long modall;
    long penultimate;
    long last;
    do
    {
        number = get_long("Number: ");
        regressive = number;
        modall = 1;
        penultimate = 0;
        last = 0;
        // Calculate digit length and modall
        for (int i = 1; regressive > 0; i++)
        {
            regressive /= 10 - (regressive % 10 / 10);
            length = i;
            modall *= 10;
        }
        // Calculate last
        for (long i = 10; i <= modall; i *= 100)
        {
            long j = i / 10;
            last += ((number % i) - (number % j)) / j;
        }
        // Calculate penultimate
        for (long i = 100; i <= modall; i *= 100)
        {
            long j = i / 10;
            long k = ((number % i) - (number % j)) / j;
            if (k >= 5)
            {
                k = k * 2;
                int leftdig = ((k % 100) - (k % 10)) / 10;
                k = leftdig + (k % 10);
            }
            else
            {
                k = k * 2;
            }
            penultimate += k;
        }
        // Get Mod 10 from the sum of penultimate and last
        verification = (last + penultimate) % 10;
    }
    while (number <= 0);
    // Mod used to know the first two digits
    long modtwo = modall / 100;
    // Mod used to know the first  digit
    long modone = modall / 10;
    int tdigits = ((number % modall) - (number % modtwo)) / modtwo;
    int fdigit = ((number % modall) - (number % modone)) / modone;
    // TODO: Print the type of card according to the conditions of length and first two digits or just first digit.
    if (length == 15 && (tdigits == 34 || tdigits == 37) && verification == 0)
    {
        printf("AMEX\n");
    }
    else if (length == 16 && (tdigits >= 51 && tdigits <= 55) && verification == 0)
    {
        printf("MASTERCARD\n");
    }
    else if ((length == 13 || length == 16) && fdigit == 4 && verification == 0)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
