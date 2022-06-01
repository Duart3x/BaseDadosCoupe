
#include "BDadosCoupe.h"
#include <time.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

/** \brief Criar_BDados: A) Criar a Base de dados
 *
 * \param nome_bd char* : Nome da Base de Dados
 * \param versao char*  : Vers�o da Base de Dados
 * \return BDadosCoupe* : Ponteiro para a Base de Dados Criada
 *
 */
BDadosCoupe *Criar_BDados(char *nome_bd, char *versao)
{
    BDadosCoupe *BD = (BDadosCoupe *)malloc(sizeof(BDadosCoupe));
    strcpy(BD->NOME_BDADOS, nome_bd);
    strcpy(BD->VERSAO_BDADOS, versao);
    BD->LTabelas = CriarLG();
    return BD;
}

/** \brief B) Criar uma Tabela na Base de Dados,
 * a tabela deve ser inserida à lista de tabelas da BD
 *
 * \param BD BDadosCoupe* : Ponteiro para a Base de Dados
 * \param nome_tabela char* : Nome da tabela a Criar
 * \return TABELA*        : Retorna a Tabela Criada
 * \author                : CS, FM & JL
 */
TABELA *Criar_Tabela(BDadosCoupe *BD, char *nome_tabela)
{
    TABELA *T = (TABELA *)malloc(sizeof(TABELA));
    strcpy(T->NOME_TABELA, nome_tabela);
    T->LCampos = CriarLG();
    T->LRegistos = CriarLG();
    AddFimLG(BD->LTabelas, T);
    return T;
}
/** \brief C)  Adicionar um campo a uma tabela.
 *
 * \param T TABELA* : Ponteiro para a tabela
 * \param nome_campo char* : Nome do campo
 * \param tipo_campo char* : Tipo do Campo (INT, STRING, CHAR, FLOAT)
 * \return int             : SUCESSO/INSUCESSO
 * \author                 : CS, FM & JL              :
 * \version                : Versao 1.0
 * \date                   : 23/04/2022
 */
int Add_Campo_Tabela(TABELA *T, char *nome_campo, char *tipo_campo)
{
    CAMPO *C = (CAMPO *)malloc(sizeof(CAMPO));
    if (!C)
        return INSUCESSO;
    strcpy(C->NOME_CAMPO, nome_campo);
    strcpy(C->TIPO, tipo_campo);
    int res = AddFimLG(T->LCampos, C);
    return res;
}
// D)	Adicionar dados(registos) a uma tabela, os dados s�o dados numa string onde o separador � �;�m ex: Add_Valores_Tabela(T, �123;Joao;965654449�)
int Add_Valores_Tabela(TABELA *T, char *dados)
{
    if (!T)
        return INSUCESSO;

    char *token;
    char *delim = ";";
    char *dados_copia = (char *)malloc(sizeof(char) * (strlen(dados) + 1));

    strcpy(dados_copia, dados);
    token = strtok(dados_copia, delim);
    char *valor = (char *)malloc(sizeof(char) * (strlen(token) + 1));
    strcpy(valor, token);

    REGISTO *R = (REGISTO *)malloc(sizeof(REGISTO));
    if (!R)
        return INSUCESSO;

    R->LValores = CriarLG();

    AddFimLG(R->LValores, valor);

    while (token)
    {
        token = strtok(NULL, delim);
        if (!token)
            break;
        valor = (char *)malloc(sizeof(char) * (strlen(token) + 1));
        strcpy(valor, token);
        AddFimLG(R->LValores, valor);
    }

    AddFimLG(T->LRegistos, R);

    // free(token);
    free(dados_copia);

    return SUCESSO;
}
// E)	Adicionar dados(registos) a uma tabela, os dados s�o dados numa string onde o separador � �;�
int Add_Valores_Tabela_BDados(BDadosCoupe *BD, char *nome_tabela, char *dados)
{
    TABELA *T = Pesquisar_Tabela(BD, nome_tabela);
    int res = Add_Valores_Tabela(T, dados);
    return res;
}
// F)	Pesquisar uma Tabela da base de dados
TABELA *Pesquisar_Tabela(BDadosCoupe *BD, char *nome_tabela)
{
    if (BD == NULL)
        return INSUCESSO;

    // TABELA *findedTable;

    NOG *N = BD->LTabelas->Inicio;
    while (N != NULL)
    {
        TABELA *T = (TABELA *)N->Info;

        if (strcmp(T->NOME_TABELA, nome_tabela) == 0)
            return T;

        N = N->Prox;
    }
    return INSUCESSO;
}
// G)	Mostrar uma Tabela
void Mostrar_Tabela_NOME(BDadosCoupe *BD, char *tabela)
{
    TABELA *T = Pesquisar_Tabela(BD, tabela);
    Mostrar_Tabela(T);
    free(T);
}

