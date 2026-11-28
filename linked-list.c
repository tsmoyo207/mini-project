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

int seachList(List *L, char word[]){
    for(List *temp = L; temp ; temp= temp->next){
        if(strcmp(temp->dict.word,word) == 0){
            return temp->dict.freq;
        } 
    }
    return -1;
}



int deletefromList(List *L, char word[]){
    List *temp = L;
    List *p = NULL;
    while(temp){
        /*there are 3 cases for this one. When we've found the node we want to remove we need to check 
        if its at the start, at the middle or at the end*/
       if(strcmp(temp->dict.word , word) == 0){
          p = temp;
          temp = p->next;
          free(p);
          return 1;
       }
       //p = &(*p)->next; //this line was just giving me an error idk
    }
  return 0;
}


void displayListDictionary(List *L, int longest ) {
    int n = 0;
    /*I genuinely don't understand what going on here. Shouldnt it just traverse the list and display. Whats going on here*/

    for (List *temp = L; temp; temp = temp->next){
        printf("%*s : %d\n",longest, temp->dict.word, temp->dict.freq);
    }
    
    /*I genuinely don't understand what going on here. Shouldnt it just traverse the list and display. Whats going on here*/
    
    /*for (List *p = head; p; p = p->next) n++;
    if (n == 0) return;
    List **t = malloc(n * sizeof(dictionary *));
    if (!t) exit(1);
    int i = 0;
    for (dictionary *p = head; p; p = p->next) t[i++] = p;

    for (i = 1; i < n; i++) {
        dictionary *key = t[i];
        int j = i - 1;
        while (j >= 0 && strcmp(t[j]->word, key->word) > 0) {
            t[j + 1] = t[j];
            j--;
        }
        t[j + 1] = key;
    }
    for (i = 0; i < n; i++) printf("%*s : %d\n",longest, t[i]->word, t[i]->freq);
    free(t);
    */
}


void mostFrequentList(List *L, int k) {
   /*Sorry I messed something up on this one, I'll fix it though, when I understand it....... 
   
   int n = 0, max = 0;
    for (List *temp = L; temp; temp = temp->next) {
        n++;
        if (temp->dict.freq > max) max = temp->dict.freq;
    }
    if (n == 0) return;

    List **sorted = malloc(n*sizeof(List*));
    int *start = calloc(max + 1, sizeof(int));
    if (!sorted || !start) exit(1);

    for (List *p = head; p; p = p->next) start[p->freq]++;

    int pos = 0;
    for (int f = max; f >= 1; f--) {
        int c = start[f];
        start[f] = pos;
        pos += c;
    }
    for (List *temp = L; temp; temp = temp->next) sorted[start[temp->freq]++] = temp;

    for (int i = 0; i < k && i < n; i++)
        printf("%d. %s : %d\n", i + 1, sorted[i]->word, sorted[i]->freq);

    free(sorted);
    free(start);
    */
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
    if (!f) { perror("fopen"); return; }
    for (int i = 0; i < n; i++)
        fprintf(f, "word%d ", rand() % V);
    fclose(f);
}

