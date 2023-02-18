#include <stdio.h>
#define MAX_LENGTH 100

int main() {
    char uniqueWords[MAX_LENGTH][MAX_LENGTH]; // array to store uniqueWords
    int uniqueCount = 0;
    
    // read one word from stdin
    char word[MAX_LENGTH];
    while (fscanf(stdin, "%s", word) != EOF) {
        
        // check if word is already in array
        int found = 0;
        for (int i = 0; i < uniqueCount; i++) {
            int j = 0;
            while (uniqueWords[i][j] == word[j]) {
                if (word[j] == '\0') {
                    found = 1;
                    break;
                }
                j++;
            }
        }
        
        // add new word to array
        if (!found) {
            int j = 0;
            while (word[j] != '\0') {
                uniqueWords[uniqueCount][j] = word[j];
                j++;
            }
            uniqueWords[uniqueCount][j] = '\0';
            uniqueCount++;
        }
    }
    
    // print unique uniqueWords
    for (int i = 0; i < uniqueCount; i++) {
            fprintf(stdout, "%s\n", uniqueWords[i]);
        }
    
    
    return 0;
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
