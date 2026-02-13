#ifndef FUNC_H
#define FUNC_H

#define LENGTH 40
#define MAX 25

typedef struct{
    char nome[LENGTH];
    char status[LENGTH];
}Task;

void clearInputBuffer();
void trim(char str[]);
void paraMinusculo(char name[]);

void cadastrarTarefa(Task tarefas[], int *indiceT);
void listarTarefas(Task tarefas[], int indiceT);
void concluirTarefa(Task tarefas[], int contaTarefas);
void editarTarefa(Task tarefas[], int contaTarefas);
void removerTarefa(Task tarefas[], int *contaTarefas);

void salvarArquivo(Task tarefas[], int contaTarefas);
void carregarArquivo(Task tarefas[], int *contaTarefas);

#endif