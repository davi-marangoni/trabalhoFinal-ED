#include <stdio.h>
#include <stdlib.h>
#include "tarefa.h"

void menu(){
    printf("1. Adicionar Tarefa\n");
    printf("2. Visualizacao de Tarefas\n");
    printf("3. Concluir Tarefa\n");
    printf("4. Excluir Tarefa\n");
    printf("5. Sair\n");
}


int main(){
    int opcao, id = 0;
    Arvore *arvore = malloc(sizeof(Arvore));
    iniciarArvore(arvore);
    do{
        menu();
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                id++;
                criarTarefa(arvore, id);
                break;
            case 2:
                imprimirArvore(arvore->raiz);
                break;
            case 3:

            case 4:

            case 5:

            default:
                printf("Opcao invalida!\n");
        }
    }while(opcao != 5);
    return 0;
}