void Mostrar_Campo(void *C)
{
    CAMPO *c = (CAMPO *)C;
    printf("%s ", c->NOME_CAMPO);
}

void Mostra_Valor(void *V)
{
    char *valor = (char *)V;
    printf("%s ", valor);
}

void Mostrar_Registo(void *R)
{
    REGISTO *r = (REGISTO *)R;
    MostrarLG(r->LValores, Mostra_Valor);
    printf("\n");
}

void Mostrar_Tabela(TABELA *T)
{
    clock_t init = clock();
    printf("Nome da Tabela: %s\n", T->NOME_TABELA);
    MostrarLG(T->LCampos, Mostrar_Campo);
    printf("\n");
    MostrarLG(T->LRegistos, Mostrar_Registo);
    printf("\n");
    clock_t end = clock();
    double time = (double)(end - init) / CLOCKS_PER_SEC;
    printf("Tempo de Execucao: %f\n", time);
}

// H)	Mostrar toda a base de dados, dever� mostrar todas as Tabelas da BDados.
void Mostrar_BDados(BDadosCoupe *BD)
{
    clock_t init = clock();
    NOG *T = BD->LTabelas->Inicio;
    while (T)
    {
        Mostrar_Tabela(T->Info);
        printf("\n-----------------------------------------------------\n");
        T = T->Prox;
    }
}

void Destruir_Valor(void *V)
{
    char *valor = (char *)V;
    free(valor);
}

void Destruir_Registo(void *R)
{
    REGISTO *r = (REGISTO *)R;
    DestruirLG(r->LValores, Destruir_Valor);
    free(r);
}

void Destruir_Campo(void *C)
{
    CAMPO *c = (CAMPO *)C;
    free(c);
}

