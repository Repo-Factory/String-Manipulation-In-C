#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_WORD_LEN 30
#define MAX_WORDS 1000

/*  
 *  @author: Conner Sommerfield
 *  Program to pick random strings from stdin and output them to the user with conditions provided at command line
 * -d <degree> Number of words from input stream to combine in each crunched output (default = 4). 
 * -m <size> The minimum length of each word used (default = 6). 
 * -n <count> Number of output strings to produce (default = 1). 
 * -s Indicates to insert a space between the output words (default = none)
 */


/* Structs */
struct Arguments;
struct WordList;


/* Program Flow - Main Implied */
struct Arguments* initArgs();
void crunch(struct Arguments* arguments);
    struct WordList* generateWordlist(); 
    struct WordList* restrictLength(struct WordList*, int minLength);
    struct WordList* selectRandom(struct WordList* wordList, int degree);
    void printWords(char wordList[MAX_WORDS][MAX_WORD_LEN], int count, int crunch);
/*         END PROGRAM        */
    

/* Helper Functions */
int strEqual(char* stringOne, char* stringTwo);
int flagIs(char* arg, char* flag);
int nextArgValid(int argc, int index);
void setArgToNext(int* argVar, char* currentArg);

int appendWord(char word[], char wordList[MAX_WORDS][MAX_WORD_LEN], int count);
int isUnique(char word[], char wordList[MAX_WORDS][MAX_WORD_LEN], int count);
void alertUser(char* message);


/* ********************************************************************************************************** */


/* All args will be stored in one struct to pass around easily */
struct Arguments 
{
    int degreeFlag; // -d
    int sizeFlag; // -m
    int countFlag; // -n
    int spaceFlag; // -s
};

/* Set Args to default values */
struct Arguments* initArgs()
{
    struct Arguments* argsPtr = (struct Arguments*)malloc(sizeof(struct Arguments));
    argsPtr->degreeFlag = 4;
    argsPtr->sizeFlag = 6;
    argsPtr->countFlag = 1;
    argsPtr->spaceFlag = 0;
    return argsPtr;
}

/* Handles arguments and calls crunch function to perform functionality */
int main (int argc, char** argv)
{
    struct Arguments* arguments = initArgs();      // Set args to default values
    
    for (int i = 0; i < argc; i++)
    /* Iterate Through Each Argument Set Values Based On Flag And Number Passed In */
    {
        char* currentArg = argv[i];

            if (flagIs(currentArg, "-d"))
            {
                if (nextArgValid(argc, i))        /* Avoid segmentation fault by checking if arg passed after flag. If not, arg set to 0 */
                {
                    setArgToNext(&arguments->degreeFlag, currentArg);  /* Set value of flag variable to next passed value */
                }
            }
            if (flagIs(currentArg, "-m"))
            {
                if (nextArgValid(argc, i))       
                {
                    setArgToNext(&arguments->sizeFlag, currentArg);   
                }
            }
            if (flagIs(currentArg, "-n"))
            {
                if (nextArgValid(argc, i))        
                {
                    setArgToNext(&arguments->countFlag, currentArg);   
                }
            }
            if (flagIs(currentArg, "-s"))
            {
                arguments->spaceFlag = 1;
            }
    }

    /* Show user all args */
    printf("degreeFlag = %d\n", arguments->degreeFlag);
    printf("sizeFlag = %d\n", arguments->sizeFlag); 
    printf("countFlag = %d\n", arguments->countFlag); 
    printf("spaceFlag = %d\n", arguments->spaceFlag);
    printf("\n\n");

    crunch(arguments);                          /* Run Functionality */
    free(arguments);                            /* Cleanup */

    return 0;
}

/* Used to list flag options */
int flagIs(char* currentArg, char* flag)
{
    return (strEqual(currentArg, flag));       // return true if user passes in given flag 
}

/* Helper function equivalent to standard library strcmp() function */
int strEqual(char* stringOne, char* stringTwo)
{
    // iterate through string, if a character differs return false
    while (*stringOne)
    {
        if (*stringOne != *stringTwo) { return 0; }
        stringOne++;
        stringTwo++;
    }
    return 1; // if end of string reached with no difference, return true
}

/* Checks if arg after current isn't out of bounds of arg count */
int nextArgValid(int argc, int index)
{
    return !((index + 1) > (argc - 1));     // If next index is greater than argument amount, we are out of bounds
}

/* Convert next argument to integer and store in arguments struct */
void setArgToNext(int* argVar, char* currentArg)
{
    *argVar = atoi(currentArg+3); 
}


/****************************************AFTER ARGUMENT HANDLING************************************************/

/* Think of this as a 2D word array that also stores the number of words it contains */
struct WordList
{
    int size;
    char words[MAX_WORDS][MAX_WORD_LEN];         
};

/* Create a 2D array that contains all the words that are passed to stdin */
struct WordList* generateWordlist()
{
    struct WordList* wordList = (struct WordList*)malloc(sizeof(struct WordList));
    char buffer[MAX_WORD_LEN];                      // Temporarily hold words
    int i = 0; int j = 0;                           // Current word; current letter

