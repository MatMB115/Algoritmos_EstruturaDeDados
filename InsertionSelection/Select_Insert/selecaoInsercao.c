#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "selecaoInsercao.h"

// COM112 - Algoritmos e Estruturas de Dados II
// Atividade 03 – 23/04/22
// 2019005687– Matheus Martins Batista
//
// Algoritmos de Ordenação – InsertSort, SelectionSort, InverseSelectionSort and DualSelectionSort

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

void selecao(int *vet, int tam){ //Complexidade O(n²)
    int i = 0, marc = 0, aux = 0, menor = 0;

    while(marc < tam - 1){
        //Na progressão de marcador, atribuir os dados do primeiro elemento da parte desordenada
        menor = marc + 1;
        for(i = marc + 1; i < tam; i++){ //Busca o menor elemento da parte desordenada
            if(vet[menor] > vet[i]){ //Recebe o índice e valor se menorDes for maior que o elemento comparado
                menor = i;
            }
        }
        if(vet[menor] < vet[marc]){
            aux = vet[menor];
            vet[menor] = vet[marc];
            vet[marc] = aux;
        }
        marc++;
    }
}

void selecaoDecrescente(int *vet, int tam){ //Complexidade O(n²)
    int i = 0, marc = 0, aux = 0, maior = 0; //maiorDes é o possível maior valor da parte desordenada

    while(marc < tam - 1){
        //Na progressão de marcador, atribuir os dados do primeiro elemento da parte desordenada
        maior = marc + 1;
        for(i = marc + 1; i < tam; i++){ //Busca o maior elemento da parte desordenada
            if(vet[maior] < vet[i]){ //Recebe o índice e valor se maiorDes for menor que o elemento comparado
                maior = i;
            }
        }
        if(vet[maior] > vet[marc]){
            aux = vet[maior];
            vet[maior] = vet[marc];
            vet[marc] = aux;
        }
        marc++;
    }
}

void dualSelecao(int *vet, int tam){ //Complexidade O(n²), menor quantidade de loop se comparado ao selectionSort comum
    int leftm = 0, rightm = 0, aux;
    int i, maior, menor;

    while(leftm < rightm){
        menor = leftm;
        maior = rightm;

        for(i = leftm; i <= rightm; i++){
            if(vet[i] < vet[menor]){
                menor = i;
            } 
			if(vet[i] > vet[maior]){
                maior = i;
            } 
        }

        if (menor != leftm){
			if(menor == rightm){
				menor = maior;
            }
            aux = vet[menor];
            vet[menor] = vet[leftm];
            vet[leftm] = aux;
        }

        if(maior != rightm){
            aux = vet[maior];
            vet[maior] = vet[rightm];
            vet[rightm] = aux;
        }

        leftm++;
        rightm--;
    }

    return;
}

void insercao(int *vet, int tam){ //Complexidade: melhor caso O(n) e pior caso O(n²)
    int marc, aux = 0, pos = 0;
    for(marc = 1; marc < tam; marc++){
        pos = marc - 1;
        aux = vet[marc];
        while(aux < vet[pos] && pos >=0){
            vet[pos + 1] = vet[pos];
            pos--;
        }
        vet[pos + 1] = aux;
    }
}

void imprimeVet(int *vet, int tam){
    int i;
    for(i = 0; i < tam; i++){
        printf("%d ", vet[i]);
    }
    printf("\n");
}
