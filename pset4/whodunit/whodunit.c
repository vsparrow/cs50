#include <stdio.h>
#include <stdlib.h>


// accept exactly two command-line arguments:
//     the name of an input file to open for reading
//     the name of an output file to open for writing.

int main(int argc, char *argv[])
{
    // fewer or more than two command-line arguments
    // remind the user of correct usage, as with fprintf (to stderr), and main should return 1.
    if (argc != 3)
    {
        fprintf(stderr, "Useage: ./whodoneit inputfile outputfile\n");
        return 1;
    }

    char *input = argv[1];
    char *output = argv[2];

    // If the input file cannot be opened for reading, your program should inform the user as much,
    // as with fprintf (to stderr), and main should return 2.
    FILE *inptr = fopen(input, "r");    //r for readonly //inptr = inputPointer
    if( inptr == NULL)
    {
        fprintf(stderr,"Error cannot read input file %s\n", input);
        return 2;
    }

    return 0;
}