
#include "BDadosCoupe.h"
#include <time.h>

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
    AddLG(BD->LTabelas, T);
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
    if (!C) return INSUCESSO;
    strcpy(C->NOME_CAMPO, nome_campo);
    strcpy(C->TIPO, tipo_campo);
    int res = AddLG(T->LCampos, C);
    return res;
}
//D)	Adicionar dados(registos) a uma tabela, os dados s�o dados numa string onde o separador � �;�m ex: Add_Valores_Tabela(T, �123;Joao;965654449�)
int Add_Valores_Tabela(TABELA *T, char *dados)
{
    if(!T) return INSUCESSO;
    
    char *token;
    char *delim = ";";
    char *dados_copia = (char *)malloc(sizeof(char) * strlen(dados));
    strcpy(dados_copia, dados);
    token = strtok(dados_copia, delim);

    REGISTO *R = (REGISTO *)malloc(sizeof(REGISTO));
    R->LValores = CriarLG();
    
    AddLG(R->LValores, token);
    
    if(!R) return INSUCESSO;
    while(token)
    {
        token = strtok(NULL, delim);
        if(!token)
            break;
        AddLG(R->LValores, token);
    }

    AddLG(T->LRegistos, R);

    return SUCESSO;
}
//E)	Adicionar dados(registos) a uma tabela, os dados s�o dados numa string onde o separador � �;�
int Add_Valores_Tabela_BDados(BDadosCoupe *BD, char *nome_tabela, char *dados)
{
    TABELA *T = Pesquisar_Tabela(BD, nome_tabela);
    int res = Add_Valores_Tabela(T, dados);
    return res;
}
//F)	Pesquisar uma Tabela da base de dados
TABELA *Pesquisar_Tabela(BDadosCoupe *BD, char *nome_tabela)
{
    if (BD == NULL) return INSUCESSO;

    //TABELA *findedTable;

    NOG *N = BD->LTabelas->Inicio;
    while (N != NULL)
    {
        TABELA *T = (TABELA *)N->Info;

        if(strcmp(T->NOME_TABELA, nome_tabela) == 0)
            return T;

        N = N->Prox;
    }
    return INSUCESSO;
}
//G)	Mostrar uma Tabela
void Mostrar_Tabela_NOME(BDadosCoupe *BD, char *tabela)
{
    TABELA *T = Pesquisar_Tabela(BD, tabela);
    Mostrar_Tabela(T);
    free(T);
}

void Mostrar_Campo(void *C)
{
    CAMPO * c = (CAMPO *)C;
    printf("%s ", c->NOME_CAMPO);
}

void Mostra_Valor(void *V)
{
    printf("%s ", V);
}

void Mostrar_Registo(void *R)
{
    REGISTO * r = (REGISTO *)R;
    MostrarRevLG(r->LValores, Mostra_Valor);
    printf("\n");
}

void Mostrar_Tabela(TABELA *T)
{
    clock_t init = clock();
    printf("Nome da Tabela: %s\n", T->NOME_TABELA);
    MostrarRevLG(T->LCampos, Mostrar_Campo);
    printf("\n");
    MostrarRevLG(T->LRegistos, Mostrar_Registo);
    printf("\n");
    clock_t end = clock();
    double time = (double)(end - init) / CLOCKS_PER_SEC;
    printf("Tempo de Execucao: %f\n", time);
}

//H)	Mostrar toda a base de dados, dever� mostrar todas as Tabelas da BDados.
void Mostrar_BDados(BDadosCoupe *BD)
{
    clock_t init = clock();
    NOG* T = BD->LTabelas->Inicio;
    while (T)
    {
        Mostrar_Tabela(T->Info);
        printf("\n-----------------------------------------------------\n");
        T = T->Prox;
    }
    
}

void Destruir_Valor(void *V)
{
    free(V);
}

