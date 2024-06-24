#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tarefa.h"


// Função para adicionar uma tarefa na árvore
Node* adicionarTarefa(Node* raiz, Tarefa tarefa){
    if(raiz == NULL){
        Node* novo = (Node*)malloc(sizeof(Node));
        novo->tarefa = tarefa;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }
    if(tarefa.id < raiz->tarefa.id){
        raiz->esquerda = adicionarTarefa(raiz->esquerda, tarefa);
    }else{
        raiz->direita = adicionarTarefa(raiz->direita, tarefa);
    }
    return raiz;
}

// Function to sort a list of tasks by deadline using quicksort
void quicksort(Node* start, Node* end) {
    if (start == NULL || start == end || start == end->direita) {
        return;
    }

    Node* pivot = partition(start, end);
    quicksort(start, pivot);
    quicksort(pivot->direita, end);
}

// Function to partition the list for quicksort
Node* partition(Node* start, Node* end) {
    Tarefa pivot = end->tarefa;
    Node* i = start->esquerda;

    for (Node* j = start; j != end; j = j->direita) {
        if (j->tarefa.tempoLimite <= pivot.tempoLimite) {
            i = (i == NULL) ? start : i->direita;
            swap(&(i->tarefa), &(j->tarefa));
        }
    }
    i = (i == NULL) ? start : i->direita;
    swap(&(i->tarefa), &(end->tarefa));
    return i;
}

// Function to swap two tasks
void swap(Tarefa* a, Tarefa* b) {
    Tarefa temp = *a;
    *a = *b;
    *b = temp;
}

// Function to display a list of tasks
void exibirTarefas(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("ID: %d\n", current->tarefa.id);
        printf("Descricao: %s\n", current->tarefa.descricao);
        printf("Tempo Limite: %d horas\n", current->tarefa.tempoLimite);
        printf("Situacao: %s\n", current->tarefa.situacao == 0 ? "Ativa" : "Concluida");
        printf("\n");
        current = current->direita;
    }
}










