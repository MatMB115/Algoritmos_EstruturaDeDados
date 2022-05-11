#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"

struct no{
    char palavra[30];
    struct no *prox;
};

struct lista{
    struct no *inicio;
    int tam;
};


lista *criaLista(){
    lista *l = (lista*) malloc(sizeof(lista));

    if(l == NULL){
        printf("\nErro ao alocar lista!");
        exit(1);
    }
    else{
        l->inicio = NULL;
        l->tam = 0;
    return l;
    }
    
}
//Aloca e inicializa uma lista

int insereLista(lista *l, char *palavra){
    no *noIns = (no*) malloc(sizeof(no));

    if(noIns == NULL){
        printf("\nErro ao alocar no");
        return 1;
    }
    else{
        if(l->inicio == NULL){//Lista vazia
            noIns->prox = NULL;
            strcpy(noIns->palavra, palavra);
            l->inicio = noIns;
            return 0;
        }
        else{
            noIns->prox = l->inicio;
            l->inicio = noIns;
            strcpy(noIns->palavra, palavra);
            return 0;
        }
    }
}
//Insere uma nova palavra na lista. Ou seja, aloca um nó, inicializa e o insere na lista.
//A insersão é sempre no começo da lista.
//Retorna 1 caso ocorra erro na inserção e 0 caso contrário.

lista *getLista(lista **vet, int pos){
    int i;
    lista *listAux;

    return listAux;
}
//Retorna a lista de uma determinada posição da tabela hash

int getTamLista(lista *l){
    return l->tam;
}

int buscaLista(lista *l, char *palavra){

    if(l->inicio == NULL){
        return 0;
    }
    else{
        int i;
        no *noAux;

        noAux = l->inicio;
        for(i = 0; i < l->tam; i++){
            if(strcmp(noAux->palavra, palavra) == 0){
                return 1;
            }
            noAux = noAux->prox;
        }
        return 0;
    }
}
//Verifica se uma palavra está presente ou não em uma lista
//Se a palavra estiver presente, retorna 1. Caso contrário, retorna 0;

void removeLista(lista *l, char *palavra){
    int i;
    no *noAux, *noAnt;
    noAux = l->inicio;

    for(i = 0; i < l->tam; i++){ //Se achar a palavra, linka o elemento no Anterior com o próximo e libera o nó
        if(strcmp(noAux->palavra, palavra) == 0){ 
            noAnt->prox = noAux->prox;
            free(noAux);
            return;
        }
        else{
            noAnt = noAux;
            noAux = noAux->prox;
        }
    }
}
//Remove uma palavra da lista

void imprimeLista(lista *l){

    if(l->inicio == NULL){
        printf("Lista Vazia\n");
    }
    else{
        int i;
        no *noAux;
        noAux = l->inicio;
        for(i = 0; i < l->tam; i++){
            printf("%s\n", noAux->palavra);
            noAux = noAux->prox;
        }
    }
}
//Imprime as palavras de uma lista => printf("%s\n", noAux->palavra);
//Se a lista estiver vazia => printf("Lista Vazia\n");
