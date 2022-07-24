#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
{
    // Prompts the user for a positive value of change owed
    float dollars = 0;
    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars <= 0);
    // Rounds the change owed to cents
    int cents = round(dollars * 100);

    int coins_used = 0;
    int change_given = 0;
    int change_remaining = cents - change_given;
    // Loop for counting coins used
    for (int i = change_given; i != cents; i++)
    {
        if (change_remaining >= 25)
        {
            change_given += 25;
            coins_used++;
            change_remaining = cents - change_given;
        }
        else if (change_remaining >= 10 && change_remaining < 25)
        {
            change_given += 10;
            coins_used++;
            change_remaining = cents - change_given;
        }
        else if (change_remaining >= 5 && change_remaining < 10)
        {
            change_given += 5;
            coins_used++;
            change_remaining = cents - change_given;
        }
        else if (change_remaining >= 1 && change_remaining < 5)
        {
            change_given += 1;
            coins_used++;
            change_remaining = cents - change_given;
        }
    }
    // Prints the number of coins used to the console
    printf("%i\n", coins_used);
}
