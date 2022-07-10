#include <stdio.h>
#include <stdlib.h>
#include "btree.h"
#include "rb.h"
#include "converte.h"

/*
  Luis Ricardo Albano Santos - 2021031844
  Matheus Martins Batista 2019005687
*/

int main() {
    int menuBtree(btree*, rb*);
    int menuRb(btree*, rb*);

    char nomeArquivo[100];
    int opcao;
    btree* btree;
    rb* rb = NULL;

    btree = criaArvoreBt(4);
    if (btree == NULL) {
        printf("A ordem deve ser par\n");
        return 1;
    }

    printf("Insira o nome do arquivo: ");
    scanf("%s", nomeArquivo);

    manipulaBTree(btree, nomeArquivo, 'i');

    printf("\n ----Arvore 2-3-4----\n");
    imprimeArvore((retornaRaiz(btree)), 0);

    do {
        if (rb == NULL) {
            printf("\n---------Menu Btree---------\n");
            printf("1 - Inserir elemento na arvore 2-3-4\n");
            printf("2 - Remover elemento na arvore 2-3-4\n");
            printf("3 - Imprimir arvore 2-3-4\n");
            printf("4 - Converter em uma arvore rubro-negra\n");
            printf("5 - Sair\n");
            printf("----------------------\n");
            printf("Insira a opcao: ");
            scanf("%d", &opcao);

            switch (opcao) {
            case 1:
                printf("Insira o elemento: ");
                scanf("%d", &opcao);
                insereElemento(btree, opcao);
                break;
            case 2:
                printf("Insira o elemento: ");
                scanf("%d", &opcao);
                removeElemento(btree, opcao);
                break;
            case 3:
                printf("\n --Arvore 2-3-4--\n");
                imprimeArvore((retornaRaiz(btree)), 0);
                printf("\n");
                break;
            case 4:
                rb = converte(btree);
                break;
            case 5:
                opcao = 0;
                break;
            default:
                printf("Opcao invalida\n");
                break;
            }
        }
        else {
            printf("\n---------Menu Rubro-Negra---------\n");
            printf("1 - Inserir elemento na arvore rubro-negra\n");
            printf("2 - Remover elemento na arvore rubro-negra\n");
            printf("3 - Imprimir arvore rubro-negra\n");
            printf("4 - Sair\n");

            printf("Insira a opcao: ");
            scanf("%d", &opcao);

            switch (opcao) {
            case 1:
                printf("Insira o elemento: ");
                scanf("%d", &opcao);
                insereNo(rb, opcao);
                break;
            case 2:
                printf("Insira o elemento: ");
                scanf("%d", &opcao);
                removeNo(rb, opcao);
                break;
            case 3:
                printf("\n ----Arvore rubro-negra----\n");
                percorre(getRaiz(rb));
                printf("\n");
                break;
            case 4:
                opcao = 0;
                break;
            default:
                printf("Opcao invalida\n");
                break;
            }
        }
    } while (opcao != 0);

    return 0;
}