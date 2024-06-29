#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tarefa.h"

void iniciarArvore(Arvore *a){
    a->raiz = NULL;
}

No* inserirElemento(No *no, No *novo, No *pai) {
    if (no == NULL) {
        novo->pai = pai;
        novo->altura = 1; // um no sem filhos tem altura 1
        return novo;
    }

    if (novo->tarefa.id < no->tarefa.id) {
        no->esquerda = inserirElemento(no->esquerda, novo, no);
    } else if (novo->tarefa.id > no->tarefa.id) {
        no->direita = inserirElemento(no->direita, novo, no);
    } else {
        return no; // IDs duplicados não sao permitidos
    }

    // Atualiza a altura do no atual e balanceia a arvore
    return balancearArvore(no);
}

No* balancearArvore(No* no) {
    if (no == NULL) {
        return no;
    }

    // Atualiza a altura do no
    no->altura = 1 + max(altura(no->esquerda), altura(no->direita));

    // Verifica o balanceamento do no
    int balance = verificaBalanceamento(no);

    // Rotação a direita
    if (balance > 1 && verificaBalanceamento(no->esquerda) >= 0) {
        return rotacaoDireita(no);
    }

    // Rotação a esquerda
    if (balance < -1 && verificaBalanceamento(no->direita) <= 0) {
        return rotacaoEsquerda(no);
    }

    // Rotacao dupla (esquerda-direita)
    if (balance > 1 && verificaBalanceamento(no->esquerda) < 0) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    // Rotacao dupla (direita-esquerda)
    if (balance < -1 && verificaBalanceamento(no->direita) > 0) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }
    return no;
}


No* rotacaoDireita(No* y) {
    No* x = y->esquerda;
    No* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    if (T2 != NULL) {
        T2->pai = y;
    }

    x->pai = y->pai;
    y->pai = x;

    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    return x;
}

No* rotacaoEsquerda(No* x) {
    No* y = x->direita;
    No* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    if (T2 != NULL) {
        T2->pai = x;
    }

    y->pai = x->pai;
    x->pai = y;

    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

    return y;
}

int verificaBalanceamento(No* no) {
    if (no == NULL) {
        return 0;
    }
    return altura(no->esquerda) - altura(no->direita);
}

// funcao auxiliar para obter a altura de um no
int altura(No* no) {
    if (no == NULL) {
        return 0;
    }
    return no->altura;
}

// funcao auxiliar para obter o maximo de dois inteiros
int max(int a, int b) {
    return (a > b)? a : b;
}

void imprimirArvore(No *no){
    if(no != NULL){
        imprimirArvore(no->esquerda);
        printf("Tarefa ID-%d\n", no->tarefa.id);
        printf("Descricao: %s", no->tarefa.descricao);
        printf("Tempo limite (em horas): %d\n", no->tarefa.tempoLimite);
        printf("Situcao: %s\n", no->tarefa.situacao == 1 ? "Ativa" : "Concluida");
        printf("DEBUG\n");
        printf("Pai: %d\n", no->pai == NULL ? -1 : no->pai->tarefa.id);
        printf("Altura: %d\n", no->altura);
        printf("Filho esquerdo: %d\n", no->esquerda == NULL ? -1 : no->esquerda->tarefa.id);
        printf("Filho direito: %d\n", no->direita == NULL ? -1 : no->direita->tarefa.id);
        printf("--------------------\n");
        imprimirArvore(no->direita);
    }
}

No* buscarElemento(No *no, int id){
    if(no == NULL){
        return NULL;
    } else {
        if(no->tarefa.id == id){
            return no;
        } else {
            if(no->tarefa.id > id){
                return buscarElemento(no->esquerda, id);
            } else {
                return buscarElemento(no->direita, id);
            }
        }
    }
}

void excluirTarefa(Arvore *arvore) {
    int id;
    printf("Digite o ID da tarefa que deseja excluir: ");
    scanf("%d", &id);
    arvore->raiz = excluirElemento(arvore->raiz, id);
}

No* excluirElemento(No* no, int id) {
    if (no == NULL) {
        printf("Tarefa nao encontrada!\n");
        return no;
    }

    if (id < no->tarefa.id) {
        no->esquerda = excluirElemento(no->esquerda, id);
    } else if (id > no->tarefa.id) {
        no->direita = excluirElemento(no->direita, id);
    } else {
        if (no->esquerda == NULL || no->direita == NULL) {
            No* temp = no->esquerda ? no->esquerda : no->direita;

            if (temp == NULL) {
                temp = no;
                no = NULL;
            } else {
                *no = *temp;
            }
            free(temp);
        } else {
            No* temp = encontrarMaximo(no->esquerda);
            no->tarefa = temp->tarefa;
            no->esquerda = excluirElemento(no->esquerda, temp->tarefa.id);
        }
    }

    if (no == NULL) {
        return no;
    }

    // Atualiza pai dos filhos apos a exclusao
    if (no->esquerda != NULL) {
        no->esquerda->pai = no;
    }
    if (no->direita != NULL) {
        no->direita->pai = no;
    }

    return balancearArvore(no);
}


No* encontrarMinimo(No* no) {
    No* atual = no;

    while (atual->esquerda != NULL) {
        atual = atual->esquerda;
    }

    return atual;
}

No* encontrarMaximo(No* no) {
    No* atual = no;

    while (atual->direita != NULL) {
        atual = atual->direita;
    }

    return atual;
}

void concluirTarefa(Arvore *arvore){
    int id;
    printf("Digite o ID da tarefa que deseja concluir: ");
    scanf("%d", &id);
    No *tarefa = buscarElemento(arvore->raiz, id);
    if(tarefa != NULL){
        if (tarefa->tarefa.situacao == 2) {
            printf("Tarefa ja concluida!\n");
            return;
        }
        tarefa->tarefa.situacao = 2;
    } 
    else {
        printf("Tarefa nao encontrada!\n");

    }
}

void criarTarefa(Arvore *arvore, int id) {
    Tarefa tarefa;
    printf("Digite a descricao da tarefa: \n");

    // Limpa o buffer do teclado
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}

    fgets(tarefa.descricao, sizeof tarefa.descricao, stdin);
    printf("Digite o tempo limite da tarefa (Em horas): \n");
    scanf("%d", &tarefa.tempoLimite);
    tarefa.situacao = 1;
    tarefa.id = id;

    No *novo = malloc(sizeof(No));
    novo->tarefa = tarefa;
    novo->esquerda = NULL;
    novo->direita = NULL;
    novo->pai = NULL;  // O no novo ainda nao tem pai

    // Atualiza a raiz da arvore se necessario
    if (arvore->raiz == NULL) {
        arvore->raiz = novo;
    } else {
        arvore->raiz = inserirElemento(arvore->raiz, novo, NULL);
    }
}