    while ((fscanf(stdin, "%s", buffer) != EOF))
    /* Scan word-by-word from stdin into bufer. 
     * i refers to current word | j refers to current letter
     * Then copy from the buffer to the wordlist until a \0 is reached
     * Here we can start our new word, so we increment i and place \0 to finish the previous string
     */
    {
        j = 0;
        while (buffer[j] != '\0')
        {
            wordList->words[i][j] = buffer[j];
            j++;
        }
        wordList->words[i][j] = '\0';
        i++;
    }

    wordList->size = i;
    return wordList;
}

/* Get word list from input and output desired strings based on user arguments */
void crunch(struct Arguments* arguments)
{
    struct WordList* wordList = generateWordlist();                               // Put words from input in list
    struct WordList* validWords = restrictLength(wordList, arguments->sizeFlag);  // Get words only of size sizeFlag
    struct WordList* randomWords;

    for (int i = 0; i < arguments->countFlag; i++)                                // Print countFlag # of wordStrings
    {
        randomWords = selectRandom(validWords, arguments->degreeFlag);            // select d flag valid words for wordString
        printWords(randomWords->words, randomWords->size, arguments->spaceFlag);  // print random strings with space or no space
        printf(" ");                                                              // Place space in between random strings
    }

    printf("\n");
    free(randomWords);                                                            // Cleanup
    free(validWords);
    free(wordList);
}

/* Make a new list of words and only places in words that fit the length requirement */
struct WordList* restrictLength(struct WordList* wordlist, int minLength)
{
    struct WordList* validWords = (struct WordList*)malloc(sizeof(struct WordList));
    int i = 0; int j = 0; int wordLength = 0; validWords->size = 0;

    for (i = 0; i < wordlist->size; i++)
    /* 
     * i will refer to current word
     * j will refer to current letter
     * wordLength will hold the length of current word
     * increment wordLength until reaching a null termination 
     */
    {
        while (wordlist->words[i][j] != '\0')
        {
            wordLength++;
            j++;
        }
        /* Any word that has a length > than our specified -m flag can be added to our list */
        if (wordLength >= minLength)
        {
            validWords->size = appendWord(wordlist->words[i], validWords->words, validWords->size);
        }
        wordLength = 0;                         // Reset our variables
        j = 0;
    }
    if (validWords->size == 0)                  // If we find no words of given size, can't create strings 
    {
        alertUser("There aren't any words in the text with that length, try inputing a smaller -m flag!\n");
    }
    return validWords;
}

/* Selects a number of random words from a list based on desired amount */
struct WordList* selectRandom(struct WordList* wordList, int degree)
{
    struct WordList* randomWords = (struct WordList*)malloc(sizeof(struct WordList));

    srand((long int)randomWords);                           // seed the random generator using array address

    if (wordList->size == 0 || wordList->size < degree)     // Can't select from empty or short list
    {
        alertUser("There aren't enough words in the text with that length, try inputing a smaller -d flag!\n");
    }    

    for (int i = 0; i < degree; i++)
    {
        int randomIndex = rand() % wordList->size;          // Pick random index in range [0 : wordlist size]
        if (!isUnique(wordList->words[randomIndex], randomWords->words, wordList->size)) 
        {                                                   // If word already in our string, don't select
            i--;                                            // Don't count iteration since word not selected
            continue;                                       // Try picking again
        }
        randomWords->size = appendWord(wordList->words[randomIndex], randomWords->words, randomWords->size);
    }                                                       // If word is selected, append and increment size
    return randomWords;
}

/* Adds a word to an existing list and returns its size + 1 */
int appendWord(char word[], char wordList[MAX_WORD_LEN][MAX_WORD_LEN], int count)
{
    /* Count holds how many words in list, we want to append the word at next available spot */
    int j = 0;
    while (word[j] != '\0')
    {
        wordList[count][j] = word[j];      // Set letters of empty word in list to letters of word 
        j++;
    }
    wordList[count][j] = '\0';             // Once we reach termination, place \0 to mark new string
    count++;                               // Number of words in list increased by 1
    return count;                         
}

/* Determines if a word is already in a list */
int isUnique(char word[], char wordList[MAX_WORD_LEN][MAX_WORD_LEN], int count)
{
    int i; int j;                             // i is word, j is letter
    for (i = 0; i < count; i++)               // For each words in list
    {
        j = 0;
        while (wordList[i][j] == word[j])     // compare each letter of word in list and word in question
        {
            if (word[j] == '\0') {            // if null character reached we know words are equal, not unique
                return 0;
            }
        j++;
        }
    }
    return 1;
}

/* Print all words in list */
void printWords(char wordList[MAX_WORD_LEN][MAX_WORD_LEN], int wordCount, int crunch)
{
    for (int i = 0; i < wordCount; i++)             // i indicates current word in list
    /* 
     * If -s flag passed in, the words will be crunched together with space,
     * otherwise default is that strings are printed with no space 
     */
    {   
        if (crunch)
        {
            fprintf(stdout, "%s ", wordList[i]);    // Note space at end of string
        }
        else
        {
            fprintf(stdout, "%s", wordList[i]);       
        }
    }
}

/* Give user suggestion on how to fix problems with getting desired output */
void alertUser(char* message)
{
    printf("%s", message);
    exit(0);                // Exit program so user can try again
}
