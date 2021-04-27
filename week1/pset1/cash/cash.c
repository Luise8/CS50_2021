#include <cs50.h>
#include <stdio.h>
#include <math.h>
int main(void)
{
    // Prompt user for Change owed (dollars variable).
    //If the Change owed is not a positive number, go back to step one.
    //Defined variable coins what take and save number the change.
    //Defined the variable cents that take variable dollars and convert them to whole numbers.
    float dollars;
    int coins = 0;
    int cents;
    do
    {
        dollars = get_float("Change owed: ");
        cents = round(dollars * 100);
    }
    while (dollars <= 0);
    //First step with 25 cents.
    //Check if the amount given is less than 25. If it is fulfilled, subtract 25 from the cents and increase the number of coins.
    while (25 <= cents)
    {
        cents -= 25;
        coins++;
    }
    //Second step with 10 cents.
    //Check if the amount given is less than 10. If it is fulfilled, subtract 10 from the cents and increase the number of coins.
    while (10 <= cents)
    {
        cents -= 10;
        coins++;
    }
    //Third step with 5 cents.
    //Check if the amount given is less than 5. If it is fulfilled, subtract 5 from the cents and increase the number of coins.
    while (5 <= cents)
    {
        cents -= 5;
        coins++;
    }
    //Fourth step with 1 cents.
    //Check if the amount given is less than 1. If it is fulfilled, subtract 1 from the cents and increase the number of coins.
    while (1 <= cents)
    {
        cents -= 1;
        coins++;
    }

    // TODO: Print number of coins.
    printf("%i\n", coins);
}
