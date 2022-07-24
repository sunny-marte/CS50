#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(int argc, string argv[])
{
    //if the user inputs more than 2 command line arguments, they will keep being reminded of the proper usage
    if (argc > 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    if (argc < 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // if the key the user inputs is not a digit, then they will keep being reminded of the proper usage
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    int key = atoi(argv[1]); //this transforms the key from a string to an integer

    if (key < 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string plaintext = get_string("plaintext: ");
    string ciphertext = plaintext;

    //this for loop iterates through each character of the string array that is plaintext, and then encrypts it
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                int ascii = plaintext[i] - 65; //this operation turns the character into an int ascii value
                int cipher = (ascii + key) % 26; //encrypts the character according to the caesar formula
                ascii = cipher + 65; //reconverts the encrypted char back to ascii
                ciphertext[i] = ascii;
            }
            if (islower(plaintext[i]))
            {
                int ascii = plaintext[i] - 97; //this operation turns the character into an int ascii value
                int cipher = (ascii + key) % 26; //encrypts the character according to the caesar formula
                ascii = cipher + 97; //reconverts the encrypted char back to ascii
                ciphertext[i] = ascii;
            }
        }
    }
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}