void Destruir_Tabela(void *T)
{
    TABELA *t = (TABELA *)T;
    DestruirLG(t->LCampos, Destruir_Campo);
    DestruirLG(t->LRegistos, Destruir_Registo);
    free(t);
}
// I)	Libertar toda a mem�ria alocada pela base de dados.
void Destruir_BDados(BDadosCoupe *BD)
{
    DestruirLG(BD->LTabelas, Destruir_Tabela);
    free(BD);
}
// J)	Mem�ria ocupada por toda a base de dados.
long int Memoria_BDados(BDadosCoupe *BD)
{
    long int memoria = 0;
    memoria += sizeof(BD->NOME_BDADOS);
    memoria += sizeof(BD->VERSAO_BDADOS);
    NOG *N = BD->LTabelas->Inicio;
    NOG *N2 = NULL;
    NOG *N3 = NULL;
    NOG *N4 = NULL;

    TABELA *T = NULL;
    CAMPO *C = NULL;
    REGISTO *R = NULL;

    while (N)
    {
        T = (TABELA *)N->Info;
        memoria += sizeof(T->NOME_TABELA);
        N2 = T->LCampos->Inicio;
        while (N2)
        {
            C = (CAMPO *)N2->Info;
            memoria += sizeof(C->NOME_CAMPO);
            memoria += sizeof(C->TIPO);
            N2 = N2->Prox;
        }

        N3 = T->LRegistos->Inicio;
        while (N3)
        {
            R = (REGISTO *)N3->Info;
            N4 = R->LValores->Inicio;
            while (N4)
            {
                memoria += strlen((char *)N4->Info);

                N4 = N4->Prox;
            }

            N3 = N3->Prox;
        }

        N = N->Prox;
    }

    return memoria;
}
long int Memoria_Desperdicada_BDados(BDadosCoupe *BD)
{
    long int memoriaExata = 0;

    memoriaExata += sizeof(char) * strlen(BD->NOME_BDADOS);
    memoriaExata += sizeof(char) * strlen(BD->VERSAO_BDADOS);

    NOG *N = BD->LTabelas->Inicio;
    NOG *N2 = NULL;
    NOG *N3 = NULL;
    NOG *N4 = NULL;

    TABELA *T = NULL;
    CAMPO *C = NULL;
    REGISTO *R = NULL;

    while (N)
    {
        T = (TABELA *)N->Info;
        memoriaExata += sizeof(char) * strlen(T->NOME_TABELA);
        N2 = T->LCampos->Inicio;
        while (N2)
        {
            C = (CAMPO *)N2->Info;
            memoriaExata += sizeof(char) * strlen(C->NOME_CAMPO);
            memoriaExata += sizeof(char) * strlen(C->TIPO);
            N2 = N2->Prox;
        }

        N3 = T->LRegistos->Inicio;
        while (N3)
        {
            R = (REGISTO *)N3->Info;
            N4 = R->LValores->Inicio;
            while (N4)
            {
                memoriaExata += strlen((char *)N4->Info);
                N4 = N4->Prox;
            }

            N3 = N3->Prox;
        }

        N = N->Prox;
    }

    return Memoria_BDados(BD) - memoriaExata;
}
// K)	Exportar/Importar para/de Ficheiro (o retorno destas fun��es, permite saber se a fun��o foi bem/mal-executada!):
int Exportar_Tabela_BDados_Excel(BDadosCoupe *BD, char *tabela, char *ficheir_csv)
{
    // export listaGenerica to excel file
    TABELA *T = Pesquisar_Tabela(BD, tabela);
    if (!T)
        return INSUCESSO;
    FILE *f = fopen(ficheir_csv, "w");
    if (!f)
        return INSUCESSO;
    NOG *NC = T->LCampos->Inicio;
    NOG *NR = NULL;
    NOG *NV = NULL;

    NC = T->LCampos->Inicio;
    while (NC)
    {
        CAMPO *C = (CAMPO *)NC->Info;

        if (NC->Prox != NULL)
            fprintf(f, "%s;", C->TIPO);
        else
            fprintf(f, "%s", C->TIPO);
        NC = NC->Prox;
    }
    fprintf(f, "\n");

    NC = T->LCampos->Inicio;
    while (NC)
    {
        CAMPO *C = (CAMPO *)NC->Info;

        if (NC->Prox != NULL)
            fprintf(f, "%s;", C->NOME_CAMPO);
        else
            fprintf(f, "%s", C->NOME_CAMPO);
        NC = NC->Prox;
    }
    fprintf(f, "\n");
    NR = T->LRegistos->Inicio;
    while (NR)
    {
        REGISTO *R = (REGISTO *)NR->Info;
        NV = R->LValores->Inicio;
        while (NV)
        {

            if (NV->Prox != NULL)
                fprintf(f, "%s;", NV->Info);
            else
                fprintf(f, "%s", NV->Info);
            NV = NV->Prox;
        }
        fprintf(f, "\n");

        NR = NR->Prox;
    }
    fclose(f);
    char *ficheiroBaseDados = malloc(sizeof(char) * (strlen(BD->NOME_BDADOS) + 6));
    sprintf(ficheiroBaseDados, "%s.csv", BD->NOME_BDADOS);

    AtualizaFicheiroBDados(BD, ficheiroBaseDados, T->NOME_TABELA, ficheir_csv);
    return SUCESSO;
}

int AtualizaFicheiroBDados(BDadosCoupe *BD, char *ficheiro_csv, char *nomeTabela, char *ficheiroTabela)
{
    // Check if file exists
    FILE *f = fopen(ficheiro_csv, "r");
    if (!f)
    {
        fclose(f);
        f = fopen(ficheiro_csv, "a");
        if (!f)
            return INSUCESSO;

        fprintf(f, "%s;%s\n", "TABELA", "FICHEIRO");
        fprintf(f, "%s;%s\n", nomeTabela, ficheiroTabela);

        fclose(f);
        return SUCESSO;
    }

    // Check if table exists
    int nCamposLidos;
    while (!feof(f))
    {
        char **V = Read_Split_Line_File(f, 2, &nCamposLidos, ";");
        if (!V)
            continue;

        if (strcmp(V[0], nomeTabela) == 0)
        {
            fclose(f);
            return SUCESSO;
        }
    }
    fclose(f);
    f = fopen(ficheiro_csv, "a");
    if (!f)
        return INSUCESSO;

    fprintf(f, "%s;%s\n", nomeTabela, ficheiroTabela);
    fclose(f);

    return SUCESSO;
}

