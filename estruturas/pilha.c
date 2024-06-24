#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int dado;
    struct no *next;
} No;

typedef struct pilha {
    No *head;
    No *tail;
} Pilha;

void iniciarPilha(Pilha *p){
    p->head = NULL;
    p->tail = NULL;
}

void inserirElementos(Pilha *p, int dado){
    No *novo = (No*)malloc(sizeof(No));
    novo->dado = dado;
    novo->next = NULL;

    if(p->head == NULL){
        p->head = novo;
    } else {
        novo->next = p->head;
        p->head = novo;
    }
}

void removerElemento(Pilha *p){
    No *aux = p->head;
    p->head = p->head->next;
    free(aux);
}

void imprimirPilha(Pilha *p){
    No *aux = p->head;
    while(aux != NULL){
        printf("%d\n", aux->dado);
        aux = aux->next;
    }
}

void destruirPilha(Pilha *p){
    No *aux = p->head;
    while(aux != NULL){
        No *temp = aux->next;
        free(aux);
        aux = temp;
    }
    p->head = NULL;
    p->tail = NULL;
}

int main(){
    Pilha p;
    iniciarPilha(&p);

    int opcao;
    do {
        printf("1 - Inserir\n");
        printf("2 - Remover\n");
        printf("3 - Imprimir\n");
        printf("4 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                int dado;
                printf("Digite o dado: ");
                scanf("%d", &dado);
                inserirElementos(&p, dado);
                break;
            case 2:
                removerElemento(&p);
                break;
            case 3:
                imprimirPilha(&p);
                break;
            case 4:
                destruirPilha(&p);
                break;
            default:
                printf("Opcao invalida\n");
        }
    } while(opcao != 4);

}