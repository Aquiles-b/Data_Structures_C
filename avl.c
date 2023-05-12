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

// Cria um nodo e devolve um ponteiro para ele. Em caso de erro retorna NULL.
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

// Desaloca toda a memoria da arvore. Retorna NULL.
struct nodo *destroiArvore(struct nodo *raiz)
{
    if (raiz == NULL)
        return NULL;
    destroiArvore(raiz->fe);
    destroiArvore(raiz->fd);
    free(raiz);

    return NULL;
}

// Retorna 1 se o nodo passado e raiz e 0 caso contrario.
int ehRaiz(struct nodo *no)
{
    if (no == NULL)
        return 0;

    return no->pai == NULL;
}

// Insere um nodo na arvore com a chave passada e retorna um ponteiro para ele.
// Em caso de erro, retorna NULL.
struct nodo *insereNodo(struct nodo *n, int chave)
{
    if (n->chave == chave)
        return NULL;

    if (n->chave > chave) {
        if (n->fe != NULL)
            return insereNodo(n->fe, chave);

        n->fe = criaNodo(chave);
        if (n->fe == NULL)
            return NULL;
        n->fe->pai = n;
        return n->fe;
    }
    if (n->fd != NULL)
        return insereNodo(n->fd, chave);

    n->fd = criaNodo(chave);
    if (n->fd == NULL)
        return NULL;
    n->fd->pai = n;
    return n->fd;
}

// Faz a rotacao para esquerda no nodo passado. Retorna um ponteiro para o pai
// da arvore apos a rotacao.
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

// Faz a rotacao para direita no nodo passado. Retorna um ponteiro para o pai
// da arvore apos a rotacao.
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

// Devolve a altura do nodo passado. Em caso de erro retorna -1.
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

// Calcula o balanco do nodo passado.
void corrigeBalanco(struct nodo *p)
{
    p->balanco = 0;
    p->fe->balanco = (alturaNodo(p->fe->fd) - alturaNodo(p->fe->fe));
    p->fd->balanco = (alturaNodo(p->fd->fd) - alturaNodo(p->fd->fe));
}

// Escolhe o tipo de rotacao para balancear a arvore passada. Retorna um ponteiro
// para a raiz da arvore apos o balanceamento.
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

// Retorna 1 se o nodo esta balanceado e 0 caso contrario.
int balanceado(struct nodo *no)
{
    if (no == NULL)
        return 0;

    return no->balanco != 2 && no->balanco != -2;
}

// Itera subindo a arvore atualizando o balanco apos uma nova insercao.
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

// Insere um novo nodo na arvore com a chave passada e retorna um ponteiro 
// para ele. Em caso de erro retorna NULL.
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

// Retorna 1 se for folha, 0 se não for e -1 em caso de erro.
int ehFolha(struct nodo *no)
{
    if (no == NULL)
        return -1;

    return no->fe == NULL && no->fd == NULL;
}

// Itera subindo a arvore atualizando o balanco apos uma exclusao.
void atualizaBalancoExcluir(struct nodo *nodo, struct nodo **raiz)
{
    struct nodo *pai = nodo->pai;
    
    if (pai->fe != NULL && nodo == pai->fe)
        pai->balanco++;
    else
        pai->balanco--;

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

// Devolve o antecessor do nodo passado.
struct nodo *antecessorNodoAux(struct nodo *no)
{
    if (no->fd == NULL)
        return no;

    return antecessorNodoAux(no->fd);
}

// Devolve o antecessor do nodo passado. Em caso de erro ou o antecessor 
// nao exista retorna NULL.
struct nodo *antecessorNodo(struct nodo *no)
{
    if (no == NULL || no->fe == NULL)
        return NULL;

    return antecessorNodoAux(no->fe);
}

// Substitui o nodo passado pelo seu antecessor.
void transplante(struct nodo **no)
{
    struct nodo *ant;
    ant = antecessorNodo(*no);
    if (ant == NULL) {
        ant = (*no)->fd;
    }
    else if (ant->fe != NULL) {
        ant->pai->fd = ant->fe;
        ant->fe->pai = ant->pai;
    }
    (*no)->chave = ant->chave;
    (*no) = ant;
}

// Remove o nodo da arvore que contem a chave passada.
// Retorna 1 se der certo e 0 caso contrario.
int excluir(struct nodo **raiz, int chave)
{
    struct nodo *no;
    no = buscar(*raiz, chave);
    if (no == NULL)
        return 0;
    if (!ehFolha(no)) {
        transplante(&no);
        atualizaBalancoExcluir(no, raiz);
    } else {
        atualizaBalancoExcluir(no, raiz);
        no->pai->fe = NULL;
        no->pai->fd = NULL;
    }
    free(no);

    return 1;
}

// Devolve o nodo que contem a chave passada. Caso ele nao exista retorna NULL.
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

// Devolve o nodo com a maior chave da arvore.
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
    if (no->chave != maior)
        printf ("%d ", no->chave);
    else
        printf ("%d\n", no->chave);
    imprimirEmOrdemAux(no->fd, maior);
}

// Imprime a arvore em ordem crescente.
void imprimirEmOrdem(struct nodo *no)
{
    if (no == NULL)
        return;

    struct nodo *maior = maiorNodo(no);
    imprimirEmOrdemAux(no, maior->chave);
}

// Adiciona no final da fila os nodos filhos (caso existam) do nodo passado.
// Aumenta o qntProxNodos para indicar quantos nodos estaram no proximo nivel.
void addProxNodosFila(struct fila *f, struct nodo *no, int *qntProxNodos)
{
    if (no->fe != NULL) {
        addItemFila(f, no->fe);
        (*qntProxNodos)++;
    }
    if (no->fd != NULL) {
        addItemFila(f, no->fd);
        (*qntProxNodos)++;
    }
}

// Imprime a arvore em largura.
void imprimirEmLargura(struct nodo *raiz)
{
    if (raiz == NULL)
        return;
    struct nodo *no;
    int qntNodos = 1, qntProxNodos = 0, nivelAtual = 0;
    struct fila *f = iniciaFila();
    addItemFila(f, raiz);

    printf ("[%d] ", nivelAtual);
    while (!filaVazia(f)) {
        no = retiraItemFila(f);
        addProxNodosFila(f, no, &qntProxNodos);
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
    destroiFila(f);
}
