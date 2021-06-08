#include <cs50.h>
#include <stdio.h>
int main(void)
{
    // Prompt for start size
    int startsize;
    do
    {
        startsize = get_int("Start population?\n");
    }
    while (startsize < 9);

    // Prompt for end size
    int endsize;
    do
    {
        endsize = get_int("End population?\n");
    }
    while (endsize < startsize);
    
    // Calculate number of years until we reach threshold
    int n = startsize;
    int years = 0;
    while (n < endsize)
    {
        n = n + (n / 3) - (n / 4);
        years++;
    }
    // Print number of years
    printf("Years: %i", years);
}
