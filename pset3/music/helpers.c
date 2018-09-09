// Helper functions for music

//already added:
#include <cs50.h>
#include "helpers.h"
//needed for round
#include <math.h>

//console this out below:
#include <stdio.h>
#include <string.h>




// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // TODO
    // string a fraction and convert it into some int number of eighths
    //  only be passed a string formatted as X/Y,
    //  X and Y is a positive digit, and Y is, moreover, a power of 2.
    // printf("%s ",fraction);
    // 1/4 and return as an int a corresponding number of eigths
    // 2, in this case, since 1/4 is equivalent to 2/8)

    // printf("%c ",fraction[0]);
    // printf("%c ",fraction[1]);
    // printf("%c ",fraction[2]);
    float a = fraction[0] - '0';
    float b = fraction[2] - '0';
    // printf("(a is %i) ",a);
    // printf("(b is %i) ",b);
    if(b == 8)
    {
        return a;
    }
    //algo for converting dec to fraction here:
    //https://www.mathsisfun.com/converting-decimals-fractions.html
    float c = a/b;
    c = c * 100;
    c = c / 25 * 2;
    int d = (int) round(c);
    printf("[%f %i] ", c, d);
    return d;

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
    // string test1s = get_string("enter some string:");
    // int d = duration( "fraction");
    int d = duration( "1/4");
    int f = frequency( "note");
    bool r = is_rest( "");
    // bool r = is_rest(test1s);

    printf("\n%i %i %d ", d, f, r);
    printf("test\n");
    return 0;
}