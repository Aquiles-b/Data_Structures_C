#include <stdio.h>
#include <stdlib.h>
#include "trataEntrada.h"
#include "tabelaHash.h"
#define TRUE 1
#define FALSE 0

int main()
{
    size_t tamTabela = 0;
    scanf("%ld", &tamTabela);
    if (tamTabela == 0) {
        fprintf(stderr, "O tamanho da tabela nao pode ser 0.\n");
        return 1;
    }
    struct hashTable *table = gerarTabelaHash(tamTabela);
    char *entrada = malloc(sizeof(char) * TAM_STR);
    short sts = TRUE;
    while(sts) {
        pegaEntrada(entrada);
        switch (entrada[0]) {
        case 'i':
            adicionaNodo(table, entrada, tamTabela);
            break;
        case 'r':
            excluirNodo(table, entrada, tamTabela);
            break;
        case 'l':
            imprimirTabelaHash(table, tamTabela);
            break;
        case 'f':
            sts = FALSE;
            break;
        case 'b':
            buscaNodo(table, entrada, tamTabela);
            break;
        default:
            break;
        }
    }
    liberarTabelaHash(table, tamTabela);
    free(entrada);

    return 0;
}