int Exportar_BDados_Excel(BDadosCoupe *BD)
{
    NOG *NT = BD->LTabelas->Inicio;

    char *ficheiroTabelas = malloc(sizeof(char) * 250);

    while (NT)
    {
        TABELA *T = (TABELA *)NT->Info;
        sprintf(ficheiroTabelas, "%s.csv", T->NOME_TABELA);
        Exportar_Tabela_BDados_Excel(BD, T->NOME_TABELA, ficheiroTabelas);
        NT = NT->Prox;
    }

    return SUCESSO;
}

int ImportarTabelaBDados(BDadosCoupe *BD, char *ficheiro_csv, char *nomeTabela)
{
    // Check if file exists
    FILE *f = fopen(ficheiro_csv, "r");
    if (!f)
    {
        fclose(f);
        return INSUCESSO;
    }

    TABELA *T = Criar_Tabela(BD, nomeTabela);

    char *aux = malloc(sizeof(char) * MAX_LINHA_FICHEIRO);
    char **DataTypes = malloc(sizeof(char *) * MAX_LINHA_FICHEIRO);
    int nCamposLidos;
    int nMaxCampos = 0;

    //? Numero de campos da tabela
    //? Retirar tipo de dados dos Campos (1ª Linha do ficheiro)
    if (fgets(aux, MAX_LINHA_FICHEIRO, f) != NULL)
    {
        char *pch = strtok(aux, ";");

        while (pch != NULL)
        {
            nMaxCampos++;
            if (pch[strlen(pch) - 1] == '\n')
                pch[strlen(pch) - 1] = '\0';
            DataTypes[nMaxCampos - 1] = malloc(sizeof(char) * (strlen(pch) + 1));
            strcpy(DataTypes[nMaxCampos - 1], pch);
            pch = strtok(NULL, ";");
        }

        free(pch);
    }

    //? Adicionar campos á tabela (2ª Linha do ficheiro)
    char **V = Read_Split_Line_File(f, nMaxCampos, &nCamposLidos, ";");
    if (!V)
        return INSUCESSO;

    for (size_t i = 0; i < nCamposLidos; i++)
    {
        if (V[i][strlen(V[i]) - 1] == '\n')
            V[i][strlen(V[i]) - 1] = '\0';

        Add_Campo_Tabela(T, V[i], DataTypes[i]);
    }

    free(DataTypes);

    //? Adicionar registos á tabela
    while (fgets(aux, MAX_LINHA_FICHEIRO, f) != NULL)
    {
        if (!aux)
            continue;
        aux[strlen(aux) - 1] = '\0';
        Add_Valores_Tabela(T, aux);
    }

    free(aux);
    fclose(f);
    return SUCESSO;
}

