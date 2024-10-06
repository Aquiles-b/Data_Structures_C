#ifndef TABELA_HASH_H
#define TABELA_HASH_H

#include <stddef.h>

struct nodoHash {
    int chave;
    struct nodoHash *prox;
    struct nodoHash *anter;
};

struct hashTable {
    struct nodoHash **nodos;
};

//aloca a tabela hash na memória
struct hashTable *gerarTabelaHash(size_t tamTabela);

//insere a chave na tabela hash. Duplicatas não são permitidas.
//Retorna o nodo inserido, ou NULL em caso de problemas (ex.: caso a chave seja uma duplicata)
struct nodoHash *inserir(struct hashTable tabelaHash[], size_t tamTabela, int chave);

//deleta a tabela hash
void liberarTabelaHash(struct hashTable tabelaHash[], size_t tamTabela);

//imprime na tela a tabela completa
void imprimirTabelaHash(struct hashTable tabelaHash[], size_t tamTabela);

//busca o nodo com o chave, ou retorna NULL caso tal nodo não exista
struct nodoHash *buscar(struct hashTable tabelaHash[], size_t tamTabela, int chave);

//exclui o nodo pela chave passada
int excluirPelaChave(struct hashTable tabelaHash[], size_t tamTabela, int chave);

//exclui o nodo apontado
void excluir(struct hashTable tabelaHash[], size_t tamTabela, struct nodoHash *nodo);

#endif // TABELA_HASH_H
