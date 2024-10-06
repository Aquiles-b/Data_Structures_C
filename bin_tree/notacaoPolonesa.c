#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_ENT 64

struct nodo{
    char *caracter;
    float valor;
    struct nodo *filho_esq;
    struct nodo *filho_dir;
};

/*Le entrada do teclado e retorna um ponteiro.*/
char* lerEntrada()
{
    char* entrada = malloc(sizeof(size_t)*TAM_ENT);
    fgets(entrada, TAM_ENT, stdin);
    entrada[strcspn(entrada, "\n")] = '\0';

    return entrada;
}

struct nodo* criaNodo()
{
    struct nodo* nodo = malloc(sizeof(struct nodo));
    if (!nodo)
        return NULL;

    return nodo;
}

int ehOperacao(char* op)
{
    switch (*op){
        case '*': 
            return 1;
            break;
        case '/':
            return 1;
            break;
        case '-':
            return 1;
            break;
        case '+':
            return 1;
            break;
        default:
            return 0;
            break;
    }
}


void montaSubArvore(struct nodo* nodo)
{
    char *pt;
    pt = strtok(NULL, " ");
    nodo->caracter = pt;
    nodo->valor = ehOperacao(pt);
    if(nodo->valor == 0){
        nodo->valor = strtod(pt, NULL);
        nodo->filho_dir = NULL;
        nodo->filho_esq = NULL;
        return;
    }
    nodo->filho_esq = criaNodo();
    nodo->filho_dir = criaNodo();
    montaSubArvore(nodo->filho_esq);
    montaSubArvore(nodo->filho_dir);
}

struct nodo* montaArvore(char* entrada)
{
    char *pt;
    struct nodo *raiz;
    raiz = criaNodo();

    pt = strtok(entrada, " ");
    raiz->caracter = pt;
    raiz->valor = ehOperacao(pt);
    if(raiz->valor == 0)
        return raiz;

    raiz->filho_esq = criaNodo();
    raiz->filho_dir = criaNodo();

    montaSubArvore(raiz->filho_esq);
    montaSubArvore(raiz->filho_dir);

    return raiz;
}

float resolveOperacao(float n1, float n2, char* op)
{
    switch (*op){
        case '*': 
            return n1*n2;
            break;
        case '/':
            return n1/n2;
            break;
        case '-':
            return n1-n2;
            break;
        case '+':
            return n1+n2;
            break;
        default:
            return 0;
            break;
    }
}

float resolveArvore(struct nodo* nodo)
{
    if (!ehOperacao(nodo->caracter))
        return nodo->valor;

    float n1 = resolveArvore(nodo->filho_esq);
    float n2 = resolveArvore(nodo->filho_dir);

    return resolveOperacao(n1, n2, nodo->caracter);
}

void imprimeArvore(struct nodo* nodo)
{
    if(nodo == NULL)
        return;

    printf ("%s ", nodo->caracter);
    imprimeArvore(nodo->filho_esq);
    imprimeArvore(nodo->filho_dir);
}


int main(){
    char* entrada = lerEntrada();
    struct nodo* raiz = montaArvore(entrada);
    imprimeArvore(raiz);

    float resul = resolveArvore(raiz);

    printf ("\n");
    printf ("%f\n", resul);

    free(entrada);

    return 0;
}
