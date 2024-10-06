#ifndef STRUCT_AVL
#define STRUCT_AVL
struct nodo {
    int chave;
    int balanco;
    struct nodo *pai;
    struct nodo *fe;
    struct nodo *fd;
};
#endif

struct fila {
    struct filaNo *head;
    struct filaNo *tail;
    int tam;
};

// Monta a interface da fila. Retorna NULL em caso de erro.
struct fila *iniciaFila();

// Adiciona um item no fim da fila.
// Retorna 0 se der certo e 1 caso contrario.
int addItemFila(struct fila *f, struct nodo *no);

// Retorna o primeiro elemento da fila. Em caso de erro retorna NULL.
struct nodo *retiraItemFila(struct fila *f);

// Retorna 1 se a fila esta vazia, 0 caso nao esteja e -1 caso o ponteiro
// passado seja invalido.
int filaVazia(struct fila *f);

// Desaloca toda memoria da fila passada. Retorna NULL.
struct fila *destroiFila(struct fila *f);
