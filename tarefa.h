typedef struct {
    int id;             // Identificador único
    char descricao[256];// Descrição da tarefa
    int tempoLimite;    // Tempo limite em horas
    int situacao;       // 0 para ativa, 1 para concluída
} Tarefa;


typedef struct Node {
    Tarefa tarefa;
    struct Node* esquerda;
    struct Node* direita;
} Node;

// Funções de manipulação de árvore
Node* adicionarTarefa(Node* raiz, Tarefa tarefa);
void visualizarTarefas(Node* raiz);

// Funções de manipulação de tarefas
Tarefa criarTarefa(int id, char descricao[], int tempoLimite, int situacao);
void concluirTarefa(Node* raiz, int id);
void excluirTarefa(Node* raiz, int id);






