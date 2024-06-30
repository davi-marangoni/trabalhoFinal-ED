#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tarefa.h"

// Função para iniciar a árvore
void iniciarArvore(Arvore *a) {
    a->raiz = NULL; // Define a raiz da árvore como NULL, indicando que a árvore está vazia
}

// Função para inserir um elemento na árvore
No* inserirElemento(No *no, No *novo, No *pai) {
    if (no == NULL) {
        novo->pai = pai;  // Define o pai do novo nó
        novo->altura = 1; // Um nó sem filhos tem altura 1
        return novo;      // Retorna o novo nó como a raiz da subárvore
    }

    // Inserção recursiva na subárvore esquerda ou direita
    if (novo->tarefa.id < no->tarefa.id) {
        no->esquerda = inserirElemento(no->esquerda, novo, no);
    } else if (novo->tarefa.id > no->tarefa.id) {
        no->direita = inserirElemento(no->direita, novo, no);
    } else {
        return no; // IDs duplicados não são permitidos
    }

    // Atualiza a altura do nó atual e balanceia a árvore
    return balancearArvore(no);
}

// Função para balancear a árvore AVL
No* balancearArvore(No* no) {
    if (no == NULL) {
        return no;
    }

    // Atualiza a altura do nó
    no->altura = 1 + max(altura(no->esquerda), altura(no->direita));

    // Verifica o balanceamento do nó
    int balance = verificaBalanceamento(no);

    // Realiza rotações para balancear a árvore
    if (balance > 1 && verificaBalanceamento(no->esquerda) >= 0) {
        return rotacaoDireita(no); // Rotação simples à direita
    }
    if (balance < -1 && verificaBalanceamento(no->direita) <= 0) {
        return rotacaoEsquerda(no); // Rotação simples à esquerda
    }
    if (balance > 1 && verificaBalanceamento(no->esquerda) < 0) {
        no->esquerda = rotacaoEsquerda(no->esquerda); // Rotação dupla (esquerda-direita)
        return rotacaoDireita(no);
    }
    if (balance < -1 && verificaBalanceamento(no->direita) > 0) {
        no->direita = rotacaoDireita(no->direita); // Rotação dupla (direita-esquerda)
        return rotacaoEsquerda(no);
    }

    return no; // Retorna o nó balanceado
}

// Função para realizar rotação à direita
No* rotacaoDireita(No* y) {
    No* x = y->esquerda;       // Define x como filho esquerdo de y
    No* T2 = x->direita;       // Salva a subárvore direita de x

    // Realiza a rotação
    x->direita = y;
    y->esquerda = T2;

    // Atualiza os pais
    if (T2 != NULL) {
        T2->pai = y;
    }
    x->pai = y->pai;
    y->pai = x;

    // Atualiza as alturas
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    return x; // Retorna a nova raiz da subárvore
}

// Função para realizar rotação à esquerda
No* rotacaoEsquerda(No* x) {
    No* y = x->direita;        // Define y como filho direito de x
    No* T2 = y->esquerda;      // Salva a subárvore esquerda de y

    // Realiza a rotação
    y->esquerda = x;
    x->direita = T2;

    // Atualiza os pais
    if (T2 != NULL) {
        T2->pai = x;
    }
    y->pai = x->pai;
    x->pai = y;

    // Atualiza as alturas
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

    return y; // Retorna a nova raiz da subárvore
}

// Função para verificar o balanceamento de um nó
int verificaBalanceamento(No* no) {
    if (no == NULL) {
        return 0; // Se o nó é NULL, o balanceamento é 0
    }
    return altura(no->esquerda) - altura(no->direita); // Retorna a diferença de altura entre as subárvores
}

// Função auxiliar para obter a altura de um nó
int altura(No* no) {
    if (no == NULL) {
        return 0; // Se o nó é NULL, sua altura é 0
    }
    return no->altura; // Retorna a altura do nó
}

// Função auxiliar para obter o máximo de dois inteiros
int max(int a, int b) {
    return (a > b)? a : b; // Retorna o maior dos dois valores
}

// Função para imprimir a árvore
void imprimirArvore(No *no) {
    if (no != NULL) {
        imprimirArvore(no->esquerda); // Imprime a subárvore esquerda
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
        imprimirArvore(no->direita); // Imprime a subárvore direita
    }
}

// Função para buscar um elemento na árvore pelo ID
No* buscarElemento(No *no, int id) {
    if (no == NULL) {
        return NULL; // Se o nó é NULL, a busca falhou
    } else {
        if (no->tarefa.id == id) {
            return no; // Se o nó contém o ID buscado, retorna o nó
        } else {
            if (no->tarefa.id > id) {
                return buscarElemento(no->esquerda, id); // Busca na subárvore esquerda
            } else {
                return buscarElemento(no->direita, id); // Busca na subárvore direita
            }
        }
    }
}

// Função para excluir uma tarefa da árvore
void excluirTarefa(Arvore *arvore) {
    int id;
    printf("Digite o ID da tarefa que deseja excluir: ");
    scanf("%d", &id); // Lê o ID da tarefa a ser excluída
    arvore->raiz = excluirElemento(arvore->raiz, id); // Exclui o elemento da árvore
}

