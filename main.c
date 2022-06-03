#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include <conio.h>
#include "BDadosCoupe.h"

BDadosCoupe *GetSelectBDCoupByIndex(ListaGenerica *X, int op)
{

    NOG *aux = X->Inicio;
    BDadosCoupe *bd = NULL;
    int i = 0;

    while (aux != NULL)
    {
        bd = aux->Info;
        if (i == op - 1)
        {
            return bd;
        }
        aux = aux->Prox;
        i++;
    }
    return NULL;
}
TABELA *GetSelectedTableByIndex(BDadosCoupe *BD, int op)
{
    NOG *aux = BD->LTabelas->Inicio;
    TABELA *T = NULL;
    int i = 0;
    while (aux != NULL)
    {
        T = aux->Info;
        if (i == op - 1)
        {
            return T;
        }
        aux = aux->Prox;
        i++;
    }
}

CAMPO *GetSelectedCampoByIndex(TABELA *T, int op)
{
    NOG *aux = T->LCampos->Inicio;
    CAMPO *C = NULL;
    int i = 0;
    while (aux != NULL)
    {
        C = aux->Info;
        if (i == op - 1)
        {
            return C;
        }
        aux = aux->Prox;
        i++;
    }
}

char **listabasedados(ListaGenerica *X)
{
    BDadosCoupe *BD3 = NULL;
    // percorrer listagenerica
    NOG *aux = X->Inicio;
    int nel = X->NEL;
    char **listaBDs = malloc(sizeof(char) * nel);
    int i = 0;

    while (aux != NULL)
    {
        BD3 = aux->Info;
        listaBDs[i] = malloc(sizeof(char) * (strlen(BD3->NOME_BDADOS) + 1));
        strcpy(listaBDs[i], BD3->NOME_BDADOS);
        printf("%s\n", listaBDs[i]);
        aux = aux->Prox;
        i++;
    }
    return listaBDs;
}
int Compara_Nome_BD(void *t1, void *t2)
{
    BDadosCoupe *T1 = (BDadosCoupe *)t1;
    BDadosCoupe *T2 = (BDadosCoupe *)t2;

    return strcmp(T1->NOME_BDADOS, T2->NOME_BDADOS);
}
char **listanometabelas(BDadosCoupe *BD)
{
    NOG *aux = BD->LTabelas->Inicio;
    TABELA *T = NULL;
    int nel = BD->LTabelas->NEL;
    char **listanomeTabelas = malloc(sizeof(char) * nel);
    int i = 0;

    while (aux != NULL)
    {
        T = aux->Info;
        listanomeTabelas[i] = malloc(sizeof(char) * (strlen(T->NOME_TABELA) + 1));
        strcpy(listanomeTabelas[i], T->NOME_TABELA);
        printf("%s\n", listanomeTabelas[i]);
        aux = aux->Prox;
        i++;
    }
    return listanomeTabelas;
}
char **listanomecampos(TABELA *T)
{
    NOG *aux = T->LCampos->Inicio;
    CAMPO *C = NULL;
    int nel = T->LCampos->NEL;
    char **listanomeCampos = malloc(sizeof(char) * nel);
    int i = 0;

    while (aux != NULL)
    {
        C = aux->Info;
        listanomeCampos[i] = malloc(sizeof(char) * (strlen(C->NOME_CAMPO) + 1));
        strcpy(listanomeCampos[i], C->NOME_CAMPO);
        // printf("%s\n", listanomeCampos[i]);
        aux = aux->Prox;
        i++;
    }
    return listanomeCampos;
}
void CriarBaseDados(ListaGenerica *BDS)
{
    system("cls");
    char *nomeBD = (char *)malloc(sizeof(char) * 50);
    char *versaoBD = (char *)malloc(sizeof(char) * 50);
    BDadosCoupe *BD = NULL;
    printf("\n  \033[4mCriar Base Dados\033[0m\n\n");
    printf("  Nome Base de Dados: ");
    scanf("%s", nomeBD);
    printf("  Versao Base de Dados: ");
    scanf("%s", versaoBD);
    BD = Criar_BDados(nomeBD, versaoBD);
    if (AddFimLG(BDS, BD) == 1)
        printf("\n  \033[32mBase de Dados criada com sucesso!\033[0m\n");
    else
        printf("\n  \033[31mErro ao criar Base de Dados!\033[0m\n");

    free(nomeBD);
    free(versaoBD);
}

