#ifndef UTILS_H
#define UTILS_H

#include<stdio.h>

#define MAX_LINHA_FICHEIRO 300
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27
#define KEY_ENTER 13
#define KEY_SPACE 32
#define KEY_BACKSPACE 8

typedef struct datetime
{
    int day;
    int month;
    int year;

    int hour;
    int minute;
    int second;
} DATETIME;

typedef enum boolean { false, true } bool;

char **Read_Split_Line_File(FILE *f, int n_campos_max, int *n_campos_lidos, char *separadores);
int getNumberOfLinesInFile(FILE *f);
FILE *openFile(char *fileName, char *mode);
char* replaceChar(char* str, char find, char replace);
bool contaisNumber(char *str);
char* strToUpper(char *str);
bool isNumber(char* value);
bool checkIfArrayContainsElement(int* array,int length, int element);
int drawMenu(char *opcoes[], int numOpcoes, char *title);
char* concatString(const char *s1, const char *s2);

#endif