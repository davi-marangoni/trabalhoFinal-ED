#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int dado;
    struct no *next;
} No;

typedef struct fila {
    No *head;
    No *tail;
} Fila;

void iniciarFila(Fila *f){
    f->head = NULL;
    f->tail = NULL;
}

void inserirElementos(Fila *f, int dado){
    No *novo = (No*)malloc(sizeof(No));
    novo->dado = dado;
    novo->next = NULL;

    if(f->head == NULL){
        f->head = novo;
    } else {
        f->tail->next = novo;
    }
    f->tail = novo;
}

void removerElemento(Fila *f){
    No *aux = f->head;
    f->head = f->head->next;
    free(aux);
}

void imprimirFila(Fila *f){
    No *aux = f->head;
    while(aux != NULL){
        printf("%d\n", aux->dado);
        aux = aux->next;
    }
}

void destruirFila(Fila *f){
    No *aux = f->head;
    while(aux != NULL){
        No *temp = aux->next;
        free(aux);
        aux = temp;
    }
    f->head = NULL;
    f->tail = NULL;
}


int main(){

    Fila f;
    iniciarFila(&f);

    int opcao;
    do{
        printf("1 - Inserir\n");
        printf("2 - Remover\n");
        printf("3 - Imprimir\n");
        printf("4 - Destruir\n");
        printf("0 - Sair\n");
        printf("Digite a opcao: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                printf("Digite o valor a ser inserido: ");
                int valor;
                scanf("%d", &valor);
                inserirElementos(&f, valor);
                break;
            case 2:
                removerElemento(&f);
                break;
            case 3:
                imprimirFila(&f);
                break;
            case 4:
                destruirFila(&f);
                break;
        }
    } while(opcao != 0);
}