int Importar_BDados_Excel(BDadosCoupe *BD, char *ficheir_csv)
{
    FILE *f = fopen(ficheir_csv, "r");
    if (!f)
        return INSUCESSO;

    int nCamposLidos;
    while (!feof(f))
    {
        char **V = Read_Split_Line_File(f, 2, &nCamposLidos, ";");
        if (!V)
            continue;

        if (strcmp(V[0], "TABELA") == 0)
            continue;

        V[1][strlen(V[1]) - 1] = '\0';

        ImportarTabelaBDados(BD, V[1], V[0]);
    }

    return SUCESSO;
}
int Exportar_BDados_Ficheiro_Binario(BDadosCoupe *BD, char *fich_dat)
{
    FILE *f = fopen(fich_dat, "wb");
    if (!f)
        return INSUCESSO;

    NOG *NT = BD->LTabelas->Inicio;

    fwrite(&BD->LTabelas->NEL, sizeof(int), 1, f);
    while (NT)
    {
        TABELA *T = (TABELA *)NT->Info;
        NOG *NC = T->LCampos->Inicio;
        char *nomeFicheiro = malloc(sizeof(char) * 55);
        sprintf(nomeFicheiro, "%s.dat", T->NOME_TABELA);
        FILE *ft = fopen(nomeFicheiro, "wb");

        fwrite(&(T->LCampos->NEL), sizeof(int), 1, ft);
        while (NC)
        {
            CAMPO *C = (CAMPO *)NC->Info;
            int N = sizeof(C->TIPO);
            fwrite(&(N), sizeof(int), 1, ft);
            fwrite(C->TIPO, sizeof(char), N, ft);

            N = sizeof(C->NOME_CAMPO);
            fwrite(&(N), sizeof(int), 1, ft);
            fwrite(C->NOME_CAMPO, sizeof(char), N, ft);
            NC = NC->Prox;
        }

        NOG *NR = T->LRegistos->Inicio;
        fwrite(&(T->LRegistos->NEL), sizeof(int), 1, ft);
        while (NR)
        {
            REGISTO *R = (REGISTO *)NR->Info;
            NOG *NV = R->LValores->Inicio;

            while (NV)
            {
                char *valor = (char *)NV->Info;
               // strcat(valor, ";");

                int length = strlen(valor) + 1;

                fwrite(&length, sizeof(int), 1, ft);
                fwrite(valor, sizeof(char), length, ft);

                NV = NV->Prox;
            }
            NR = NR->Prox;
        }

        fclose(ft);
        int lengthNomeTabela = strlen(T->NOME_TABELA) + 1;
        fwrite(&lengthNomeTabela, sizeof(int), 1, f);
        fwrite(T->NOME_TABELA, sizeof(char), lengthNomeTabela, f);

        int lengthNomeFicheiro = strlen(nomeFicheiro) + 1;
        fwrite(&lengthNomeFicheiro, sizeof(int), 1, f);
        fwrite(nomeFicheiro, sizeof(char), lengthNomeFicheiro, f);

        NT = NT->Prox;
    }

    fclose(f);
    return SUCESSO;
}
int Importar_BDados_Ficheiro_Binario(BDadosCoupe *BD, char *fich_dat)
{
    FILE *f = fopen(fich_dat, "rb");
    FILE *ft = NULL;

    int numTabelas;
    int numCampos;
    int numRegistos; 

    fread(&numTabelas, sizeof(int), 1, f);

    for (size_t i = 0; i < numTabelas; i++)
    {
        int lengthNomeTabela;
        fread(&lengthNomeTabela, sizeof(int), 1, f);
        char *nomeTabela = malloc(sizeof(char) * (lengthNomeTabela + 1));
        fread(nomeTabela, sizeof(char), lengthNomeTabela, f);

        int lengthNomeFicheiro;
        fread(&lengthNomeFicheiro, sizeof(int), 1, f);
        char *nomeFicheiro = malloc(sizeof(char) * (lengthNomeFicheiro + 1));
        fread(nomeFicheiro, sizeof(char), lengthNomeFicheiro, f);

        ft = fopen(nomeFicheiro, "rb");
        if (!ft)
            return INSUCESSO;

        TABELA* T = Criar_Tabela(BD, nomeTabela);



        numCampos = 0;
        fread(&numCampos, sizeof(int), 1, ft);

        for (size_t i = 0; i < numCampos; i++)
        {
            int lengthTipo;
            fread(&lengthTipo, sizeof(int), 1, ft);
            char *tipo = malloc(sizeof(char) * (lengthTipo + 1));
            fread(tipo, sizeof(char), lengthTipo, ft);

            int lengthNomeCampo;
            fread(&lengthNomeCampo, sizeof(int), 1, ft);
            char *nomeCampo = malloc(sizeof(char) * (lengthNomeCampo + 1));
            fread(nomeCampo, sizeof(char), lengthNomeCampo, ft);

            Add_Campo_Tabela(T, nomeCampo, tipo);
        }

        fread(&numRegistos, sizeof(int), 1, ft);
        for (size_t i = 0; i < numRegistos; i++)
        {
            char* valores = malloc(sizeof(char) * 255);
            strcpy(valores, "");
            for (size_t k = 0; k < numCampos; k++)
            {
                int lengthValor;
                fread(&lengthValor, sizeof(int), 1, ft);

                char* valor = malloc(sizeof(char) * (lengthValor + 1));
                fread(valor, sizeof(char), lengthValor, ft);

                // Concat valor into valores with ';' separator
                strcat(valores, valor);

                if(k != numCampos - 1)
                    strcat(valores, ";");

            }

            Add_Valores_Tabela(T, valores);
        }

        fclose(ft);
    }

    fclose(f);

    return SUCESSO;
}
// L)	Apagar o conte�do de uma Tabela. A Tabela continua a existir na BDados, mas n�o cont�m os dados, ou seja, os campos continuam, mas os registos s�o eliminados.
int DELETE_TABLE_DATA(TABELA *T)
{
    if (!T)
        return INSUCESSO;
    DestruirLG(T->LRegistos, Destruir_Registo);
    T->LRegistos = CriarLG();

    return SUCESSO;
}

