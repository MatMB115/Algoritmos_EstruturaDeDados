#include <stdio.h>
#include <stdlib.h>
#include "btree.h"
#include "rb.h"

rb* converte(btree* bt) {
    
    rb* rb = criaArvoreRb();
    noBt* atual = retornaRaiz(bt);

    //Verificar em qual caso a raiz se encaixa
    if(atual->ocupacao == 1){ //nó de ordem 2
        noRb* novaRaiz = (noRb*)malloc(sizeof(noRb));
        novaRaiz->chave = atual->chaves[0];
        novaRaiz->cor = 'p';
        novaRaiz->dir = getNULL(rb);
        novaRaiz->esq = getNULL(rb);
        novaRaiz->pai = rb->sentinela;
        rb->sentinela->dir = novaRaiz;
        rb->numElementos++;

    }else if(atual->ocupacao == 2){ //nó de ordem 3
        //primeiro elemento vira o pai e segundo o filho
        noRb* novaRaiz = (noRb*)malloc(sizeof(noRb));
        novaRaiz->chave = atual->chaves[0];
        novaRaiz->cor = 'p';
        novaRaiz->esq = getNULL(rb);

        noRb* novoFilho = (noRb*)malloc(sizeof(noRb));
        novoFilho->chave = atual->chaves[1];
        novoFilho->cor = 'v';
        novoFilho->dir = getNULL(rb);
        novoFilho->esq = getNULL(rb);

        novoFilho->pai = novaRaiz;
        novaRaiz->dir = novoFilho;
        novaRaiz->pai = rb->sentinela;
        rb->sentinela->dir = novaRaiz;
        rb->numElementos++;

    }else{ //nó de ordem 4
        //elemento do meio vira o pai e os demais filhos
        noRb* novaRaiz = (noRb*)malloc(sizeof(noRb));
        novaRaiz->chave = atual->chaves[1];
        novaRaiz->cor = 'p';
        

        noRb* novoDir= (noRb*)malloc(sizeof(noRb));
        novoDir->chave = atual->chaves[2];
        novoDir->cor = 'v';
        novoDir->dir = getNULL(rb);
        novoDir->esq = getNULL(rb);

        noRb* novoEsq= (noRb*)malloc(sizeof(noRb));
        novoEsq->chave = atual->chaves[0];
        novoEsq->cor = 'v';
        novoEsq->dir = getNULL(rb);
        novoEsq->esq = getNULL(rb);

        novoDir->pai = novaRaiz;
        novoEsq->pai = novaRaiz;
        novaRaiz->esq = novoEsq;
        novaRaiz->dir = novoDir;
        novaRaiz->pai = rb->sentinela;
        rb->sentinela->dir = novaRaiz;
        rb->numElementos++;
    }

    return rb;
}
