#ifndef BDADOSCOUPE_H_INCLUDED
#define BDADOSCOUPE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListaGenerica.h"
typedef struct
{
    char NOME_BDADOS[50];
    char VERSAO_BDADOS[50];
    ListaGenerica *LTabelas;
    //ListaTabelas *LTabelas;
}BDadosCoupe;

typedef struct
{
    char NOME_TABELA[50];
    ListaGenerica *LCampos;
    ListaGenerica *LRegistos;
    //ListaCampos *LCampos;
    //ListaRegistos *LRegistos;
}TABELA;

typedef struct
{
    char NOME_CAMPO[50];
    char TIPO[10];
}CAMPO;

typedef struct 
{ 
    ListaGenerica *LValores;
}REGISTO; 



//A) Criar a Base de dados;
BDadosCoupe *Criar_BDados(char *nome_bd, char *versao);
//B) Criar uma Tabela na Base de Dados, a tabela deve ser inserida � lista de tabelas da BD
TABELA *Criar_Tabela(BDadosCoupe *BD, char *nome_tabela);
//C)  Adicionar um campo a uma tabela.
int Add_Campo_Tabela(TABELA *T, char *nome_campo, char *tipo_campo);
//D)	Adicionar dados(registos) a uma tabela, os dados s�o dados numa string onde o separador � �;�m ex: Add_Valores_Tabela(T, �123;Joao;965654449�)
int Add_Valores_Tabela(TABELA *T, char *dados);
//E)	Adicionar dados(registos) a uma tabela, os dados s�o dados numa string onde o separador � �;�
int Add_Valores_Tabela_BDados(BDadosCoupe *BD, char *nome_tabela, char *dados);
//F)	Pesquisar uma Tabela da base de dados
TABELA *Pesquisar_Tabela(BDadosCoupe *BD, char *nome_tabela);
//G)	Mostrar uma Tabela
void Mostrar_Tabela_NOME(BDadosCoupe *BD, char *tabela);
void Mostrar_Tabela(TABELA *T);
//H)	Mostrar toda a base de dados, dever� mostrar todas as Tabelas da BDados.
void Mostrar_BDados(BDadosCoupe *BD);
//I)	Libertar toda a mem�ria alocada pela base de dados.
void Destruir_BDados(BDadosCoupe *BD);
//J)	Mem�ria ocupada por toda a base de dados.
long int Memoria_BDados(BDadosCoupe *BD);
long int Memoria_Desperdicada_BDados(BDadosCoupe *BD);

//K)	Exportar/Importar para/de Ficheiro (o retorno destas fun��es, permite saber se a fun��o foi bem/mal-executada!):
int AtulizaFicheiroBDados(BDadosCoupe *BD,char *ficheiro_csv, char* nomeTabela, char* ficheiroTabela);
int Exportar_Tabela_BDados_Excel(BDadosCoupe *BD, char *tabela, char *ficheir_csv);
int ImportarTabelaBDados(BDadosCoupe *BD, char *ficheiro_csv, char *nomeTabela);
int Exportar_BDados_Excel(BDadosCoupe *BD);
int Importar_BDados_Excel(BDadosCoupe *BD, char *ficheir_csv);
int Exportar_BDados_Ficheiro_Binario(BDadosCoupe *BD, char *fich_dat);
int Importar_BDados_Ficheiro_Binario(BDadosCoupe *BD, char *fich_dat);
//L)	Apagar o conte�do de uma Tabela. A Tabela continua a existir na BDados, mas n�o cont�m os dados, ou seja, os campos continuam, mas os registos s�o eliminados.
int DELETE_TABLE_DATA(TABELA *T);
//M)	Apagar o conte�do de uma Tabela e remove a tabela da base de dados.
int DROP_TABLE(BDadosCoupe *BD, char *nome_tabela);
//N)	Selecionar (Apresentar no ecran!) da base de dados todos os registos que obede�am a uma dada condi��o, a fun��o deve retornar o n�mero de registos selecionados. (Ter em aten��o o exemplo das aulas te�ricas!). Nota: esta � certamente a funcionalidade mais usada num sistema de base de dados�, por isso se estiver bem otimizada�. O utilizador agradece!!!!
int SELECT(BDadosCoupe *BD, char *_tabela, int (*f_condicao)(char *, char *), char *nome_campo, char *valor_comparacao);
//O)	Remover todos os registos que obede�am a uma dada condi��o, a fun��o deve retornar o n�mero de registos removidos.
int DELETE(BDadosCoupe *BD, char *_tabela, int (*f_condicao)(char *, char *), char *nome_campo, char *valor_comparacao);
//P)	Atualizar todos os registos da tabela onde o Campo � dado, que obede�am a uma dada condi��o, a fun��o deve retornar o n�mero de registos que foram atualizados.
int UPDATE(BDadosCoupe *BD, char *_tabela, int (*f_condicao)(char *, char *), char *campo_comp, char *valor_campo_comp, char *nome_campo_update, char *valor_campo_update);

#endif // BDADOSCOUPE_H_INCLUDED
