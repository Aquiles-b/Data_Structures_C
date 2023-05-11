#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main(){
	imprimirDadosAlunos();

    struct nodo *raiz = NULL;
    inserir(&raiz, 5);
    inserir(&raiz, 6);
    inserir(&raiz, 1);
    imprimirEmLargura(raiz);

	return 0;
}
