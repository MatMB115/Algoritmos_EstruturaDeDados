#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"

struct no{
    char palavra[30];
    no *prox;
};

struct lista{
    no *inicio;
    int tam;
};


lista *criaLista(){
    lista *l = (lista*) malloc(sizeof(lista));
    if(l == NULL){
        printf("\nErro ao alocar lista!");
        exit(1);
    }else{
        l->inicio = NULL;
        l->tam = 0;
    return l;
    }
    
}
//Aloca e inicializa uma lista

int insereLista(lista *l, char *palavra){
    no *el = (no*) malloc(sizeof(no));
    if(el == NULL){
        printf("\nErro ao alocar no");
        return 1;
    }
    else{
        if(l->inicio == NULL){//Lista vazia
            el->prox = NULL;
            strcpy(el->palavra, palavra);
            l->inicio = el;
            return 0;
        }
        else{
            el->prox = l->inicio;
            l->inicio = el;
            strcpy(el->palavra, palavra);
            return 0;
        }
    }
}
//Insere uma nova palavra na lista. Ou seja, aloca um nó, inicializa e o insere na lista.
//A insersão é sempre no começo da lista.
//Retorna 1 caso ocorra erro na inserção e 0 caso contrário.

lista *getLista(lista **vet, int pos){
    int i;

    /*for(i = 0; i < ; i++){

    }*/

}
//Retorna a lista de uma determinada posição da tabela hash

int getTamLista(lista *l){
    return l->tam;
}

int buscaLista(lista *l, char *palavra){
    int i;
    no *aux;

    aux = l->inicio;
    for(i = 0; i < l->tam; i++){
        if(strcmp(aux->palavra, palavra) == 0){
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}
//Verifica se uma palavra está presente ou não em uma lista
//Se a palavra estiver presente, retorna 1. Caso contrário, retorna 0;

void removeLista(lista *l, char *palavra){
    int i;
    no *aux, *ant;

    aux = l->inicio;
    for(i = 0; i < l->tam; i++){
        if(strcmp(aux->palavra, palavra) == 0){
            ant->prox = aux->prox;
            free(aux);
            return 1;
        }
        ant = aux;
        aux = aux->prox;
    }
    return 0;
}
//Remove uma palavra da lista

void imprimeLista(lista *l){

}
//Imprime as palavras de uma lista => printf("%s\n", noAux->palavra);
//Se a lista estiver vazia => printf("Lista Vazia\n");
