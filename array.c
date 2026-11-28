//Hey Prince

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXlen 100000
#define MAX 100

typedef struct{
    char word[MAX]; //stores the word itself
    int freq; // stores how many times the word appears in the text
}dictionary;

// Define a structure to hold an array of dictionary entries
typedef struct{
    dictionary dictTab[MAXlen]; // array of dictionary entries
    int n; // number of words currently stored in the array
}Array;

// Procedure to convert a word to lowercase
void lowercase(char word[]){
    int i = 0;
    while(word[i] != '\0'){  // continue until we reach the end of the string
        word[i] = tolower((unsigned char)(word[i]));
        i++;
    }
}

//Procedure to initialize the array
void initialise(Array *A){
    A->n = 0; //at the beginning, the array is empty, so we set the number of words to 0
}

// Function to search for a word in the array using binary search
int search(Array *A, char word[]){
    // low and high defines the current search intervals
    int low = 0;
    int high = A->n - 1;

    while(low <= high){
        // calculate the middle index of the current search interval
        int mid = (low + high) / 2; 
        // compares the searched word with the word at the middle index
        int compare = strcmp(word, A->dictTab[mid].word); 
        // if both words are equal, we found the word and return its index
        if(compare == 0){
            return mid;
        //if the word comes alphabetically before the middle word, we search in the left half of the dictionary
        }else if(compare < 0){
            high = mid - 1; 
        // otherwise, we search in the right half of the dictionary
        }else{
            low = mid + 1;
        }
    }
    // return -1 if the word is not found in the dictionary
    return -1;
}

// Procedure to add a word to the array or increase its frequency if it already exists
void addword(Array *A, char word[]){
    // First, we search for the word in the dictionary
    int index = search(A, word);
    // If the word is found, we increase its frequency and return
    if(index != -1){
        A->dictTab[index].freq++;
        return;
    }

    //check wheter the dictionary have reached it maximum capacity, if so we print an error message and return
    if(A->n >= MAXlen){
        printf("Dictionary, cannot add more words.\n");
        return;
    }

    /*
    start from the last occupied position in the array and move backwards,
    shifting words to the right until we find the correct position for the new word
     */
    int pos = A->n - 1;
    while(pos >= 0 && strcmp(word, A->dictTab[pos].word) < 0){
        // shift the current entry one position to the right
        A->dictTab[pos + 1] = A->dictTab[pos];
        pos--; // move to the previous position
    }
    /*
     insert the new entry at the correct position and set its frequency to 1 and then increase the number of dictionary entries
     */
    strcpy(A->dictTab[pos + 1].word, word);
    A->dictTab[pos + 1].freq = 1;
    A->n++;
}
// Function to delete a word from the array
int deleteword(Array *A, char word[]){
    // search for the word in the dictionary
    int index = search(A, word);
    // if the word is not found, return 0 to indicate failure
    if(index == -1){
        return 0; 
    }
    // shift all words after the found word one position to the left to fill the gap
    for(int pos = index; pos < A->n - 1; pos++){
        A->dictTab[pos] = A->dictTab[pos + 1];
    }
    A->n--; // decrease the number of words in the dictionary
    return 1; 
}

// Procedure to display the contents of the dictionary and their frequencies
void displayDictionary(Array *A){
    for(int i = 0; i < A->n; i++){
        printf("%s : %d\n", 
            A->dictTab[i].word, 
            A->dictTab[i].freq
        );
    }
}

// Procedure to find and display the most frequent words in the dictionary using counting sort algorithm
void MostFrequent(Array *A, int Nbwords){
    //checks if the dictionary is empty, if so it prints a message and returns
    if(A->n == 0){
        printf("The dictionary is empty\n");
        return;
    }
    // find the maximum frequency in the dictionary to determine the size of the counting array
    int fmax = 0;
    for(int i = 0; i < A->n; i++){
        if(A->dictTab[i].freq > fmax){
            fmax = A->dictTab[i].freq;
        }
    }
    /*
    allocate an array to count how words have each frequency,
     index represents the frequency
    */
    int *count = calloc(fmax + 1, sizeof(int));
    /*
     allocate an array to store the order of words based on their frequencies, arranged by decreasing frequency
     */
    int *order = malloc(A->n * sizeof(int));

    // ensures if the memory was successfully allocated
    if(count == NULL || order == NULL){
        printf("memory allocation failed\n");
        free(count);
        free(order);
        return;
    }
    // count how many words have each frequency
    for(int i = 0; i < A->n; i++){
        count[A->dictTab[i].freq]++;
    }

    /*
     calculate the starting index for each frequency
     we start from the highest frequency and move downwards
    */
    int start = 0;
    for(int f = fmax; f >= 0; f--){
        // number of words having frequency f
        int c = count[f];
        // set the starting index for frequency f
        count[f] = start;
        // update the starting index for the next lower frequency
        start += c;
    }

    //place the dictionary indices in order of decreasing frequencies
    for(int i = 0; i < A->n; i++){
        // place the index of the word in the order array based on its frequency
        order[count[A->dictTab[i].freq]++] = i;
        // increment the count for that frequency to point to the next position
    }
    // limits the result to the dictionary size if the requested number of words exceeds it
    if(Nbwords > A->n){
        Nbwords = A->n;
    }

    // prevents invalid requests
    if(Nbwords <= 0){
        return;
    }
    // display the most frequent words along with their frequencies
    for(int rank = 0; rank < Nbwords; rank++){
        //order[rank] gives the index of the word in the original dictionary dictionary
        printf("%d : %s : %d\n", 
            rank + 1, A->dictTab[order[rank]].word,
             A->dictTab[order[rank]].freq
            );
    }

    free(count);
    free(order);
}

// declare the global dictionary array
Array A;

int main(){
    // initialise the dictionary before using it
    initialise(&A);
    //open an input file in reading mode
    FILE *f = fopen("input.csv", "r");

   // check if the file was opened successfully
    if(!f){
        printf("error in openning the file");
        return 1;
    }

    char line[MAX];// buffer used to temporarily store the word being read
    int length = 0;// tracks the length of the current word being read
    int ch; // variable to store each character read from the file

    // read the file character by character until the end of the file is reached
    if((ch = fgetc(f)) != EOF){
        // If the character is a letter, a space, or an apostrophe,
        // add it to the temporary buffer
        if(isalpha((unsigned char)ch) || ch == ' ' || ch == '\''){
            // ensure we dont exceed the maximum length of the buffer
            if(length < MAX - 1){
                // add the character to the buffer and increment the length
                line[lenght] = (char)ch;
                length++;
            }
        // if the character is not accepted, it acts as a sepator, and we process the current word in the buffer
        }else if(length > 0){
            line[length] = '\0';// terminate the string in the buffer
            lowercase(line); // convert the word to lowercase before adding it to the dictionary
            addword(&A, line); // add the word to the dictionary
            length = 0; // initialise the buffer length for the next word
        }
    }
    // after the loop, if there is still a word in the buffer, we process it
    if(length > 0){
        line[length] = '\0';// terminate the string in the buffer
        lowercase(line); // convert the word to lowercase before adding it to the dictionary
        addword(&A, line); // add the word to the dictionary
    }
    fclose(f); // close the input file after reading all words
    
    displayDictionary(&A); // display the contents of the dictionary along with their frequencies
    printf("\nMost frequent words:\n"); // display the most frequent words in the dictionary
    MostFrequent(&A, 10);// diplay 10 most frequent words

    return 0;

}
