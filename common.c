#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "common.h"
#include "tree.h"
#include "array.h"
#include "linked-list.h" 


void lowercase(char word[]){
    int i = 0;
    while(word[i] != '\0'){
        word[i] = tolower((unsigned char)word[i]);
        i++;
    }
}

void splitWordsFromFile(List **L, Array **A, Tree **T,  int indicator, int *longest){
    FILE*f = fopen("input.txt" , "r");
    if(!f){
        printf("Failed to open file\n");
        return;
    }
    char line[MAXLINE]; 
    char line_clean[MAXLINE];
    

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
            if(e > *longest){
                *longest = e;
            }
            if (e > 0) {
                lowercase(word);
                switch(indicator){
                case 1:
                    *L = addtoList(*L, word);
                    break;
                case 2:
                    *A = addtoArray(*A, word);
                    break;
                case 3:
                    *T = addtoABR(*T, word);
                    break;     
            }
            }
        }
    }
    fclose(f);
    printf(GRN"Process Complete\n"RESET);
}

void pause() {
    printf(GREY "\nPress Enter to continue..." RESET);
    while(getchar() != '\n');
    getchar();
    system(CLEAR_SCREEN);
}

bool generateText(char Filename [], int n, int V){
    FILE *f = fopen(Filename, "w");
    
    if(!f){
        printf("error in opening the file\n");
        return false;
    }

    if(n <= 0 || V <= 0 || V > RAND_MAX){
        printf("n must be positive and V must be between 1 and %d\n", RAND_MAX);
        fclose(f);
        return false;
    }
    

    for(int i = 0; i < n; i++){
        fprintf(f, "w%d\n", rand() % V);
    }

    fclose(f);
    printf("text successfully generated!");
    return true;
}