// Função para excluir um elemento da árvore
No* excluirElemento(No* no, int id) {
    if (no == NULL) {
        printf("Tarefa nao encontrada!\n");
        return no; // Se o nó é NULL, a tarefa não foi encontrada
    }

    // Busca o nó a ser excluído
    if (id < no->tarefa.id) {
        no->esquerda = excluirElemento(no->esquerda, id);
    } else if (id > no->tarefa.id) {
        no->direita = excluirElemento(no->direita, id);
    } else {
        // Nó encontrado, realiza a exclusão
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
        return no; // Se o nó é NULL após a exclusão, retorna NULL
    }

    // Atualiza pai dos filhos após a exclusão
    if (no->esquerda != NULL) {
        no->esquerda->pai = no;
    }
    if (no->direita != NULL) {
        no->direita->pai = no;
    }

    return balancearArvore(no); // Balanceia a árvore após a exclusão
}

// Função para encontrar o mínimo de uma subárvore
No* encontrarMinimo(No* no) {
    No* atual = no;

    while (atual->esquerda != NULL) {
        atual = atual->esquerda; // Vai para o nó mais à esquerda
    }

    return atual; // Retorna o nó mínimo
}

// Função para encontrar o máximo de uma subárvore
No* encontrarMaximo(No* no) {
    No* atual = no;

    while (atual->direita != NULL) {
        atual = atual->direita; // Vai para o nó mais à direita
    }

    return atual; // Retorna o nó máximo
}

// Função para concluir uma tarefa
void concluirTarefa(Arvore *arvore) {
    int id;
    printf("Digite o ID da tarefa que deseja concluir: ");
    scanf("%d", &id); // Lê o ID da tarefa a ser concluída
    No *tarefa = buscarElemento(arvore->raiz, id); // Busca a tarefa na árvore
    if (tarefa != NULL) {
        if (tarefa->tarefa.situacao == 2) {
            printf("Tarefa ja concluida!\n");
            return; // Se a tarefa já está concluída, sai da função
        }
        tarefa->tarefa.situacao = 2; // Define a tarefa como concluída
    } else {
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

    // Atualiza a raiz da árvore se necessário
    if (arvore->raiz == NULL) {
        arvore->raiz = novo; // Se a árvore está vazia, o novo nó se torna a raiz
    } else {
        arvore->raiz = inserirElemento(arvore->raiz, novo, NULL); // Insere o novo nó na árvore existente
    }
}

void visualizarTarefas(Arvore *arvore) {
    int opcao;
    printf("1. Todas as tarefas\n");
    printf("2. Somente tarefas ativas\n");
    printf("3. Somente tarefas concluidas\n");
    printf("Digite a opcao de visualizacao desejada: ");
    scanf("%d", &opcao);

    int count = 0;
    coletarTarefas(arvore->raiz, NULL, &count); // Conta o número de tarefas na árvore

    Tarefa *tarefas = malloc(count * sizeof(Tarefa)); // Aloca memória para armazenar as tarefas
    int idx = 0;
    coletarTarefas(arvore->raiz, &tarefas, &idx); // Coleta as tarefas da árvore

    // Ordena as tarefas se necessário
    if (opcao == 1 || opcao == 2 || opcao == 3) {
        qsort(tarefas, count, sizeof(Tarefa), compararTarefas); // Ordena as tarefas
    }

    imprimirTarefas(tarefas, count, opcao == 1 ? 0 : (opcao == 2 ? 1 : 2)); // Imprime as tarefas de acordo com a opção escolhida

    free(tarefas);
}


void coletarTarefas(No *no, Tarefa **tarefas, int *count) {
    if (no != NULL) {
        coletarTarefas(no->esquerda, tarefas, count); // Coleta tarefas da subárvore esquerda
        if (tarefas != NULL) {
            (*tarefas)[*count] = no->tarefa; // Adiciona a tarefa atual ao array de tarefas
        }
        (*count)++; // Incrementa o contador de tarefas
        coletarTarefas(no->direita, tarefas, count); // Coleta tarefas da subárvore direita
    }
}

int compararTarefas(const void *a, const void *b) {
    Tarefa *tarefaA = (Tarefa *)a;
    Tarefa *tarefaB = (Tarefa *)b;

    // Se as situações são diferentes, coloca as ativas primeiro
    if (tarefaA->situacao != tarefaB->situacao) {
        return tarefaA->situacao - tarefaB->situacao;
    }
    // Se as situações são iguais, ordena por tempo limite
    return tarefaA->tempoLimite - tarefaB->tempoLimite;
}

void imprimirTarefas(Tarefa *tarefas, int count, int situacaoFiltro) {
    for (int i = 0; i < count; i++) {
        if (situacaoFiltro == 0 || tarefas[i].situacao == situacaoFiltro) {
            printf("Tarefa ID-%d\n", tarefas[i].id);
            printf("Descricao: %s", tarefas[i].descricao);
            printf("Tempo limite (em horas): %d\n", tarefas[i].tempoLimite);
            printf("Situcao: %s\n", tarefas[i].situacao == 1 ? "Ativa" : "Concluida");
            printf("--------------------\n");
        }
    }
}