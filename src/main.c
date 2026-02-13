#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <locale.h>
#include "lib/func.h"

int main(){
    setlocale(LC_ALL, "Portuguese_Brazil.1252");
    Task tasks[MAX];
    int contaTarefas = 0;
    int escolher;

    carregarArquivo(tasks, &contaTarefas);

    do{
        system("clear");
        printf("//=====================================\\\\\n");
        printf("||                                       ||\n");
        printf("||           GERENCIADOR DE TAREFAS      ||\n");
        printf("||                                       ||\n");
        printf("\\\\=====================================//\n");
        printf("  ||                                 ||\n");
        printf("  ||   (1) ... Cadastrar tarefa      ||\n");
        printf("  ||   (2) ... Concluir tarefa       ||\n");
        printf("  ||   (3) ... Listar Tarefas        ||\n");
        printf("  ||   (4) ... Editar Tarefa         ||\n");
        printf("  ||   (5) ... Deletar Tarefa        ||\n");
        printf("  ||   (6) ... Sair                  ||\n");
        printf("  ||                                 ||\n");
        printf("  ||=================================||\n");
        printf("Selecione ==> ");
        scanf("%d", &escolher);
        clearInputBuffer();


        switch (escolher){
        case 1:
            cadastrarTarefa(tasks, &contaTarefas);
            break;
        case 2:
            concluirTarefa(tasks, contaTarefas);
            break;
        case 3:
            listarTarefas(tasks, contaTarefas);
            break;
        case 4:
            editarTarefa(tasks, contaTarefas);
            break;
        case 5:
            removerTarefa(tasks, &contaTarefas);
            break;
        case 6:
            salvarArquivo(tasks, contaTarefas);
            printf("Saindo do programa.\n");
            break;
        default:
            printf("Opcao nao encontrada.\n");
            break;
        }

        if(escolher != 6){
            printf("\nPressione ENTER para continuar...");
            getchar(); 
        }

    }while(escolher != 6);

    return 0;
}