#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tree.h"
#include "common.h"


Tree *addword(Tree *T, char word[]){
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

void displayDictionary(Tree *t, int width){
    if(t->left != NULL){
        displayDictionary(t->left, width);
    }
    printf("%-*s  :%d\n",width, t->dict.word, t->dict.freq);
    if(t->right != NULL){
        displayDictionary(t->right, width);
    }
}

Tree *deleteABR(Tree *T, char word[]){
    if(T == NULL){
        return NULL;
    }
    if(strcmp(word, T->dict.word) < 0){
        T->left = deleteABR(T->left, word);
    }else{
        if(strcmp(word, T->dict.word) > 0){
            T->right = deleteABR(T->right, word);
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
                        T->right = deleteABR(T->right, temp->dict);
                    }
                }
            }
        }
    }
    return abr;
}

dictionary searchTree(Tree *T, char word[], dictionary dict){
    if(T == NULL){
        return dict;
    }
    if(strcmp(word, T->dict.word) < 0){
        dict = searchTree(T->left, word, dict);
    }else{
        if(strcmp(word, T->dict.word) > 0){
           dict =  searchTree(T->right, word, dict);
        }else{
            dict = T->dict;
        }
    }
    return dict;
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

void freeTree(Tree *t){
    if(t == NULL){
        return;
    }
    freeTree(t->left);
    freeTree(t->right);
    free(t);

}






int main(){
    
   
   
}






