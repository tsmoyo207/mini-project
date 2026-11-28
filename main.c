#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "array.h"
#include "common.h"
#include "tree.h"

int main(){

    Tree *T = NULL;
    Array *A = initialiseArray();

    bool loop = true;
    
    int opt2, opt1, opt3;
    char word[MAXWORD];
    int freq;
    int k;

   
    

    do{
        printf(GRN  "SELECT DATA STRUCTURE \n"  RESET);
        printf(CYAN"[1]"RESET"Fixed Length Array\n");
        printf(CYAN"[2]"RESET"Dynamic Linked List\n");
        printf(CYAN"[3]"RESET"Binary Search Tree\n");
        printf("Select Option: ");
       
        bool loop1 = true;
        bool loop2 = true;

        scanf("%d", &opt1);
        switch(opt1){
            case 1:
                do{
                    printf(GRN  "FIXED LENGTH ARRAY\n"  RESET);
                    printf(CYAN"[1]"RESET"Read file and build dictionary\n");
                    printf(CYAN"[2]"RESET"Search for a word and display its frequency\n");
                    printf(CYAN"[3]"RESET"Delete Word\n");
                    printf(CYAN"[4]"RESET"Display Tree\n");
                    printf(CYAN"[5]"RESET"Display k most frequent words\n");
                    printf(CYAN"[6]"RESET"Generate Random Text\n");
                    printf(CYAN"[7]"RESET"Back to Main\n");
                    printf("Select Option: ");
                    scanf("%d", &opt2);

                    switch(opt2){
                        case 1:
                            splitWordsFromFile(&T, &A, 1, 0);
                            pause();
                            break;
                        case 2:
                            
                            printf("Enter Word to Search for: ");
                            scanf("%s", word);

                            freq = searchArray(A, word);

                            if(freq == -1){
                                printf(RED"Word not found on Dictionary"RESET);
                            }else{
                                printf(GRN"Seach Complete:"RESET"The word"GRN" %s "RESET"has a Freq of"GRN" %d " RESET, word, freq);
                            }
                            pause();
                            break;
                        case 3:
                            printf("Enter Word to Delete: ");
                            scanf("%s", word);
                            A = deletefromArray(A, word);
                            pause();
                            break;
                        
                        case 4:
                            displayArrayDictionary(A);
                            pause();
                            break;
                        
                        case 5:
                            printf("Enter how many words to Display: ");
                            scanf("%d", &k);
                            mostFrequent(A, k);
                            pause();
                            break;
                        case 6:
                            //to be added
                            break;
                        case 7: 
                            printf("Exiting to Main Menu............\n");
                            system(CLEAR_SCREEN);
                            loop1 = false;
                            break;
                        default:
                            printf(RED"Invalid Option"RESET);
                            pause();
                            break;
                    }

                }while(loop1);
                break;

            case 3:
                do{
                    printf(GRN  "BINARY SEARCH TREE\n"  RESET);
                    printf(CYAN"[1]"RESET"Read file and build dictionary\n");
                    printf(CYAN"[2]"RESET"Search for a word and display its frequency\n");
                    printf(CYAN"[3]"RESET"Delete Word\n");
                    printf(CYAN"[4]"RESET"Display Tree\n");
                    printf(CYAN"[5]"RESET"Display k most frequent words\n");
                    printf(CYAN"[6]"RESET"Generate Random Text\n");
                    printf(CYAN"[7]"RESET"Back to Main\n");
                    printf("Select Option: ");
                    scanf("%d", &opt3);

                    switch(opt3){
                        case 1:
                            int e = 0;
                            splitWordsFromFile(&T, &A, 3, &e);
                            pause();
                            break;
                        case 2:
                            
                            printf("Enter Word to Search for: ");
                            scanf("%s", word);

                            freq = searchABR(T, word);

                            if(freq == -1){
                                printf(RED"Word not found on Dictionary"RESET);
                            }else{
                                printf(GRN"Seach Complete:"RESET"The word"GRN" %s "RESET"has a Freq of"GRN" %d " RESET, word, freq);
                            }
                            pause();
                            break;
                        case 3:
                            printf("Enter Word to Delete: ");
                            scanf("%s", word);
                            T = deletefromABR(T, word);
                            printf(GRN"Process Complete"RESET);
                            pause();
                            break;

                        
                        case 4:
                            displayABRDictionary(T);
                            pause();

                            break;
                        
                        case 5:
                        /*
                            printf("Enter how many words to Display: ");
                            scanf("%d", &k);
                            mostFrequent(A, k);
                            break;
                        */
                        case 6:
                            //to be added
                            break;
                        case 7: 
                            printf("Exiting to Main Menu............\n");
                            system(CLEAR_SCREEN);
                            loop2 = false;
                            break;
                        default:
                            printf(RED"Invalid Option"RESET);
                            pause();
                            break;
                    }

                }while(loop2);
                break;
            default: 
                printf(RED"Sorry, Section not yet available\n");

        }

    }while(loop);
    freeABR(T);
  
    return 0;
}

