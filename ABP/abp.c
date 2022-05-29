#include <stdio.h>
#include <stdlib.h>

#include "abp.h"

// COM112 - Algoritmos e Estruturas de Dados II
// Atividade 05 – 24/05/22
// 2019005687– Matheus Martins Batista
// 2020003596 - Kaique de Souza Leal Silva
// Árvore Binária de Busca com Sentinela

struct no{
    int chave;
    struct no *esq;
    struct no *dir;
    struct no *pai;
};

struct arvore{
    no *sentinela;
    int numElementos;
};

//Cria uma nova árvore inicializando a sentinela
abp *criaArvore(){
    abp *arv = (abp*) malloc(sizeof(abp));
    if(arv == NULL){
        return NULL;
    }
    else{
        no *sent = (no*) malloc(sizeof(no));
        if(sent == NULL){
            return NULL;
        }
        else{ //Preencher os campos da árvore
            sent->chave = -1000;
            sent->esq = NULL;
            sent->dir = NULL;
            sent->pai = NULL;
            arv->sentinela = sent;
            arv->numElementos = 0;
            return arv;
        }
    }
}

//Popula uma árvore binária de pesquisa a partir de números contidos no arquivo
//Retorna -1 caso haja erros durante a inserção e/ou leitura do arquivo
//Retorna 0 caso contrário
int carregaArvore(abp *arv, char *nomeArquivo){
    int chave;
    FILE *arq = fopen(nomeArquivo, "r");
    if(arq == NULL){
        return -1;
    }
    else{
        while (!feof(arq)){
            if(fscanf(arq, "%d", &chave) == 0){
                printf("Erro ao ler do arquivo de entrada\n");
                fclose(arq);//
                return 1;
            }
            if(insereNo(arv, chave) == -1){
                printf("Erro ao inserir um nó");
                fclose(arq);
                return 1;
            }
        }
        fclose(arq);
        return 0;
    }
}

//Aloca um novo nó e o insere na árvore
//Retorna 0 caso a inserção aconteça e -1 caso contrário
int insereNo(abp *arv, int chave){
    no *noAux = (no*) malloc(sizeof(no));
    no *noAnt, *noAtual;
    
    if(noAux == NULL){
        printf("Erro ao alocar nó");
        return -1;
    }
    else{//Atualizar campos genéricos do filho
        noAux->chave = chave;
        noAux->dir = NULL;
        noAux->esq = NULL;
        if(arv->numElementos == 0){//Se lista vazia, insere a raiz
            noAux->pai = arv->sentinela;
            arv->sentinela->dir = noAux;
            arv->numElementos++;
            return 0;
        }
        else{
            noAtual = arv->sentinela->dir;
            //Percorre a árvore buscando a posição para inserir uma folha
            while(noAtual != NULL){
                if(chave < noAtual->chave){//Se menor que o nó, vá para a esquerda
                    noAnt = noAtual;
                    noAtual = noAtual->esq;
                }
                else{//Senão vá para a direita
                    noAnt = noAtual;
                    noAtual = noAtual->dir;
                }
            } //Verificar se é o filho da direita ou esquerda
            if(chave < noAnt->chave){
                noAux->pai = noAnt;
                noAnt->esq = noAux;
                arv->numElementos++;
                return 0;
            }
            else{
                noAux->pai = noAnt;
                noAnt->dir = noAux;
                arv->numElementos++;
                return 0;
            }
        }
    }
}

