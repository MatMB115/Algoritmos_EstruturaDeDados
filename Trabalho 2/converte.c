#include <stdio.h>
#include <stdlib.h>
#include "converte.h"
#include "btree.h"
#include "rb.h"

//Converte uma BTree 2-3-4 para uma RubroNegra
rb* converte(btree* bt) {
    void converteNos(noBt * btAtual, noRb * rbAtual, rb * rb);
    rb* rb = criaArvoreRb();
    noBt* btAtual = retornaRaiz(bt);

    converteNos(btAtual, NULL, rb);

    return rb;
}

//Converte os nós da BTree recursivamente
void converteNos(noBt* btAtual, noRb* rbAtual, rb* rb) {
    if (btAtual == NULL) return;

    if (btAtual->ocupacao == 0) {
        printf("Vazio");
        return;
    }


    noRb* novoNo = (noRb*)malloc(sizeof(noRb));
    if (btAtual->ocupacao == 1) { //nó de ordem 2
        novoNo->chave = btAtual->chaves[0];
        novoNo->cor = 'p';
        if (btAtual->folha == 1) {
            novoNo->dir = getNULL(rb);
            novoNo->esq = getNULL(rb);
        }
        rb->numElementos++;
    }
    else if (btAtual->ocupacao == 2) { //nó de ordem 3
        //primeiro elemento vira o pai e segundo o filho
        novoNo->chave = btAtual->chaves[0];
        novoNo->cor = 'p';

        noRb* novoFilho = (noRb*)malloc(sizeof(noRb));
        novoFilho->chave = btAtual->chaves[1];
        novoFilho->cor = 'v';

        if (btAtual->folha == 1) {
            novoNo->esq = getNULL(rb);
            novoFilho->dir = getNULL(rb);
            novoFilho->esq = getNULL(rb);
        }

        novoFilho->pai = novoNo;
        novoNo->dir = novoFilho;
        rb->numElementos += 2;
    }
    else { //nó de ordem 4
        //elemento do meio vira o pai e os demais filhos
        novoNo->chave = btAtual->chaves[1];
        novoNo->cor = 'p';

        noRb* novoDir = (noRb*)malloc(sizeof(noRb));
        novoDir->chave = btAtual->chaves[2];
        novoDir->cor = 'v';

        noRb* novoEsq = (noRb*)malloc(sizeof(noRb));
        novoEsq->chave = btAtual->chaves[0];
        novoEsq->cor = 'v';

        if (btAtual->folha == 1) {
            novoEsq->dir = getNULL(rb);
            novoEsq->esq = getNULL(rb);
            novoDir->dir = getNULL(rb);
            novoDir->esq = getNULL(rb);
        }

        novoDir->pai = novoNo;
        novoEsq->pai = novoNo;
        novoNo->esq = novoEsq;
        novoNo->dir = novoDir;
        rb->numElementos += 3;
    }

    if (rbAtual == NULL) {
        rb->sentinela->dir = novoNo;
        novoNo->pai = rb->sentinela;
    }
    else {
        if (rbAtual->chave > novoNo->chave) {
            rbAtual->esq = novoNo;
        }
        else {
            rbAtual->dir = novoNo;
        }
    }

    if (btAtual->folha == 0) {
        if (btAtual->ocupacao == 1) {
            converteNos(btAtual->ponteiros[0], novoNo, rb);
            converteNos(btAtual->ponteiros[1], novoNo, rb);
        }
        if (btAtual->ocupacao == 2) {
            converteNos(btAtual->ponteiros[0], novoNo, rb);
            converteNos(btAtual->ponteiros[1], novoNo->dir, rb);
            converteNos(btAtual->ponteiros[2], novoNo->dir, rb);
        }
        if (btAtual->ocupacao == 3) {
            converteNos(btAtual->ponteiros[0], novoNo->esq, rb);
            converteNos(btAtual->ponteiros[1], novoNo->esq, rb);
            converteNos(btAtual->ponteiros[2], novoNo->dir, rb);
            converteNos(btAtual->ponteiros[3], novoNo->dir, rb);
        }
    }

}

