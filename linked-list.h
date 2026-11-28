#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED
#include "common.h"

List *addtoList(List *L, char word[]);
int searchList(List *L, char word[]);
List *deletefromList(List *L, char word[]);
void displayListDictionary(List *L, int longest);
void mostFrequentList(List *L, int k);
void freeList(List *L);
void generate_random_text(const char *filename, int n, int V);

#endif