#include "avl.h"
#include "fila.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

struct nodo *destroiArvore(struct nodo *raiz)
{
    if (raiz == NULL)
        return NULL;
    destroiArvore(raiz->fe);
    destroiArvore(raiz->fd);
    free(raiz);

    return NULL;
}

int ehRaiz(struct nodo *no)
{
    if (no == NULL)
        return 0;

    return no->pai == NULL;
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
    if (!ehRaiz(q)) {
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
    if (!ehRaiz(r)) {
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

int balanceado(struct nodo *no)
{
    if (no == NULL)
        return 0;

    return no->balanco != 2 && no->balanco != -2;
}

void atualizaBalancoInserir(struct nodo *nodo, struct nodo **raiz)
{
    struct nodo *pai = nodo->pai;
    if (ehRaiz(nodo))
        return;
    if (nodo == pai->fe)
        pai->balanco--;
    else
        pai->balanco++;

    while (!ehRaiz(pai) && balanceado(pai)) {
        nodo = pai;
        pai = pai->pai;
        if (nodo->balanco == 0)
            return;
        if (nodo == pai->fe)
            pai->balanco--;
        else
            pai->balanco++;
    }
    if (!balanceado(pai)) {
        if (ehRaiz(pai))
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

    atualizaBalancoInserir(n, raiz);

    return n;
}

int ehFolha(struct nodo *no)
{
    if (no == NULL)
        return -1;

    return no->fe == NULL && no->fd == NULL;
}

void atualizaBalancoExcluir(struct nodo *nodo, struct nodo **raiz)
{
    struct nodo *pai = nodo->pai;
    if (nodo == pai->fe) {
        pai->balanco++;
        pai->fe = NULL;
    }
    else {
        pai->balanco--;
        pai->fd = NULL;
    }

    while (!ehRaiz(pai) && pai->balanco == 0) {
        nodo = pai;
        pai = pai->pai;
        if (nodo == pai->fe)
            pai->balanco++;
        else
            pai->balanco--;
    }
    if (!balanceado(pai)) {
        if (ehRaiz(pai))
            *raiz = rebalancear(pai);
        else
            rebalancear(pai);
    }
}

struct nodo *antecessorNodoAux(struct nodo *no)
{
    if (no->fd == NULL)
        return no;

    return antecessorNodoAux(no->fd);
}

struct nodo *antecessorNodo(struct nodo *no)
{
    if (no == NULL)
        return NULL;

    return antecessorNodoAux(no->fe);
}

int excluir(struct nodo **raiz, int chave)
{
    struct nodo *no, *ant;
    no = buscar(*raiz, chave);
    if (no == NULL)
        return 0;
    if (!ehFolha(no)) {
        ant = antecessorNodo(no);
        no->chave = ant->chave;
        no = ant;
    }
    atualizaBalancoExcluir(no, raiz);
    free(no);

    return 1;
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

struct nodo *maiorNodo(struct nodo *raiz)
{
    if (raiz->fd == NULL)
        return raiz;

    return maiorNodo(raiz->fd);
}

void imprimirEmOrdemAux(struct nodo *no, int maior)
{
    if (no == NULL)
        return;

    imprimirEmOrdemAux(no->fe, maior);
    if (no->chave == maior)
        printf ("%d\n", no->chave);
    else
        printf ("%d ", no->chave);
    imprimirEmOrdemAux(no->fd, maior);
}

void imprimirEmOrdem(struct nodo *no)
{
    if (no == NULL)
        return;

    struct nodo *maior = maiorNodo(no);
    imprimirEmOrdemAux(no, maior->chave);
}

void addProxNodosFila(struct fila *fNivel, struct nodo *no, int *qntProxNodos)
{
    if (no->fe != NULL) {
        addItemFila(fNivel, no->fe);
        (*qntProxNodos)++;
    }
    if (no->fd != NULL) {
        addItemFila(fNivel, no->fd);
        (*qntProxNodos)++;
    }
}

void imprimirEmLargura(struct nodo *raiz)
{
    if (raiz == NULL)
        return;
    struct nodo *no;
    int qntNodos = 1, qntProxNodos = 0, nivelAtual = 0;
    struct fila *fNivel = iniciaFila();
    addItemFila(fNivel, raiz);

    printf ("[%d] ", nivelAtual);
    while (!filaVazia(fNivel)) {
        no = retiraItemFila(fNivel);
        addProxNodosFila(fNivel, no, &qntProxNodos);
        qntNodos--;
        if (qntNodos == 0) {
            printf ("%d(%d)\n", no->chave, no->balanco);
            if (qntProxNodos != 0) {
                nivelAtual++;
                printf ("[%d] ", nivelAtual);
                qntNodos = qntProxNodos;
                qntProxNodos = 0;
            }
        } else {
            printf ("%d(%d) ", no->chave, no->balanco);
        }
    }
}
