#include "crunch.h"
#include <string.h>
#define MAX_WORD_LEN 50


/*  This program randomly combines words contained in its input stream and sends them 
to the output stream. At program execution, the application shall read in the entire set of words 
to use during the combination process. After reaching the EOF symbol, the program shall then 
begin randomly selecting words and combining them into a concatenated output word. By 
default, the program produces only one combined output word for each execution, but users 
may change this behavior by providing an optional command line argument (through *argv). 

    The words the program selects must meet minimum length criteria, and users may also 
change this value at program execution to meet their needs. The program must accept this.
 By default, the program squeezes the words together and omits any spacing between 
them (e.g., somewhatlikethisbutrandom), but users may override this behavior with a command 
line argument as well, and the program will produce output with the user specified parameter.
The command line arguments may appear in any order.

    When unable to construct strings meeting the minimum length from the input stream, 
the program shall alert the user to an error and suggest corrective action.
 There shall be no duplicate words in any single output combination, but the same word 
may appear twice in the total output when producing more than one string (i.e. -n specified >1)

Program Name: crunch
    Command Line Args: -d <degree> Number of words from input stream to combine in each 
    crunched output (default =4). 
    -m <size> The minimum length of each word used (default =6). 
    -n <count> Number of output strings to produce (default =1). 
    -s Indicates to insert a space between the output words 
    (default=none).
    Program Input: stdin
    Program Output: stdout
    Return: 0 on completion
    Allowed Imports: stdio.h stdlib.h time.h */

/* Constants */
struct Arguments;
struct WordList;

/* Program Flow */
struct Arguments* initArgs();
struct WordList* generateWordlist();
void crunch(struct Arguments* arguments);
    char** fillWordList(char buffer[MAX_WORD_LEN][MAX_WORD_LEN]);
    char* selectRandomWords(char* wordStream, int minLength);
        int canConstruct();
        void alertUser();
    void splitRandomWords(char* wordStream, int wordPreference);
    void removeSpace(char* wordStream, int shouldRemove);



/* Helper Functions */
int strEqual(char* stringOne, char* stringTwo);
int nextArgValid(int argc, int index);
int flagIs(char* arg, char* flag);
void setArgToNext(int* argVar, char* currentArg);

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
                printf("degreeFlag = %d\n", arguments->degreeFlag);
            }
            if (flagIs(currentArg, "-m"))
            {
                if (nextArgValid(argc, i))       
                {
                    setArgToNext(&arguments->sizeFlag, currentArg);   
                }
                printf("sizeFlag = %d\n", arguments->sizeFlag); 
            }
            if (flagIs(currentArg, "-n"))
            {
                if (nextArgValid(argc, i))        
                {
                    setArgToNext(&arguments->countFlag, currentArg);   
                }
                printf("countFlag = %d\n", arguments->countFlag); 
            }
            if (flagIs(currentArg, "-s"))
            {
                arguments->spaceFlag == 1;
                printf("spaceFlag = %d\n", arguments->spaceFlag);
            }
    }

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

void printWords(char wordList[MAX_WORD_LEN][MAX_WORD_LEN], int count)
{
    for (int i = 0; i < count; i++) 
    {
        fprintf(stdout, "%s ", wordList[i]); 
    }
}


/****************************************AFTER ARGUMENT HANDLING************************************************/


struct WordList
{
    int size;
    char words[MAX_WORD_LEN][MAX_WORD_LEN];
};

struct WordList* generateWordlist()
{
    struct WordList* wordList = (struct WordList*)malloc(sizeof(struct WordList));
    int i = 0;
    int j = 0;
    char buffer[MAX_WORD_LEN];

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
    printWords(wordList->words, wordList->size);
}

char* selectRandomWords(char* wordStream, int minLength)
{
    // char buffer[MAX_WORD_LEN];
    // int i = 0;
    // int currLength = 0;

    // while (*wordStream != EOF)
    // {
    //     wordStream[i];

    //     if (strEqual(wordStream[i], " "))
    //     {
    //         currLength = 0;
    //     }
    // }
}

int canConstruct()
{

}

void alertUser()
{

}


/* Given pointer to buffer array, fills it until stdin EOF or defined limit reached */


// int nextChar;
//     int index = 0;

//     while ((nextChar = getchar()) != EOF && index < limit) /* Use Standard getChar() to place stream into array */
//     {
//         buffer[index] = nextChar;
//         ++index;
//     }

//     for (int i = 0; i < index; ++i)
//         putchar(buffer[i]);
//         putchar('\n'); 
    
//     return buffer;

