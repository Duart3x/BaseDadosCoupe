
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
    if(!T) return INSUCESSO;
    
    char *token;
    char *delim = ";";
    char *dados_copia = (char *)malloc(sizeof(char) * (strlen(dados) + 5));

    strcpy(dados_copia, dados);
    token = strtok(dados_copia, delim);

    REGISTO *R = (REGISTO *)malloc(sizeof(REGISTO));
    R->LValores = CriarLG();

    AddFimLG(R->LValores, token);

    if (!R)
        return INSUCESSO;
    while (token)
    {
        token = strtok(NULL, delim);
        if (!token)
            break;
        AddFimLG(R->LValores, token);
    }

    AddFimLG(T->LRegistos, R);

    free(token);
    // free(dados_copia);

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
    /*char* valor = (char*)V;
    free(valor);*/
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
                memoria += strlen((char* )N4->Info);
                
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

    NOG* N = BD->LTabelas->Inicio;
    NOG* N2 = NULL;
    NOG* N3 = NULL;
    NOG* N4 = NULL;

    TABELA* T = NULL;
    CAMPO* C = NULL;
    REGISTO * R = NULL;
    
    while (N)
    {
        T = (TABELA *)N->Info;
        memoriaExata += sizeof(char) * strlen(T->NOME_TABELA);
        N2 = T->LCampos->Inicio;
        while(N2)
        {
            C = (CAMPO *)N2->Info;
            memoriaExata += sizeof(char) * strlen(C->NOME_CAMPO);
            memoriaExata += sizeof(char) * strlen(C->TIPO);
            N2 = N2->Prox;
        }

        N3 = T->LRegistos->Inicio;
        while(N3)
        {
            R = (REGISTO *)N3->Info;
            N4 = R->LValores->Inicio;
            while(N4)
            {
                memoriaExata += strlen((char* )N4->Info);
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
        
        if(NC->Prox != NULL)
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

            if(NV->Prox != NULL)
                fprintf(f, "%s;", NV->Info);
            else
                fprintf(f, "%s", NV->Info);
            NV = NV->Prox;
        }
        fprintf(f, "\n");
        
        NR = NR->Prox;
    }
    fclose(f);
    char* ficheiroBaseDados = malloc(sizeof(char)*(strlen(BD->NOME_BDADOS)+6));
    sprintf(ficheiroBaseDados, "%s.csv", BD->NOME_BDADOS);

    AtulizaFicheiroBDados(BD,ficheiroBaseDados,T->NOME_TABELA,ficheir_csv);
    return SUCESSO;
}

int AtulizaFicheiroBDados(BDadosCoupe *BD,char *ficheiro_csv, char* nomeTabela, char* ficheiroTabela)
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
        char **V = Read_Split_Line_File(f,2,&nCamposLidos,";");
        if(!V)
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
    NOG* NT = BD->LTabelas->Inicio;

    char* ficheiroTabelas = malloc(sizeof(char)*250);

    while (NT)
    {
        TABELA *T = (TABELA *)NT->Info;
        sprintf(ficheiroTabelas, "%s.csv", T->NOME_TABELA);
        Exportar_Tabela_BDados_Excel(BD, T->NOME_TABELA, ficheiroTabelas);
        NT = NT->Prox;
    }

    return SUCESSO;
}

//TODO: IMPORTAR TABELA
int ImportarTabelaBDados(BDadosCoupe *BD, char *ficheiro_csv, char *nomeTabela)
{
    // Check if file exists
    FILE *f = fopen(ficheiro_csv, "r");
    if (!f)
    {
        fclose(f);
        return INSUCESSO;
    }
    
    TABELA* T = malloc(sizeof(TABELA));

    // Check if table exists
    int nCamposLidos;
    while (!feof(f))
    {
        char **V = Read_Split_Line_File(f,2,&nCamposLidos,";");
        if(!V)
            continue;
        
    }
    fclose(f);
    return INSUCESSO;
}

//TODO: ACABAR ESTA PORRA
int Importar_BDados_Excel(BDadosCoupe *BD, char *ficheir_csv)
{
    FILE* f = fopen(ficheir_csv, "r");
    if (!f)
        return INSUCESSO;

    int nCamposLidos;
    while (!feof(f))
    {
        char** V = Read_Split_Line_File(f,2,&nCamposLidos,";");
        if(!V)
            continue;
        
        if (strcmp(V[0], "TABELA") == 0)
            continue;
        
        FILE* ft = fopen(V[1], "r");
        
        if (!ft)
        {
            fclose(f);
            fclose(ft);
            return INSUCESSO;
        }

    }
    
    return SUCESSO;
}
int Exportar_BDados_Ficheiro_Binario(BDadosCoupe *BD, char *fich_dat)
{
    return SUCESSO;
}
int Importar_BDados_Ficheiro_Binario(BDadosCoupe *BD, char *fich_dat)
{
    return SUCESSO;
}
// L)	Apagar o conte�do de uma Tabela. A Tabela continua a existir na BDados, mas n�o cont�m os dados, ou seja, os campos continuam, mas os registos s�o eliminados.
int DELETE_TABLE_DATA(TABELA *T)
{
    if (!T)
        return INSUCESSO;
    DestruirLG(T->LRegistos, Destruir_Registo);
    free(T);
    return SUCESSO;
}
// M)	Apagar o conte�do de uma Tabela e remove a tabela da base de dados.
int DROP_TABLE(BDadosCoupe *BD, char *nome_tabela)
{
    NOG *N = BD->LTabelas->Inicio;
    while (N != NULL)
    {
        TABELA *T = (TABELA *)N->Info;
        if (strcmp(T->NOME_TABELA, nome_tabela) == 0)
        {
            DestruirLG(T->LCampos, Destruir_Campo);
            DestruirLG(T->LRegistos, Destruir_Registo);
            free(N);
            return SUCESSO;
        }
        N = N->Prox;
    }
    return INSUCESSO;
}
// N)	Selecionar (Apresentar no ecran!) da base de dados todos os registos que obede�am a uma dada condi��o, a fun��o deve retornar o n�mero de registos selecionados. (Ter em aten��o o exemplo das aulas te�ricas!). Nota: esta � certamente a funcionalidade mais usada num sistema de base de dados�, por isso se estiver bem otimizada�. O utilizador agradece!!!!
int SELECT(BDadosCoupe *BD, char *_tabela, int (*f_condicao)(char *, char *), char *nome_campo, char *valor_comparacao)
{
    return SUCESSO;
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
