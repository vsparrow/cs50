// Prints frequencies of and outputs WAV file with all notes in an octave

#include <cs50.h>
#include <stdio.h>
#include <string.h>

#include "helpers.h"
#include "wav.h"

// Notes in an octave
const string NOTES[] = {"C", "C#", "D", "D#", "E", "F",
                        "F#", "G", "G#", "A", "A#", "B"
                       };

// Default octave
#define OCTAVE 4

int main(int argc, string argv[])
{
    // Override default octave if specified at command line
    int octave = OCTAVE; //4
    if (argc == 2)
    {
        octave = atoi(argv[1]);
        if (octave < 0 || octave > 8)
        {
            // fprintf to print error messages to stderr
            fprintf(stderr, "Invalid octave\n");
            return 1;
        }
    }
    else if (argc > 2)
    {
        fprintf(stderr, "Usage: notes [OCTAVE]\n");
        return 1;
    }

    // Open file for writing
    song s = song_open("notes.wav");

    // Add each semitone
    for (int i = 0, n = sizeof(NOTES) / sizeof(string); i < n; i++)
    {
        // Append octave to note
        char note[4];
        // sprintf doesn’t  print to the screen but instead
        //     stores its output in a string
        sprintf(note, "%s%i", NOTES[i], octave);

        // Calculates frequency (in Hz) of a note formatted as XY,
            // where X is any of A through G and Y is any of 0 through 8,
            // or formatted as XYZ, where X is any of A through G, Y is # or b,
            // and Z is any of 0 through 8
            // int frequency(string note);
        // Calculate frequency of note
        int f = frequency(note);

        // Print note to screen
        printf("%3s: %i\n", note, f);

        // Write (eighth) note to file
            // // Adds a note to a song for a given duration (in eighths)
            // bool note_write(song s, int frequency, int duration);
        note_write(s, f, 1);
    }

    // Close file
    song_close(s);
}
