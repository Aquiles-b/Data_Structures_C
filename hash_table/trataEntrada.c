#include "trataEntrada.h"
#include "tabelaHash.h"

// Pega entrada do stdin e passa para @entrada.
void pegaEntrada(char *entrada)
{
    char in[TAM_STR];
    fgets(in, TAM_STR, stdin);
    in[strcspn(in, "\n")] = '\0';
    int i = 0, j = 0;
    while (in[i] != '\0') {
        if (in[i] != ' ') {
            entrada[j] = in[i];
            j++;
        }
        i++;
    }
    entrada[j] = '\0';
}

// Busca um nodo na tabela como base na entrada
void buscaNodo(struct hashTable *table, char *entrada, size_t tamTabela)
{
    int chave;
    struct nodoHash *status;
    sscanf(entrada + 1, "%d", &chave);
    status = buscar(table, tamTabela, chave);
    if (status == NULL)
        printf("Nao encontrado %d.\n", chave);
    else
        printf("Encontrado %d.\n", chave);
}

// Adiciona um nodo na tabela como base na entrada
void adicionaNodo(struct hashTable *table, char *entrada, size_t tamTabela)
{
    int chave;
    struct nodoHash *status;
    sscanf(entrada + 1, "%d", &chave);
    status = inserir(table, tamTabela, chave);
    if (status == NULL)
        printf("Falha ao inserir %d.\n", chave);
}

// Apaga um nodo da tabela com base na entrada
void excluirNodo(struct hashTable *table, char *entrada, size_t tamTabela)
{
    int chave, ok;
    sscanf(entrada + 1, "%d", &chave);
    ok = excluirPelaChave(table, tamTabela, chave);
    if (!ok)
        printf("Falha ao remover %d.\n", chave);
}