void Destruir_Registo(void *R)
{
    REGISTO * r = (REGISTO *)R;
    DestruirLG(r->LValores, Destruir_Valor);
    free(r);
}

void Destruir_Campo(void* C)
{
    CAMPO * c = (CAMPO *)C;
    free(c);
}

void Destruir_Tabela(void* T)
{
    TABELA * t = (TABELA *)T;
    DestruirLG(t->LCampos, Destruir_Campo);
    DestruirLG(t->LRegistos, Destruir_Registo);
    free(t);
}
//I)	Libertar toda a mem�ria alocada pela base de dados.
void Destruir_BDados(BDadosCoupe *BD)
{
    DestruirLG(BD->LTabelas, Destruir_Tabela);
    free(BD);
}
//J)	Mem�ria ocupada por toda a base de dados.
long int Memoria_BDados(BDadosCoupe *BD)
{
    return -1;
}
long int Memoria_Desperdicada_BDados(BDadosCoupe *BD)
{
    return -1;
}
//K)	Exportar/Importar para/de Ficheiro (o retorno destas fun��es, permite saber se a fun��o foi bem/mal-executada!):
int Exportar_Tabela_BDados_Excel(BDadosCoupe *BD, char *tabela, char *ficheir_csv)
{
    return SUCESSO;
}
int Exportar_BDados_Excel(BDadosCoupe *BD, char *ficheir_csv)
{
    return SUCESSO;
}
int Importar_BDados_Excel(BDadosCoupe *BD, char *ficheir_csv)
{
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
//L)	Apagar o conte�do de uma Tabela. A Tabela continua a existir na BDados, mas n�o cont�m os dados, ou seja, os campos continuam, mas os registos s�o eliminados.
int DELETE_TABLE_DATA(TABELA *T)
{
    TABELA *T =malloc(sizeof(TABELA));
    if(!T) return INSUCESSO;
    DestruirLG(T->LRegistos, Destruir_Registo);
    free(T);
    return SUCESSO;
}
//M)	Apagar o conte�do de uma Tabela e remove a tabela da base de dados.
int DROP_TABLE(BDadosCoupe *BD, char *nome_tabela)
{
     NOG *N = BD->LTabelas->Inicio;
    while (N != NULL)
    {
        TABELA *T = (TABELA *)N->Info;
        if(strcmp(T->NOME_TABELA, nome_tabela) == 0)
        {
            destruir_LG(T->LCampos, Destruir_Campo);
            destruir_LG(T->LRegistos, Destruir_Registo);
            free(N);
            return SUCESSO;
        }
        N = N->Prox;
    }
    return INSUCESSO;
}
//N)	Selecionar (Apresentar no ecran!) da base de dados todos os registos que obede�am a uma dada condi��o, a fun��o deve retornar o n�mero de registos selecionados. (Ter em aten��o o exemplo das aulas te�ricas!). Nota: esta � certamente a funcionalidade mais usada num sistema de base de dados�, por isso se estiver bem otimizada�. O utilizador agradece!!!!
int SELECT(BDadosCoupe *BD, char *_tabela, int (*f_condicao)(char *, char *), char *nome_campo, char *valor_comparacao)
{
    return SUCESSO;
}
//O)	Remover todos os registos que obede�am a uma dada condi��o, a fun��o deve retornar o n�mero de registos removidos.
int DELETE(BDadosCoupe *BD, char *_tabela, int (*f_condicao)(char *, char *), char *nome_campo, char *valor_comparacao)
{
    return SUCESSO;
}
//P)	Atualizar todos os registos da tabela onde o Campo � dado, que obede�am a uma dada condi��o, a fun��o deve retornar o n�mero de registos que foram atualizados.
int UPDATE(BDadosCoupe *BD, char *_tabela, int (*f_condicao)(char *, char *), char *campo_comp, char *valor_campo_comp, char *nome_campo_update, char *valor_campo_update)
{
    return SUCESSO;
}

