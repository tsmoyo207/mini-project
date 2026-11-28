#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include <ctype.h>    
#include <time.h>     

#define MAX 100       


typedef struct node{
    char word[MAX];
    int freq;
    struct node *next;
}dictionary;


void list_add(dictionary **head, const char *w)   
{
    for(dictionary *p = *head ; p ; p = p->next){
        if(strcmp(p->word,w) == 0 ){
            p->freq++;
            return ;
        }
    }
        dictionary *n = malloc(sizeof(dictionary));
        if (!n) { fprintf(stderr, "malloc failed\n"); exit(1); }
        strncpy(n->word, w , MAX - 1);
        n->word[MAX - 1] = '\0';
        n->freq = 1;
        n->next = *head;
        *head = n;
}

int list_search(dictionary *head, const char *w)
{
    for(dictionary *p = head; p ; p= p->next)
         if(strcmp(p->word,w) == 0) return p->freq;
    return 0;
}

int list_delete(dictionary **head, const char *w)
{
    dictionary **p = head;
    while(*p){
       if(strcmp((*p)->word , w) == 0){
          dictionary *tmp = *p;
          *p = tmp->next;
          free(tmp);
          return 1;
       }
       p = &(*p)->next;
    }
  return 0;
}

void list_print_alpha(dictionary *head) {
    int n = 0;
    for (dictionary *p = head; p; p = p->next) n++;
    if (n == 0) return;
    dictionary **t = malloc(n * sizeof(dictionary *));
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
    for (i = 0; i < n; i++) printf("%s : %d\n", t[i]->word, t[i]->freq);
    free(t);
}

void list_top_k(dictionary *head, int k) {
    int n = 0, max = 0;
    for (dictionary *p = head; p; p = p->next) {
        n++;
        if (p->freq > max) max = p->freq;
    }
    if (n == 0) return;

    dictionary **sorted = malloc(n * sizeof(dictionary *));
    int *start = calloc(max + 1, sizeof(int));
    if (!sorted || !start) exit(1);

    for (dictionary *p = head; p; p = p->next) start[p->freq]++;

    int pos = 0;
    for (int f = max; f >= 1; f--) {
        int c = start[f];
        start[f] = pos;
        pos += c;
    }
    for (dictionary *p = head; p; p = p->next) sorted[start[p->freq]++] = p;

    for (int i = 0; i < k && i < n; i++)
        printf("%d. %s : %d\n", i + 1, sorted[i]->word, sorted[i]->freq);

    free(sorted);
    free(start);
}

/* ADDED: frees every node of the list */
void list_destroy(dictionary **head) {
    dictionary *p = *head;
    while (p) {
        dictionary *next = p->next;
        free(p);
        p = next;
    }
    *head = NULL;
}

/* Reads a text file: lowercase, punctuation removed, each word added.
   Returns the number of words read, -1 on error. */
int list_load_file(dictionary **head, const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) { perror("fopen"); return -1; }

    char buf[MAX];
    int len = 0, count = 0, c;

    while ((c = fgetc(f)) != EOF) {
        if (isalnum(c) || c >= 128) {          /* letter, digit, or accented byte */
            if (len < MAX - 1) buf[len++] = (char)tolower(c);
        } else if (len > 0) {                  /* separator: the word is finished */
            buf[len] = '\0';
            list_add(head, buf);
            count++;
            len = 0;
        }
    }
    if (len > 0) {                             /* last word if no trailing space */
        buf[len] = '\0';
        list_add(head, buf);
        count++;
    }
    fclose(f);
    return count;
}


/* Writes n random words taken from a vocabulary of V words */
void generate_random_text(const char *filename, int n, int V) {
    FILE *f = fopen(filename, "w");
    if (!f) { perror("fopen"); return; }
    for (int i = 0; i < n; i++)
        fprintf(f, "word%d ", rand() % V);
    fclose(f);
}

/* Average build time (seconds) for n words from a vocabulary of V words */
static double build_time(int n, int V, int sims) {
    double total = 0;
    char (*words)[MAX] = malloc((size_t)n * sizeof *words);
    if (!words) exit(1);
    for (int s = 0; s < sims; s++) {
        for (int i = 0; i < n; i++) sprintf(words[i], "word%d", rand() % V);
        dictionary *l = NULL;
        clock_t t0 = clock();
        for (int i = 0; i < n; i++) list_add(&l, words[i]);
        total += (double)(clock() - t0) / CLOCKS_PER_SEC;
        list_destroy(&l);
    }
    free(words);
    return total / sims;
}


/* Average time (seconds) of ONE search, repeated 'reps' times */
static double search_time(int n, int V, int sims, int reps) {
    double total = 0;
    char (*words)[MAX] = malloc((size_t)n * sizeof *words);
    char (*queries)[MAX] = malloc((size_t)reps * sizeof *queries);
    if (!words || !queries) exit(1);
    for (int s = 0; s < sims; s++) {
        dictionary *l = NULL;
        for (int i = 0; i < n; i++) {
            sprintf(words[i], "word%d", rand() % V);
            list_add(&l, words[i]);
        }
        for (int i = 0; i < reps; i++) sprintf(queries[i], "word%d", rand() % V);
        volatile int sink = 0;
        clock_t t0 = clock();
        for (int i = 0; i < reps; i++) sink += list_search(l, queries[i]);
        total += (double)(clock() - t0) / CLOCKS_PER_SEC / reps;
        list_destroy(&l);
    }
    free(words);
    free(queries);
    return total / sims;
}
