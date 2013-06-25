#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height = -1;
    do
    {
        printf("Height: ");
        height = GetInt();
    }
    while (height > 23 || height < 0);
    
    for (int i = 0; i <= height; i++)
    {
        if (i == 0)
            continue;
        for (int o = 0; o <= height - i -1; o++)
            printf(" ");
        for (int o = 0; o <= i; o++)
            printf("#");
        printf("\n");
    }
    return 0;
}  
