#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifndef TABELA_HASH_H
#include "tabelaHash.h"
#endif
#define TAM_STR 14

// Pega entrada do stdin e passa para @entrada.
void pegaEntrada(char *entrada);

// Busca um nodo na tabela como base na entrada
void buscaNodo(struct hashTable *table, char *entrada, size_t tamTabela);

// Adiciona um nodo na tabela como base na entrada
void adicionaNodo(struct hashTable *table, char *entrada, size_t tamTabela);

// Apaga um nodo da tabela com base na entrada
void excluirNodo(struct hashTable *table, char *entrada, size_t tamTabela);
