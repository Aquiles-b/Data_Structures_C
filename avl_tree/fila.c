#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

struct filaNo {
    struct nodo *item;
    struct filaNo *prox;
};

// Cria um no da fila e o retorna. Em caso de erro devolve NULL.
struct filaNo *criaNoFila(struct nodo *nodo)
{
    struct filaNo *fn = malloc(sizeof(struct filaNo));
    if (fn == NULL)
        return NULL;
    fn->item = nodo;
    fn->prox = NULL;

    return fn;
}

// Monta a interface da fila. Retorna NULL em caso de erro.
struct fila *iniciaFila()
{
    struct fila *f = malloc(sizeof(struct fila));
    if (f == NULL)
        return NULL;
    f->head = NULL;
    f->tail = NULL;
    f->tam = 0;

    return f;
}

// Adiciona um item no fim da fila.
// Retorna 0 se der certo e 1 caso contrario.
int addItemFila(struct fila *f, struct nodo *no)
{
    struct filaNo *fn = criaNoFila(no);
    if (fn == NULL || f == NULL || no == NULL)
        return 1;

    if (f->tam != 0) {
        f->tail->prox = fn;
        f->tail = fn;
    } else {
        f->head = fn;
        f->tail = fn;
    }
    f->tam++;

    return 0;
}

// Retorna o primeiro elemento da fila. Em caso de erro retorna NULL.
struct nodo *retiraItemFila(struct fila *f)
{
    struct nodo *nodo;
    struct filaNo *newHead;
    if (f == NULL || f->tam == 0)
        return NULL;

    nodo = f->head->item;
    newHead = f->head->prox;
    free(f->head);
    f->head = newHead;
    f->tam--;

    return nodo;
}

// Retorna 1 se a fila esta vazia, 0 caso nao esteja e -1 caso o ponteiro
// passado seja invalido.
int filaVazia(struct fila *f)
{
    if (f == NULL)
        return -1;

    return f->tam == 0;
}

// Desaloca os nos de uma fila.
void destroiNoFila(struct filaNo *no)
{
    if (no == NULL)
        return;

    destroiNoFila(no->prox);
    free(no);
}

// Desaloca toda memoria da fila passada. Retorna NULL.
struct fila *destroiFila(struct fila *f)
{
    if (f != NULL) {
        destroiNoFila(f->head);
        free(f);
    }

    return NULL;
}
