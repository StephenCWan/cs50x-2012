/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dictionary.h"

typedef struct node
{
    struct node* points[27];
    bool end;
} node;

node* head = NULL;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node* cur = head;
    // go through letters
    for (int i = 0, l = strlen(word); i < l; i++)
    {
    	char c = word[i];
    	if (cur->points[map(c)] == NULL)
    		break;
    	else
    	{
    		cur = cur->points[map(c)];
			if (i + 1 == l && cur->end == true)
				return true;
    	}
    }
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
	// init head
	head = malloc(sizeof(node));
	
	head->end = false;
	for (int o = 0; o < 27; o++)
		head->points[o] = NULL;
			
    node* cur = head;
    count = 0;
    
    // open file
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    	return false;
    
    while (!feof(fp))
    {
    	int c = fgetc(fp);
    	if (c == EOF)
    		break;
    	else if (c == '\n')
    	{    
			// end of word, prepare for next
			cur->end = true;
			cur = head;
	
			count++;
			
			cur = head;
			
    	}
    	
    	else
    	{
			// create if missing
			if (cur->points[map(c)] == NULL)
			{
			    node* tptr = malloc(sizeof(node));
			    tptr->end = false;
				for (int o = 0; o < 27; o++)
					tptr->points[o] = NULL;
				cur->points[map(c)] = tptr;
			}
			
			// go to next ptr
			cur = cur->points[map(c)];
		}
    }
 	fclose(fp);   
    return true;
}

int map(int c)
{
    if (c >= 65 && c <= 90)
        return c - 65;
    else if (c >= 97 && c <=  122)
        return c - 97;
    else if (c == 39)
        return 26;
    return 0;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
void unloadnode(node* cur);

bool unload(void)
{
    // TODO
    unloadnode(head);
    return true;
}

void unloadnode(node* cur)
{
	if (cur == NULL)
		return;
	else
	{
		for (int i = 0; i < 27; i++)
			unloadnode(cur->points[i]);
		free(cur);
	}
}

