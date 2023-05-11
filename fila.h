#ifndef AVL_H_
struct nodo {
    int chave;
    int balanco;
    struct nodo *pai;
    struct nodo *fe;
    struct nodo *fd;
};
#endif

struct filaNo {
    struct nodo *item;
    struct filaNo *prox;
};

struct fila {
    struct filaNo *head;
    struct filaNo *tail;
    int tam;
};

struct filaNo *criaNoFila(struct nodo *nodo);

struct fila *iniciaFila();

int addItemFila(struct fila *f, struct nodo *no);

struct nodo *retiraItemFila(struct fila *f);

/* Retorna 1 se a fila esta vazia, 0 caso nao esteja e -1 caso o ponteiro
 * passado seja invalido.*/
int filaVazia(struct fila *f);

