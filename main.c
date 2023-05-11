#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

void adicionarNodo(struct nodo **raiz, char *entrada)
{
    int chave = 0;
    sscanf(entrada + 1, "%d", &chave);
    inserir(raiz, chave);
}

int main(){
    imprimirDadosAlunos();

    struct nodo *raiz = NULL;
    char entrada[10];
    int sts = 1;
    while(sts) {
        fgets(entrada, 10, stdin);
        switch (entrada[0]) {
        case 'i':
            adicionarNodo(&raiz, entrada);
            break;
        case 'l':
            imprimirEmLargura(raiz);
            break;
        case 'f':
            sts = 0;
            break;
        default:
            break;
        }
    }

    return 0;
}
