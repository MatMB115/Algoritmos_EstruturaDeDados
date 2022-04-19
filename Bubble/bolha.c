#include <stdio.h>
#include <stdlib.h>

#include "bolha.h"

// COM112 - Algoritmos e Estruturas de Dados II
// Lista 02 – 08/04/22
// 2019005687– Matheus Martins Batista
//
// Algoritmos de ordenação – Bubblesort

struct tReturn {
    int erro, tam, *vet;
};

tReturn *alocatReturn(){
    tReturn *p = (tReturn*) malloc(sizeof(tReturn));
    return p;
}

int *getVet(tReturn *rep){
    return rep->vet;
}

int getTam(tReturn *rep){
    return rep->tam;
}

int getErro(tReturn *rep){
    return rep->erro;
}

void trataErro(int erro){
    if(erro == 1){
        printf("Erro de abertura do arquivo");
    }
    else{
        if(erro == 2){
            printf("Erro de leitura do arquivo");
        }
        else{
            if(erro == 3){
                printf("Erro de alocação de memória");
            }
            else{
                printf("Erro desconhecido");
            }
        }
    }
}


tReturn* leArquivo(char nomeArquivo[]){
    tReturn *aux = alocatReturn();
    FILE *arq;
    arq = fopen(nomeArquivo, "r");
    if(arq == NULL){
        aux->erro = 1;
    }
    else {
        if(fscanf(arq, "%d", &aux->tam) != EOF){
            int *vet = (int *) malloc(aux->tam * sizeof(int)); //Não esquecer de declarar o tipo que alocação vai retornar
            if (vet == NULL) {
                aux->erro = 3;
            }
            else {
                aux->vet = vet;
                for (int i = 0; i < aux->tam; ++i) {
                    fscanf(arq, "%d", &aux->vet[i]);
                }
                aux->erro = 0;
            }
            fclose(arq);
        }
        else{
            aux->erro = 2;
        }
    }
    return aux;
}
//Essa função lê um arquivo com números inteiros (um número por linha) e preenche um vetor
//A primeira linha do arquivo contém o tamanho do vetor
//A função retorna o tipo TReturn formado por um ponteiro para inteiros, um inteiro que guarda o tamanho do vetor e um inteiro que codifica erros

void bolha (int *vet, int tam){
    int i, aux, j;

    for (i = 0; i < tam; i++){
        for (j = 1; j < tam; j++){
            if(vet[j] < vet[j - 1]){
                aux = vet[j - 1];
                vet[j - 1] = vet[j];
                vet[j] = aux;
            }
        }
    }
}

void imprimeVet(int *vet, int tam){
    int i;

    for (i = 0; i < tam; i++){
        printf("%d\n", vet[i]);
    }
}
//Essa função imprime os dados de um vetor (um número por linha)

