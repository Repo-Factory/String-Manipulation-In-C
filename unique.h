#include <stdio.h>
#define WORD_LENGTH 50

int nextWordExists(char buffer[]);
int isUnique(char word[], char wordList[WORD_LENGTH][WORD_LENGTH], int count);
int appendWord(char word[], char wordList[WORD_LENGTH][WORD_LENGTH], int count);
void printWords(char wordList[WORD_LENGTH][WORD_LENGTH], int count);
