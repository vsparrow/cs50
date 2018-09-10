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


    float a = fraction[0] - '0';
    float b = fraction[2] - '0';
    if (b == 8)
    {
        return a;
    }
    //algo for converting dec to fraction here:
    //https://www.mathsisfun.com/converting-decimals-fractions.html
    float c = a / b;
    c = c * 100;
    c = c / 25 * 2;
    int d = (int) round(c);
    return d;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    bool sharp = false; //#
    bool flat = false;  //b
    int octive = 0;
    char noteOnly[3] = "\0";
    int noteIntVal = 0;
    if (note[1] == '#')
    {
        sharp = true;
        noteIntVal += 35;
    }
    else if (note[1] == 'b')
    {
        flat = true;
        noteIntVal += 98;
    }
    //else no sharp or otive
    if (!sharp && !flat)
    {
        char temp[2];
        temp[0] = note[1];
        temp[1] = '\0';
        octive = atoi(temp);
        noteOnly[0] = note[0];
        noteOnly[1] = '\0';
        noteIntVal += note[0] - 0;
    }
    else
    {
        char temp[2];
        temp[0] = note[2];
        temp[1] = '\0';
        octive = atoi(temp);
        noteOnly[0] = note[0];
        noteOnly[1] = note[1];
        noteOnly[2] = '\0';
        noteIntVal += (note[0] - 0);
    }
    //********************************** calc the frquency
    int multiplyOrDivide = 4 - octive;
    int currentFreq = 440; //standard for a4
    // if ( multiplyOrDivide == 0) //do nothing
    if (multiplyOrDivide < 0)   //we need to  440 * x * 2
    {
        currentFreq = currentFreq * -2 * multiplyOrDivide; // 440 * -2 * multiplyOrDivide, the teo negatives cancel each other
    }
    else if (multiplyOrDivide > 0)
    {
        currentFreq = currentFreq / 2 / multiplyOrDivide;
    }
    //order is:     //  c c#/db d d#/eb e f f#/gb g g#/Ab a a#/Bb b
    switch (noteIntVal)
    {
        case 66: //B
            currentFreq = round(((double) currentFreq) * pow(2.0, ((double) 2) / ((double) 12)));
            break;
        case 164: //Bb  66+98
        case 100: //A#  65+35
            currentFreq = round(((double) currentFreq) * pow(2.0, ((double) 1) / ((double) 12)));
            break;
        //DO NOTHING FOR A
        case 163: //Ab  65+98
        case 106: //G#  71+35
            currentFreq = round(((double) currentFreq) / pow(2.0, ((double) 1) / ((double) 12)));
            break;
        case 71: //G
            currentFreq = round(((double) currentFreq) / pow(2.0, ((double) 2) / ((double) 12)));
            break;
        case 169: //Gb  71+98
        case 105: //F#  70+35
            currentFreq = round(((double) currentFreq) / pow(2.0, ((double) 3) / ((double) 12)));
            break;
        case 70: //F
            currentFreq = round(((double) currentFreq) / pow(2.0, ((double) 4) / ((double) 12)));
            break;
        case 69: //E
            currentFreq = round(((double) currentFreq) / pow(2.0, ((double) 5) / ((double) 12)));
            break;
        case 167: //Eb  69+98
        case 103: //D#  68+35
            currentFreq = round(((double) currentFreq) / pow(2.0, ((double) 6) / ((double) 12)));
            break;
        case 68: //D
            currentFreq = round(((double) currentFreq) / pow(2.0, ((double) 7) / ((double) 12)));
            break;
        case 166: //Db  68+98
        case 102: //C#  67+35
            currentFreq = round(((double) currentFreq) / pow(2.0, ((double) 8) / ((double) 12)));
            break;
        case 67: //C
            currentFreq = round(((double) currentFreq) / pow(2.0, ((double) 9) / ((double) 12)));
            break;
    }
    //a#4 or a4
    //  note is a#4 or a
    //  octive is 4
    //what is the frquency of hte note?
    // a4 is 440
    // every semi tone up multiply by 2^1/12
    // every semi tone down divide by 2^1/12
    //  c c#/db d d#/eb e f f#/gb g g#/Ab a a#/Bb b
    // example g# would be 440 * 2^11/12 because it is 11 spaces away from a
    // example2     a5 would be 44 * 12/12 because it is 12 spaces away
    //  every a up is 12/12 away, so a6  would be 400* 2^24/12
    //  or you could just say every octive up, multiply by 2, a4=440 a5=880, a6 = 1760 and viceversa a3 would be 440/2 a2 is 440/4, a1 is 440/8

    //notes could be #sharp or bflat so account for flats   this is called "accidentals"
    // so note[1] could be an "accidental"(# or b) or it could be an octive(4,5,6,etc)
    //  side note: if note[1] is an octive, that is called a "natural" note

    return currentFreq;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // get_string: If user * inputs only a line ending,
    //  returns "", not NULL.
    if (strlen(s) == 0)
    {
        return true;
    }
    return false;
}

