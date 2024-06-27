typedef struct {
    int id;             // Identificador único
    char descricao[256];// Descrição da tarefa
    int tempoLimite;    // Tempo limite em horas
    int situacao;       // 1 para ativa, 2 para concluída
} Tarefa;


typedef struct No {
    struct No* pai;
    Tarefa tarefa;
    struct No* esquerda;
    struct No* direita;
    int altura;
} No;

typedef struct arvore {
    No *raiz;
} Arvore;

// Funcoes de manipulacao de arvore
void iniciarArvore(Arvore *a);
No* inserirElemento(No *no, No *novo, No *pai);
void imprimirArvore(No *no);
No* buscarElemento(No *no, int id);
int altura(No *no);
int max(int a, int b);
No* rotacaoDireita(No *y);
No* rotacaoEsquerda(No *x);
int verificaBalanceamento(No *no);
No* balancearArvore(No* no);

// Funcoes de manipulacao de tarefas
void criarTarefa(Arvore *arvore, int id);
void concluirTarefa(Arvore *arvore);
void excluirTarefa(Arvore *arvore);
No* excluirElemento(No* no, int id);
No* encontrarMinimo(No* no);
No* encontrarMaximo(No* no);






