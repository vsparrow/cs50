#include <cs50.h>
#include <stdio.h>
#include <string.h>

//Your program must accept a single command-line argument, a non-negative integer.
int main(int argv, char *argc[])
{
    //If no args or more than 1 arg, printf somme error, return 1
    if (argv != 2)
    {
        printf("Usage: ./caesar k");
        return 1;
    }
    //convert the input character into an integer
    int key = atoi(argc[1]);
    //mod key by 26
    key = key % 26;

    //*****************************************************************************************
    // output plaintext: (without a newline) and then prompt the user for a string of plaintext (using get_string).
    // must preserve case:
    char *plaintext = get_string("plaintext:");
    int length = (int)strlen(plaintext);
    int i = 0;
    // output ciphertext: (without a newline) followed by the plaintext’s corresponding ciphertext
    printf("ciphertext: ");
    for (i = 0; i < length; i++)
    {
        int cipherint = plaintext[i];
        int zvalue = 0;
        int avalue = 0;
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
        {
            cipherint = plaintext[i] + key;
            zvalue = 122;
            avalue = 96;
            if (cipherint > 122) //greater than z, over flow
            {
                cipherint = cipherint - zvalue + avalue;
            }
        }
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
        {
            cipherint = plaintext[i] + key;
            zvalue = 90;
            avalue = 65;
            if (cipherint > 90) //greater than z, over flow
            {
                cipherint = cipherint - zvalue + avalue;
            }
        }
        printf("%c", cipherint);
    }
    //*****************************************************************************************

    // After outputting ciphertext, you should print a newline.
    printf("\n");
    return 0; //default
}