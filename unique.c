#include <stdio.h>
#define WORD_LENGTH 50

/* Program Flow */
int nextWordExists(char buffer[]);
int isUnique(char word[], char wordList[WORD_LENGTH][WORD_LENGTH], int count);
int appendWord(char word[], char wordList[WORD_LENGTH][WORD_LENGTH], int count);
void printWords(char wordList[WORD_LENGTH][WORD_LENGTH], int count);

int main() {

    int wordCount = 0;
    char uniqueWords[WORD_LENGTH][WORD_LENGTH];     // Empty list that will store words
    char buffer[WORD_LENGTH];                       // Will temporarily store each word

    while (nextWordExists(buffer))                  // Read next word from input into buffer
    {
        if (isUnique(buffer, uniqueWords, wordCount))
        {
            wordCount = appendWord(buffer, uniqueWords, wordCount);
        }            
    }
    
    printWords(uniqueWords, wordCount);
    
    return 0;
}

/* If stdin has more input, place it into the buffer */
int nextWordExists(char buffer[])
{
    return (fscanf(stdin, "%s", buffer) != EOF) ? 1 : 0;
}

/* Compares current word to every word in our list and return 0 if it finds a match */
int isUnique(char word[], char wordList[WORD_LENGTH][WORD_LENGTH], int count)
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

/* Adds our unique word to the list and returns the new number of words in the list (previous + 1) */
int appendWord(char word[], char wordList[WORD_LENGTH][WORD_LENGTH], int count)
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

/* Simple helper to print words of list */
void printWords(char wordList[WORD_LENGTH][WORD_LENGTH], int count)
{
    for (int i = 0; i < count; i++) 
    {
        fprintf(stdout, "%s ", wordList[i]); 
    }
}