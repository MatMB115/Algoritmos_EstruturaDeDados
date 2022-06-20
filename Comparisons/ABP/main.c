#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "abp.h"

int main() {
    int i = 0, chave, altura, qtd = 1000, type;
    clock_t inicio, fim;
    double SearchTime = 0;
    double ChargeT;
    double FreeT;

    abp *arvAleatoria = criaArvore();
    abp *arvOrdenada= criaArvore();
    abp *arvDescrescente = criaArvore();
    
    printf("Aleatorio\n");
    //N = 1000
    type = 1;
    inicio = clock();
    carregaArvore(arvAleatoria, "data/1K.txt");
    fim = clock();
    ChargeT = (double)(fim - inicio) / CLOCKS_PER_SEC;
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

    registraDados(ChargeT, FreeT, SearchTime, "registro.txt", qtd, altura, type);
    
    //N = 10000
    SearchTime = 0;
    qtd = qtd*10;
    inicio = clock();
    carregaArvore(arvAleatoria, "data/10K.txt");
    fim = clock();
    ChargeT = (double)(fim - inicio) / CLOCKS_PER_SEC;
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
    esvaziaArvore(arvAleatoria, "data/10K.txt");
    fim = clock();
    FreeT = (double)(fim - inicio) / CLOCKS_PER_SEC;

    registraDados(ChargeT, FreeT, SearchTime, "registro.txt", qtd, altura, type);

    //N = 100000
    SearchTime = 0;
    qtd = qtd*10;
    inicio = clock();
    carregaArvore(arvAleatoria, "data/100K.txt");
    fim = clock();
    ChargeT = (double)(fim - inicio) / CLOCKS_PER_SEC;
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
    esvaziaArvore(arvAleatoria, "data/100K.txt");
    fim = clock();
    FreeT = (double)(fim - inicio) / CLOCKS_PER_SEC;

    registraDados(ChargeT, FreeT, SearchTime, "registro.txt", qtd, altura, type);

    //N = 500000
    SearchTime = 0;
    qtd = qtd*5;
    inicio = clock();
    carregaArvore(arvAleatoria, "data/500K.txt");
    fim = clock();
    ChargeT = (double)(fim - inicio) / CLOCKS_PER_SEC;
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
    esvaziaArvore(arvAleatoria, "data/500K.txt");
    fim = clock();
    FreeT = (double)(fim - inicio) / CLOCKS_PER_SEC;

    registraDados(ChargeT, FreeT, SearchTime, "registro.txt", qtd, altura, type);

    //N = 1000000
    SearchTime = 0;
    qtd = qtd*2;
    inicio = clock();
    carregaArvore(arvAleatoria, "data/1M.txt");
    fim = clock();
    ChargeT = (double)(fim - inicio) / CLOCKS_PER_SEC;
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
    esvaziaArvore(arvAleatoria, "data/1M.txt");
    fim = clock();
    FreeT = (double)(fim - inicio) / CLOCKS_PER_SEC;

    registraDados(ChargeT, FreeT, SearchTime, "registro.txt", qtd, altura, type);

    SearchTime = 0;
    //-------------------------------------Crescente------------------------------------
    printf("Crescente\n");
    type = 2;
    qtd = 1000;
    inicio = clock();
    carregaArvore(arvOrdenada, "data/1K_Ord.txt");
    fim = clock();
    ChargeT = (double)(fim - inicio) / CLOCKS_PER_SEC;
    altura = getAltura(getRaiz(arvOrdenada));
    //Busca
    for(i = 0; i < 30; i++){
        chave = rand() % 30000;
        inicio = clock();
        recuperaNo(arvOrdenada, chave);
        fim = clock();
        SearchTime += (double)(fim - inicio) / CLOCKS_PER_SEC;
    }
    SearchTime = SearchTime / 30;
    inicio = clock();
    esvaziaArvore(arvOrdenada, "data/1K_Ord.txt");
    fim = clock();
    FreeT = (double)(fim - inicio) / CLOCKS_PER_SEC;

    registraDados(ChargeT, FreeT, SearchTime, "registro.txt", qtd, altura, type);
    
    //N = 10000
    SearchTime = 0;
    qtd = qtd*10;
    inicio = clock();
    carregaArvore(arvOrdenada, "data/10K_Ord.txt");
    fim = clock();
    ChargeT = (double)(fim - inicio) / CLOCKS_PER_SEC;
    altura = getAltura(getRaiz(arvOrdenada));
    //Busca
    for(i = 0; i < 30; i++){
        chave = rand() % 30000;
        inicio = clock();
        recuperaNo(arvOrdenada, chave);
        fim = clock();
        SearchTime += (double)(fim - inicio) / CLOCKS_PER_SEC;
    }
    SearchTime = SearchTime / 30;
    inicio = clock();
    esvaziaArvore(arvOrdenada, "data/10K_Ord.txt");
    fim = clock();
    FreeT = (double)(fim - inicio) / CLOCKS_PER_SEC;

    registraDados(ChargeT, FreeT, SearchTime, "registro.txt", qtd, altura, type);

    //N = 100000
    SearchTime = 0;
    qtd = qtd*10;
    inicio = clock();
    carregaArvore(arvOrdenada, "data/100K_Ord.txt");
    fim = clock();
    ChargeT = (double)(fim - inicio) / CLOCKS_PER_SEC;
    altura = getAltura(getRaiz(arvOrdenada));
    //Busca
    for(i = 0; i < 30; i++){
        chave = rand() % 30000;
        inicio = clock();
        recuperaNo(arvOrdenada, chave);
        fim = clock();
        SearchTime += (double)(fim - inicio) / CLOCKS_PER_SEC;
    }
    SearchTime = SearchTime / 30;
    inicio = clock();
    esvaziaArvore(arvOrdenada, "data/100K_Ord.txt");
    fim = clock();
    FreeT = (double)(fim - inicio) / CLOCKS_PER_SEC;

    registraDados(ChargeT, FreeT, SearchTime, "registro.txt", qtd, altura, type);
    /*
    //N = 500000
    SearchTime = 0;
    qtd = qtd*5;
    inicio = clock();
    carregaArvore(arvOrdenada, "data/500K_Ord.txt");
    fim = clock();
    ChargeT = (double)(fim - inicio) / CLOCKS_PER_SEC;
    altura = getAltura(getRaiz(arvOrdenada));
    //Busca
    for(i = 0; i < 30; i++){
        chave = rand() % 30000;
        inicio = clock();
        recuperaNo(arvOrdenada, chave);
        fim = clock();
        SearchTime += (double)(fim - inicio) / CLOCKS_PER_SEC;
    }
    SearchTime = SearchTime / 30;
    inicio = clock();
    esvaziaArvore(arvOrdenada, "data/500K_Ord.txt");
    fim = clock();
    FreeT = (double)(fim - inicio) / CLOCKS_PER_SEC;

    registraDados(ChargeT, FreeT, SearchTime, "registro.txt", qtd, altura, type);
    
    SearchTime = 0;
    //N = 1000000
    SearchTime = 0;
    qtd = qtd*2;
    inicio = clock();
    carregaArvore(arvOrdenada, "data/1M_Ord.txt");
    fim = clock();
    ChargeT = (double)(fim - inicio) / CLOCKS_PER_SEC;
    altura = getAltura(getRaiz(arvOrdenada));
    //Busca
    for(i = 0; i < 30; i++){
        chave = rand() % 30000;
        inicio = clock();
        recuperaNo(arvOrdenada, chave);
        fim = clock();
        SearchTime += (double)(fim - inicio) / CLOCKS_PER_SEC;
    }
    SearchTime = SearchTime / 30;
    inicio = clock();
    esvaziaArvore(arvOrdenada, "data/1M_Ord.txt");
    fim = clock();
    FreeT = (double)(fim - inicio) / CLOCKS_PER_SEC;

    registraDados(ChargeT, FreeT, SearchTime, "registro.txt", qtd, altura, type);
    */
    SearchTime = 0;
    //-------------------------------------Decrescente------------------------------------
    printf("Decrescente\n");
    type = 3;
    qtd = 1000;
    inicio = clock();
    carregaArvore(arvDescrescente, "data/1K_Reverse.txt");
    fim = clock();
    ChargeT = (double)(fim - inicio) / CLOCKS_PER_SEC;
    altura = getAltura(getRaiz(arvDescrescente));
    //Busca
    for(i = 0; i < 30; i++){
        chave = rand() % 30000;
        inicio = clock();
        recuperaNo(arvDescrescente, chave);
        fim = clock();
        SearchTime += (double)(fim - inicio) / CLOCKS_PER_SEC;
    }
    SearchTime = SearchTime / 30;
    inicio = clock();
    esvaziaArvore(arvDescrescente, "data/1K_Reverse.txt");
    fim = clock();
    FreeT = (double)(fim - inicio) / CLOCKS_PER_SEC;

    registraDados(ChargeT, FreeT, SearchTime, "registro.txt", qtd, altura, type);
    
    //N = 10000
    SearchTime = 0;
    qtd = qtd*10;
    inicio = clock();
    carregaArvore(arvDescrescente, "data/10K_Reverse.txt");
    fim = clock();
    ChargeT = (double)(fim - inicio) / CLOCKS_PER_SEC;
    altura = getAltura(getRaiz(arvDescrescente));
    //Busca
    for(i = 0; i < 30; i++){
        chave = rand() % 30000;
        inicio = clock();
        recuperaNo(arvDescrescente, chave);
        fim = clock();
        SearchTime += (double)(fim - inicio) / CLOCKS_PER_SEC;
    }
    SearchTime = SearchTime / 30;
    inicio = clock();
    esvaziaArvore(arvDescrescente, "data/10K_Reverse.txt");
    fim = clock();
    FreeT = (double)(fim - inicio) / CLOCKS_PER_SEC;

    registraDados(ChargeT, FreeT, SearchTime, "registro.txt", qtd, altura, type);

    //N = 100000
    SearchTime = 0;
    qtd = qtd*10;
    inicio = clock();
    carregaArvore(arvDescrescente, "data/100K_Reverse.txt");
    fim = clock();
    ChargeT = (double)(fim - inicio) / CLOCKS_PER_SEC;
    altura = getAltura(getRaiz(arvDescrescente));
    //Busca
    for(i = 0; i < 30; i++){
        chave = rand() % 30000;
        inicio = clock();
        recuperaNo(arvDescrescente, chave);
        fim = clock();
        SearchTime += (double)(fim - inicio) / CLOCKS_PER_SEC;
    }
    SearchTime = SearchTime / 30;
    inicio = clock();
    esvaziaArvore(arvDescrescente, "data/100K_Reverse.txt");
    fim = clock();
    FreeT = (double)(fim - inicio) / CLOCKS_PER_SEC;

    registraDados(ChargeT, FreeT, SearchTime, "registro.txt", qtd, altura, type);
    /*
    //N = 500000
    SearchTime = 0;
    qtd = qtd*5;
    inicio = clock();
    carregaArvore(arvDescrescente, "data/500K_Reverse.txt");
    fim = clock();
    ChargeT = (double)(fim - inicio) / CLOCKS_PER_SEC;
    altura = getAltura(getRaiz(arvDescrescente));
    //Busca
    for(i = 0; i < 30; i++){
        chave = rand() % 30000;
        inicio = clock();
        recuperaNo(arvDescrescente, chave);
        fim = clock();
        SearchTime += (double)(fim - inicio) / CLOCKS_PER_SEC;
    }
    SearchTime = SearchTime / 30;
    inicio = clock();
    esvaziaArvore(arvDescrescente, "data/500K_Reverse.txt");
    fim = clock();
    FreeT = (double)(fim - inicio) / CLOCKS_PER_SEC;

    registraDados(ChargeT, FreeT, SearchTime, "registro.txt", qtd, altura, type);
    
    
    SearchTime = 0;
    //N = 1000000
    SearchTime = 0;
    qtd = qtd*2;
    inicio = clock();
    carregaArvore(arvDescrescente, "data/1M_Reverse.txt");
    fim = clock();
    ChargeT = (double)(fim - inicio) / CLOCKS_PER_SEC;
    altura = getAltura(getRaiz(arvDescrescente));
    //Busca
    for(i = 0; i < 30; i++){
        chave = rand() % 30000;
        inicio = clock();
        recuperaNo(arvDescrescente, chave);
        fim = clock();
        SearchTime += (double)(fim - inicio) / CLOCKS_PER_SEC;
    }
    SearchTime = SearchTime / 30;
    inicio = clock();
    esvaziaArvore(arvDescrescente, "data/1M_Reverse.txt");
    fim = clock();
    FreeT = (double)(fim - inicio) / CLOCKS_PER_SEC;

    registraDados(ChargeT, FreeT, SearchTime, "registro.txt", qtd, altura, type);
    */
    free(arvAleatoria);
    free(arvDescrescente);
    free(arvOrdenada);
    return 0;
}
