/****************************************************************************
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
 
typedef uint8_t  BYTE;
 
 int main(void)
 {
    FILE* raw = fopen("card.raw", "r");
    if (raw == NULL)
    {
        printf("could not open raw data to be read");
        return 1;
    }  
    
    BYTE* buffer = malloc(sizeof(BYTE) * 512);
    FILE* open = NULL;
    int img = 0;
    char* name = malloc(sizeof(char) * 7);
    
    while (!feof(raw))
    {
    
        fread(buffer, 512, 1, raw);
        
        
        if ((buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff & buffer[3] == 0xe0) 
        || (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff & buffer[3] == 0xe1))
        {
            if (open != NULL)
                fclose(open);
                
            // start a new file
            sprintf(name, "%03d.jpg", img);
            open = fopen(name, "w");
            img++;
        }
        
        if (feof(raw))
            break;
        
        if (open != NULL)
            fwrite(buffer, 512, 1, open);
        
    }
    
    if (open != NULL)
        fclose(open);
    
    fclose(raw);
    free(name);
    free(buffer);
    
    return 0;   
 }
 
 
