// Copies a BMP file
//BITMAPFILEHEADER  offset 2    type DWORD  name bfSize
    //size of file in bytes include pixels+padding+header
    //see also bf.bfsize down below
//BITMAPINFOHEADER  offset 14   type DWORD  name biSize
//BITMAPINFOHEADER  offset 8    type LONG   name biWidth
//BITMAPINFOHEADER  offset 22   type LONG   name biHeight   2800 = 28 = 170
//LONG size: 4bytes
//biWidth : image width in pixels, not include padding
//biHeight: image height in pixels
//biSizeImage  total image size in bytes (pixels + padding)
//  actual "image" starts at offset 54  with BGR as the color order
//bf.bfsize = bi.biSizeImage+sizeof(BITMAPFILEHEADER)+
//  sizeof(BITMAPINFOHEADER)
//color: is 3 bytes : bgr : ff0000 <- example :: 2hex = 1 byte
//padding: if the number of pixels is not a multiple of 4
//  we need to then add padding 0x00
//  ex  4 triples * 3 bytes each = 12 bytes total/ no pad need
//  ex  5 triples * 3 bytes each = 15 bytes total// add 00 <1 byte padd
//  ex  3 triples * 3 bytes = 9 bytes // to get multiple of 4
//      need to add  3 bytes, 000000 <- padding
//  PADDING formula below in code: look for "int padding"
//      int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
//      RGBTRIPLE always 3 bytes so only thing change is biWidth
//  writing padding //user fputc(chr, outptr)
//      where char in ex 3 could be 000000

//may not be needed
// struct RGBTRIPLE triple; triple.rgbtBlue = 0xff //asign colors
//fseek file position indicator
//scale bmp by n: argv[1]
//TODO
//  1) OPEN file
//  2) UPDATE headers for outfile
//      changes: file size, imagesize, width, height
//      bi.biWidth * n; bi.biHeight * n;
//      bibiSizeImage = ?; bf.bfSize = ?; //figure this out
//      padding_new = ? ; padding_old = ?
//  3) read each scanline, pixel by pixel
//  4) write each pixel into outputs file scanline
//  Resize horizontally first; each pixel in row write each n times
//      ex: ff00ff ffff00 ff12aa 000000(pad9->12) becomes
//          ff00ff ff00ff ffff00 ffff00 ff12aa ff12aa 0000(18->20)
//          use fwrite for this:
//      remember padding is not rgbtriple, cant fread/fwrite
//          need fputc

//PSEUDOCODE resize horizontal :: see rewrite method Psedo below
// for each row
//     for each pixel in row
//         write to outfile n times
//     write outfiles padding
//     skip over infiles padding
//Remmember not only every pixel repeated n times, every row too!
// n=2; single pixel in  row = ff12AA resize is
// ff12aa ff12aa        <- the resize
// ff12aa ff12aa
// rows: remember piels in array: rewrite row array as many times as needed
//PSEUDOCODE rewrite
// for each row
//     for each pixel in row
//         write to array n times
//     for n times
//          write array to outfile
//          write outfile padding
//     skip over infiles padding (fseek over infile padding)

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    //ARGUMENTS
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // the first (n) must be a positive integer less than or equal to 100,
    int n = atoi(argv[1]);
    if (n < 1 || n > 100)
    {
        fprintf(stderr,"Integer for resize must be between 1 and 100\n");
        return 1;
    }
    // the second must be the name of a BMP to be resized, and
    // the third must be the name of the resized version to be written.
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
    //*******************************************************************
    // bf = BITMAPFILEHEADER
    // bi = BITMAPINFOHEADER
    // printf("%d %d %d %d", bi.biSize, bi.biWidth, bi.biHeight, bi.biSizeImage);
    printf("\nbi.biSize %d, bi.biWidth %d, bi.biHeight %d, bi.biSizeImage %d\n", bi.biSize, bi.biWidth, bi.biHeight, bi.biSizeImage);
    //padding:
    printf("\nbfOffBits: %d\n", bf.bfOffBits);  //offset where the bmp starts
    printf("\nOLD: biWidth: %d",bi.biWidth);
    printf("\nOLD: biHeight: %d",bi.biHeight);
    //CALC PADDING OLD
    int widthWithPadding = bi.biWidth; //
    while(widthWithPadding % 4 != 0)
    {
        widthWithPadding++;
    }
    int oldPadding = widthWithPadding-bi.biWidth;
    printf("\nOld widthWithPadding is %d || old padding is %d", widthWithPadding, oldPadding);
    //get triples count
    int newWidth = bi.biWidth * n;
    int newHeight = bi.biHeight * n;
    int newWidthWithPadding = newWidth;
    while(newWidthWithPadding % 4 != 0)
        newWidthWithPadding++;
    int newPadding = newWidthWithPadding - newWidth;
    printf("\nNew width will be: %i", newWidth);
    printf("\nNew padding will be: %i", newPadding);
    printf("\nNew hieght will be: %i", newHeight);
    // biSizeImage = (biWidth * sizeof(RGBTRIPLE) + padding) * abs(biHeight)
    int newBiSizeImage = (newWidth * sizeof(RGBTRIPLE) + newPadding) * abs(newHeight);
    printf("\nNew BiSizeImage is %i, old was %i", newBiSizeImage,bi.biSizeImage);
    // bfSize = biSizeImage + 54(biSize(40) aka BITMAPINFOHEADER + BITMAPFILEHEADER)
    int newBfSize = newBiSizeImage + 54;
    printf("\nNew bfsize = %i", newBfSize);
    printf("\nalternate bfsize = %lu", newBiSizeImage + bi.biSize + sizeof(BITMAPFILEHEADER) );
    //*******************************************************************

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
