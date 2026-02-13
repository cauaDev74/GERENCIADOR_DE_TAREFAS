#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <locale.h>

#define LENGTH 40
#define MAX 25

typedef struct{
    char nome[LENGTH];
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

void paraMinusculo(char name[]){
    for(int i = 0; name[i] != '\0'; i++){
        name[i] = tolower((unsigned char)name[i]);
    }
}

//Funções crud
void cadastrarTarefa(Task tarefas[], int *indiceT){
    if(*indiceT >= MAX){
        printf("Total de cadastros concluidos.\n");
        return;
    }

    Task novaTarefa;

    //Recebendo o nome da tarefa
    printf("<============| CADASTRO DE TAREFA |============>\n\n");
    printf("Nome da tarefa: ");
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
    
    strcpy(novaTarefa.status, "Pendente");
    
    tarefas[*indiceT] = novaTarefa;
    (*indiceT)++;
    
    printf("Tarefa adicionada com sucesso.\n");
    printf("<============================================>\n\n");

}

void listarTarefas(Task tarefas[], int indiceT){
    if(indiceT <= 0){
        printf("Nao ha tarefas cadastradas.\n");
        return;
    }
    printf("//=============================\\\\\n");
    printf("||        Lista de Tarefas:      ||\n");
    printf("\\\\=============================//\n\n");

    printf("\n");
    for(int i = 0; i < indiceT; i++){
        printf("||==========Tarefa %d============||\n", i+1);
        printf("Nome: %s\n", tarefas[i].nome);
        printf("Status: %s\n", tarefas[i].status);
        printf("||================================||\n");
    }
    
}

void concluirTarefa(Task tarefas[], int contaTarefas){
    if(contaTarefas <= 0){
        printf("Nenhuma tarefa cadastrada.\n");
        return;
    }

    int indice;
    char confirmar;
    printf("<<=====SELECIONE UMA TAREFA=====>>\n\n");
    printf("1 a %d -> ", contaTarefas);
    if(scanf("%d", &indice) != 1 || indice < 1 || indice > contaTarefas){
        printf("Indice invalido. \n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    indice--;

    printf("||==========Tarefa %d============||\n", indice);
    printf("Nome: %s\n", tarefas[indice].nome);
    printf("Status: %s\n", tarefas[indice].status);
    printf("||================================||\n");
    while(confirmar != 'y' || confirmar != 'n'){
        printf("Deseja concluir? (y|n): ");
        scanf("%c", &confirmar);
        getchar();
        confirmar = tolower(confirmar);

        if(confirmar == 'y'){
            strcpy(tarefas[indice].status, "Concluido");
            printf("Tarefa concluida.\n");
            return;
        }else if(confirmar == 'n'){
            printf("Tarefa nao concluida.\n");
            return;
        }
    }

}

void editarTarefa(Task tarefas[], int contaTarefas){
    if(contaTarefas <= 0){
        printf("Nenhuma tarefa cadastrada.\n");
        return;
    }

    int indice;
    char confirmar;
    printf("<<=====SELECIONE UMA TAREFA=====>>\n\n");
    printf("1 a %d -> ", contaTarefas);
    if(scanf("%d", &indice) != 1 || indice < 1 || indice > contaTarefas){
        printf("Indice invalido. \n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    indice--;

    printf("<<======= | EDITANDO | =======>>\n\n");
    printf("||==========Tarefa %d============||\n", indice);
    printf("Nome: %s\n", tarefas[indice].nome);
    printf("Status: %s\n", tarefas[indice].status);
    printf("||================================||\n\n");
    printf("Digite o novo nome: ");

    fgets(tarefas[indice].nome, LENGTH, stdin);
    tarefas[indice].nome[strcspn(tarefas[indice].nome, "\n")] = 0;

    strcpy(tarefas[indice].status, "Pendente");

    printf("Tarefa editada com sucesso.\n");
}

void removerTarefa(Task tarefas[], int *contaTarefas){
    if(*contaTarefas <= 0){
        printf("Nenhuma tarefa cadastrada.\n");
        return;
    }

    int indice;
    char confirmar;
    printf("<<=====SELECIONE UMA TAREFA=====>>\n\n");
    printf("1 a %d -> ", *contaTarefas);
    if(scanf("%d", &indice) != 1 || indice < 1 || indice > *contaTarefas){
        printf("Indice invalido. \n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    indice--;

    printf("||==========Tarefa %d============||\n", indice);
    printf("Nome: %s\n", tarefas[indice].nome);
    printf("Status: %s\n", tarefas[indice].status);
    printf("||================================||\n");

    while(confirmar != 'y' && confirmar != 'n'){
        printf("Deseja concluir? (y|n): ");
        scanf("%c", &confirmar);
        clearInputBuffer();
        confirmar = tolower(confirmar);
        
    }
    if(confirmar == 'y'){
        for(int i = indice; i < *contaTarefas - 1; i++){
            tarefas[i] = tarefas[i + 1];
        }
        printf("Tarefa deletada com sucesso.\n");
        (*contaTarefas)--;
        return;
    }else if(confirmar == 'n'){
        printf("Nada foi deletado.\n");
        return;
}

}

//Funções arquivo
void salvarArquivo(Task tarefas[], int contaTarefas){
    FILE *arquivo = fopen("data/tasks.csv", "w");

    if(arquivo == NULL){
        printf("Erro ao ler o arquivo.\n");
        return;
    }

    //1. Salva a quantidade total
    fprintf(arquivo, "%d\n", contaTarefas);

    for(int i = 0; i < contaTarefas; i++){
        fprintf(arquivo, "%s\n", tarefas[i].nome);
        fprintf(arquivo, "%s\n", tarefas[i].status);
    }
    fclose(arquivo);
    printf("Arquivo salvo com sucesso.\n");
}
void carregarArquivo(Task tarefas[], int *contaTarefas){
    FILE *arquivo = fopen("data/tasks.csv", "r");

    if(arquivo == NULL){
        printf("Erro ao carregar o arquivo.\n");
        return;
    }

    fscanf(arquivo, "%d", contaTarefas);

    fgetc(arquivo);

    for(int i = 0; i < *contaTarefas; i++){
        Task t;

        if(fgets(t.nome, LENGTH, arquivo) == NULL) break;
        t.nome[strcspn(t.nome, "\n")] = 0;

        if(fgets(t.status, LENGTH, arquivo) == NULL) break;
        t.status[strcspn(t.status, "\n")] = 0;

        tarefas[i] = t;
    }
    fclose(arquivo);
    printf("Dados carregados: %d Tarefas carregadas\n", *contaTarefas);
    sleep(1);
}

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