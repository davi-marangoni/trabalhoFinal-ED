typedef struct {
    int id;             // Identificador único
    char descricao[256];// Descrição da tarefa
    int tempoLimite;    // Tempo limite em horas
    int situacao;       // 0 para ativa, 1 para concluída
} Tarefa;


typedef struct No {
    struct No* pai;
    Tarefa tarefa;
    struct No* esquerda;
    struct No* direita;
} No;

typedef struct arvore {
    No *raiz;
} Arvore;

// Funções de manipulação de árvore
void iniciarArvore(Arvore *a);
No* inserirElemento(No *no, No *novo, No *pai);
void imprimirArvore(No *no);
No* buscarElemento(No *no, int id);

// Funções de manipulação de tarefas
void criarTarefa(Arvore *arvore, int id);
void concluirTarefa(Arvore *arvore);
void excluirTarefa(Arvore *arvore);






