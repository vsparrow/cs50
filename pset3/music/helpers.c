// Helper functions for music

#include <cs50.h>

//console this out
#include <stdio.h>
#include <string.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // TODO
    // string a fraction and convert it into some int number of eighths
    //  only be passed a string formatted as X/Y,
    //  X and Y is a positive digit, and Y is, moreover, a power of 2.
    printf("%s ",fraction);
    return 0;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    // TODO
    printf("%s ",note);
    return 0;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    printf("is_rest ");
    // TODO
    // blank lines represent rests in our machine-readable format
    // What does it mean for a line to be blank?
    // get_string: If user * inputs only a line ending,
    //  returns "", not NULL.
    if (strlen(s) == 0)
    {
       return true;
    }
    return false;
}


int main(void)
{
    string test1s = get_string("enter some string:");
    int d = duration( "fraction");
    int f = frequency( "note");
    // bool r = is_rest( "");
    bool r = is_rest(test1s);

    printf("\n%i %i %d ", d, f, r);
    printf("test\n");
    return 0;
}