
#include "ListaGenerica.h"

ListaGenerica *CriarLG()
{
    ListaGenerica *L = (ListaGenerica *)malloc(sizeof(ListaGenerica));
    L->Inicio = NULL;
    L->Fim = NULL;
    L->UltimaConsulta = NULL;
    L->IndexUltimaConsulta = -1;
    L->NEL = 0;
    return L;
}
void DestruirLG(ListaGenerica *L, void (*func)(void *))
{
    if (!L) return;
    NOG *P = L->Inicio;
    NOG *Aux;
    while (P)
    {
        Aux = P->Prox;
        func(P->Info);
        free(P);
        P = Aux;
    }
    free(L);
}
int AddLG(ListaGenerica *L, void *X)
{
    NOG *N = (NOG *)malloc(sizeof(NOG));
    N->Info = X;
    N->Prox = L->Inicio;
    N->Ant = NULL;
    if (L->Inicio)
        L->Inicio->Ant = N;
    else
        L->Fim = N;
    L->Inicio = N;
    L->NEL++;

    return SUCESSO;
}
void MostrarLG(ListaGenerica *L, void (*fshow)(void *))
{
    if (L == NULL) return;
    if (!L->Inicio) return;
    NOG *P = L->Inicio;
    while (P != NULL)
    {
        fshow(P->Info);
        P = P->Prox;
    }
}

void MostrarRevLG(ListaGenerica *L, void (*fshow)(void *))
{
    if (L == NULL) return;
    if (!L->Fim) return;
    NOG *P = L->Fim;
    while (P != NULL)
    {
        fshow(P->Info);
        P = P->Ant;
    }
}
