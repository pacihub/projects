// Implements a dictionary's functionality

#include <stdbool.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdio.h>
#include<strings.h> //for strcasecmp

#include "dictionary.h"

//prototypes
unsigned int size(void);

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 65381;

// Hash table. Initializing pointers for table indices. No need for malloc as it is just a pointer
node *table[N];

int word_count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
//this function compares words from a file to words in my uploaded dictionary
//since we don't know how the words will come, I need to make it canse insensitive
//the solution is to copy all words from file that i read -> convert all letters to lowercase

//hey computer give me a buffer array long enough to store one word + 1 (for \0)

    char copy_word[LENGTH + 1];
    strcpy(copy_word, word);  //copy word string into array (destination, source)

    for (int i = 0; copy_word[i] != '\0'; i++)  //read word until you reach end
    {
        copy_word[i] = tolower(word[i]);   //convert to lower case
    }

    int index = hash(copy_word);

//getting the hash table index after hashing the word in all lower case.
//this will ensure me that i always get the same index since everything is lower case
//and my dictionary is all lower case too


    for (node *cursor = table[index]; cursor != NULL; cursor = cursor->next)
    {
        if (strcasecmp(copy_word, cursor->word) == 0)
        {
            return true;
        }

    }

//for loop - initializing a cursor pointer to point at the same thing the head is pointing
//aka the first node in line. cursor will stop at the end of the list (when it hits NULL)
//increments with one node forward at a time.
//every iteration the copied word from file is compared to the word in the node (in my dictionary)
//strcasemp returns 0 if true, so when match found, the f-n returns true.

    return false;
}

// Hashes word to a number
// Djb2 hash function credit to
// http://www.cse.yorku.ca/~oz/hash.html?fbclid=IwAR2eA4ZpRyCMYFvuKqost_FSIf9LOqztSTUgDfcnNBH3dwoo3sb7wp9K0k0

unsigned int hash(const char *word)
{
    unsigned int hash = 5381;
    int c;
    while ((c = *word++))

            hash = ((hash << 5) + hash) + c;    /* hash * 33 + c */

        return hash % N;       // % N ensures the index will be within the hash table number

}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO

    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;   //set hash table pointers to null
    }

    FILE *infile = fopen(dictionary, "r");    //open the file and read

//check if infile got a valid pointer to dictionary. if pointer was NULL then ERROR.
    if (infile == NULL)
    {
        printf("Dictionary cannot be opened.");
        return 1;
    }

//declaring and allocating a buffer for scanf function to read into. +1 for the \0 terminator.
    char buffer_word[LENGTH + 1];

//read every word from file and copy into buffer (one at a time)
    while (fscanf(infile, "%s", buffer_word) != EOF)
    {

//for every read word, allocate a memory with size of a node, defined globally. (word + pointer field)
//and store the address of that memory into a pointer *new_node
        node *new_node = malloc(sizeof(node)); //allocating space in memory for new node

        if (new_node == NULL)
        {
            printf("not enough memory\n");
            unload(); //unload file
            return false; //so the program can quit
        }
        else
        {

//after node is created, i can copy the word in that node
            strcpy(new_node->word, buffer_word); //syntax: (destination, source)

            int index = hash(new_node->word);   //I hash every word and get an index for it

            word_count++;   //increasing the word counter

//sorting the word nodes inside the hash table. (words go into buckets)

//if bucket is empty (aka the head or table[index] are NULL, then I set table[index] to point at new_node
//and initialize NEXT field from that new_node to point to NULL, as there is nothing after it yet

            if (table[index] == NULL)
            {
                table[index] = new_node;
                new_node->next = NULL;
            }

            else
            {
                new_node->next = table[index];
                table[index] = new_node;
            }       //inner else closing bracket

        } //big(outer) else closing bracket

//else statement takes care of collision (when there are already other nodes in the bucket).
//first line tells the new_node (upcoming one) to point at the same thing the head is pointing at (1st node in line)
//then we are setting the pointer head(table index) to point at the newest one
//we are inserting the new_node between head and 1st pointer (youtube zamyla speller load explains well)
//that way we avoid orphaning the chain


    } //while loop closing bracket

    fclose(infile);
    return true;
} //bool function closing bracket

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO

    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO

    for (int i = 0; i < N; i++)    //we clean up memory for every linked list from the hash table.
    {

        node *cursor = table[i];  //initialize a pointer cursor to point at the hash table index

        while (cursor != NULL)
        {

            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);

        }

    }

//cursor will travel along the list until it reaches NULL. Setting up a temporary pointer *tmp
//to point at the same node, while cursor advances to the next node, we clear what *tmp is pointing at
//which is actually the node already behind cursor. then we free tmp and all over again
//the goal is to clear all the table so we don't have memory leak.
//pointer syntax: node *tmp = cursor (no need to put * before cursor aka *cursor)
//because I already declared cursor to be a pointer. so this line means:
//'hey tmp, point at the same node as cursor, so it can advance ahead and you clean up after it'
//this way we never lose track.
    return true;
}
