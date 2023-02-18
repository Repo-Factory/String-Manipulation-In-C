#include <stdio.h>
#define MAX_LENGTH 100


int isUnique(char word[], char* wordList[], int count);


int isUnique(char word[], char* wordList[], int count)
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
        }
    }
    return 1;
}

int main() {
    char uniqueWords[MAX_LENGTH][MAX_LENGTH]; // array to store uniqueWords
    int uniqueCount = 0;
    
    // read one word from stdin
    char word[MAX_LENGTH];



    while (fscanf(stdin, "%s", word) != EOF) {


        if (isUnique(word, (char**)uniqueWords, uniqueCount))
        {
            int j = 0;
            while (word[j] != '\0') {
                uniqueWords[uniqueCount][j] = word[j];
                j++;
            }
            uniqueWords[uniqueCount][j] = '\0';
            uniqueCount++;
        }    
        // check if word is already in array
        
        
        // add new word to array
        
    }
    
    // print unique uniqueWords
    for (int i = 0; i < uniqueCount; i++) {
            fprintf(stdout, "%s\n", uniqueWords[i]);
        }
    
    
    return 0;
}
