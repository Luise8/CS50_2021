  
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
    for (int starheight = 0; starheight < height; starheight++)
    {
        // print the remaining amount of characters to reach 8 in the form of spaces decreasing
        for (int j = height - 1; j > starheight; j--)
        {
            printf(" ");
        }
        // Print height in form of # increasing
        for (int k = 0; k < starheight + 1; k++)
        {
            printf("#");
        }
        // print two spaces between hashes
        for (int l = 0; l < 1; l++)
        {
            printf("  ");
        }
        // Print height in form of # increasing
        for (int m = 0; m < starheight + 1; m++)
        {
            printf("#");
        }
        printf("\n");

    }
}
