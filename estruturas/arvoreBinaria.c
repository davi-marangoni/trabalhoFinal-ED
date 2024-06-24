#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int dado;
    struct no *esquerda;
    struct no *direita;
} No;

typedef struct arvore {
    No *raiz;
} Arvore;


void iniciarArvore(Arvore *a){
    a->raiz = NULL;
}

No* inserirElemento(No *no, No *novo){
    if (no == NULL){
        return novo;
    } else {
        if (no->dado >= novo->dado)
            no->esquerda = inserirElemento(no->esquerda, novo);
        else
            no->direita = inserirElemento(no->direita, novo);
    }
    return no;
}

void imprimirArvore(No *no){
    if(no != NULL){
        imprimirArvore(no->esquerda);
        printf("%d\n", no->dado);
        imprimirArvore(no->direita);
    }
}

No* buscarElemento(No *no, int valor){
    if(no == NULL){
        return NULL;
    } else {
        if(no->dado == valor){
            return no;
        } else {
            if(no->dado > valor){
                return buscarElemento(no->esquerda, valor);
            } else {
                return buscarElemento(no->direita, valor);
            }
        }
    }
}

void removerElemento(Arvore *a, int valor){
    No *no = buscarElemento(a->raiz, valor);
    if(no != NULL){
        //Caso 1: Nó folha
        if(no->esquerda == NULL && no->direita == NULL){
            free(no);
        } else {
            //Caso 2: Nó com um filho
            if(no->esquerda == NULL || no->direita == NULL){
                No *filho = no->esquerda != NULL ? no->esquerda : no->direita;
                no->dado = filho->dado;
                no->esquerda = filho->esquerda;
                no->direita = filho->direita;
                free(filho);
            } else {
                //Caso 3: Nó com dois filhos
                No *aux = no->esquerda;
                while(aux->direita != NULL){
                    aux = aux->direita;
                }
                no->dado = aux->dado;
                free(aux);
            }
        }
    }
}


int main(){
    Arvore a;
    iniciarArvore(&a);

    int opcao, valor;
    do{
        printf("1 - Inserir\n");
        printf("2 - Remover Elemento\n");
        printf("3 - Buscar Elemento\n");
        printf("4 - Imprimir Arvore\n");
        printf("5 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                printf("Digite o valor: ");
                scanf("%d", &valor);

                //Criar um novo nó
                No *novo = (No*)malloc(sizeof(No));
                novo->dado = valor;
                novo->esquerda = NULL;
                novo->direita = NULL;

                //Inserir o novo nó na árvore
                a.raiz = inserirElemento(a.raiz, novo);
                break;
            case 2:
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor);
                removerElemento(&a, valor);
                break;
            case 3:
                printf("Digite o valor a ser buscado: ");
                scanf("%d", &valor);
                No *no = buscarElemento(a.raiz, valor);
                if(no != NULL){
                    printf("Valor encontrado: %d\n", no->dado);
                } else {
                    printf("Valor nao encontrado\n");
                }
                break;
            case 4:
                imprimirArvore(a.raiz);
                break;
        }
    } while(opcao != 5);


}