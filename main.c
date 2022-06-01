#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

#include "BDadosCoupe.h"

BDadosCoupe *SelectBDCoup(ListaGenerica *X,int op)
{

    NOG *aux = X->Inicio;
    BDadosCoupe *bd = NULL;
    int i = 0;

    while (aux != NULL)
    {
        bd = aux->Info;
        if (i==op-1)
        {
            return bd;
        }
        aux = aux->Prox;
        i++;
    }  
    return NULL;
}
TABELA *SelectedTable(BDadosCoupe *BD,int op){
    NOG *aux=BD->LTabelas->Inicio;
    TABELA *T=NULL;
    int i=0;
    while(aux!=NULL){
        T=aux->Info;
        if(i==op-1){
            return T;
        }
        aux=aux->Prox;
        i++;
    }
}
char **listabasedados(ListaGenerica *X){
     BDadosCoupe *BD3 = NULL;
    // percorrer listagenerica
    NOG *aux = X->Inicio;
    int nel = X->NEL;
    char **listaBDs= malloc(sizeof(char) * nel);
    int i = 0;

    while (aux != NULL)
    {
        BD3 = aux->Info;
        listaBDs[i] = malloc(sizeof(char) * (strlen(BD3->NOME_BDADOS)+1));
        strcpy(listaBDs[i], BD3->NOME_BDADOS);
        printf("%s\n", listaBDs[i]);
        aux = aux->Prox;
        i++;
    }
    return listaBDs;
}
char** listanometabelas(BDadosCoupe *BD){
    NOG *aux = BD->LTabelas->Inicio;
    TABELA *T = NULL;
    int nel = BD->LTabelas->NEL;
    char **listaBDs= malloc(sizeof(char) * nel);
    int i = 0;

    while (aux != NULL)
    {
        T= aux->Info;
        listaBDs[i] = malloc(sizeof(char) * (strlen(T->NOME_TABELA)+1));
        strcpy(listaBDs[i],T->NOME_TABELA);
        printf("%s\n", listaBDs[i]);
        aux = aux->Prox;
        i++;
    }
    return listaBDs;

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

     char *ficheiroBaseDados = malloc(sizeof(char) * strlen(BD->NOME_BDADOS) + 6);
     sprintf(ficheiroBaseDados, "%s.dat", BD->NOME_BDADOS);
     Exportar_BDados_Ficheiro_Binario(BD, ficheiroBaseDados);

     Destruir_BDados(BD);

     /*BDadosCoupe *BD2 = Criar_BDados("BD", "Versao 1.0");
     Importar_BDados_Ficheiro_Binario(BD2, "BD.dat");
     Destruir_BDados(BD2);*/
    // system("pause");
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

    BDadosCoupe *SelectedBD=NULL;
    BDadosCoupe *BD = NULL;

    char *menu[] = {"Criar a Base de Dados",
                    "Entrar na Base de Dados",
                    "Importar Base de Dados",
                    "Exportar Base de Dados",
                    "\033[31mSAIR\033[0m"};
    char *expoptions[] = {"Excel(.cvs)",
                          "Binário(.dat)",
                          "\033[31mVoltar\033[0m"};
    char *submenu[] = {"Criar Tabela",
                       "Adicionar dados a uma tabela",
                       "Mostrar Todas as Tabelas",
                       "Apagar Tabela",
                       "SELECT",
                       "UPDATE",
                       "DELETE",
                       "\033[31mVoltar\033[0m"};
    bool exitMenu = false;
    bool askToContinue = false;
    int file = -1;
    int op = -1;
    int expop = -1;
    int subop = -1;
    TABELA *T = NULL;
    char **p;
    do
    {
        askToContinue = true;
        op = drawMenu(menu, 5, "Menu Principal");
        switch (op)
        {
        case 1:
        {
            char *nomeBD = (char *)malloc(sizeof(char) * 50);
            char *versaoBD = (char *)malloc(sizeof(char) * 50);
            printf("Nome Base de Dados: ");
            scanf("%s", nomeBD);
            printf("Versão Base de Dados: ");
            scanf("%s", versaoBD);
            BD = Criar_BDados(nomeBD, versaoBD);
            AddFimLG(BDS, BD);

            askToContinue = false;
            break;
        }
        case 2:
            if (BDS->Inicio == NULL)
            {
                printf("Não tem uma Base de dados\n");
                system("pause");
                askToContinue = false;
            }
            else
            {
                system("cls");
                
                int lbds = 0;
                p=listabasedados(BDS);
                lbds = drawMenu(p, BDS->NEL, "Escolha a Base de Dados");
                SelectedBD=SelectBDCoup(BDS, lbds);
                printf("Base de Dados: %s\n", SelectedBD->NOME_BDADOS);
                subop = drawMenu(submenu, 8, "Menu Base Dados");
                switch (subop)
                {
                case 1:
                    
                    char *nomeTabela = (char *)malloc(sizeof(char) * 50);
                    char *nomeCampo = (char *)malloc(sizeof(char) * 50);
                    char *tipoCampo = (char *)malloc(sizeof(char) * 50);
                    int nCampos = 0;
                    printf("Nome da Tabela: ");
                    scanf("%s", nomeTabela);
                    T = Criar_Tabela(SelectedBD, nomeTabela);
                    printf("Quantos campos pretende criar? ");
                    scanf("%d", &nCampos);
                    for (size_t i = 0; i < nCampos; i++)
                    {
                        printf("Nome do campo: ");
                        scanf("%s", nomeCampo);
                        printf("Tipo do campo: ");
                        scanf("%s", tipoCampo);
                        Add_Campo_Tabela(T, nomeCampo, tipoCampo);
                    }
                    
                    break;

                case 2:
                    int ltbs=0;
                    p=listanometabelas(SelectedBD);
                    ltbs = drawMenu(p, SelectedBD->LTabelas->NEL, "Escolha a Tabela");
                    T=SelectedTable(SelectedBD, ltbs);
                    /*printf("Nome da Tabela: ");
                    //scanf("%s", nomeTabela);
                    if (Pesquisar_Tabela(SelectedBD, nomeTabela) == 0)
                    {
                        printf("Não existe a tabela %s\n", nomeTabela);
                        system("pause");
                    }
                    else
                    {*/
                        int nRegistos;
                        char *dados = (char *)malloc(sizeof(char) * 100);
                        printf("Quantos registos pretende adicionar?\n");
                        scanf("%d", &nRegistos);
                        printf("Adicione os dados delimitados por ';'\n");
                        /*if(Pesquisar_Tabela(SelectedBD, T->NOME_TABELA) == 0)
                        {
                             printf("Não existe a tabela %s\n", nomeTabela);
                        }
                        else
                        {*/
                            for (size_t i = 0; i < nRegistos; i++)
                            {
                                printf("Dados: ");
                                scanf("%s", dados);
                                printf("%d",Add_Valores_Tabela_BDados(SelectedBD, T->NOME_TABELA, dados));

                            }
                           
                            system("pause");
                        //}
                        
                        free(dados);
                    //}
                    break;
                case 3:
                    if (SelectedBD->LTabelas->Inicio == NULL)
                    {   printf("Não existem Tabelas\n");
                        system("pause");
                    }
                    else
                    {
                        Mostrar_BDados(SelectedBD);
                        system("pause");
                    }
                    break;

                case 4:
                    printf("Nome da Tabela: ");
                    scanf("%s", nomeTabela);
                    if (Pesquisar_Tabela(SelectedBD, nomeTabela) == 0)
                    {
                        printf("Não existe uma tabela com esse nome %s\n", nomeTabela);
                        system("pause");
                    }
                    else
                    {
                       DROP_TABLE(SelectedBD, nomeTabela);
                      
                    }
                    free(nomeTabela);
                    
                    break;
                case 5:
                    break;
                case 6:
                    break;
                case 7:
                    break;
                case 8:
                    break;
                }
            }
                askToContinue = false;
                break;

        case 3:
                system("cls");
                int lbds = 0;
                p=listabasedados(BDS);
                lbds = drawMenu(p, BDS->NEL, "Escolha a Base de Dados");
                SelectedBD=SelectBDCoup(BDS, lbds);
                expop=drawMenu(expoptions, 3, "Menu Importar");
                char * fich_name=SelectedBD->NOME_BDADOS;
                switch (expop)
                {
                case 1:
                    strcat(fich_name,".csv");
                    Importar_BDados_Excel(SelectedBD, fich_name);  
                    break;
                case 2:
                    strcat(fich_name,".bin");
                    Importar_BDados_Ficheiro_Binario(SelectedBD, fich_name);
                    break;
                case 3:
                    break;
                
                }
            free(fich_name);
            askToContinue = false;
            break;

        case 4:
                system("cls");
                p=listabasedados(BDS);
                lbds = drawMenu(p, BDS->NEL, "Escolha a Base de Dados");
                SelectedBD=SelectBDCoup(BDS, lbds);
                expop=drawMenu(expoptions, 3, "Menu Exportar");
                switch (expop)
                {
                case 1:
                    Exportar_BDados_Excel(SelectedBD);
                    break;
                case 2:
                    char * fich_name=SelectedBD->NOME_BDADOS;
                    strcat(fich_name,".bin");
                    Exportar_BDados_Ficheiro_Binario(SelectedBD,fich_name);
                    break;
                case 3:
                    break;
                
                }
            askToContinue = false;
            break;

        case 5:
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
            system("cls");
        }
    } while (exitMenu == false);

    return 0;
}

