/****************************************************************************
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 ***************************************************************************/
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: copy n infile outfile\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    int factor = atoi(argv[1]);

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
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
    
    // determine padding for scanlines
    int oldpadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding =  (4 - (bi.biWidth * factor * sizeof(RGBTRIPLE)) % 4) % 4;
    
    bi.biWidth *= factor;
    bi.biHeight *= factor;
    int size = abs(3 * bi.biWidth * bi.biHeight + padding * bi.biHeight);
    bi.biSizeImage = size;
    bf.bfSize = 54 + bi.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // reverse for processing
    bi.biWidth /= factor;
    bi.biHeight /= factor;


    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for (int o = 0; o < factor; o++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                
                for (int k = 0; k < factor; k++)
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }

            // skip over padding, if any
            fseek(inptr, oldpadding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < padding; k++)
                fputc(0x00, outptr);
            
            if (o + 1 != factor)
                fseek(inptr, -1 * (sizeof(RGBTRIPLE) * bi.biWidth + oldpadding), SEEK_CUR);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
