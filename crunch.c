#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_WORD_LEN 50


/*  @author: Conner Sommerfield
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
        void alertUser();
    struct WordList* selectRandom(struct WordList* wordList, int degree);
/*         END PROGRAM        */
    

/* Helper Functions */
int strEqual(char* stringOne, char* stringTwo);
int nextArgValid(int argc, int index);
int flagIs(char* arg, char* flag);
void setArgToNext(int* argVar, char* currentArg);

int appendWord(char word[], char wordList[MAX_WORD_LEN][MAX_WORD_LEN], int count);
int isUnique(char word[], char wordList[MAX_WORD_LEN][MAX_WORD_LEN], int count);
void alertUser();
void printWords(char wordList[MAX_WORD_LEN][MAX_WORD_LEN], int count, int crunch);


/* ********************************************************************************************************** */


struct Arguments 
{
    int degreeFlag; // -d
    int sizeFlag; // -m
    int countFlag; // -n
    int spaceFlag; // -s
};

/* Set Default Args, Return in struct to be passed easily */
struct Arguments* initArgs()
{
    struct Arguments* argsPtr = (struct Arguments*)malloc(sizeof(struct Arguments));
    argsPtr->degreeFlag = 4;
    argsPtr->sizeFlag = 6;
    argsPtr->countFlag = 1;
    argsPtr->spaceFlag = 0;
    return argsPtr;
}

int main (int argc, char** argv)
{
    struct Arguments* arguments = initArgs();
    
    /* Iterate Through Each Argument Passed And Print Value */
    for (int i = 0; i < argc; i++) 
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
    return (strEqual(currentArg, flag) == 1) ? 1 : 0; 
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
    return !((index + 1) > (argc - 1)) ?  1 : 0; 
}

/* Convert next argument to integer and store in arguments struct */
void setArgToNext(int* argVar, char* currentArg)
{
    *argVar = atoi(currentArg+3); 
}


/****************************************AFTER ARGUMENT HANDLING************************************************/


struct WordList
{
    int size;
    char words[MAX_WORD_LEN][MAX_WORD_LEN];
};

/* Returns a struct that contains a 2D string array and the number of words it contains */
struct WordList* generateWordlist()
{
    struct WordList* wordList = (struct WordList*)malloc(sizeof(struct WordList));
    char buffer[MAX_WORD_LEN];
    int i = 0; int j = 0;

    while ((fscanf(stdin, "%s", buffer) != EOF))
    {
        j = 0;
        while (buffer[j] != '\0')
        {
            wordList->words[i][j] = buffer[j];
            j++;
        }
        wordList->words[i][j] = '\0';
        i++;
        j++;
    }

    wordList->size = i;
    return wordList;
}

/* Fill Buffer, Perform Output Based On Requirement */
void crunch(struct Arguments* arguments)
{
    struct WordList* wordList = generateWordlist();
    struct WordList* validWords = restrictLength(wordList, arguments->sizeFlag);
    
    struct WordList* randomWords;
    for (int i = 0; i < arguments->countFlag; i++)
    {
        randomWords = selectRandom(validWords, arguments->degreeFlag);
        printWords(randomWords->words, randomWords->size, arguments->spaceFlag);
        printf(" ");
    }

    free(validWords);
    free(wordList);
    free(randomWords);
}

/*  */
struct WordList* restrictLength(struct WordList* wordlist, int minLength)
{
    struct WordList* validWords = (struct WordList*)malloc(sizeof(struct WordList));
    int i = 0; int j = 0; int wordLength = 0; validWords->size = 0;

    for (i = 0; i < wordlist->size; i++)
    {
        while (wordlist->words[i][j] != '\0')
        {
            wordLength++;
            j++;
        }
        if (wordLength >= minLength)
        {
            validWords->size = appendWord(wordlist->words[i], validWords->words, validWords->size);
        }
        wordLength = 0;
        j = 0;
    }
    if (validWords->size == 0)
    {
        alertUser();
    }
    return validWords;
}

/*  */
struct WordList* selectRandom(struct WordList* wordList, int degree)
{
    struct WordList* randomWords = (struct WordList*)malloc(sizeof(struct WordList));

    srand((long int)randomWords);                                         // seed the random generator

    if (wordList->size == 0 || wordList->size < degree) {return randomWords;}          // Can't select from empty list

    for (int i = 0; i < degree; i++)
    {
        int randomIndex = rand() % wordList->size;          // Pick random index in range [0 : wordlist size]
        if (!isUnique(wordList->words[randomIndex], randomWords->words, wordList->size)) 
        {
            i--;                                            // Don't count iteration if word not selected
            continue;                                       // Don't pick same word twice
        }
        randomWords->size = appendWord(wordList->words[randomIndex], randomWords->words, randomWords->size);
    }
    return randomWords;
}

/*  */
int appendWord(char word[], char wordList[MAX_WORD_LEN][MAX_WORD_LEN], int count)
{
    int j = 0;
    while (word[j] != '\0')
    {
        wordList[count][j] = word[j];      // Set letters of current word in list to letters of word 
        j++;
    }
    wordList[count][j] = '\0';
    count++;                               // Needed so we can differentiate between strings
    return count;                          // Number of words in list increased by 1
}

/*  */
int isUnique(char word[], char wordList[MAX_WORD_LEN][MAX_WORD_LEN], int count)
{
    int i;
    int j;
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

/*  */
void printWords(char wordList[MAX_WORD_LEN][MAX_WORD_LEN], int wordCount, int crunch)
{
    for (int i = 0; i < wordCount; i++) 
    {   
        if (crunch)
        {
            fprintf(stdout, "%s", wordList[i]); 
        }
        else
        {
            fprintf(stdout, "%s ", wordList[i]);
        }
    }
}

/*  */
void alertUser()
{
    printf("There aren't any words in the text with that length, sorry!\n");
}

