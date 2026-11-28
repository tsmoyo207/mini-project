#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED


#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif


#define MAXWORD 200
#define MAXLINE 1000
#define MAXlen 100000


#define GRN "\x1B[32m"
#define GRN_BR_BOLD "\x1B[1;92m"
#define GRN_BR_UND "\x1B[1;4;92m"
#define RESET "\x1B[0m"
#define YEL "\x1B[33m"
#define RED "\x1B[31m"
#define RED_BR "\x1B[91m"
#define CYAN "\x1B[36m"
#define MGT "\x1B[35m"
#define MGT_B_U "\x1B[1;4;95m"
#define BB_WHITE "\x1B[1;97m"
#define BR_YEL "\x1B[93m"
#define GREY "\x1B[90m"



typedef struct{
    char word[MAXWORD];
    int freq;
}dictionary;

typedef struct Tree{
    dictionary dict;
    struct Tree *left;
    struct Tree *right;
}Tree;

typedef struct{
    dictionary dict[MAXlen]; // array of dictionary entries
    int n; // number of words currently stored in the array
}Array;

typedef struct List{
    dictionary dict;
    struct List *next;
}List;






void lowercase(char word[]);
void splitWordsFromFile(List **L, Array **A, Tree **T,  int indicator, int *e);
void pause();
bool generateText(char Filename[], int n, int V);


#endif // CONSTANTS_H_INCLUDED