// Helper functions for music

#include <cs50.h>

// Converts a fraction to eighths
    // input a string a fraction (e.g., 1/4)
    // return as an int a corresponding number of eigths 
    // (2, in this case, since 1/4 is equivalent to 2/8);
int duration(string fraction);

// Calculates frequency (in Hz) of a note formatted as XY,
// where X is any of A through G and Y is any of 0 through 8,
// or formatted as XYZ, where X is any of A through G, Y is # or b,
// and Z is any of 0 through 8
int frequency(string note);

// Determines whether a string represents a rest
bool is_rest(string s);
