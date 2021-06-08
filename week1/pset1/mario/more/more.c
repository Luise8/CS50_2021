#include <cs50.h>
#include <stdio.h>
int main(void)
{
    // Prompt user for height
    //If the height is not a positive number from 1 to 8 (including 1 and 8), go back to step one
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Iterate from 1 through height:
    //On iteration i, print i hashes and rest of spaces to complete 8 char and then a newline
    for (int startheight = 0; startheight < height; startheight++)
    {
        // print the remaining amount of characters to reach 8 in the form of spaces decreasing
        for (int j = height - 1; j > startheight; j--)
        {
            printf(" ");
        }
        for (int k = 0; k < startheight + 1; k++)
        {
            printf("#");
        }
        printf("  ");
        // Print height in form of # increasing
        for (int m = 0; m < startheight + 1; m++)
        {
            printf("#");
        }
        printf("\n");

    }
}
