#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "lista.h"

struct hash{
    lista **tabela;
    int tamanho;
};


hash *criaHash(int tam){
    hash *t = (hash*) malloc(sizeof(hash));

    if(t == NULL){
        printf("\nErro ao alocar tabela!");
        exit(1);
    }
    else{
        //t->*tabela->inicio = 
        t->tamanho = tam;
        t->tabela = (struct lista**) malloc (tam * sizeof(struct lista*));
        for(int i = 0; i < tam; i++){
            lista *ant = criaLista();
        
        }
        //t->tamanho = tam;
    return t;
    }
}
//Aloca e inicializa uma tabela hash de tamanho "tam";

int funcaoHash(char *palavra, int tamHash){
    int num, i = 0, sum = 0, key;
    char ascii = palavra[i];
    
    while(ascii != '\0'){
        num = ascii;
        sum += num;
        i++;
        ascii = palavra[i];
    }
    key = sum % tamHash;
    
    return key;
}
//Retorna a posição da palavra na tabela hash de tamanho "tamHash"
//O cálculo está na descrição da atividade

void insere(hash *h, char *palavra){
    int i;
    no *noAux;
    int posLista = funcaoHash(palavra, h->tamanho);
    lista *list = getLista(h->tabela, posLista);
    insereLista(list, palavra);
}
//Insere uma nova palavra na hash utilizando a função insereLista da TAD lista.

int encontraElemento(hash *h, char *palavra){
    int i, flag;
    lista *listAux;
    for(i = 0; i < h->tamanho; i++){
        listAux = getLista(h->tabela, i);
        flag = buscaLista(listAux, palavra);
        if(flag == 1){
            return i;
        }
    }
    return - 1;
}
//Verifica a presença de uma palavra na tabela hash utilizando a função buscaLista da TAD lista
//Se o elemento estiver presente, retorna a posição dele na Hash. Caso contrário, retorna -1.

void percorre(hash *h, int pos){
    lista *listAux = getLista(h->tabela, pos);
    imprimeLista(listAux);
}
//Imprime a lista de uma posição da hash utilizando a função imprimeLista da TAD lista

int getTamanhoLista(hash *h, int pos){
    lista *listAux = getLista(h->tabela, pos);
    return getTamLista(listAux);
}
//Retorna o tamanho de uma lista da hash utilizando a função getTamLista da TAD lista.

int removeElemento(hash *h, char *palavra){
    int pos = encontraElemento(h, palavra);
    if(pos == -1){
        return -1;
    }
    else{
        lista *listAux = getLista(h->tabela, pos);
        removeLista(listAux, palavra);
        return 0;
    }
    
}
//Remove uma palavra da hash utilizando as funções encontraElemento e removeLista da TAD lista.
//Se o elemento existia na hash e foi removido, retorna 0. Caso contrário, retorna -1.