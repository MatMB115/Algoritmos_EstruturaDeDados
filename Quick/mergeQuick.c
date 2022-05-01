#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "mergeQuick.h"

// COM112 - Algoritmos e Estruturas de Dados II
// Atividade 03 – 23/04/22
// 2019005687– Matheus Martins Batista
//
// Algoritmos de Ordenação – MergeSort e QuickSort

int geraAleatorios(char *nomeArquivo, int qtd){
    int i, num = 0;

    FILE *arq = fopen(nomeArquivo, "w+"); //Abre a sobrescreve o que estiver no arquivo inteiro
    if(arq == NULL){ //Erro na abertura
        return 1;
    }
    else{
        //Definir semente para randomizar os números
        srand(time(0));
        for (i = 0; i < qtd; ++i){
            num = rand() % 1000; 
            if(fprintf(arq, "%d\n", num) == -1){//Erro ao tentar escrever no arquivo
                fclose(arq);
                return 1;
            }
        }
        fclose(arq);
        return 0;
    }
}

int* leArquivo(char *nomeArquivo, int qtd){
    int i;

    FILE *arq = fopen(nomeArquivo, "r"); //Abre e lê o que estiver no arquivo
    if(arq == NULL){
        return NULL;
    }
    else{
        int *vet = (int*) malloc(qtd * sizeof(int)); //Alocar memória para vetor de inteiros
        if(vet == NULL){
            return NULL;
        }
        else{
            for(i = 0; i < qtd; i++){
                if(fscanf(arq, "%d", &vet[i]) == EOF){ //Verificar se a leitura foi realizada corretamente
                    return NULL;
                }
            }
            fclose(arq);
            return vet;
        }

    }

}

void imprimeVet(int *vet, int tam){
    int i;
    for(i = 0; i < tam; i++){
        printf("%d ", vet[i]);
    }
    printf("\n");
}

void mergeSort(int *vet, int inicio, int fim){
    int meio;

    if(inicio < fim){
        meio = abs((inicio+fim)/2);
        mergeSort(vet, inicio, meio);
        mergeSort(vet, meio + 1, fim);
    }
}
//Função Mergesort Recursiva

void merge(int *vet, int inicio, int meio, int fim){
    int mV1 = inicio; //Primeira metade do vetor
    int mV2 = meio + 1; //Segunda metade do vetor
    int *vetAux = (int*) malloc(((fim-inicio)+1)*sizeof(int)); //Vetor para guardar os elementos ordenados
    int i = 0;

    while(mV1 <= meio && mV2 <= fim){
        if(vet[mV1] < vet[mV2]){
            vetAux[i] = vet[mV1];
            mV1++;
        }
        else{
            vetAux[i] = vet[mV2];
            vet[mV2]++;
        }
        i++;
    }

    for(i = 0; i <= (fim-inicio); i++){
        vet[i] = vetAux[i];
    }
    free(vetAux);
}
//Função Merge, que combina dois vetores previamente ordenados

void quickSort(int *vet, int inicio, int fim){
    int pivo;
    
    if(inicio < fim){
        pivo = particiona(vet, inicio, fim);
        quickSort(vet, inicio, pivo - 1);
        quickSort(vet, pivo + 1, fim);
    }
}
//Função QuickSort recursiva

int particiona(int *vet, int inicio, int fim){
    int pivo = vet[inicio];
    int pos = inicio; //posição final do pivo
    int aux;
    int i;
    
    for(i = inicio + 1; i <= fim; i++){
        if(vet[i] < pivo){
            pos++;
            if(pos != i){
                aux = vet[i];
                vet[i] = vet[pos];
                vet[pos] = aux;
            }
        }
        aux = vet[inicio];
        vet[inicio] = vet[pos];
        vet[pos] = aux;
    }

    return pos;
}
//Função que ordena o elemento pivô.