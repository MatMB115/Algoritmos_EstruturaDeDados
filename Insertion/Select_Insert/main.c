#include <stdio.h>
#include <string.h>

#include "selecaoInsercao.h"

int main() {
    int qtd = 20, *vet, *vet2, *vet3, *vet4;
    char nomeArquivo[7];

    scanf(" %s", nomeArquivo);
    geraAleatorios(nomeArquivo, qtd);
    vet = leArquivo(nomeArquivo, qtd);
    vet2 = leArquivo(nomeArquivo, qtd);
    vet3 = leArquivo(nomeArquivo, qtd);
    vet4 = leArquivo(nomeArquivo, qtd);
    imprimeVet(vet, qtd);
    printf("\n");
    selecao(vet, qtd);
    dualSelecao(vet2, qtd);
    selecaoDecrescente(vet3, qtd);
    insercao(vet4, qtd);
    imprimeVet(vet, qtd);
    imprimeVet(vet2, qtd);
    imprimeVet(vet3, qtd);
    imprimeVet(vet4, qtd);

    return 0;
}
