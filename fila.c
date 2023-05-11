#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

struct filaNo *criaNoFila(struct nodo *nodo)
{
    struct filaNo *fn = malloc(sizeof(struct filaNo));
    if (fn == NULL)
        return NULL;
    fn->item = nodo;
    fn->prox = NULL;

    return fn;
}

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

/* Retorna 1 se a fila esta vazia, 0 caso nao esteja e -1 caso o ponteiro
 * passado seja invalido.*/
int filaVazia(struct fila *f)
{
    if (f == NULL)
        return -1;

    return f->tam == 0;
}

