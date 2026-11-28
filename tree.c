#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tree.h"
#include "common.h"


Tree *addtoABR(Tree *T, char word[]){
    Tree *prev = NULL;
    Tree *C = T;
    int last_move = 0; 
    while( C != NULL){
        if(strcmp(word, C->dict.word) < 0){
            prev = C;
            C = C->left;
            last_move = - 1;
        }else{
            if((strcmp(word, C->dict.word) > 0)){
                prev = C;
                C = C->right;
                last_move = 1;
            }else{
                C->dict.freq = C->dict.freq + 1;
                break;
            }
        }
    }
    if(C == NULL){
        Tree *newNode = (Tree*)malloc(sizeof(Tree));
        strcpy(newNode->dict.word , word);
        newNode->dict.freq = 1;
        newNode->left = NULL;
        newNode->right =NULL;
        if (prev == NULL){
            T = newNode;
        }else{
            if(last_move == -1){
                prev->left = newNode;
            }else{
                if(last_move == 1){
                    prev->right = newNode;
                }
            }
        }
    }
    return  T;
}

void displayABRDictionary(Tree *t, int longest ){
    if(t != NULL){
        if(t->left != NULL){
            displayABRDictionary(t->left, longest);
        }
        printf("%*s  :%d\n",longest, t->dict.word, t->dict.freq);
        if(t->right != NULL){
            displayABRDictionary(t->right, longest);
        }
    }
}

Tree *deletefromABR(Tree *T, char word[]){
    if(T == NULL){
        return NULL;
    }
    if(strcmp(word, T->dict.word) < 0){
        T->left = deletefromABR(T->left, word);
    }else{
        if(strcmp(word, T->dict.word) > 0){
            T->right = deletefromABR(T->right, word);
        }else{
            if(T->left == NULL && T->right == NULL){
                free(T);
                return NULL;
            }else{
                if(T->left == NULL){
                    Tree *temp = T->right;
                    free(T);
                    return temp;
                }else{ 
                    if(T->right == NULL){
                        Tree *temp = T->left;
                        free(T);
                        return temp;
                    }else{
                        Tree *temp = T->right;

                        while(temp->left != NULL){
                        temp = temp->left;
                        }

                        T->dict = temp->dict;
                        T->right = deletefromABR(T->right, temp->dict.word);
                    }
                }
            }
        }
    }
    return T;
}

int searchABR(Tree *T, char word[]){
    if(T == NULL){
        return -1;
    }
    int freq = -1;

    while(T != NULL){
        if(strcmp(word, T->dict.word) < 0){
            T = T->left;
        }else{
            if(strcmp(word, T->dict.word) > 0){
            T = T->right;
            }else{
                freq = T->dict.freq;
                break;
            }
        }
    }
    return freq;
}


int maxFreqABR(Tree *T, int fmax){
    if(T != NULL){
        fmax = maxFreqABR(T->left, fmax);
        if(T->dict.freq > fmax){
            fmax = T->dict.freq;
        }
        fmax = maxFreqABR(T->right, fmax);
    }
    return fmax;
}

void freeABR(Tree *t){
    if(t == NULL){
        return;
    }
    freeABR(t->left);
    freeABR(t->right);
    free(t);

}