int Compara_Nome_Tabela(void *t1, void *t2)
{
    TABELA *T1 = (TABELA *)t1;
    TABELA *T2 = (TABELA *)t2;

    return strcmp(T1->NOME_TABELA, T2->NOME_TABELA);
}

// M)	Apagar o conte�do de uma Tabela e remove a tabela da base de dados.
int DROP_TABLE(BDadosCoupe *BD, char *nome_tabela)
{
    if (!BD || !nome_tabela)
        return INSUCESSO;

    TABELA *T = Pesquisar_Tabela(BD, nome_tabela);

    if (!T)
        return INSUCESSO;

    DestruirLG(T->LCampos, Destruir_Campo);
    DestruirLG(T->LRegistos, Destruir_Registo);

    RemoveLG(BD->LTabelas, T, Compara_Nome_Tabela);
    // free(T);

    return INSUCESSO;
}

int Compare(char *s1, char *s2)
{
    return strcmp(s1, s2);
}

// N)	Selecionar (Apresentar no ecran!) da base de dados todos os registos que obede�am a uma dada condi��o, a fun��o deve retornar o n�mero de registos selecionados. (Ter em aten��o o exemplo das aulas te�ricas!). Nota: esta � certamente a funcionalidade mais usada num sistema de base de dados�, por isso se estiver bem otimizada�. O utilizador agradece!!!!
int SELECT(BDadosCoupe *BD, char *_tabela, int (*f_condicao)(char *, char *), char *nome_campo, char *valor_comparacao)
{
    if (!BD || !_tabela || !f_condicao || !nome_campo || !valor_comparacao)
        return INSUCESSO;

    TABELA *T = Pesquisar_Tabela(BD, _tabela);

    if (!T)
        return INSUCESSO;

    NOG* NR = T->LRegistos->Inicio;
    NOG* NC = T->LCampos->Inicio;

    int campoIndex = -1;
    int aux = 0;

    while (NC)
    {
        CAMPO* C = (CAMPO *)NC->Info;

        if (strcmp(C->NOME_CAMPO, nome_campo) == 0)
            campoIndex = aux;
            

        aux++;
        NC = NC->Prox;
    }

    if(campoIndex == -1)
        return INSUCESSO;

    aux = 0;
    int count = 0;
    int found = 0;

    printf("  QUERY: SELECT * FROM %s WHERE %s = %s\n  Resultado(s):\n\n", _tabela, nome_campo, valor_comparacao);

    while (NR)
    {
        REGISTO* R = (REGISTO *)NR->Info;
        NOG* NV = R->LValores->Inicio;

        aux = 0;

        while (NV)
        {
            if(aux == campoIndex)
            {
                char* valor = (char*) NV->Info;
                if (f_condicao(valor, valor_comparacao) == 0) {
                    found = 1;
                    count++;
                }  
            }

            aux++;

            if(found)
                break;

            NV = NV->Prox;
        }

        if(!found)
        {
            NR = NR->Prox;
            continue;
        }

        NV = R->LValores->Inicio;
        
        MostrarLG(R->LValores, Mostra_Valor);
        printf("\n");
        
        found = 0;
        NR = NR->Prox;
    }

    return count;
}

// O)	Remover todos os registos que obede�am a uma dada condi��o, a fun��o deve retornar o n�mero de registos removidos.
int DELETE(BDadosCoupe *BD, char *_tabela, int (*f_condicao)(char *, char *), char *nome_campo, char *valor_comparacao)
{
    return SUCESSO;
}
// P)	Atualizar todos os registos da tabela onde o Campo � dado, que obede�am a uma dada condi��o, a fun��o deve retornar o n�mero de registos que foram atualizados.
int UPDATE(BDadosCoupe *BD, char *_tabela, int (*f_condicao)(char *, char *), char *campo_comp, char *valor_campo_comp, char *nome_campo_update, char *valor_campo_update)
{
    return SUCESSO;
}
