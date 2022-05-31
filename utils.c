#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "utils.h"
#include <conio.h>

char **Read_Split_Line_File(FILE *f, int n_campos_max, int *n_campos_lidos, char *separadores)
{
    *n_campos_lidos = 0;
    char *LT = (char *)malloc(sizeof(char) * MAX_LINHA_FICHEIRO);

    if (!f)
        return NULL;
    if (fgets(LT, MAX_LINHA_FICHEIRO, f) != NULL) // fgets l� uma linha do ficheiro de texto para a string LT
    {
        // "partir" a linha lida, usando os separadores definidos
        char **Res = (char **)malloc(n_campos_max * sizeof(char *)); // aloca��o de um array com n_campos_max ponteiros para STRING
        char *pch = strtok(LT, separadores);
        int cont = 0;
        while (pch != NULL)
        {
            Res[cont] = (char *)malloc((strlen(pch) + 1) * sizeof(char)); // aloca��o do espa�o necess�rio para guardar a string correspondente ao campo
            strcpy(Res[cont++], pch);
            pch = strtok(NULL, separadores);
        }
        *n_campos_lidos = cont;
        return Res;
    }
    return NULL;
};

int getNumberOfLinesInFile(FILE *f)
{
    int size = 0;
    char *LT = (char *)malloc(sizeof(char) * MAX_LINHA_FICHEIRO);
    while (fgets(LT, MAX_LINHA_FICHEIRO, f) != NULL)
    {
        size++;
    }
    rewind(f);

    /*long pos;
    pos = ftell(f); // guarda a posicao actual do ponteiro do ficheiro 
    fseek(f,0L, SEEK_END);
    size = ftell(f);
    fseek(f, pos, SEEK_SET);*/

    free(LT);
    return size;
}

FILE *openFile(char *fileName, char *mode)
{
    FILE *f = fopen(fileName, mode);
    if (f == NULL)
    {
        printf("Erro ao abrir o ficheiro: %s\n", fileName);
        return NULL;
    }
    return f;
}

char *replaceChar(char *str, char find, char replace)
{
    char *current_pos = strchr(str, find);
    while (current_pos)
    {
        *current_pos = replace;
        current_pos = strchr(current_pos, find);
    }
    return str;
}

bool contaisNumber(char *str)
{
    int i;
    for (i = 0; i < strlen(str); i++)
    {
        if (isdigit(str[i]))
            return true;
    }
    return false;
}

char *strToUpper(char *str)
{
    int i;
    for (i = 0; i < strlen(str); i++)
    {
        str[i] = toupper(str[i]);
    }
    return str;
}

bool isNumber(char *value)
{

    int point = 0;
    bool number = true;
    for (int i = 0; i < strlen(value); i++)
    {

        if (value[i] == '.' || value[i] == ',')
        {
            if (point > 0)
            {
                number = false;
                break;
            }

            point++;
        }
        else if (!isdigit(value[i]))
        {
            number = false;
            break;
        }
    }
    return number;
}


bool checkIfArrayContainsElement(int* array,int length, int element)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if (array[i] == element)
            return true;
    }
    return false;
}

int drawMenu(char *opcoes[], int numOpcoes, char *title)
{
    int key = 0;
    int option = 1;
    int biggerOption = 0;
    int i = 0;

    biggerOption = strlen(title);

    for (i = 0; i < numOpcoes; i++)
    {
        if (strlen(opcoes[i]) > biggerOption)
            biggerOption = strlen(opcoes[i]);
    }

    if (biggerOption == strlen(title))
        biggerOption += 10;

    do
    {
        system("cls");

        //printf("\n  ********     %s     ********\n\n", title);
        printf("\n  ");
        i = 0;
        for (i = 0; i < ceil(abs(((biggerOption + 14) - (strlen(title) + 10))) / 2.0); i++)
        {
            printf("*");
        }
        printf("     %s     ", title);
        i = 0;
        for (i = 0; i < abs(((biggerOption + 14) - (strlen(title) + 10))) / 2; i++)
        {
            printf("*");
        }
        printf("\n\n");

        i = 0;
        for (i = 0; i < numOpcoes; i++)
        {
            printf("    %s %s\n", (option == i + 1) ? "   \033[37;1m[\033[31;1mx\033[0m]\033[37;1m\033[0m" : "   \033[30;1m[ ]\033[0m", opcoes[i]);
        }
        printf("\n  ");
        i = 0;
        for (i = 0; i < 14 + biggerOption; i++)
        {
            printf("*");
        }

        printf("\n  Use as setas para selecionar uma opcao. ENTER para confimar. ESC para sair.\n");
        key = getch();
        fflush(stdin);

        if (key == KEY_ESC)
            return -1;

        if (key == KEY_UP)
        {
            if (option > 1)
                option--;
            else
                option = 1;
        }

        if (key == KEY_DOWN)
        {
            if (option < numOpcoes)
                option++;
            else
                option = numOpcoes;
        }

    } while (key != KEY_ENTER);

    return option;
}

char* concatString(const char *s1, const char *s2)
{
    const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2);
    char *result = malloc(len1 + len2 + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1); // +1 to copy the null-terminator
    return result;
}