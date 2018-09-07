#include <cs50.h>
#include <stdio.h>
#include <string.h>

//Your program must accept a single command-line argument, a non-negative integer.
int main(int argv, char* argc[])
{
    //If no args or more than 1 arg, printf somme error, return 1
    if(argv != 2)
    {
        printf("Error must include only 1 argument, some non-negative int.\n");
        return 1;
    }
    printf("%s\n",argc[1]);
    //convert the input character into an integer
    int key = atoi(argc[1]);
    //mod key by 26
    key = key % 26;
    printf("\nkey is: %i\n",key);
    // output plaintext: (without a newline) and then prompt the user for a string of plaintext (using get_string).
    char* plaintext = get_string("plaintext:");
    printf("\n%s\n",plaintext);
    printf("\naplus 1 is: %c\n", 'a'+1);

    // must preserve case:
    //cycle through each character:
    int length = (int)strlen(plaintext);
    int i=0;
    for(  i=0; i<length;i++ )
    {
        int cipherint = plaintext[i] + key;
        int zvalue = 0;
        int avalue = 0;
        // printf(" %i ",i);
        printf("\n%c %i", plaintext[i],(plaintext[i] + key - 97));
        if(plaintext[i] >= 'a' && plaintext[i] <= 'z')
        {
            zvalue = 122;
            avalue = 96;
            if(cipherint > 122) //greater than z, over flow
            {
                // cipherint = cipherint - 122 + 96;
                cipherint = cipherint - zvalue + avalue;
            }
            // printf(" %i lowercase \n", cipherint);
            printf(" %i %c", cipherint, cipherint);
        }
        if(plaintext[i] >= 'A' && plaintext[i] <= 'Z')
        {


            printf(" CAPS ");
        }
    }
    // output ciphertext: (without a newline) followed by the plaintext’s corresponding ciphertext,

    // After outputting ciphertext, you should print a newline.

    return 0; //default
}