#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

void adicionarNodo(struct nodo **raiz, char *entrada)
{
    int chave;
    sscanf(entrada + 1, "%d", &chave);
    struct nodo *sts = inserir(raiz, chave);
    if (sts == NULL)
        printf ("Falha ao inserir.\n");
}

void buscarNodo(struct nodo *raiz, char *entrada)
{
    int chave;
    struct nodo *no;
    sscanf(entrada + 1, "%d", &chave);
    no = buscar(raiz, chave);
    if (no != NULL)
        printf("Encontrado %d\n", chave);
    else
        printf("Nao encontrado %d.\n", chave);
}

void excluirNodo(struct nodo **raiz, char *entrada)
{
    int chave;
    sscanf(entrada + 1, "%d", &chave);
    int sts = excluir(raiz, chave);
    if (sts == 0)
        printf ("Falha ao remover %d.\n", chave);
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
        case 'r':
            excluirNodo(&raiz, entrada);
            break;
        case 'l':
            imprimirEmLargura(raiz);
            break;
        case 'f':
            sts = 0;
            break;
        case 'e':
            imprimirEmOrdem(raiz);
            break;
        case 'b':
            buscarNodo(raiz, entrada);
            break;
        default:
            break;
        }
    }

    return 0;
}
