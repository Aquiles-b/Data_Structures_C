#include "tabelaHash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void matarProgramaFaltaMemoria()
{
    fputs("Falha ao alocar memoria.\n", stderr);
    exit(1);
}

struct aluno *getAluno1()
{
    struct aluno *retorno = malloc(sizeof(struct aluno));
    if (!retorno) matarProgramaFaltaMemoria();
    retorno->nome = malloc(sizeof("Bruno Aquiles de Lima"));  // sizeof conta o \0
    if (!retorno->nome)
        matarProgramaFaltaMemoria();
    retorno->nomeDinf = malloc(sizeof("bal22"));
    if (!(retorno->nomeDinf))
        matarProgramaFaltaMemoria();

    strcpy(retorno->nome, "Bruno Aquiles de Lima");
    strcpy(retorno->nomeDinf, "bal22");
    retorno->grr = 20221230;

    return retorno;
}

struct aluno *getAluno2()
{
    return NULL;
}

void imprimirDadosAlunos()
{
    struct aluno *aluno = getAluno1();

    printf("Trabalho de %s\n", aluno->nome);
    printf("Login Dinf %s\n", aluno->nomeDinf);
    printf("GRR %u\n\n", aluno->grr);

    free(aluno->nome);
    free(aluno->nomeDinf);
    free(aluno);

    aluno = getAluno2();
    if (!aluno) return;

    printf("...E... \n\n");
    printf("Trabalho de %s\n", aluno->nome);
    printf("Login Dinf %s\n", aluno->nomeDinf);
    printf("GRR %u\n\n", aluno->grr);

    free(aluno->nome);
    free(aluno->nomeDinf);
    free(aluno);
}

// Gera a tabela hash com o tamanho @tamTabela.
// Retorna um ponteiro para a tabela criada.
struct hashTable *gerarTabelaHash(size_t tamTabela)
{
    struct hashTable *table = malloc(sizeof(*table));
    if (table == NULL)
        matarProgramaFaltaMemoria();

    table->nodos = malloc(sizeof(struct nodoHash*) * tamTabela);
    if (table->nodos == NULL) {
        free(table);
        matarProgramaFaltaMemoria();
    }
    for (size_t i = 0; i < tamTabela; i++)
        table->nodos[i] = NULL;

    return table;
}

// Funcao hash que calcula e retorna o indice de cada chave.
size_t hashFunction(size_t tamTabela, int k)
{
    if (k >= 0)
        return k % tamTabela;

    return k % (long) tamTabela + tamTabela;
}

// Retorna um nodo do tipo struct nodoHash. Devolve NULL em caso de erro.
struct nodoHash *criaNodoHash(int chave)
{
    struct nodoHash *no = malloc(sizeof(struct nodoHash));
    if (no == NULL)
        return NULL;

    no->chave = chave;
    no->anter = NULL;
    no->prox = NULL;

    return no;
}

// Insere um nodo na lista e o retorna.
struct nodoHash *insereLista(struct nodoHash *posi, int chave)
{
    while (posi->chave != chave && posi->prox != NULL)
        posi = posi->prox;

    if (posi->chave == chave)
        return NULL;

    posi->prox = criaNodoHash(chave);
    if (posi->prox == NULL)
        matarProgramaFaltaMemoria();
    posi->prox->anter = posi;

    return posi->prox;
}

// Insere um nodo na tabela e retorna um ponteiro para ele. Devolve NULL
// em caso de erro.
struct nodoHash *inserir(struct hashTable tabelaHash[], size_t tamTabela, int chave)
{
    size_t indice = hashFunction(tamTabela, chave);
    struct nodoHash *posicao, *nodo;
    posicao = tabelaHash->nodos[indice];

    if (posicao == NULL) {
        tabelaHash->nodos[indice] = criaNodoHash(chave);
        nodo = tabelaHash->nodos[indice];
        if (nodo == NULL)
            matarProgramaFaltaMemoria();
    }
    else if (posicao->chave == chave)
        nodo = NULL;
    else 
        nodo = insereLista(posicao, chave);

    return nodo;
}

// Desaloca toda memoria da lista.
void destroiLista(struct nodoHash *no)
{
    if (no == NULL)
        return;
    destroiLista(no->prox);
    free(no);
}

// Desaloca toda memoria da tabelaHash
void liberarTabelaHash(struct hashTable tabelaHash[], size_t tamTabela)
{
    for (size_t i = 0; i < tamTabela; i++)
        destroiLista(tabelaHash->nodos[i]);

    free(tabelaHash->nodos);
    free(tabelaHash);
}

// Imprime lista
void imprimeLista(struct nodoHash *no, size_t ind)
{
    printf("%li ", ind);

    if (no == NULL) {
        printf("NULL\n");
        return;
    }
    while (no != NULL) {
        printf("[%d] -> ", no->chave);
        no = no->prox;
    }
    printf("NULL\n");
}

// Imprime a tabelaHash passada
void imprimirTabelaHash(struct hashTable tabelaHash[], size_t tamTabela)
{
    for (size_t i = 0; i < tamTabela; i++)
        imprimeLista(tabelaHash->nodos[i], i);
}

// Busca um nodo pela chave na lista e o retorna. Devolve NULL em caso de erro.
struct nodoHash *buscaLista(struct nodoHash *posi, int chave)
{
    while (posi->chave != chave && posi->prox != NULL)
        posi = posi->prox;
    if (posi->chave == chave)
        return posi;
    
    return NULL;
}

// Busca um nodo pela chave na tabela e o retorna. Devolve NULL em caso de erro.
struct nodoHash *buscar(struct hashTable tabelaHash[], size_t tamTabela, int chave)
{
    size_t indice = hashFunction(tamTabela, chave);
    struct nodoHash *posicao;
    posicao = tabelaHash->nodos[indice];
    if (posicao != NULL) {
        if (posicao->chave != chave)
            posicao = buscaLista(posicao, chave);
    }

    return posicao;
}

// Exclui um nodo pela chave
int excluirPelaChave(struct hashTable tabelaHash[], size_t tamTabela, int chave)
{
    struct nodoHash *no = buscar(tabelaHash, tamTabela, chave);
    if (no == NULL)
        return 0;
    excluir(tabelaHash, tamTabela, no);

    return 1;
}

// Exclui da tabela hash o nodo passado no parametro 
void excluir(struct hashTable tabelaHash[], size_t tamTabela, struct nodoHash *nodo)
{
    size_t ind = hashFunction(tamTabela, nodo->chave);
    if (nodo->anter == NULL) {
        if (nodo->prox == NULL) {
            tabelaHash->nodos[ind] = NULL;
        }
        else {
            tabelaHash->nodos[ind] = nodo->prox;
            nodo->prox->anter = NULL;
        }
    }
    else {
        nodo->anter->prox = nodo->prox;
        if (nodo->prox != NULL)
            nodo->prox->anter = nodo->anter;
    }
    free(nodo);
}
