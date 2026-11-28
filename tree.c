#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 200
#define MAXLINE 1000
typedef struct{
    char word[MAXWORD];
    int freq;
}dictionary;


typedef struct Tree{
    dictionary dict;
    struct Tree *left;
    struct Tree *right;
}Tree;


void lowercase(char word[]){
    
    int i = 0;
    while(word[i] != '\0'){
        word[i] = tolower((unsigned char)word[i]);
        i++;
    }
}


Tree *addword(Tree *T, char word[]){

    Tree *prev = NULL;
    Tree *C = T;
    int last_move = 0; //I use this variable to measure which side I turned last before exiting the loop;

    while( C != NULL){
        if(strcmp(word, C->dict.word) < 0){
            prev = C;
            C = C->left;
            last_move = -1;
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
    
    Tree *T = NULL;
    FILE*f = fopen("input.txt" , "r");
    if(!f){
        printf("Failed to open file\n");
        return 1;
    }
   
    char line[MAXLINE]; 
    char line_clean[MAXLINE];
    int longest_word = 0;


    while(fgets(line, sizeof line, f)!= NULL){
        
        line[strcspn(line, "\n")] = '\0';
        
        int k = 0;
        int l = 0;
        
        while(line[k]!= '\0'){

            if(line[k] == '-'){
                line[k] = ' ';
            }

            if(isalpha((unsigned char)line[k]) || line[k]== ' ' || line[k] == '\''){
                line_clean[l] = line[k];
                l++;
            }
            k++;
        }

        line_clean[l] = '\0';
            
        int q = 0;

        while(line_clean[q] != '\0'){
            char word[MAXWORD];
            int e = 0;

            while(line_clean[q]!= ' ' && line_clean[q] != '\0'){
               if (e < MAXWORD - 1) {
                    word[e] = line_clean[q];
                    e++;
               }
                q++;
            }

            if(line_clean[q] != '\0'){
                q++;
            }
            
            word[e] = '\0';
            if(e > longest_word){
                longest_word = e;
            }

            if (e > 0) {   
                lowercase(word);
                //printf("[%s] len=%d\n", word, e);
                T = addword(T, word);
            }
        }
    }


    dictionary *dict = (*dictionary)malloc(sizeof(dictionary));
    dict->freq = 0;
    strcpy("404", dict->word);



    displayDictionary(T, longest_word);
    freeTree(T);
    fclose(f);

}






