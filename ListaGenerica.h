#ifndef LISTAGENERICA_H_INCLUDED
#define LISTAGENERICA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define SUCESSO   1
#define INSUCESSO 0

typedef struct NOG
{
    void       *Info;
    struct NOG *Prox;
    struct NOG *Ant;
}NOG;
typedef struct
{
    NOG *Inicio;
    NOG *Fim;
    int NEL;
}ListaGenerica;

ListaGenerica *CriarLG();
void DestruirLG(ListaGenerica *L, void (*func)(void *));
int AddLG(ListaGenerica *L, void *X);
void MostrarLG(ListaGenerica *L, void (*fshow)(void *));
void MostrarRevLG(ListaGenerica *L, void (*fshow)(void *));
int AddFimLG(ListaGenerica *L, void *X);
int RemoveLG(ListaGenerica *L, void *X, int (*fcomp)(void *, void *));
int RemoveLG_Index(ListaGenerica *L, int Index, void (*func)(void *));

#endif // LISTAGENERICA_H_INCLUDED

