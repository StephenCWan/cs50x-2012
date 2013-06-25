#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "huffile.h"
#include "forest.h"

void unload(Tree* tree);

int main (int argc, char* argv[])
{
    
    // check args
    if (argc != 3)
    {
        printf("usage: puff [binary] [destination]\n");
        return 1;
    }
    
    // load file
    Huffile* fp = hfopen(argv[1], "r");
    
    if (fp == NULL)
    {
        printf("could not read the compressed file\n");
        return 1;
    }
    
    // read comp header
    Huffeader* header = malloc(sizeof(Huffeader));
    
    if (!hread(header, fp))
    {
        printf("could not read the file header\n");
        return 1;
    }
    
    // check magic number identifier
    if (header->magic != MAGIC)
    {
        printf("not huffed file\n");
        return 1;
    }
    
    // populate forest
    Forest* forest = mkforest();
    
    int fcount = 0;
    for (int i = 0, l = SYMBOLS; i < l; i++)
    {
        if (header->frequencies[i] == 0)
            continue;
        Tree* tmp = mktree();
        tmp->symbol = i;
        tmp->frequency = header->frequencies[i];
        plant(forest, tmp);
        fcount += header->frequencies[i];
    }
    
    // check checksum against count
    if (fcount != header->checksum)
    {
        printf("file corrupted, invalid checksum\n");
        return 1;
    }
    
    // condense forest into single tree
    while (true)
    {
        Tree* cur1 = pick(forest);
        Tree* cur2 = pick(forest);
        if (cur2 == NULL)
        {
            plant(forest, cur1);
            break;
        }
        else
        {
            Tree* tmp = mktree();
            tmp->frequency = cur1->frequency + cur2->frequency;
            tmp->left = cur1;
            tmp->right = cur2;
            plant(forest, tmp);
        }
    }
    
    // read rest of the file
    FILE* wfp = fopen(argv[2], "w");
    
    if (wfp == NULL)
    {
        printf("could not open file for writing\n");
        return 1;
    }
    
    Tree* head = pick(forest);
    Tree* cur = head;
    int buffer = -1;
    while ((buffer = bread(fp)) != EOF)
    {
        if (fcount == 1 && buffer == 0)
            fwrite(&(cur->symbol), sizeof(char), 1, wfp);
        else
        {
            // if bit = 1, go right
            if (buffer == 1)
                cur = cur->right;
                
            // else, go left
            else
                cur = cur->left;
                
            if (cur->left == NULL && cur->right == NULL)
            {
                fwrite(&(cur->symbol), sizeof(char), 1, wfp);
                cur = head;
            }
        }
    }
    
    fclose(wfp);
    
    // free all resources
    rmtree(head);
    rmforest(forest);
    hfclose(fp);
    free(header);
    
    return 0;
}


