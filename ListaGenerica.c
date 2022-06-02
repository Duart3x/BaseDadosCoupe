
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

int AddFimLG(ListaGenerica *L, void *X)
{
    NOG *N = (NOG *)malloc(sizeof(NOG));
    N->Info = X;
    N->Prox = NULL;
    
    N->Ant = L->Fim;

    if(L->Fim)
        L->Fim->Prox = N;

    if(L->Inicio == NULL)
        L->Inicio = N;

    L->Fim = N;
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


// Remover elemento da lista

int RemoveLG(ListaGenerica *L, void *X, int (*fcomp)(void *, void *))
{
    if (L == NULL) return INSUCESSO;
    if (!L->Inicio) return INSUCESSO;
    NOG *P = L->Inicio;
    while (P != NULL)
    {
        if (fcomp(P->Info, X) == 0)
        {
            if (P->Ant)
                P->Ant->Prox = P->Prox;
            else
                L->Inicio = P->Prox;
            if (P->Prox)
                P->Prox->Ant = P->Ant;
            else
                L->Fim = P->Ant;
            free(P);
            L->NEL--;
            return SUCESSO;
        }
        
        P = P->Prox;
    }
    return INSUCESSO;
}

int RemoveLG_Index(ListaGenerica *L, int Index, void (*func)(void *))
{
    if (L == NULL) return INSUCESSO;
    if (!L->Inicio) return INSUCESSO;
    if (Index < 0 || Index >= L->NEL) return INSUCESSO;
    NOG *P = L->Inicio;
    int i = 0;
    while (P != NULL)
    {
        if (i == Index)
        {
            if (P->Ant)
                P->Ant->Prox = P->Prox;
            else
                L->Inicio = P->Prox;
            if (P->Prox)
                P->Prox->Ant = P->Ant;
            else
                L->Fim = P->Ant;
            
            func(P->Info);
            free(P);
            L->NEL--;
            return SUCESSO;
        }
        P = P->Prox;
        i++;
    }
    return INSUCESSO;
}