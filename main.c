#include <stdio.h>
#include <stdlib.h>
#include "tarefa.h"

void menu() {
    printf("1. Adicionar Tarefa\n");
    printf("2. Visualizacao de Tarefas\n");
    printf("3. Concluir Tarefa\n");
    printf("4. Excluir Tarefa\n");
    printf("5. Sair\n");
}

int main() {
    int opcao, id = 0;
    Arvore *arvore = malloc(sizeof(Arvore));
    iniciarArvore(arvore);
    do {
        menu();
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                id++;
                criarTarefa(arvore, id);
                break;
            case 2:
                visualizarTarefas(arvore);
                break;
            case 3:
                concluirTarefa(arvore);
                break;
            case 4:
                excluirTarefa(arvore);
                break;
            case 5:
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 5);
    return 0;
}