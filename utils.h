#include<stdio.h>


#ifndef UTILS_H
#define UTILS_H

#define MAX_LINHA_FICHEIRO 300

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
#endif