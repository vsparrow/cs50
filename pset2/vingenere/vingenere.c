// A represents 0, B represents 1, C represents 2, …​, and Z represents 25)
// this cipher’s use of kj as opposed to just k.
// And if k is shorter than p, then the letters in k must be reused cyclically as many times as it takes to encrypt p.

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// accept a single command-line argument: a keyword, k, composed entirely of alphabetical characters.
int main(int argc, char *argv[])
{
    printf("%i %s\n",argc, argv[0]);

    // If your program is executed without any command-line arguments, with more than one command-line argument exit
    // your program should print an error (of your choice) and exit immediately, with main returning 1 (thereby signifying an error).
    if (argc != 2)
    {
        printf("Useage: ./vingenere k\n");
        return 1;
    }
    //check if  key contains any non-alphabetical character,
    for(int i=0; i < strlen(argv[1]); i++)
    {
        if(argv[1][i] < 'a' || argv[1][i] > 'z')
        {
            if(argv[1][i] < 'A' || argv[1][i] > 'Z')
            {
                printf("ERROR: key should only contain alphabetical characters\n");
                return 1;
            }
        }
        printf("%c ", (argv[1][i]));
    }
    printf("\n");
// proceed to prompt the user for a string of plaintext, p, (as by a prompt for plaintext:)
// With respect to the characters in k, you must treat A and a as 0, B and b as 1, ... , and Z and z as 25.
// BUT preserve case

//  encrypt according to Vigenère’s cipher with k,
// only apply Vigenère’s cipher to a character in p if that character is a letter.
// All other characters (numbers, symbols, spaces, punctuation marks, etc.) must be outputted unchanged
// apply key to only valid chars, current key must not change if invalid char, wait for next valid char to apply key

//  printing the result (prepended with ciphertext: and ending with a newline)
//  exiting, with main returning 0.
}