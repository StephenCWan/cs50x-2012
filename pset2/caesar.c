#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Please specify k when running this program!\n");
        return 1;
    }
    int k = atoi(argv[1]);
    
    string input = GetString();
    
    for (int i = 0; i < strlen(input); i++)
        if (input[i] >= 65 && input[i] <= 90)
            input[i] = ((k + input[i]-65) % 26) + 65;
        else if (input[i] >= 97 && input[i] <= 122)
            input[i] = ((k + input[i]-97) % 26) + 97;
    
    printf("%s\n", input);
    
    return 0;
}
