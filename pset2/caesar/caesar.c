#include <cs50.h>
#include <stdio.h>

//Your program must accept a single command-line argument, a non-negative integer.
int main(int argv, char* argc[])
{
    //If no args or more than 1 arg, printf somme error, return 1
    if(argv != 2)
    {
        printf("Error must include only 1 argument, some non-negative int.\n");
        return 1;
    }
    printf("\n%s\n",argc[0]);
    // output plaintext: (without a newline) and then prompt the user for a string of plaintext (using get_string).

    // must preserve case:

    // output ciphertext: (without a newline) followed by the plaintext’s corresponding ciphertext,

    // After outputting ciphertext, you should print a newline.

    return 0; //default
}