#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "lista.h"

// COM112 - Algoritmos e Estruturas de Dados II
// Atividade 04 – 10/05/22
// 2019005687– Matheus Martins Batista
// 2020003596 - Kaique de Souza Leal Silva
// Tabela Hash

struct hash{
    lista **tabela;
    int tam;
};


hash *criaHash(int tam){
    hash *th = (hash*) malloc(sizeof(hash));

    if(th == NULL){
        printf("\nErro ao alocar memória para tabela hash!");
        return NULL;
    }
    else{
        th->tabela = (lista**) malloc(tam * sizeof(lista*));
        if(th->tabela == NULL){
            printf("\nErro ao alocar memória para tabela hash!");
            free(th);
            return NULL;
        }
        else{
            th->tam= tam;
            for(int i = 0; i < tam; i++){
                th->tabela[i] = criaLista();
            }
        }
    return th;
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
    int posLista = funcaoHash(palavra, h->tam);
    insereLista(h->tabela[posLista], palavra);
}
//Insere uma nova palavra na hash utilizando a função insereLista da TAD lista.

int encontraElemento(hash *h, char *palavra){
    int key, flag;
    key = funcaoHash(palavra, h->tam);
    flag = buscaLista(h->tabela[key], palavra);
    if(flag == 1){
        return key;
    }
    else{
        return - 1;
    }
}

//Verifica a presença de uma palavra na tabela hash utilizando a função buscaLista da TAD lista
//Se o elemento estiver presente, retorna a posição dele na Hash. Caso contrário, retorna -1.

void percorre(hash *h, int pos){
    imprimeLista(h->tabela[pos]);
}
//Imprime a lista de uma posição da hash utilizando a função imprimeLista da TAD lista

int getTamanhoLista(hash *h, int pos){
    return getTamLista(h->tabela[pos]);
}
//Retorna o tamanho de uma lista da hash utilizando a função getTamLista da TAD lista.

int removeElemento(hash *h, char *palavra){
    int pos = encontraElemento(h, palavra);
    if(pos == -1){
        return -1;
    }
    else{
        removeLista(h->tabela[pos], palavra);
        return 0;
    }
}
//Remove uma palavra da hash utilizando as funções encontraElemento e removeLista da TAD lista.
//Se o elemento existia na hash e foi removido, retorna 0. Caso contrário, retorna -1.