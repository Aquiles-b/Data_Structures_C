#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main(){
	imprimirDadosAlunos();

    struct nodo *raiz = criaNodo(5);
    inserir(&raiz, 8);
    imprimirEmLargura(raiz);
    printf ("\n");
    inserir(&raiz, 6);
    imprimirEmLargura(raiz);
    printf ("\n");
    /* inserir(&raiz, 1); */
    /* imprimirEmLargura(raiz); */
    /* printf ("\n"); */
    /* imprimirEmLargura(raiz); */
    /* printf ("\n"); */

    /* imprimirEmLargura(raiz); */

	return 0;
}
