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
const unsigned int N = 26;

// Hash table
node *table[N];

int word_count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    char copy_word[LENGTH + 1];  //array for new word with length of original word that I compare
    strcpy(copy_word, word);  //copy original word string (destination, source)
    
    for (int i = 0; copy_word[i] != '\0'; i++)
    {
        copy_word[i] = tolower(word[i]);
    }
    
    int index = hash(copy_word);   //getting the hash table index after hashing the word in all lower case



  
  
   for (node *cursor = table[index]; cursor != NULL; cursor = cursor->next)
    {
      if(strcasecmp(copy_word, cursor->word)==0)
        {
           return true;
        }
       
    }
return false;
}

// Hashes word to a number
// TODO
    // Djb2 hash function credit to
    // http://www.cse.yorku.ca/~oz/hash.html?fbclid=IwAR2eA4ZpRyCMYFvuKqost_FSIf9LOqztSTUgDfcnNBH3dwoo3sb7wp9K0k0
unsigned int hash(const char *word)
 {

        unsigned int hash = 5381;
        int c;
        while ((c = *word++))
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        return hash % N;

 }

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    //-------------------------
    //open the file and read
    for (int i = 0; i < N; i++)
       {
           table[i] = NULL;   //set hash table pointers to null
       }

    FILE *infile = fopen(dictionary, "r");

//check if file opened successfully. if pointer was NULL then ERROR.
    if (infile == NULL)
    {
        printf("Dictionary cannot be opened.");
        return 1;
    }

//declaring and allocating a buffer for scanf function to read into.
     char buffer_word[LENGTH + 1];

    node *new_node;
    while(fscanf(infile, "%s", buffer_word) != EOF)
    {

      new_node = malloc(sizeof(node)); //allocating space in memory for new node

            if(new_node == NULL)
             {
            printf("not enough memory\n");
            unload(); //unload file
            return false; //so the program can quit
             }
             else
            {
            
            strcpy(new_node->word,buffer_word);  //the word is copied in that node (destination, source)
            
            int index = hash(new_node->word);   //getting the index by hashing the word
            
            word_count++;   //increasing the word counter

                        //this where nodes get appended to the separate buckets
                if(table[index]==NULL)  //if there's nothing there, head (table[index]) points at new node and NEXT in new node
                                    //is initialized to NULL;
                {
                table[index] = new_node;
                new_node->next = NULL;
                }
                else            //if there is a collision, the new node points at the head, and then the head points at the node
                            //so we don't orphan the rest
                {
                new_node->next = table[index];
                table[index] = new_node;
                }       //inner else closing bracket
            } //big(outer) else closing bracket

        } //while loop closing bracket
        free(new_node);
        
    return true;
    fclose(infile);
} //bool function closing bracket

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO

    return word_count;
    printf("%i", word_count);
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    
    for (int i = 0; i <= N; i++)
    {
    
    while (table[i] != NULL)
        {
            
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
            
        }
    
    }
    
    return true;
}
