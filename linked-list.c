#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include <ctype.h>    
#include <time.h>  
#include "linked-list.h"   

List *addtoList(List *L, char word[]){
    if( L !=NULL){
        for(List *temp = L ; temp ; temp = temp->next){
            if(strcmp(temp->dict.word,word) == 0 ){
                temp->dict.freq++;
                return L;
            }
        }
    }

    List *newNode = (List*)malloc(sizeof(List));
    if (!newNode){ 
        printf(RED"Dynamic Memory allocation Failure\n"RESET);
        return L;
    }

    strcpy(newNode->dict.word, word);
    newNode->dict.freq = 1;
    newNode->next = L;
    return newNode;
}

int searchList(List *L, char word[]){
    for(List *temp = L; temp ; temp= temp->next){
        if(strcmp(temp->dict.word,word) == 0){
            return temp->dict.freq;
        } 
    }
    return -1;
}


List *deletefromList(List *L, char word[]){
    List *temp = L;
    List *prev = NULL;

    while (temp) {
        if (strcmp(temp->dict.word, word) == 0) {
            if (prev == NULL)
                L = temp->next;            // for  first node
            else
                prev->next = temp->next;   // for middle or end
            free(temp);
            printf(GRN"Deletion Successful\n"RESET);
            return L;
        }
        prev = temp;                       
        temp = temp->next;                 
    }
    printf(RED"Word not found\n"RESET);
    return L;
}


void displayListDictionary(List *L) {
    for (List *p = L; p; p = p->next)
        printf("%s : %d\n", p->dict.word, p->dict.freq);
}

void mostFrequentList(List *L, int k) {
    int n = 0, max = 0;

    /* 1. Count the nodes (n) and find the highest frequency (max) */
    for (List *temp = L; temp; temp = temp->next) {
        n++;
        if (temp->dict.freq > max) max = temp->dict.freq;
    }
    if (n == 0 || k <= 0) return;

    /* 2. Allocations */
    List **sorted = malloc(n * sizeof(List *));
    int *start = calloc(max + 1, sizeof(int));
    if (!sorted || !start) {
        free(sorted);
        free(start);
        exit(1);
    }

    /* 3. Counting: how many words have each frequency....counting sort */ 
    for (List *temp = L; temp; temp = temp->next)
        start[temp->dict.freq]++;

    /* 4. Cumulative positions, highest frequency first */
    int pos = 0;
    for (int f = max; f >= 1; f--) {
        int c = start[f];
        start[f] = pos;
        pos += c;
    }

    /* 5. Place each node at its position */
    for (List *temp = L; temp; temp = temp->next)
        sorted[start[temp->dict.freq]++] = temp;

    /* 6. Print the k most frequent */
    for (int i = 0; i < k && i < n; i++)
        printf("%d. %s : %d\n", i + 1, sorted[i]->dict.word, sorted[i]->dict.freq);

    /* 7. Free the helper arrays (not the list nodes) */
    free(sorted);
    free(start);
}
    

/* ADDED: frees every node of the list */
void freeList(List *L) {
    List *temp = L;
    while (temp) {
        List *next = temp->next;
        free(temp);
        temp = next;
    }
    L = NULL;
}


/* Writes n random words taken from a vocabulary of V words */
void generate_random_text(const char *filename, int n, int V) {
    FILE *f = fopen(filename, "w");
    if (!f) { perror("fopen"); return; } /*If the file couldn't be opened (bad path, no permission) perror states the reason and leaves the function*/
    for (int i = 0; i < n; i++)
        fprintf(f, "word%d ", rand() % V);
    fclose(f);
}

