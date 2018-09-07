// A represents 0, B represents 1, C represents 2, …​, and Z represents 25)
// this cipher’s use of kj as opposed to just k.
// And if k is shorter than p, then the letters in k must be reused cyclically as many times as it takes to encrypt p.

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// accept a single command-line argument: a keyword, k, composed entirely of alphabetical characters.
int main(int argc, char *argv[])
{
    // printf("%i %s\n",argc, argv[0]);

    // If your program is executed without any command-line arguments, with more than one command-line argument exit
    // your program should print an error (of your choice) and exit immediately, with main returning 1 (thereby signifying an error).
    if (argc != 2)
    {
        printf("Useage: ./vingenere k\n");
        return 1;
    }
    //check if  key contains any non-alphabetical character,
    for (int i=0; i < strlen(argv[1]); i++)
    {
        if (argv[1][i] < 'a' || argv[1][i] > 'z')
        {
            if (argv[1][i] < 'A' || argv[1][i] > 'Z')
            {
                printf("ERROR: key should only contain alphabetical characters\n");
                return 1;
            }
        }
        // printf("%c ", (argv[1][i]));
    }
    // printf("\n");
    // prompt the user for a string of plaintext, p, (as by a prompt for plaintext:)
    string plaintext = get_string("plaintext: ");
    printf("\n%s\n", plaintext);
    // encrypt according to Vigenère’s cipher with k,
    // only apply Vigenère’s cipher to a character in p if that character is a letter.
    // All other characters (numbers, symbols, spaces, punctuation marks, etc.) must be outputted unchanged
    // apply key to only valid chars, current key must not change if invalid char, wait for next valid char to apply key
    // With respect to the characters in k, you must treat A and a as 0, B and b as 1, ... , and Z and z as 25.
    // BUT preserve case
    int keyCounter = 0;
    int keySize = strlen(argv[1]);
    for (int i=0; i<strlen(plaintext); i++)
    {
        bool isAlpha = true;
        //check if  char is  non-alphabetical character,
        // for (int j=0; j < strlen(argv[1]); j++)
        // {
            if (plaintext[i] < 'a' || plaintext[i] > 'z')
            {
                if (plaintext[i] < 'A' || plaintext[i] > 'Z')
                {
                    isAlpha = false;
                }
            }
        // }

        if(isAlpha)             //do this work only if element is alphabetical
        {
            //get key shift
            bool caps = false;
            int intValueOfAa = 97; //default lower case; 97 refers to int value of 'a'
            if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
            {
                caps = true;
                intValueOfAa = 65; //refer to int value of 'A'
            }

            int keyShift = argv[1][keyCounter] - intValueOfAa;
            printf("(%i %c) ",keyShift,argv[1][keyCounter]);


            //cycle through key elements via counter
            if (keyCounter == keySize-1)    //keySize -1 because the last char in a string is always \0
            {
                keyCounter = 0;
            }
            else
            {
               keyCounter++;
            }
        } //end if isAlpha
        else    //remove this else, testing only
        {
            printf("(%c) ", argv[1][i]);
        }
    }
//  printing the result (prepended with ciphertext: and ending with a newline)
//  exiting, with main returning 0.
}