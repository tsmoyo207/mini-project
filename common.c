#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common.h"


void lowercase(char word[]){
    int i = 0;
    while(word[i] != '\0'){
        word[i] = tolower((unsigned char)word[i]);
        i++;
    }
}

void splitWordsFromFile(Tree **T, Array **A, int indicator, int *e){
    FILE*f = fopen("input.txt" , "r");
    if(!f){
        printf("Failed to open file\n");
        return;
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
                switch(indicator){
                case 3:
                    T = addwordtoABR(T, word);
                    break;
                case 1:
                    A = addwordtoArray(A, word);
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