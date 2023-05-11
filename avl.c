#include "avl.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct filaNo {
    struct nodo *item;
    struct filaNo *prox;
};

struct fila {
    struct filaNo *head;
    struct filaNo *tail;
    int tam;
};

//substitua por seus dados
struct aluno* getAluno1(){
    struct aluno* retorno = malloc(sizeof(struct aluno));
    if(!retorno)
        exit(1);
    retorno->nome = malloc(sizeof("Bruno Aquiles de Lima"));//sizeof conta o \0
    if(!retorno->nome)
        exit(1);
    retorno->nomeDinf = malloc(sizeof("bal22"));
    if(!retorno->nomeDinf)
        exit(1);

    strcpy(retorno->nome, "Bruno Aquiles de Lima");
    strcpy(retorno->nomeDinf, "bal22");
    retorno->grr = 20221230;

    return retorno;
}

struct aluno* getAluno2(){
    return NULL;
}

void imprimirDadosAlunos(){
    struct aluno* aluno = getAluno1();

    printf("Trabalho de %s\n", aluno->nome);
    printf("Login Dinf %s\n", aluno->nomeDinf);
    printf("GRR %u\n\n", aluno->grr);

    free(aluno->nome);
    free(aluno->nomeDinf);
    free(aluno);

    aluno = getAluno2();
    if(!aluno)
        return;

    printf("...E... \n\n");
    printf("Trabalho de %s\n", aluno->nome);
    printf("Login Dinf %s\n", aluno->nomeDinf);
    printf("GRR %u\n\n", aluno->grr);

    free(aluno->nome);
    free(aluno->nomeDinf);
    free(aluno);
}

struct nodo *criaNodo(int chave)
{
    struct nodo *n = malloc(sizeof(struct nodo));
    if (n == NULL)
        return NULL;

    n->chave = chave;
    n->fe = NULL;
    n->fd = NULL;
    n->pai = NULL;
    n->balanco = 0;

    return n;
}

struct nodo *insereNodo(struct nodo *n, int chave)
{
    if (n->chave == chave)
        return NULL;

    if (n->chave > chave) {
        if (n->fe != NULL)
            return insereNodo(n->fe, chave);

        n->fe = criaNodo(chave);
        n->fe->pai = n;
        return n->fe;
    }
    if (n->fd != NULL)
        return insereNodo(n->fd, chave);

    n->fd = criaNodo(chave);
    n->fd->pai = n;
    return n->fd;
}

struct nodo *rotacionaEsq(struct nodo *p)
{
    struct nodo *q = p->fd;
    q->pai = p->pai;
    p->pai = q;
    p->fd = q->fe;
    if (q->fe != NULL)
        q->fe->pai = p;
    if (q->pai != NULL) {
        if (q->pai->fe == p)
            q->pai->fe = q;
        else
            q->pai->fd = q;
    }
    q->fe = p;

    return q;
}

struct nodo *rotacionaDir(struct nodo *p)
{
    struct nodo *r = p->fe;
    r->pai = p->pai;
    p->pai = r;
    p->fe = r->fd;
    if (r->fd != NULL)
        r->fd->pai = p;
    if (r->pai != NULL) {
        if (r->pai->fe == p)
            r->pai->fe = r;
        else
            r->pai->fd = r;
    }
    r->fd = p;

    return r;
}

int alturaNodo(struct nodo *p)
{
    int altEsq, altDir;
    if (p == NULL)
        return -1;
    altEsq = alturaNodo (p->fe);
    altDir = alturaNodo (p->fd);
    if (altEsq > altDir)
        return altEsq + 1;

    return altDir + 1;    
}

void corrigeBalanco(struct nodo *p)
{
    p->balanco = 0;
    p->fe->balanco = (alturaNodo(p->fe->fd) - alturaNodo(p->fe->fe));
    p->fd->balanco = (alturaNodo(p->fd->fd) - alturaNodo(p->fd->fe));
}

struct nodo *rebalancear(struct nodo *n)
{
    struct nodo *noPai;

    if (n->balanco == 2) {
        if (n->fd->balanco == 1) {
            noPai = rotacionaEsq(n);
        }
        else {
            rotacionaDir(n->fd);
            noPai = rotacionaEsq(n);
        }
    } else {
        if (n->fe->balanco == -1) {
            noPai = rotacionaDir(n);
        } else {
            rotacionaEsq(n->fe);
            noPai = rotacionaDir(n);
        }
    }
    corrigeBalanco(noPai);

    return noPai;
}

void atualizaBalanco(struct nodo *nodo, struct nodo **raiz)
{
    struct nodo *pai = nodo->pai;
    if (pai == NULL)
        return;
    if (nodo == pai->fe)
        pai->balanco--;
    else
        pai->balanco++;

    while (pai->pai != NULL && pai->balanco != 2 && pai->balanco != -2) {
        nodo = pai;
        pai = pai->pai;
        if (nodo->balanco == 0)
            return;
        if (nodo == pai->fe)
            pai->balanco--;
        else
            pai->balanco++;
    }
    if (pai->balanco == 2 || pai->balanco == -2) {
        if (pai->pai == NULL)
            *raiz = rebalancear(pai);
        else
            rebalancear(pai);
    }
}

struct nodo *inserir(struct nodo **raiz, int chave)
{
    if (*raiz == NULL) {
        *raiz = criaNodo(chave);
        return *raiz;
    }
    struct nodo *n = insereNodo(*raiz, chave);
    if (n == NULL)
        return NULL;

    atualizaBalanco(n, raiz);

    return n;
}

int excluir(struct nodo **raiz, int chave)
{
    return -99;
}

struct nodo *buscar(struct nodo *nodo, int chave)
{
    if (nodo == NULL)
        return NULL;
    if (nodo->chave == chave)
        return nodo;
    if (nodo->chave < chave)
        return buscar(nodo->fd, chave);

    return buscar(nodo->fe, chave);
}

void imprimirEmOrdem(struct nodo *raiz)
{
    printf("Imprimindo em ordem\n");
}

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

void imprimirEmLargura(struct nodo *raiz)
{
    if (raiz == NULL)
        return;
    struct nodo *aux;
    struct fila *fNivel = iniciaFila();
    struct fila *fProxNivel = iniciaFila();
    int nivel = 0;

    addItemFila(fProxNivel, raiz);

    while (!filaVazia(fProxNivel)) {
        fNivel = fProxNivel;
        fProxNivel = iniciaFila();
        printf ("[%d] ", nivel);
        while (!filaVazia(fNivel)) {
            aux = retiraItemFila(fNivel);
            printf ("%d(%d) ", aux->chave, aux->balanco);
            addItemFila(fProxNivel, aux->fe);
            addItemFila(fProxNivel, aux->fd);
        }
        printf ("\n");
        nivel++;
    }
}
