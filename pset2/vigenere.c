#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("You must specify only a key as an argument!\n");
        return 1;
    }
    bool check = true;
    for (int i = 0; i < strlen(argv[1]); i++)
        if (!isalpha(argv[1][i]))
            check = false;
    if (!check)
    {
        printf("Your specified key is invalid!\n");
        return 1;
    }   
    
    string input = GetString();
    string k = argv[1];
    while (strlen(k) < strlen(input))
       strcat(k,k);
    
    int baconl = 0;
    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] >= 65 && input[i] <= 90)
        {
            input[i] = ((tolower(k[baconl])-97 + input[i]-65) % 26) + 65;
            baconl++;
        }
        else if (input[i] >= 97 && input[i] <= 122)
        {
            input[i] = ((tolower(k[baconl])-97 + input[i]-97) % 26) + 97;
            baconl++;
        }
    }
    
    printf("%s\n", input);
    return 0;
    
}
