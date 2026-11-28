#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
#include "common.h"





Array *initialiseArray();
int searchArray(Array *A, char word[]);
Array *addwordtoArray(Array *A, char word[]);
void displayArrayDictionary(Array *A);
void mostFrequent(Array *A, int Nbwords);
Array *deletefromArray(Array *A, char word[]);


#endif