//Remove um elemento da árvore
//Retorna 0 caso a deleção aconteça;
//Retorna -1 caso a árvore esteja vazia
//Retorna -2 caso o elemento não esteja presente na árvore
int removeNo(abp *arv, int chave){
    no *noAux = recuperaNo(arv, chave);
    no *predecessor, *noAtual;
    if(noAux == NULL){
        return -2;
    }
    else{
        if(arv->numElementos == 0){
            return -1;
        }
        else{
            if(noAux->dir == NULL && noAux->esq == NULL){//Eliminar um nó folha
                if(noAux->chave < noAux->pai->chave){//da esquerda
                    noAux->pai->esq = NULL;
                    free(noAux);
                    arv->numElementos--;
                    return 0;
                }
                else{//da direita
                    noAux->pai->dir = NULL;
                    arv->numElementos--;
                    free(noAux);
                    return 0;
                }
            }
            else{
                if(noAux->dir !=NULL && noAux->esq != NULL){//Eliminar um nó com 2 filhos
                    noAtual = noAux->esq;
                    while(noAtual != NULL){
                        predecessor = noAtual;
                        noAtual = noAtual->dir;
                    }
                    if(predecessor->esq != NULL){ //se predecessor tem filho
                        predecessor->esq->pai = predecessor->pai; // linka ex-filho do predecessor ao ex-pai do predecessor
                        predecessor->pai->dir = predecessor->esq; // linka ex-pai do predecessor ao ex-filho do predecessor
                        noAux->chave = predecessor->chave;
                        arv->numElementos--;
                        free(predecessor);
                        return 0;
                    }
                    else{//predecessor não tem filho
                        noAux->chave = predecessor->chave;
                        arv->numElementos--;
                        free(predecessor);
                        return 0;
                    }
                    
                }
                else{//Eliminar um nó com 1 filho
                    if(noAux->chave < noAux->pai->chave){//O nó a ser eliminado está à esquerda do pai
                        if(noAux->esq != NULL){//Há um filho na esquerda
                            noAux->pai->esq = noAux->esq;
                            arv->numElementos--;
                            free(noAux);
                            return 0;
                        }
                        else{//Há um filho na direita
                            noAux->pai->esq = noAux->dir;
                            arv->numElementos--;
                            free(noAux);
                            return 0;
                        }
                    }
                    else{//O nó a ser eliminado está à direita do pai
                        if(noAux->esq != NULL){//Há um filho na esquerda
                            noAux->pai->dir = noAux->esq;
                            arv->numElementos--;
                            free(noAux);
                            return 0;
                        }
                        else{//Há um filho na direita
                            noAux->pai->dir = noAux->dir;
                            arv->numElementos--;
                            free(noAux);
                            return 0;
                        }
                    }
                }
            }
        }
    }
}

//Percorrimeraiznto em pré-ordem
//printf("%d\t", raiz->chave)
void percorre(no *raiz){
    if(raiz != NULL){//Recursivo
        printf("%d\t", raiz->chave);
        percorre(raiz->esq);
        percorre(raiz->dir);
    }
}

//Retorna o nó que contém a chave indicada (não trata valores repetidos)
//Retorna NULL caso o elemento não exista na árvore
no *recuperaNo(abp *arv, int chave){
    no *noAtual;
    noAtual = arv->sentinela->dir;
    if(noAtual == NULL){
        return NULL;
    }
    else{
        while(noAtual != NULL){//Percorrer a árvore comparando as chaves até achar um nó (sem considerar chaves repetidas)
            if(chave == noAtual->chave){
                return noAtual;
            }
            else{
                if(chave < noAtual->chave){
                    noAtual = noAtual->esq;
                }
                else{
                    noAtual = noAtual->dir;
                }
            }
        }
        return NULL;
    }
}

//Imprime a chave do nó, as chaves de seus filhos e do seu pai
//Se o nó não tiver filho da esquerda e/ou da direita, imprime NULO
//Se o pai for a sentinela, imprime Sentinela
void imprimeNo(no *atual){
    printf("Chave : %d\n", atual->chave);
    if(atual->dir == NULL && atual->esq == NULL){
        printf("Filho Esq : NULO\n");
        printf("Filho Dir : NULO\n");
    }
    else{
        if(atual->esq == NULL){
            printf("Filho Esq : NULO\n");
            printf("Filho Dir : %d\n", atual->dir->chave);
        }
        else{
            if(atual->dir == NULL){
            printf("Filho Esq : %d\n", atual->esq->chave);
            printf("Filho Dir : NULO\n");
            }
            else{
                printf("Filho Esq : %d\n", atual->esq->chave);
                printf("Filho Dir : %d\n", atual->dir->chave);
            }
        }
    }
    if(atual->pai->chave == -1000){
        printf("Pai : Sentinela\n");
    }
    else{
        printf("Pai : %d\n", atual->pai->chave);
    }
}

//Retorna a quantidade de elementos contidos na árvore
int getNumElementos(abp *arv){
    return arv->numElementos;
}

//Retorna a raiz da árvore (filho direita da sentinela)
no *getRaiz(abp *arv){
    return arv->sentinela->dir;
}
