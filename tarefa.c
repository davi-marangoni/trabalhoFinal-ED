#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tarefa.h"

void iniciarArvore(Arvore *a){
    a->raiz = NULL;
}

No* inserirElemento(No *no, No *novo, No *pai){
    if (no == NULL){
        novo->pai = pai;
        return novo;
    } else {
        if (no->tarefa.id >= novo->tarefa.id)
            no->esquerda = inserirElemento(no->esquerda, novo, no);
        else
            no->direita = inserirElemento(no->direita, novo, no);
    }
    return no;
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

void excluirTarefa(Arvore *arvore){
    int id;
    printf("Digite o ID da tarefa que deseja excluir: ");
    scanf("%d", &id);
    No *tarefa = buscarElemento(arvore->raiz, id);
    if(tarefa != NULL){
        if(tarefa->esquerda == NULL && tarefa->direita == NULL){
            if(tarefa->pai == NULL){
                arvore->raiz = NULL;
            } else {
                if(tarefa->pai->esquerda == tarefa){
                    tarefa->pai->esquerda = NULL;
                } else {
                    tarefa->pai->direita = NULL;
                }
            }
        } else if(tarefa->esquerda == NULL || tarefa->direita == NULL){
            No *filho = tarefa->esquerda == NULL ? tarefa->direita : tarefa->esquerda;
            if(tarefa->pai == NULL){
                arvore->raiz = filho;
            } else {
                if(tarefa->pai->esquerda == tarefa){
                    tarefa->pai->esquerda = filho;
                } else {
                    tarefa->pai->direita = filho;
                }
            }
            filho->pai = tarefa->pai;
        } else {
            No *sucessor = tarefa->direita;
            while(sucessor->esquerda != NULL){
                sucessor = sucessor->esquerda;
            }
            tarefa->tarefa = sucessor->tarefa;
            excluirTarefa(arvore);
        }
        free(tarefa);
    } else {
        printf("Tarefa nao encontrada!\n");
    }
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

void criarTarefa(Arvore *arvore, int id){
    Tarefa tarefa;
    printf("Digite a descricao da tarefa: \n");

    // Clear the input buffer
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

    if(arvore->raiz == NULL){
        arvore->raiz = novo;
        novo->pai = NULL;  // the root node has no parent
    } else {
        inserirElemento(arvore->raiz, novo, NULL);
    }
    
}











