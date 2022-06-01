#include <stdio.h>
#include <stdlib.h>

#include "avl.h"

struct no{
    int chave;
    int fb;
    struct no *esq;
    struct no *dir;
    struct no *pai;
};

struct arvore{
    no *sentinela;
    int numElementos;
};

//Cria uma nova árvore inicializando a sentinela
avl *criaArvore(){
    avl *arv = (avl*) malloc(sizeof(avl));
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
            sent->fb = 0;
            arv->sentinela = sent;
            arv->numElementos = 0;
            return arv;
        }
    }
}

//Popula uma árvore binária de pesquisa a partir de números contidos no arquivo
//Retorna -1 caso haja erros durante a inserção e/ou leitura do arquivo
//Retorna 0 caso contrário
int carregaArvore(avl *arv, char *nomeArquivo){
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
int insereNo(avl *arv, int chave){
    no *noAux = (no*) malloc(sizeof(no));
    no *noAnt, *noAtual;
    
    if(noAux == NULL){
        printf("Erro ao alocar nó");
        return -1;
    }
    else{
        noAux->chave = chave;
        noAux->dir = NULL;
        noAux->esq = NULL;
        noAux->fb = 0;
        if(arv->numElementos == 0){
            noAux->pai = arv->sentinela;
            arv->sentinela->dir = noAux;
            arv->numElementos++;
            atualizaFB_insercao(arv, noAux);
            return 0;
        }
        else{
            noAtual = arv->sentinela->dir;
            while(noAtual != NULL){//Percorre até encontrar um pai com campo filho nulo
                if(chave < noAtual->chave){
                    noAnt = noAtual;
                    noAtual = noAtual->esq;
                }
                else{
                    noAnt = noAtual;
                    noAtual = noAtual->dir;
                }
            }
            if(chave < noAnt->chave){//insere filho à esquerda
                noAux->pai = noAnt;
                noAnt->esq = noAux;
                arv->numElementos++;
                atualizaFB_insercao(arv, noAux);
                return 0;
            }
            else{//insere filho à direita
                noAux->pai = noAnt;
                noAnt->dir = noAux;
                arv->numElementos++;
                atualizaFB_insercao(arv, noAux);
                return 0;
            }
        }
    }
}

//Remove um elemento da árvore
//Retorna 0 caso a deleção aconteça;
//Retorna -1 caso a árvore esteja vazia
//Retorna -2 caso o elemento não esteja presente na árvore
int removeNo(avl *arv, int chave){
    no *noRemove = recuperaNo(arv, chave);
    no *predecessor, *noAtual;
    if(noRemove == NULL){
        return -2;
    }
    else{
        if(arv->numElementos == 0){//Árvore vazia
            return -1;
        }
        else{
            if(noRemove->dir == NULL && noRemove->esq == NULL){//Eliminar um nó folha
                if(noRemove->chave < noRemove->pai->chave){//da esquerda
                    noRemove->pai->esq = NULL;
                }
                else{//da direita
                    noRemove->pai->dir = NULL;
                }
                free(noRemove);
                arv->numElementos--;
                return 0;
            }
            else{
                if(noRemove->dir !=NULL && noRemove->esq != NULL){//Eliminar um nó com 2 filhos
                    noAtual = noRemove->esq;
                    while(noAtual != NULL){
                        predecessor = noAtual;
                        noAtual = noAtual->dir;
                    }
                    if(predecessor->esq != NULL){ //se predecessor tem filho
                        predecessor->esq->pai = predecessor->pai; // linka ex-filho do predecessor ao ex-pai do predecessor
                        predecessor->pai->dir = predecessor->esq; // linka ex-pai do predecessor ao ex-filho do predecessor
                    }
                    //Copiar chave e desalocar o nó
                    noRemove->chave = predecessor->chave;
                    arv->numElementos--;
                    free(predecessor);
                    return 0;
                }
                else{//Eliminar um nó com 1 filho
                    if(noRemove->chave < noRemove->pai->chave){//O nó a ser eliminado está à esquerda do pai
                        if(noRemove->esq != NULL){//Há um filho na esquerda
                            noRemove->pai->esq = noRemove->esq; // linka ex-pai do noRemove ao ex-filho do predecessor
                            noRemove->esq->pai = noRemove->pai; // linka ex-filho do noRemove ao ex-pai do predecessor
                        }
                        else{//Há um filho na direita
                            noRemove->pai->esq = noRemove->dir;
                            noRemove->dir->pai = noRemove->pai;
                        }
                    }
                    else{//O nó a ser eliminado está à direita do pai
                        if(noRemove->esq != NULL){//Há um filho na esquerda
                            noRemove->pai->dir = noRemove->esq;
                            noRemove->esq->pai = noRemove->pai;
                        }
                        else{//Há um filho na direita
                            noRemove->pai->dir = noRemove->dir;
                            noRemove->dir->pai = noRemove->pai;
                        }
                    }
                    //Desalocar o nó
                    arv->numElementos--;
                    free(noRemove);
                    return 0;
                }
            }
        }
    }
}

//Percorrimeraiznto em pré-ordem
//printf("%d\t", raiz->chave)
void percorre(no *raiz){
    if(raiz != NULL){
        printf("%d\t", raiz->chave);
        percorre(raiz->esq);
        percorre(raiz->dir);
    }
}

//Retorna o nó que contém a chave indicada (não trata valores repetidos)
//Retorna NULL caso o elemento não exista na árvore
no *recuperaNo(avl *arv, int chave){
    no *noAtual;
    noAtual = arv->sentinela->dir;
    if(noAtual == NULL){
        return NULL;
    }
    else{
        while(noAtual != NULL){
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
        printf("Sentinela\n");
    }
    else{
        printf("Pai : %d\n", atual->pai->chave);
    }
}

//Retorna a quantidade de elementos contidos na árvore
int getNumElementos(avl *arv){
    return arv->numElementos;
}

//Retorna a raiz da árvore (filho direita da sentinela)
no *getRaiz(avl *arv){
    return arv->sentinela->dir;
}

//Atualiza o valor do fator de balanceamento dos nós após a inserção de um nó 
//Condições de parada : após ajuste do FB => chegar no nó raiz ou o nó ficar com fb 0, 2 OU -2
void atualizaFB_insercao(avl *arv, no *novoNo){
    no *noAux = novoNo;
    do{
        if(noAux->pai->chave < noAux->chave){
            noAux->pai->fb++;
        }
        else{
            noAux->pai->fb--;
        }
        noAux = noAux->pai;
    }while((noAux->fb != 0) || (noAux->fb != 2) || (noAux->fb != -2) || (noAux != arv->sentinela));
    if((noAux->fb != 2) || (noAux->fb != -2)){
        balanceamento_Insercao(arv, noAux);
    }
}

//Verifica a estratégia de balanceamento do nó e ajusta o fator de balanceamento
void balanceamento_Insercao(avl *arv, no *noDesbalanceado){
    no *filho, *neto = NULL;
    int fbAux;
    if (noDesbalanceado->fb == 2){ //inicio fator = 2
        filho = noDesbalanceado->dir;
        if(filho->fb == -1){ //confere o fb do filho = -1
            if(filho->dir){
                neto = filho->dir;
            }
            fbAux = neto->fb;
            rotacaoDir(arv, filho);
            rotacaoEsq(arv, noDesbalanceado);
            if(fbAux == -1){
                filho->fb = 1;
            }
            else{
                if(fbAux == 1){
                    noDesbalanceado->fb = -1;
                }
            }
        }
        else{
            rotacaoEsq(arv, noDesbalanceado);
        }
    } // fim fator = 2
    if (noDesbalanceado->fb == -2){ //inicio fator = -2
        filho = noDesbalanceado->esq;
        if(filho->fb == 1){ //confere o fb do filho = 1
            if(filho->esq){
                neto = filho->esq;
            }
            fbAux = neto->fb;
            rotacaoEsq(arv, filho);
            rotacaoDir(arv, noDesbalanceado);
            if(fbAux == 1){
                filho->fb = -1;
            }
            else{
                if(fbAux == -1){
                    noDesbalanceado->fb = 1;
                }
            }
        }
        else{
            rotacaoDir(arv, noDesbalanceado);
        }
    } // fim fator = -2
}

//Rotação à esquerda no nó desbalanceado
void rotacaoEsq(avl *arv, no *noDesbalanceado){
    no *noAux = noDesbalanceado->dir;
    
    noDesbalanceado->dir = noAux->esq;
    if(noAux->esq != arv->sentinela){
        noAux->esq->pai = noDesbalanceado;
    }
    noAux->pai = noDesbalanceado->pai;
    if(noDesbalanceado->pai == arv->sentinela){
        arv->sentinela->dir = noAux;
    }
    else{
        if(noDesbalanceado == noDesbalanceado->pai->esq){
            noDesbalanceado->pai->esq = noAux;
        }
        else{
            noDesbalanceado->pai->dir = noAux;
        }
    }
    noAux->esq = noDesbalanceado;
    noDesbalanceado->pai = noAux;
}

//Rotação à direita no no desbalanceado
void rotacaoDir(avl *arv, no *noDesbalanceado){
        no *noAux = noDesbalanceado->esq;
    
    noDesbalanceado->esq = noAux->dir;
    if(noAux->dir != arv->sentinela){
        noAux->dir->pai = noDesbalanceado;
    }
    noAux->pai = noDesbalanceado->pai;
    if(noDesbalanceado->pai == arv->sentinela){
        arv->sentinela->dir = noAux;
    }
    else{
        if(noDesbalanceado == noDesbalanceado->pai->dir){
            noDesbalanceado->pai->dir = noAux;
        }
        else{
            noDesbalanceado->pai->esq = noAux;
        }
    }
    noAux->dir = noDesbalanceado;
    noDesbalanceado->pai = noAux;
}
