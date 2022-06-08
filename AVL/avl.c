#include <stdio.h>
#include <stdlib.h>

#include "avl.h"

// COM112 - Algoritmos e Estruturas de Dados II
// Atividade 06
// 2019005687– Matheus Martins Batista
// 2020003596 - Kaique de Souza Leal Silva
// AVL

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
avl *criaArvore(){ //OK
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
int carregaArvore(avl *arv, char *nomeArquivo){ //OK
    int chave;
    FILE *arq = fopen(nomeArquivo, "r");
    if(arq == NULL){
        return -1;
    }
    else{
        while(!feof(arq)){
            if(fscanf(arq, "%d", &chave) == 0){
                printf("Erro ao ler do arquivo de entrada\n");
                fclose(arq);
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
int insereNo(avl *arv, int chave){ //OK
    no *noNovo = (no*) malloc(sizeof(no));
    no *pai, *noAux;
    
    if(noNovo == NULL){
        printf("Erro ao alocar memória para o nó");
        return -1;
    }
    else{
        noNovo->chave = chave;
        noNovo->dir = NULL;
        noNovo->esq = NULL;
        noNovo->pai = NULL;
        noNovo->fb = 0;
        if(arv->numElementos == 0){
            noNovo->pai = arv->sentinela;
            arv->sentinela->dir = noNovo;
            //atualizaFB_Insercao(arv, noNovo);
            arv->numElementos++;
            return 0;
        }
        else{
            noAux = arv->sentinela->dir;
            while(noAux != NULL){//Percorre até encontrar um pai com campo filho nulo
                pai = noAux;
                
                if(chave < noAux->chave){
                    noAux = noAux->esq;
                }
                else{
                    noAux = noAux->dir;
                }
            }
            if(chave < pai->chave){//insere filho à esquerda
                pai->esq = noNovo;
            }
            else{//insere filho à direita
                pai->dir = noNovo;
            }
            noNovo->pai = pai;
            atualizaFB_Insercao(arv, noNovo);
            arv->numElementos++;
            return 0;
        }
    }
}

//Remove um elemento da árvore
//Retorna 0 caso a deleção aconteça;
//Retorna -1 caso a árvore esteja vazia
//Retorna -2 caso o elemento não esteja presente na árvore
int removeNo(avl *arv, int chave){ //OK
    no *noRemove = recuperaNo(arv, chave);
    no *predecessor;
    if(noRemove == NULL){
        return -2;
    }
    else{
        if(arv->numElementos == 0){
            printf("Árvore vazia\n");
            return -1;
        }

        if(noRemove->esq != NULL && noRemove->dir != NULL){//Dois filhos
            predecessor = noRemove->esq;
            while(predecessor->dir != NULL){
                predecessor = predecessor->dir;
            }
            noRemove->chave = predecessor->chave;
            noRemove = predecessor;
        }

        if(noRemove->esq == NULL && noRemove->dir == NULL){//Dois filhos
            if(noRemove->chave < noRemove->pai->chave){
                noRemove->pai->esq = NULL;
            }
            else{
                noRemove->pai->dir = NULL;
            }
            atualizaFB_Remocao(arv, noRemove, chave);
            free(noRemove);
            arv->numElementos--;
            return 0;
        }

        if(noRemove->esq == NULL || noRemove->dir == NULL){//Um filho
            if(noRemove->dir != NULL){//à direita
                if(noRemove->chave < noRemove->pai->chave){ //Ficará à esquerda do pai
                    noRemove->pai->esq = noRemove->dir;
                }
                else{ //Ficará à direita do pai
                    noRemove->pai->dir = noRemove->dir; 
                }
                noRemove->dir->pai = noRemove->pai; 
            }
            else{ //à esquerda
                if(noRemove->chave < noRemove->pai->chave){
                    noRemove->pai->esq = noRemove->esq;
                }
                else{
                    noRemove->pai->dir = noRemove->esq;
                }
                noRemove->esq->pai = noRemove->pai; 
            }
        }
    }
    atualizaFB_Remocao(arv, noRemove, chave);
    free(noRemove);
    arv->numElementos--;
    return 0;
}

//Percorrimento em pré-ordem
//printf("%d: %d\t", raiz->chave, raiz->fb);
void percorre(no *raiz){ //OK
    if(raiz != NULL){
        printf("%d: %d\t", raiz->chave, raiz->fb);
        percorre(raiz->esq);
        percorre(raiz->dir);
    }
}

//Retorna o nó que contém a chave indicada (não trata valores repetidos)
//Retorna NULL caso o elemento não exista na árvore
no *recuperaNo(avl *arv, int chave){ //OK
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
void imprimeNo(no *atual){ //OK
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
int getNumElementos(avl *arv){ //OK
    return arv->numElementos;
}

//Retorna a raiz da árvore (filho direita da sentinela)
no *getRaiz(avl *arv){ //OK
    return arv->sentinela->dir;
}

//Função recursiva que retorna a altura da árvore
//A altura é maior distância entre a raiz e uma folha
int getAltura(no *raiz){ //OK
    if((raiz == NULL) || (raiz->esq == NULL && raiz->dir == NULL)){
        return 0;
    }  
    else{ //retorna a pilha do lado com maior profundidade
        if(getAltura(raiz->esq) > getAltura(raiz->dir)){
            return 1 + getAltura(raiz->esq);
        }
        else{
            return 1 + getAltura(raiz->dir);
        }
    }
}

//Atualiza o valor do fator de balanceamento dos nós após a inserção de um nó 
//Condições de parada : após ajuste do FB => chegar no nó raiz ou o nó ficar com fb 0, 2 OU -2
void atualizaFB_Insercao(avl *arv, no *novoNo){ //OK
    no *noAux = novoNo;
    
    do{
        if(noAux->pai->chave < noAux->chave){
            noAux->pai->fb++;
        }
        else{
            noAux->pai->fb--;
        }
        noAux = noAux->pai;
    }while((noAux->fb != 0) && (noAux->fb != 2) && (noAux->fb != -2) && (noAux != arv->sentinela->dir));
    
    if((noAux->fb == 2) || (noAux->fb == -2)){
        balanceamento(arv, noAux);
    }
}

//Atualiza o valor do fator de balanceamento dos nós após a remoção de um nó
//Condições de parada : após ajuste do FB => chegar na sentinela ou o nó ficar com fb 1, -1, 2 ou -2
void atualizaFB_Remocao(avl *arv, no *pai, int chave){ //OK
    no *noAux = pai;
    
    if(noAux->chave < noAux->pai->chave){
        noAux->pai->fb++;
    }
    else{
        noAux->pai->fb--;
    }
    noAux = noAux->pai;
    
    while((noAux->fb == 0) && (noAux->pai != arv->sentinela)){
        if(noAux->chave < noAux->pai->chave){
            noAux->pai->fb++;
        }
        else{
            noAux->pai->fb--;
        }
        noAux = noAux->pai;
    }

    if((noAux->fb == 2) || (noAux->fb == -2)){
        balanceamento(arv, noAux);
        noAux = noAux->pai;
        
        if((noAux->fb == 0) && (noAux != arv->sentinela->dir)){
            atualizaFB_Remocao(arv, noAux, chave);
        }
    }
}

//Verifica a estratégia de balanceamento do nó e ajusta o fator de balanceamento
void balanceamento(avl *arv, no *noDesbalanceado){ //OK
    no *filho, *neto;
    
    if (noDesbalanceado->fb == 2){ //inicio fator = 2
        filho = noDesbalanceado->dir;
        if(filho->fb == -1){ //rotação dupla, dir-esq
            neto = filho->esq;

            rotacaoDir(arv, filho);
            rotacaoEsq(arv, noDesbalanceado);

            if(neto->fb == -1){ //Corrige os fatores de balanceamento
                noDesbalanceado->fb = 0;
                filho->fb = 1;
                neto->fb = 0;
            }
            else{
                if(neto->fb == 1){
                    noDesbalanceado->fb = -1; 
                }
                else{
                    noDesbalanceado->fb = 0;
                }
            filho->fb = 0;
            neto->fb = 0;
            }
        }
        else{ //rotação simples a esquerda
            rotacaoEsq(arv, noDesbalanceado);

            if(filho->fb == 0){
                noDesbalanceado->fb = 1;
                filho->fb = -1;
            }
            else{
                noDesbalanceado->fb = 0;
                filho->fb = 0;
            }
        }
    } //fim fator = 2
    else{ //inicio fator = -2
        filho = noDesbalanceado->esq;
        if(filho->fb == 1){ //Rotação dupla, esq-dir
            neto = filho->esq;

            rotacaoEsq(arv, filho);
            rotacaoDir(arv, noDesbalanceado);

            if(neto->fb == -1){ //Corrige os fatores de balanceamento
                noDesbalanceado->fb = 1;
                filho->fb = 0;
                neto->fb = 0;
                }
            else{
                if(neto->fb == 1){
                    filho->fb = -1;
                }
                else{
                    filho->fb = 0;
                }
                noDesbalanceado->fb = 0;
                neto->fb = 0;
            }
        }
        else{ //rotação simples a direita
            rotacaoDir(arv, noDesbalanceado);

            if(filho->fb == 0) {
                noDesbalanceado->fb = -1;
                filho -> fb = 1;
            }
            else{
                noDesbalanceado->fb = 0;
                filho->fb = 0;
            }
        }
    }// fim fator = -2
}

//Rotação à esquerda no nó desbalanceado
void rotacaoEsq(avl *arv, no *noDesbalanceado){ //OK
    
    no *filhoDir;
    no *esqFilho;
    
    filhoDir = noDesbalanceado -> dir;
    esqFilho = filhoDir->esq;
    
    filhoDir->pai = noDesbalanceado->pai;
    
    if(filhoDir -> chave < noDesbalanceado -> pai -> chave){
        noDesbalanceado->pai->esq = filhoDir; 
    }
    else{
        noDesbalanceado->pai->dir = filhoDir;
    }
    
    filhoDir -> esq = noDesbalanceado;
    noDesbalanceado->pai = filhoDir;
    noDesbalanceado->dir = esqFilho;
    
    if(esqFilho != NULL){
        esqFilho->pai = noDesbalanceado;
    }
}

//Rotação à direita no no desbalanceado
void rotacaoDir(avl *arv, no *noDesbalanceado){ //OK
      
    no *filhoEsq;
    no *dirFilho;
    
    filhoEsq = noDesbalanceado -> esq;
    dirFilho = filhoEsq->dir;
    
    filhoEsq->pai = noDesbalanceado->pai;
    
    if(filhoEsq -> chave < noDesbalanceado->pai->chave){
        noDesbalanceado->pai->esq = filhoEsq;
    }
    else{
        noDesbalanceado->pai->dir = filhoEsq;
    }
    filhoEsq -> dir = noDesbalanceado;
    noDesbalanceado->pai = filhoEsq;
    noDesbalanceado->esq = dirFilho;
    
    if(dirFilho != NULL){
        dirFilho->pai = noDesbalanceado;
    }
}