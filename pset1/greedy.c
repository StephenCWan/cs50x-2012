#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    printf("O hai!  ");
    float ch = -1;
    do
    {
        printf("how much change is owed?\n");
        ch = GetFloat();
    }
    while (ch < 0);
    
    int c = (int)(round(ch * 100));

    int count = 0;
    while (c > 0)
    {
        if (c >= 25)
            c -= 25;
        else if (c >= 10)
            c -= 10;
        else if (c >= 5)
            c -= 5;
        else if (c >= 1)
            c -= 1;
        count++;
    }  
    printf("%i\n", count);
    return 0;
}
