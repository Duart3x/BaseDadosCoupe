#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

#include "BDadosCoupe.h"

int main()
{
    /*BDadosCoupe *BD = Criar_BDados("BD", "Versao 1.0");

    TABELA *T = Criar_Tabela(BD, "CLIENTES");
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

    char *ficheiroBaseDados = malloc(sizeof(char) * strlen(BD->NOME_BDADOS) + 6);
    sprintf(ficheiroBaseDados, "%s.dat", BD->NOME_BDADOS);
    Exportar_BDados_Ficheiro_Binario(BD, ficheiroBaseDados);
    
    Destruir_BDados(BD);*/

    BDadosCoupe *BD2 = Criar_BDados("BD", "Versao 1.0");
    Importar_BDados_Excel(BD2, "BD.csv");

    //Mostrar_BDados(BD2);

    printf("\n  N de resultados: %d\n", SELECT(BD2, "CLIENTES", Compare, "IDADE", "34"));

    system("pause");

    Destruir_BDados(BD2);
    system("pause");
    /*time_t end = clock();
    double time = (double)(end - init) / CLOCKS_PER_SEC;
    printf("Tempo de execucao: %f segundos\n", time);

    free(nomeUtilizador);
    free(dados);
    // Add_Valores_Tabela_BDados(BD, "CLIENTES", "23;Joao;25");


    // Exportar_Tabela_BDados_Excel(BD,"CLIENTES","clientes.csv");
    // Exportar_Tabela_BDados_Excel(BD,"PRODUTOS","produtos.csv");
    Mostrar_BDados(BD);

    Exportar_BDados_Excel(BD);


    long int memoria = Memoria_BDados(BD);

    printf("Memoria ocupada: %ld bytes\n", memoria);

    Destruir_BDados(BD);
    system("pause");

    BDadosCoupe *BD2 = Criar_BDados("BD", "Versao 1.0");

    Importar_BDados_Excel(BD2,"BD.csv");
    Mostrar_BDados(BD2);
    Destruir_BDados(BD2);

    system("pause");*/

    /*char *menu[] = {"Criar a Base de Dados",
                    "Criar uma Tabela na Base de Dados",
                    "Adicionar um campo a uma tabela",
                    "Adicionar dados a uma tabela",
                    "Pesquisar uma Tabela da Base de Dados",
                    "Mostrar uma tabela",
                    "Mostrar a Base de Dados(Todas as tabelas)",
                    "Libertar toda a memória alocada pela Base de Dados",
                    "Apagar o conteúdo de uma Tabela",
                    "Apagar o conteúdo de uma Tabela e removê-la da Base de Dados",
                    "Selecionar da Base de Dados todos os registos que obedeçam a uma dada condição",
                    "Remover todos os registos que obedeçam a uma dada condição",
                    "Atualizar todos os registos da tabela onde o Campo é dado",
                    "\033[31mSAIR\033[0m"};

    bool exitMenu = false;
    bool askToContinue = false;
    int file = -1;
    int op = -1;

    do
    {
        askToContinue = true;
        op = drawMenu(menu, 14, "Menu");
        switch (op)
        {
                case 1:

                    break;

                case 2:

                    break;

                case 3:

                    break;

                case 4:

                    break;

                case 5:

                    break;

                case 6:

                    break;

            case -1:
                exitMenu = true;
                break;
        }
    } while (exitMenu == false);
*/
    return 0;
}
