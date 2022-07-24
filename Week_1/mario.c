#include <stdio.h>
#include <cs50.h>

void spaces_f(int n);
void hashes_f(int n);

int main(void)
{
    // Prompting user for their desired height of the pyramid
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Printing the pyramid in the console
    int hashes_left = 1;
    int hashes_right = 1;
    int spaces = height - 1;

    // Prints height amount of lines
    for (int x = 0; x < height; x++)
    {
        spaces_f(spaces--);
        hashes_f(hashes_left++);
        printf("  ");
        hashes_f(hashes_right++);
        printf("\n");
    }
}

// Prints spaces n number of times
void spaces_f(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" ");
    }
}
// Prints hashes n number of times
void hashes_f(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
}
