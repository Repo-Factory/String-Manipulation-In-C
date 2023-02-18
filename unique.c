/* 
    Students shall create a program in C which reads ASCII strings from the standard input 
until it reaches the EOF symbol. From the accumulated input, the program shall extract only its 
unique tokens, seperated by the space character, and send these to the standard output.

For example, if provided with a file containing a text document, it shall send to the 
standard output every unique word contained therein. 

The order the words appear in the 
output does not need to be sorted in any particular order. 

The program shall insert a space character between each output word and ignore line 
endings.

Program Name: unique
Command Line Args: none
Program Input: stdin
Program Output: stdout
Return: 0 on completion
Allowed Imports: Stdio.h
Example Use:
user@computer: $ ./unique<iamsam.txt */

#include <stdio.h>
#include <stdlib.h>


/* ABCD ABCC ABDD AYHU ABCD 

open a file

read words from the file

determine if the word is unique or a duplicate

Add to an array of words if unique

Ignore if a duplicate
Print the array of unique words

*/

/* Constants */
int BUFFER_LIMIT = 100;
int UNIQUE_WORDS_LIMIT = 10000;

/* Program Flow */
char* fillBuffer(char* buffer, int limit);
void read_words (FILE *f);
int isUnique(char* word, char* uniqueWords, char* currentPtr);
    int strEqual(char* stringOne, char* stringTwo);
char* addToArray(char* buffer, char* uniqueWords, char* currentPtr);



int main()
{
    char* buffer = (char*)(malloc(BUFFER_LIMIT*sizeof(char)));
    char* uniqueWords = (char*)(malloc(UNIQUE_WORDS_LIMIT*sizeof(char)));
    char* uniquePtr = uniqueWords;
    char* uniqueCurrent = uniqueWords;

    /* Scan the next word into buffer, if it's unique, place it in unique words */
    while (fscanf(stdin, " %100s", buffer) == 1) 
    {
        if (isUnique(buffer, uniqueWords, uniqueCurrent))
        {
            uniqueCurrent = addToArray(buffer, uniqueWords, uniqueCurrent);
        }
    }

    printf("%s", uniqueWords);

    free(buffer);
    free(uniqueWords);
    return 0;
}

int isUnique(char* word, char* uniqueWords, char* uniqueCurrent)
{ 
    char* currentWord = (char*)(malloc(BUFFER_LIMIT*sizeof(char)));
    char* currentWordPtr = currentWord;
    char* uniquePtr = uniqueWords;
    char* uniquePtr2 = uniqueWords;

    while (uniquePtr2 < uniqueCurrent)
    {
        while (*uniquePtr != ' ')
        {
            *currentWordPtr = *uniquePtr;
            currentWordPtr++;
            uniquePtr++;
            uniquePtr2++;
        }
        uniquePtr++;
        if (strEqual(word, currentWord))
        {
            return 0;
        }
    }
    free(currentWord);
    return 1;
}

char* addToArray(char* buffer, char* uniqueWords, char* currentPtr)
{
    char* bufferPtr = buffer;
    while (*bufferPtr)
    {
        *currentPtr = *bufferPtr;
        bufferPtr++;
        currentPtr++;
    }
    *currentPtr = ' ';
    currentPtr++;
    return currentPtr;
}

















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
