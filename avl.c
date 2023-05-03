#include "avl.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//substitua por seus dados
struct aluno* getAluno1(){
    struct aluno* retorno = malloc(sizeof(struct aluno));
    if(!retorno)
        exit(1);
    retorno->nome = malloc(sizeof("Paulo Ricardo Lisboa de Almeida"));//sizeof conta o \0
	if(!retorno->nome)
		exit(1);
    retorno->nomeDinf = malloc(sizeof("paulo"));
    if(!retorno->nomeDinf)
        exit(1);
    
	strcpy(retorno->nome, "Paulo Ricardo Lisboa de Almeida");
    strcpy(retorno->nomeDinf, "paulo");
    retorno->grr = 1234;

	return retorno;
}

struct aluno* getAluno2(){
    return NULL;
}

void imprimirDadosAlunos(){
    struct aluno* aluno = getAluno1();
    
    printf("Trabalho de %s\n", aluno->nome);
    printf("Login Dinf %s\n", aluno->nomeDinf);
    printf("GRR %u\n\n", aluno->grr);

    free(aluno->nome);
    free(aluno->nomeDinf);
    free(aluno);

    aluno = getAluno2();
    if(!aluno)
        return;
    
    printf("...E... \n\n");
    printf("Trabalho de %s\n", aluno->nome);
    printf("Login Dinf %s\n", aluno->nomeDinf);
    printf("GRR %u\n\n", aluno->grr);

    free(aluno->nome);
    free(aluno->nomeDinf);
    free(aluno);
}

struct nodo* inserir(struct nodo** raiz, int chave){
	return NULL;
}

int excluir(struct nodo** raiz, int chave){
	return -99;
}

struct nodo* buscar(struct nodo* nodo, int chave){
	return NULL;
}

void imprimirEmOrdem(struct nodo* raiz){
	printf("Imprimindo em ordem\n");
}

void imprimirEmLargura(struct nodo* raiz){
	printf("Imprimindo em largura\n");
}