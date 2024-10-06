#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#define TAM_STR 32

// Adiciona o nodo na arvore. Em caso de erro, imprime no stdout que nao foi 
// possivel inserir.
void adicionarNodo(struct nodo **raiz, char *entrada)
{
    int chave;
    struct nodo *sts = NULL;
    int leitura = sscanf(entrada + 1, "%d", &chave);
    if (leitura != -1)
        sts = inserir(raiz, chave);
    if (sts == NULL)
        printf ("Falha ao inserir.\n");
}

// Busca o nodo na arvore que contem a chave passada.
// Imprime no stdout se o nodo foi encontrado ou nao.
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

// Apaga o nodo da arvore que contem a chave passada. 
// Caso a remocao nao seja possivel, imprime no stdout uma mensagem de erro.
void excluirNodo(struct nodo **raiz, char *entrada)
{
    int chave = 0;
    int sts = 0;
    int leitura = sscanf(entrada + 1, "%d", &chave);
    if (leitura != -1)
        sts = excluir(raiz, chave);
    if (sts == 0)
        printf ("Falha ao remover %d.\n", chave);
}

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

int main(){
    imprimirDadosAlunos();

    struct nodo *raiz = NULL;
    char *entrada = malloc(sizeof(char) * TAM_STR);
    int sts = 1;
    while(sts) {
        pegaEntrada(entrada);
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
    raiz = destroiArvore(raiz);
    free(entrada);

    return 0;
}
