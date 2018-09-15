// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy multiplier infile outfile\n");
        return 1;
    }

    // the first (n) must be a positive integer less than or equal to 100,
    int n = atoi(argv[1]);
    if (n < 1 || n > 100)
    {
        fprintf(stderr,"Integer for resize must be between 1 and 100\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    //////////////////////////////////////////////////////get new header info
    long oldWidth = bi.biWidth;
    long newWidth = bi.biWidth * n;
    long oldHeight = bi.biHeight;
    long newHeight = bi.biHeight * n;
    //calc new padding for new biSizeImage
    // int newPad = newWidth;
    // while(newPad % 4 != 0)
    //     newPad++;
    // newPad = newPad - newWidth;
    int newPad = (4 - (newWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    // biSizeImage = (biWidth * sizeof(RGBTRIPLE) + padding) * abs(biHeight)
    int newBiSizeImage = (newWidth * sizeof(RGBTRIPLE) + newPad) * labs(newHeight);
    // int newBfSize = newBiSizeImage + bf.bfOffBits; // which is 54
    int newBfSize = newBiSizeImage + 54; // which is 54
    //bi.biSize does not change, always 40

    //////////////////////////////////////////////////////Change header
    bi.biWidth = newWidth;
    bi.biHeight = newHeight;
    bi.biSizeImage = newBiSizeImage;
    bf.bfSize = newBfSize;
    //////////////////////////////////////////////////////


    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding = (4 - (oldWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = labs(oldHeight); i < biHeight; i++)
    {
        //duplicate line
        for(int writeRowNtimes = 0; writeRowNtimes < n; writeRowNtimes++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < oldWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile n times
                for(int writeNtimes = 0; writeNtimes < n; writeNtimes++)
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

            }
            //add output padding, if any
            for (int k = 0; k < newPad; k++)
                fputc(0x00, outptr);
            //JUMP BACK TO BEGINGING OF LINE HERE::
            if(writeRowNtimes < n-1)
                fseek(inptr, -((int) sizeof(RGBTRIPLE) * oldWidth), SEEK_CUR);
        }
        // skip over input file padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
