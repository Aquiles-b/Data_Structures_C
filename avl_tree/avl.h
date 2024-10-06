#ifndef AVL_H_
#define AVL_H_

#ifndef STRUCT_AVL
#define STRUCT_AVL
struct nodo {
    int chave;
    int balanco;
    struct nodo *pai;
    struct nodo *fe;
    struct nodo *fd;
};
#endif 

//retorna NULL se não foi possível inserir
struct nodo* inserir(struct nodo** raiz, int chave);

//retorna 1 caso removido, ou 0 caso não seja possível remover
int excluir(struct nodo** raiz, int chave);

//retorna NULL se não existe
struct nodo* buscar(struct nodo* nodo, int chave);

void imprimirEmOrdem(struct nodo* nodo);

void imprimirEmLargura(struct nodo* raiz);

//desaloca toda memoria da arvore. Retorna NULL.
struct nodo *destroiArvore(struct nodo *raiz);

#endif // AVL_H_