void EntrarBaseDados(ListaGenerica *BDS)
{
    char *submenu[] = {"Criar Tabela",
                       "Adicionar dados a uma tabela",
                       "Adicionar campos a uma tabela",
                       "Mostrar Todas as Tabelas",
                       "Mostar uma tabela",
                       "Apagar Tabela",
                       "SELECT",
                       "UPDATE",
                       "DELETE",
                       "\033[31mVoltar\033[0m"};

    char *nomeCampo = (char *)malloc(sizeof(char) * 50);
    bool askToContinue = true;
    BDadosCoupe *SelectedBD = NULL;
    TABELA *T = NULL;
    char *dadosconcat = (char *)malloc(sizeof(char) * 50);
    char *dados = malloc(sizeof(char *) * 100);
    char *nomeTabela = (char *)malloc(sizeof(char) * 50);
    char *tipoCampo = (char *)malloc(sizeof(char) * 50);
    int option = 0;
    char **arrayOpcoes;
    char **lncampos;
    int ncampos = 0;
    bool exitMenu = false;
    NOG *NC = NULL;

    CAMPO *campoSelecionado = NULL;
    char *valorPesquisar = (char *)malloc(sizeof(char) * 50);

    if (BDS->Inicio == NULL)
    {
        system("cls");
        printf("\n  \033[4mEntrar Base Dados\033[0m\n\n");
        // printf color red
        printf("  \033[31mNao existem Base de Dados!\033[0m\n");
        system("pause");
        askToContinue = false;
    }
    else
    {
        system("cls");
        arrayOpcoes = listabasedados(BDS);
        option = drawMenu(arrayOpcoes, BDS->NEL, "Escolha a Base de Dados");
        for (size_t i = 0; i < BDS->NEL; i++)
            free(arrayOpcoes[i]);
        // free(arrayOpcoes);

        SelectedBD = GetSelectBDCoupByIndex(BDS, option);
        printf("Base de Dados: %s\n", SelectedBD->NOME_BDADOS);
        char *title = malloc(sizeof(char) * (20 + strlen(SelectedBD->NOME_BDADOS)));

        do
        {
            askToContinue = true;
            sprintf(title, "Menu Base Dados (%s)", SelectedBD->NOME_BDADOS);

            int op = drawMenu(submenu, 10, title);
            switch (op)
            {
            case 1:
                system("cls");
                printf("\n  \033[4mCriar tabela\033[0m\n\n");
                printf("  Nome da Tabela: ");
                scanf("%s", nomeTabela);
                T = Criar_Tabela(SelectedBD, nomeTabela);
                printf("  Quantos campos pretende criar? ");
                scanf("%d", &ncampos);
                for (size_t i = 0; i < ncampos; i++)
                {
                    printf("\n Campo [%d]", i + 1);
                    printf("\n  Nome: ");
                    scanf("%s", nomeCampo);
                    printf("  Tipo (INT, STRING, CHAR, FLOAT): ");
                    scanf("%s", tipoCampo);
                    strToUpper(tipoCampo);
                    if (strcmp(tipoCampo, "INT") != 0 && strcmp(tipoCampo, "STRING") != 0 && strcmp(tipoCampo, "CHAR") != 0 && strcmp(tipoCampo, "FLOAT") != 0)
                    {
                        printf("\n  Tipo invalido!\n");
                        i--;
                    }
                    else
                    {
                        Add_Campo_Tabela(T, nomeCampo, tipoCampo);
                    }
                }

                system("cls");
                printf("\n  \033[32mTabela criada com sucesso!\033[0m\n");

                printf("\n  \033[4mCampos da Tabela [\033[1m%s\033[0m]\033[0m\n\n", T->NOME_TABELA);

                printf("  \033[4mNome\033[0m\t\t\033[4mTipo\033[0m\n");
                NC = T->LCampos->Inicio;
                while (NC)
                {
                    CAMPO *C = NC->Info;
                    printf("  %s\t\t%s\n", C->NOME_CAMPO, C->TIPO);
                    NC = NC->Prox;
                }

                break;
            case 2:
                system("cls");
                printf("\n  \033[4mAdicionar dados a uma tabela\033[0m\n\n");
                printf("  Base de Dados:%s \n\n", SelectedBD->NOME_BDADOS);
                if (SelectedBD->LTabelas->Inicio == NULL)
                    printf("\n  \033[31mNao existem tabelas!\033[0m\n");
                else
                {
                    option = 0;
                    ncampos = 0;
                    arrayOpcoes = listanometabelas(SelectedBD);
                    option = drawMenu(arrayOpcoes, SelectedBD->LTabelas->NEL, "Escolha a Tabela");
                    for (size_t i = 0; i < SelectedBD->LTabelas->NEL; i++)
                        free(arrayOpcoes[i]); // free(arrayOpcoes);

                    T = GetSelectedTableByIndex(SelectedBD, option);
                    lncampos = listanomecampos(T);
                    system("cls");
                    printf("\n  \033[4mAdicionar dados a uma tabela\033[0m\n\n");
                    printf("  Tabela:%s \n", T->NOME_TABELA);
                    ncampos = T->LCampos->NEL;
                    strcpy(dadosconcat, "");
                    for (size_t i = 0; i < ncampos; i++)
                    {
                        printf("  Campo [%s]: ", lncampos[i]);
                        scanf("%s", dados);
                        strcat(dadosconcat, dados);
                        if (i != ncampos - 1)
                        {
                            strcat(dadosconcat, ";");
                        }
                    }
                    if (Add_Valores_Tabela(T, dadosconcat) == 1)
                        printf("\n  \033[32mDados adicionados com sucesso!\033[0m\n");

                    else
                        printf("\n  \033[31mErro ao adicionar dados!\033[0m\n");

                    for (size_t i = 0; i < T->LCampos->NEL; i++)
                        free(lncampos[i]); // free(arrayOpcoes);
                }
                break;
            case 3:
                system("cls");
                printf("\n  \033[4mAdicionar campos a uma tabela\033[0m\n\n");
                printf("  Base de Dados:%s \n\n", SelectedBD->NOME_BDADOS);
                if (SelectedBD->LTabelas->Inicio == NULL)
                    printf("\n  \033[31mNao existem tabelas!\033[0m\n");
                else
                {
                    arrayOpcoes = listanometabelas(SelectedBD);
                    option = drawMenu(arrayOpcoes, SelectedBD->LTabelas->NEL, "Escolha a Tabela");
                    for (size_t i = 0; i < SelectedBD->LTabelas->NEL; i++)
                        free(arrayOpcoes[i]); // free(arrayOpcoes);

                    T = GetSelectedTableByIndex(SelectedBD, option);
                    system("cls");
                    printf("\n  \033[4mAdicionar campos a uma tabela\033[0m\n\n");
                    printf("  Tabela:%s \n\n", T->NOME_TABELA);
                    printf("  Quantos campos pretende criar? ");
                    scanf("%d", &ncampos);
                    for (size_t i = 0; i < ncampos; i++)
                    {
                        printf("\n Campo [%d]", i + 1);
                        printf("\n  Nome: ");
                        scanf("%s", nomeCampo);
                        printf("  Tipo (INT, STRING, CHAR, FLOAT): ");
                        scanf("%s", tipoCampo);
                        strToUpper(nomeCampo);
                        strToUpper(tipoCampo);
                        if (strcmp(tipoCampo, "INT") != 0 && strcmp(tipoCampo, "STRING") != 0 && strcmp(tipoCampo, "CHAR") != 0 && strcmp(tipoCampo, "FLOAT") != 0)
                        {
                            printf("\n  \033[31mTipo Invalido!\033[0m\n");
                            i--;
                        }
                        else
                        {
                            if (Add_Campo_Tabela(T, nomeCampo, tipoCampo) == 1)
                            {
                                system("cls");
                                printf("\n  \033[32mCampo(s) adicionado(s) com sucesso!\033[0m\n");
                                printf("\n  \033[4mCampos da Tabela [\033[1m%s\033[0m]\033[0m\n\n", T->NOME_TABELA);
                                printf("  \033[4mNome\033[0m\t\t\033[4mTipo\033[0m\n");
                                NC = T->LCampos->Inicio;
                                while (NC)
                                {
                                    CAMPO *C = NC->Info;
                                    printf("  %s\t\t%s\n", C->NOME_CAMPO, C->TIPO);
                                    NC = NC->Prox;
                                }
                            }
                            else
                                printf("\n  \033[31mErro ao adicionar campo(s)!\033[0m\n");
                        }
                    }

                    free(nomeCampo);
                }
                askToContinue = true;

                break;

            case 4:
                system("cls");
                printf("\n  \033[4mListar todas as tabelas de uma Base de Dados\033[0m\n\n");
                printf("  Base de Dados: %s\n", SelectedBD->NOME_BDADOS);
                if (SelectedBD->LTabelas->Inicio == NULL)
                    printf("\n  \033[31mNao existem tabelas!\033[0m\n");
                else
                {
                    Mostrar_BDados(SelectedBD);
                }
                askToContinue = true;
                break;

            case 5:
                system("cls");
                printf("\n  \033[4mMostar uma tabela\033[0m\n\n");
                printf("  Base de Dados: %s\n\n", SelectedBD->NOME_BDADOS);
                if (SelectedBD->LTabelas->Inicio == NULL)
                    printf("\n  \033[31mNao existem tabelas!\033[0m\n");
                else
                {
                    arrayOpcoes = listanometabelas(SelectedBD);
                    option = drawMenu(arrayOpcoes, SelectedBD->LTabelas->NEL, "Escolha a Tabela");
                    for (size_t i = 0; i < SelectedBD->LTabelas->NEL; i++)
                        free(arrayOpcoes[i]);
                    // free(arrayOpcoes);
                    T = GetSelectedTableByIndex(SelectedBD, option);
                    system("cls");
                    printf("\n  \033[4mMostar uma tabela\033[0m\n\n");
                    Mostrar_Tabela(T);
                }

                askToContinue = true;
                break;
            case 6:
                option = 0;
                system("cls");
                printf("\n  \033[4mApagar uma tabela de uma Base de Dados\033[0m\n\n");
                printf("  Base de Dados: %s\n", SelectedBD->NOME_BDADOS);
                if (SelectedBD->LTabelas->Inicio == NULL)
                    printf("\n  \033[31mNao existem tabelas!\033[0m\n");
                else
                {
                    arrayOpcoes = listanometabelas(SelectedBD);
                    option = drawMenu(arrayOpcoes, SelectedBD->LTabelas->NEL, "Escolha a Tabela");
                    for (size_t i = 0; i < SelectedBD->LTabelas->NEL; i++)
                        free(arrayOpcoes[i]); // free(arrayOpcoes);

                    T = GetSelectedTableByIndex(SelectedBD, option);
                    nomeTabela = T->NOME_TABELA;
                    system("cls");
                    printf("\n  \033[4mApagar uma tabela de uma Base de Dados\033[0m\n\n");
                    printf("  Base de Dados: %s\n", SelectedBD->NOME_BDADOS);
                    if (DROP_TABLE(SelectedBD, nomeTabela) == 1)
                        printf("\n  \033[32mTabela removida %s com sucesso!\033[0m\n", nomeTabela);
                    else
                        printf("\n  \033[31mErro ao remover %s tabela!\033[0m\n", nomeTabela);
                }
                free(nomeTabela);
                askToContinue = true;
                break;
            case 7:
                system("cls");
                printf("\n  \033[4mSELECT\033[0m\n\n");
                if (SelectedBD->LTabelas->Inicio == NULL)
                {
                    printf("\n  \033[31mNao existem tabelas!\033[0m\n");
                    askToContinue = true;
                }
                else
                {
                    arrayOpcoes = listanometabelas(SelectedBD);
                    option = drawMenu(arrayOpcoes, SelectedBD->LTabelas->NEL, "Escolha a Tabela");
                    for (size_t i = 0; i < SelectedBD->LTabelas->NEL; i++)
                        free(arrayOpcoes[i]); // free(arrayOpcoes);

                    T = GetSelectedTableByIndex(SelectedBD, option);
                    nomeTabela = T->NOME_TABELA;
                    system("cls");

                    lncampos = listanomecampos(T);
                    option = drawMenu(lncampos, T->LCampos->NEL, "Escolha um Campo");
                    for (size_t i = 0; i < T->LCampos->NEL; i++)
                        free(lncampos[i]);

                    campoSelecionado = GetSelectedCampoByIndex(T, option);

                    system("cls");

                    printf("\n  \033[4mValor a pesquisar\033[0m: ");
                    scanf("%s", valorPesquisar);

                    SELECT(SelectedBD, nomeTabela, Compare, campoSelecionado->NOME_CAMPO, valorPesquisar);
                }
                askToContinue = true;
                break;

            case 8:
                system("cls");
                printf("\n  \033[4mDELETE\033[0m\n\n");
                if (SelectedBD->LTabelas->Inicio == NULL)
                {
                    printf("\n  \033[31mNao existem tabelas!\033[0m\n");
                    askToContinue = true;
                }
                else
                {
                    arrayOpcoes = listanometabelas(SelectedBD);
                    option = drawMenu(arrayOpcoes, SelectedBD->LTabelas->NEL, "Escolha a Tabela");
                    for (size_t i = 0; i < SelectedBD->LTabelas->NEL; i++)
                        free(arrayOpcoes[i]); // free(arrayOpcoes);

                    T = GetSelectedTableByIndex(SelectedBD, option);
                    nomeTabela = T->NOME_TABELA;
                    system("cls");

                    lncampos = listanomecampos(T);
                    option = drawMenu(lncampos, T->LCampos->NEL, "Escolha um Campo");
                    for (size_t i = 0; i < T->LCampos->NEL; i++)
                        free(lncampos[i]);

                    campoSelecionado = GetSelectedCampoByIndex(T, option);

                    system("cls");

                }
                break;
            case 9:
                system("cls");
                printf("\n  \033[4mUPDATE\033[0m\n\n");
                if (SelectedBD->LTabelas->Inicio == NULL)
                {
                    printf("\n  \033[31mNao existem tabelas!\033[0m\n");
                    askToContinue = true;
                }
                else
                {

                }
                break;

            case 10:
                exitMenu = true;
                break;
            }

            if (!exitMenu && askToContinue)
            {
                printf("\n\n");
                printf("  \033[7mPressione qualquer tecla para continuar...\033[0m");
                getch();
                system("cls");
            }
        } while (exitMenu == false);
    }
    free(nomeCampo);
    free(dadosconcat);
    free(dados);
    free(nomeTabela);
    free(tipoCampo);
    free(campoSelecionado);
    free(valorPesquisar);
}
void ImportarBaseDados(ListaGenerica *BDS)
{
    system("cls");
    int op = -1;
    char *expoptions[] = {"Excel(.cvs)",
                          "Binario(.dat)",
                          "\033[31mVoltar\033[0m"};
    char *fich_name = (char *)malloc(sizeof(char) * 50);
    op = drawMenu(expoptions, 3, "Menu Importar");
    char *bdName;
    BDadosCoupe *ImportBD;

    switch (op)
    {
    case 1:
        system("cls");
        printf("\n  \033[4mImportar Base de Dados\033[0m\n\n");
        printf("  Nome do ficheiro (****.csv): ");
        scanf("%s", fich_name);
        bdName = malloc(sizeof(char) * strlen(fich_name) + 1);
        strtok(fich_name, ".");
        strcpy(bdName, fich_name);

        ImportBD = Criar_BDados(bdName, "1.0");
        strcat(fich_name, ".csv");
        if (Importar_BDados_Excel(ImportBD, fich_name) == SUCESSO)
        {
            AddFimLG(BDS, ImportBD);
            printf("\n  \033[32mBase de Dados importada com sucesso!\033[0m\n");
            system("pause");
        }
        else
        {

            printf("\n  \033[31mErro ao importar base de dados!\033[0m\n");
            free(ImportBD);
            system("pause");
        }
        break;

    case 2:
        system("cls");
        printf("\n  \033[4mImportar Base de Dados\033[0m\n\n");
        printf("  Nome do ficheiro (****.dat): ");
        scanf("%s", fich_name);
        bdName = malloc(sizeof(char) * strlen(fich_name) + 1);
        strtok(fich_name, ".");
        strcpy(bdName, fich_name);

        ImportBD = Criar_BDados(bdName, "1.0");
        strcat(fich_name, ".dat");

        if (Importar_BDados_Ficheiro_Binario(ImportBD, fich_name) == SUCESSO)
        {
            AddFimLG(BDS, ImportBD);

            // printf color green
            printf("\n  \033[32mBase de Dados importada com sucesso!\033[0m\n");
            system("pause");
        }
        else
        {
            printf("\n  \033[31mErro ao importar base de dados!\033[0m\n");
            free(ImportBD);
            system("pause");
        }

        break;
    case 3:
        break;
    }
    free(fich_name);
}
void ExportarBaseDados(ListaGenerica *BDS)
{
    system("cls");
    char *expoptions[] = {"Excel(.cvs)",
                          "Binario(.dat)",
                          "\033[31mVoltar\033[0m"};
    char *fich_name = (char *)malloc(sizeof(char) * 50);
    BDadosCoupe *SelectedBD = NULL;
    char **arrayOpcoes;
    int option = 0;
    int op = -1;
    printf("\n  \033[4mExportar Base de Dados\033[0m\n");
    if (BDS->Inicio == NULL)
    {
        printf("\n  \033[31mNao existem base de dados para exportar!\033[0m\n");
        system("pause");
        return;
    }
    else
    {
        arrayOpcoes = listabasedados(BDS);
        option = drawMenu(arrayOpcoes, BDS->NEL, "Escolha a Base de Dados");
        for (size_t i = 0; i < BDS->NEL; i++)
            free(arrayOpcoes[i]);
        SelectedBD = GetSelectBDCoupByIndex(BDS, option);
        op = drawMenu(expoptions, 3, "Menu Exportar");
        switch (op)
        {
        case 1:
            system("cls");
            printf("\n  \033[4mExportar Base de Dados(EXCEL)\033[0m\n");
            if (SelectedBD->LTabelas->Inicio == NULL)
            {

                printf("\n  \033[31mNao existem tabelas na Base Dados %s para exportar!\033[0m\n", SelectedBD->NOME_BDADOS);
                system("pause");
            }
            else
            {

                if (Exportar_BDados_Excel(SelectedBD) == SUCESSO)
                {
                    printf("\n  \033[32mBase de Dados %s exportada com sucesso!\033[0m\n", SelectedBD->NOME_BDADOS);
                    system("pause");
                }
                else
                {
                    printf("\n  \033[31mErro ao exportar base de dados %s!\033[0m\n", SelectedBD->NOME_BDADOS);
                    system("pause");
                }
            }

            break;
        case 2:
            system("cls");
            printf("\n  \033[4mExportar Base de Dados(BIN)\033[0m\n");
            if (SelectedBD->LTabelas->Inicio == NULL)
            {

                printf("\n  \033[31mNao existem tabelas na Base Dados %s para exportar!\033[0m\n", SelectedBD->NOME_BDADOS);
                system("pause");
            }
            else
            {
                fich_name = SelectedBD->NOME_BDADOS;
                strcat(fich_name, ".bin");

                if (Exportar_BDados_Ficheiro_Binario(SelectedBD, fich_name) == SUCESSO)
                {
                    printf("\n  \033[32mBase de Dados %s exportada com sucesso!\033[0m\n", SelectedBD->NOME_BDADOS);
                    system("pause");
                }
                else
                {
                    printf("\n  \033[31mErro ao exportar base de dados %s!\033[0m\n", SelectedBD->NOME_BDADOS);
                    system("pause");
                }
            }
            break;
        case 3:
            break;
        }
    }
    free(fich_name);
}
void ApagarBaseDados(ListaGenerica *BDS)
{
    BDadosCoupe *SelectedBD = NULL;
    char **arrayOpcoes;
    int option = 0;
    int op = -1;
    system("cls");
    printf("\n  \033[4mApagar Base de Dados\033[0m\n");
    if (BDS->Inicio == NULL)
    {
        printf("\n  \033[31mNao existem  Base Dados para apagar!\033[0m\n");
        system("pause");
    }
    else
    {
        arrayOpcoes = listabasedados(BDS);
        option = drawMenu(arrayOpcoes, BDS->NEL, "Escolha a Base de Dados");
        for (size_t i = 0; i < BDS->NEL; i++)
            free(arrayOpcoes[i]);
        SelectedBD = GetSelectBDCoupByIndex(BDS, option);
        system("cls");
        printf("\n  \033[4mApagar Base de Dados\033[0m\n\n");
        Destruir_BDados(SelectedBD);
        if (RemoveLG(BDS, SelectedBD, Compara_Nome_BD) == SUCESSO)
        {
            printf("\n  \033[32mBase de Dados %s apagada com sucesso!\033[0m\n", SelectedBD->NOME_BDADOS);
            system("pause");
        }
        else
        {
            printf("\n  \033[31mErro ao apagar base de dados %s!\033[0m\n", SelectedBD->NOME_BDADOS);
            system("pause");
        }
    }
}
int main()
{

    ListaGenerica *BDS = CriarLG();

    /* TABELA *T = Criar_Tabela(BD, "CLIENTES");
     Add_Campo_Tabela(T, "ID", "INT");
     Add_Campo_Tabela(T, "NOME", "STRING");
     Add_Campo_Tabela(T, "IDADE", "INT");

     TABELA *T2 = Criar_Tabela(BD, "PRODUTOS");
     Add_Campo_Tabela(T2, "ID", "INT");
     Add_Campo_Tabela(T2, "NOME", "STRING");
     Add_Campo_Tabela(T2, "PRECO", "FLOAT");
     Add_Campo_Tabela(T2, "QUANTIDADE", "INT");

     Add_Valores_Tabela(T2, "1;agua;20;100");
     Add_Valores_Tabela(T2, "2;coca-cola;10;200");
     Add_Valores_Tabela(T2, "3;creatina;15;500");

     // Add_Valores_Tabela(T, "2;Maria;25");
     time_t init = clock();
     char *nomeUtilizador = (char *)malloc(sizeof(char) * 20);
     char *dados = (char *)malloc(sizeof(char) * 100);
     int idade;
     int a = 0;
     for (size_t i = 1; i < 100; i++)
     {

         sprintf(nomeUtilizador, "Utilizador_%d", i);

         idade = rand() % 100;

         sprintf(dados, "%d;%s;%d", i, nomeUtilizador, idade);

         Add_Valores_Tabela(T, dados);
     }
    */

    BDadosCoupe *SelectedBD = NULL;
    BDadosCoupe *BD = NULL;

    char *menu[] = {"Criar uma Base de Dados",
                    "Entrar numa Base de Dados",
                    "Importar Base de Dados",
                    "Exportar Base de Dados",
                    "Apagar uma Base de Dados",
                    "\033[31mSAIR\033[0m"};

    bool exitMenu = false;
    bool askToContinue = false;
    int file = -1;
    int op = -1;

    int lbds = 0;

    char **p;
    char **lncampos;
    do
    {
        askToContinue = true;
        op = drawMenu(menu, 6, "Menu Principal");
        switch (op)
        {
        case 1:
        {
            CriarBaseDados(BDS);
            askToContinue = true;
            break;
        }
        case 2:
            EntrarBaseDados(BDS);
            askToContinue = false;
            break;

        case 3:
            ImportarBaseDados(BDS);
            askToContinue = false;
            break;

        case 4:
            ExportarBaseDados(BDS);
            askToContinue = false;
            break;
        case 5:
            ApagarBaseDados(BDS);
            break;
        case 6:
            exitMenu = true;
            break;

        case -1:
            exitMenu = true;
            break;
        }
        if (!exitMenu && askToContinue)
        {
            printf("\n\n");
            printf("  \033[7mPressione qualquer tecla para continuar...\033[0m");
            getch();
            system("cls");
        }
    } while (exitMenu == false);

    return 0;
}
