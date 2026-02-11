#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LENGTH 40

typedef struct{
    char nome[LENGTH];
    char descricao[LENGTH];
    char status[LENGTH];
}Tarefa;

//Funções crud
void cadastrarTarefa();

void listarTarefas();

void concluirTarefa();

void removerTarefa();

void menu(int *escolha){
     printf("//=====================================\\\\\n");
    printf("||                                       ||\n");
    printf("||           GERENCIADOR DE LOJA         ||\n");
    printf("||                                       ||\n");
    printf("\\\\=====================================//\n");
    printf("  ||                                 ||\n");
    printf("  ||   (1) ... Cadastrar produto     ||\n");
    printf("  ||   (2) ... Vender                ||\n");
    printf("  ||   (3) ... Pesquisar Produto     ||\n");
    printf("  ||   (4) ... Imprimir estoque      ||\n");
    printf("  ||   (5) ... Sair                  ||\n");
    printf("  ||                                 ||\n");
    printf("  ||=================================||\n");
    scanf("%d", &escolha);
}

//Funções arquivo
void salvarArquivo();
void carregarArquivo();