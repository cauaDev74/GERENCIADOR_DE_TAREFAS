#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <locale.h>

#define LENGTH 40
#define MAX 25

typedef struct{
    char nome[LENGTH];
    char desc[LENGTH];
    char status[LENGTH];
}Task;

void clearInputBuffer() {
    //Limpa caracteres restantes no buffer de entrada
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void trim(char str[]){
    int inicio = 0;
    int fim = strlen(str) - 1;

    while(isspace(str[inicio])){
        inicio++;
    }

    while(fim >= inicio && isspace(str[fim])){
        fim--;
    }

    int i, j = 0;

    for(i = inicio; i <= fim; i++){
        str[j++] = str[i];
    }

    str[j] = '\0';
}

//Funções crud
void cadastrarTarefa(Task tarefas[], int *indiceT){
    setlocale(LC_ALL, "Portuguese_Brazil.1252");
    if(*indiceT >= MAX){
        printf("Total de cadastros concluidos.\n");
        return;
    }

    Task novaTarefa;

    //Recebendo o nome da tarefa
    printf("<============| CADASTRO DE TAREFA |============>\n\n");
    printf("Insira a tarefa: ");
    if(fgets(novaTarefa.nome, LENGTH, stdin) == NULL){
        printf("Erro ao ler o nome.\n");
        return;
    }
    
    if(strchr(novaTarefa.nome, '\n') == NULL){
        printf("Nome muito grande.\n");
        clearInputBuffer();
        return;
    }
    novaTarefa.nome[strcspn(novaTarefa.nome, "\n")] = 0;
    
    trim(novaTarefa.nome);
    if(strlen(novaTarefa.nome) == 0){
        printf("Descrição inválida.\n");
        return;
    }
    printf("\n<============================================>\n\n");
    
    //Criando uma descrição
    printf("Insira a descrição: ");
    if(fgets(novaTarefa.desc, LENGTH, stdin) == NULL){
        printf("Erro ao ler.\n");
        return;
    }
    novaTarefa.desc[strcspn(novaTarefa.desc, "\n")] = 0;
    
    trim(novaTarefa.desc);
    if(strlen(novaTarefa.desc) == 0){
        printf("ERRO.\n");
    }
    getchar();
    clearInputBuffer();
    printf("\n<============================================>\n\n");
    
    strcpy(novaTarefa.status, "Pendente");
    
    tarefas[*indiceT] = novaTarefa;
    (*indiceT)++;
    
    printf("Tarefa adicionada com sucesso.\n");
    printf("<============================================>\n\n");
    system("pause");

}

void listarTarefas(Task tarefas[], int indiceT){
    setlocale(LC_ALL, "Portuguese_Brazil.1252");
    if(indiceT <= 0){
        printf("Nao ha tarefas cadastradas.\n");
        return;
    }
    printf("//=============================\\\\\n");
    printf("||        Lista de Tarefas:      ||\n");
    printf("\\\\=============================//\n\n");

    printf("||================================||\n");
    for(int i = 0; i < indiceT; i++){
        printf("||==========Tarefa %d============||\n", i+1);
        printf("Nome: %s\n", tarefas[i].nome);
        printf("Descr: %s\n", tarefas[i].desc);
        printf("Status: %s\n", tarefas[i].status);
        printf("||================================||\n");
    }
    
}

void concluirTarefa(Task tarefas[], int *indiceT, int *indiceC){
    if(*indiceT <= 0){
        printf("Nenhuma tarefa cadastrada.\n");
        return;
    }

    printf("<<=====SELECIONE UMA TAREFA=====>>\n\n");
    printf("-> ");
}

void removerTarefa();

void menu(int *escolha){
    setlocale(LC_ALL, "Portuguese_Brazil.1252");
    int select;
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
    printf("  ||   (7) ... Sair e salvar         ||\n");
    printf("  ||                                 ||\n");
    printf("  ||=================================||\n");
    printf("Selecione ==> ");
    scanf("%d", &select);
    clearInputBuffer();

    *escolha = select;
}

//Funções arquivo
void salvarArquivo();
void carregarArquivo();

int main(){
    setlocale(LC_ALL, "Portuguese_Brazil.1252");
    Task tasks[MAX];
    int contaTarefas = 0;
    int contaTaskConcluida = 0;
    int escolher;

    do{
        system("clear");
        menu(&escolher);
        
        switch (escolher){
            case 1:
            system("cls");
            cadastrarTarefa(tasks, &contaTarefas);
            break;
            case 3:
            system("cls");
            listarTarefas(tasks, contaTarefas);
        case 7:
            exit(1);
        default:
            break;
        }
    }while(1);



    return 0;
}