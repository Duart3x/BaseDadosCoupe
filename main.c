#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "BDadosCoupe.h"
/*
Uma Base de dados Relacional � formada por tabelas,
onde cada tabela tem as v�rias colunas (campos)
e os registos (informa��o),
um registo � uma cole��o de dados.
As tabelas podem ter relacionamentos entre elas
(mas esta parte ser� dada nas disciplinas de base de dados do 2�ano do curso).
*/
int main()
{
    printf("Template do projecto BDadosCoupe para os alunos!\n");
    BDadosCoupe *BD = Criar_BDados("BD-Banco", "Versao 1.0");

    TABELA *T = Criar_Tabela(BD, "CLIENTES");
    Add_Campo_Tabela(T, "ID", "INT");
    Add_Campo_Tabela(T, "NOME", "STRING");
    Add_Campo_Tabela(T, "IDADE", "INT");
   // Add_Valores_Tabela(T, "1;Joao;18");
    //Add_Valores_Tabela(T, "2;Maria;25");
    time_t init = clock();
    char* nomeUtilizador = (char*)malloc(sizeof(char) * 20);
    char* dados = (char*)malloc(sizeof(char) * 100);

    for (size_t i = 1; i < 90001; i++)
    {
        
        sprintf(nomeUtilizador, "Utilizador_%d", i);

        int idade = rand() % 100;

        
        sprintf(dados, "%d;%s;%d", i, nomeUtilizador, idade);

        Add_Valores_Tabela(T, dados);
    }

    

    time_t end = clock();
    double time = (double)(end - init) / CLOCKS_PER_SEC;
    printf("Tempo de execucao: %f segundos\n", time);
    
    free(nomeUtilizador);
    free(dados);
   // Add_Valores_Tabela_BDados(BD, "CLIENTES", "23;Joao;25");

    //Mostrar_Tabela(T);
   // Mostrar_BDados(BD);
    
    //system("pause");

    Destruir_BDados(BD);

    return 0;
}
