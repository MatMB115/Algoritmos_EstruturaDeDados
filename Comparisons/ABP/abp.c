#include <stdio.h>
#include <stdlib.h>

#include "abp.h"

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

int esvaziaArvore(abp *arv, char *nomeArquivo){
    int chave, erro = 0;
    FILE *arq = fopen(nomeArquivo, "r");
    if(arq == NULL){
        return -1;
    }
    else{
        while (!feof(arq)){
            if(fscanf(arq, "%d", &chave) == 0){
                printf("Erro ao ler do arquivo de entrada\n");
                fclose(arq);
                return 1;
            }
            erro = removeNo(arv, chave);
            if(erro != 0){
                printf("Erro ao remover um nó %d", erro);
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
    no *noRemove = recuperaNo(arv, chave);
    no *sucessor = NULL;
    no *filho = NULL;

    if(noRemove == NULL){
        return -2;
    }
    else{
        if(arv->numElementos == 0){
            printf("Árvore vazia\n");
            return -1;
        }

        if(noRemove->esq != NULL && noRemove->dir != NULL){//Dois filhos
            sucessor = noRemove->dir;
            while(sucessor->esq != NULL){
                sucessor = sucessor->esq;
            }
            noRemove->chave = sucessor->chave;
            noRemove = sucessor;
        }
        if(noRemove->esq != NULL){
            filho = noRemove->esq;
        }
        else{
            filho = noRemove->dir;
        }

        if(filho != NULL){
            filho->pai = noRemove->pai;
        }

        if(noRemove->pai == NULL){
            arv->sentinela = filho;
        }
        else{
            if(noRemove == noRemove->pai->esq){
                noRemove->pai->esq = filho;
            }
            else{
                noRemove->pai->dir = filho;
            }
        }

        free(noRemove);
        arv->numElementos--;
        return 0;
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
no* recuperaNo(abp *arv, int chave) {
    no* atual = arv->sentinela;

    while (atual != NULL && atual->chave != chave) {
        if (chave < atual->chave) {
            atual = atual->esq;
        }
        else {
            atual = atual->dir;
        }
    }

    return atual;
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
int getNumElementos(abp *arv){
    return arv->numElementos;
}

//Retorna a raiz da árvore (filho direita da sentinela)
no *getRaiz(abp *arv){
    return arv->sentinela->dir;
}

int maior(int a, int b){
    if(a > b)
        return a;
    else
        return b;
}//maior

int getAltura(no *raiz){
   if((raiz == NULL) || (raiz->esq == NULL && raiz->dir == NULL))
       return 0;
   else
       return 1 + maior(getAltura(raiz->esq), getAltura(raiz->dir));
}

void registraDados(double chargeT, double freeT, double searchT, char *nomeArquivo, int qtd, int altura, int type){

    FILE *arq = fopen(nomeArquivo, "a+");
    if(arq == NULL){
        exit(1);
    }else{
        if(type == 1){
            fprintf(arq, "-------------\n");
            fprintf(arq, "N = %d - Aleatórios\n", qtd);
            fprintf(arq, "Altura: %d\n", altura);
            fprintf(arq, "Tempo para carregar: %lf\n", chargeT);
            fprintf(arq, "Tempo para liberar: %lf\n", freeT);
            fprintf(arq, "TM consulta: %lf\n", searchT*1000);
            fprintf(arq, "-------------\n\n");
        }else{
            if(type == 2){
                fprintf(arq, "-------------\n");
                fprintf(arq, "N = %d - Crescente\n", qtd);
                fprintf(arq, "Altura: %d\n", altura);
                fprintf(arq, "Tempo para carregar: %lf\n", chargeT);
                fprintf(arq, "Tempo para liberar: %lf\n", freeT);
                fprintf(arq, "TM consulta: %lf\n", searchT*1000);
                fprintf(arq, "-------------\n\n");
            }else{
                fprintf(arq, "-------------\n");
                fprintf(arq, "N = %d - Decrescente\n", qtd);
                fprintf(arq, "Altura: %d\n", altura);
                fprintf(arq, "Tempo para carregar: %lf\n", chargeT);
                fprintf(arq, "Tempo para liberar: %lf\n", freeT);
                fprintf(arq, "TM consulta: %lf\n", searchT*1000);
                fprintf(arq, "-------------\n\n");
            }
        } 
    }
    fclose(arq);
}