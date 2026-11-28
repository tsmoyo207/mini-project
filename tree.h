#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
#include "common.h"



Tree *addtoABR(Tree *T, char word[]);
void displayABRDictionary(Tree *t );
Tree *deletefromABR(Tree *T, char word[]);
int maxFreqABR(Tree *T, int fmax);
void freeABR(Tree *t);
int searchABR(Tree *T, char word[]);
#endif