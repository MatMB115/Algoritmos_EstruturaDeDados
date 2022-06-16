#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avl.h"

int main() {
    int i = 0, chave, altura, rotCarrega = 0, rotLibera = 0, qtd = 1000, type;
    clock_t inicio, fim;
    double SearchTime = 0;
    double ChargeT = 0;
    double FreeT = 0;

    avl *arvAleatoria = criaArvore();
    avl *arvOrdenada = criaArvore();
    avl *arvDescrescente = criaArvore();
    
    printf("Aleatorio\n");
    //N = 1000
    type = 1;
    inicio = clock();
    carregaArvore(arvAleatoria, "data/1K.txt");
    fim = clock();
    ChargeT = (double)(fim - inicio) / CLOCKS_PER_SEC;
    rotCarrega = getRotacoes(arvAleatoria);
    altura = getAltura(getRaiz(arvAleatoria));
    //Busca
    for(i = 0; i < 30; i++){
        chave = rand() % 30000;
        inicio = clock();
        recuperaNo(arvAleatoria, chave);
        fim = clock();
        SearchTime += (double)(fim - inicio) / CLOCKS_PER_SEC;
    }
    SearchTime = SearchTime / 30;
    inicio = clock();
    esvaziaArvore(arvAleatoria, "data/1K.txt");
    fim = clock();
    FreeT = (double)(fim - inicio) / CLOCKS_PER_SEC;
    rotLibera = getRotacoes(arvAleatoria) - rotCarrega;

    registraDados(ChargeT, FreeT, SearchTime, "registro.txt", qtd, altura, type, rotCarrega, rotLibera);
    
    return 0;
}
