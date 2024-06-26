typedef struct {
    int id;             // Identificador único
    char descricao[256];// Descrição da tarefa
    int tempoLimite;    // Tempo limite em horas
    int situacao;       // 0 para ativa, 1 para concluída
} Tarefa;


typedef struct No {
    Tarefa tarefa;
    struct No* esquerda;
    struct No* direita;
} No;

typedef struct arvore {
    No *raiz;
} Arvore;

// Funções de manipulação de árvore
void iniciarArvore(Arvore *a);
No* inserirElemento(No *no, No *novo);
void imprimirArvore(No *no);

// Funções de manipulação de tarefas
void criarTarefa(Arvore *arvore, int id);
void adicionarTarefa(Arvore *a, Tarefa t);
void visualizarTarefas(Arvore *a);






