# Questions

## What's `stdint.h`?
Header that declare integer types having specified widths, where  that is the number of bits used.


## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

specofy ints of different sizes, u for unaigned meaning positive numbers only allowing for more pos numers at the expense of neg numbers

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?
 BYTE 8; DWORD 32; LONG 32; WORD 16;

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."
42 4D

## What's the difference between `bfSize` and `biSize`?
biSize is the size of the BITMAPINFOHEADER only. It is 40 bytes.
bfSize = biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)
where biSizeImage is the actual image contnetns, the stuff that comes after BITMAPFILEHEADER and BITMAPINFOHEADER

## What does it mean if `biHeight` is negative?

read bmp from top to bottom

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

28, biBitCount  -  number of bits-per-pixel per msdn

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

no file

## Why is the third argument to `fread` always `1` in our code?

number of elements to read which we want only 1.

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

0x00

## What does `fseek` do?

go to a position in a file to read from

## What is `SEEK_CUR`?

current position of pointer, ie: where we are reading the file.

## Whodunit?

don't know
