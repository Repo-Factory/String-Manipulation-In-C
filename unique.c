#include <stdio.h>
#define MAX_LENGTH 100


int isUnique(char word[], char wordList[MAX_LENGTH][MAX_LENGTH], int count);
int appendWord(char word[], char wordList[MAX_LENGTH][MAX_LENGTH], int count);


int isUnique(char word[], char wordList[MAX_LENGTH][MAX_LENGTH], int count)
{
    int i;
    int j;
    for (i = 0; i < count; i++)
    {
        j = 0;
        while (wordList[i][j] == word[j])
        {
            if (word[j] == '\0') {
                return 0;
            }
        j++;
        }
    }
    return 1;
}

int appendWord(char word[], char wordList[MAX_LENGTH][MAX_LENGTH], int count)
{
    int j = 0;
    while (word[j] != '\0') {
        wordList[count][j] = word[j];
        j++;
    }
    wordList[count][j] = '\0';
    count++;
    return count;
}

int main() {

    int wordCount = 0;
    char uniqueWords[MAX_LENGTH][MAX_LENGTH]; /* array to store uniqueWords */
    
    
    char word[MAX_LENGTH];                      /* Buffer to store next word */
    while (fscanf(stdin, "%s", word) != EOF) 
    {
        if (isUnique(word, uniqueWords, wordCount))
        {
            wordCount = appendWord(word, uniqueWords, wordCount);
        }            
    }
    
    // print unique uniqueWords
    for (int i = 0; i < wordCount; i++) 
    {
        fprintf(stdout, "%s ", uniqueWords[i]);
    }
    
    return 0;
}
