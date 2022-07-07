#include <stdio.h>
#include <stdlib.h>

#include "avl.h"

// COM112 - Algoritmos e Estruturas de Dados II
// Atividade 06
// 2019005687 - Matheus Martins Batista
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
    int rot;
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
            arv->rot = 0;
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
int insereNo(avl *arv, int chave){
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
            arv->numElementos++;
            atualizaFB_Insercao(arv, noNovo);
            return 0;
        }
    }
}

//Remove um elemento da árvore
//Retorna 0 caso a deleção aconteça;
//Retorna -1 caso a árvore esteja vazia
//Retorna -2 caso o elemento não esteja presente na árvore
int removeNo(avl* arv, int chave) {
    no* atual = arv->sentinela->dir;
    no* filho = NULL;
    no* aux = NULL;

    while (atual != NULL && atual->chave != chave) {
        if (chave < atual->chave) {
            atual = atual->esq;
        }
        else {
            atual = atual->dir;
        }
    }

    if (atual == NULL) {
        return -2;
    }

    if (atual->esq != NULL && atual->dir != NULL) {
        aux = atual->dir;
        while (aux->esq != NULL) {
            aux = aux->esq;
        }
        atual->chave = aux->chave;
        atual = aux;
    }

    if (atual->esq != NULL) {
        filho = atual->esq;
    }
    else {
        filho = atual->dir;
    }

    if (filho != NULL) {
        filho->pai = atual->pai;
    }

    if (atual->pai == NULL) {
        arv->sentinela = filho;
    }
    else {
        if (atual == atual->pai->esq) {
            atual->pai->esq = filho;
        }
        else {
            atual->pai->dir = filho;
        }
    }

    if (atual->pai != arv->sentinela) {
        atualizaFB_Remocao(arv, atual->pai, atual->chave);
    }

    free(atual);
    arv->numElementos--;

    return 0;
}

//Percorrimento em pré-ordem
//printf("%d: %d\t", raiz->chave, raiz->fb);
void percorre(no *raiz){
    if(raiz != NULL){
        printf("%d: %d\t", raiz->chave, raiz->fb);
        percorre(raiz->esq);
        percorre(raiz->dir);
    }
}

//Retorna o nó que contém a chave indicada (não trata valores repetidos)
//Retorna NULL caso o elemento não exista na árvore
no* recuperaNo(avl *arv, int chave) {
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
int getNumElementos(avl *arv){
    return arv->numElementos;
}

//Retorna a raiz da árvore (filho direita da sentinela)
no *getRaiz(avl *arv){
    return arv->sentinela->dir;
}

//Função recursiva que retorna a altura da árvore
//A altura é maior distância entre a raiz e uma folha
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

int getRotacoes(avl *arv){
    return arv->rot;
}

//Atualiza o valor do fator de balanceamento dos nós após a inserção de um nó 
//Condições de parada : após ajuste do FB => chegar no nó raiz ou o nó ficar com fb 0, 2 OU -2
void atualizaFB_Insercao(avl *arv, no *novoNo){
    no *noAux = novoNo;
    
    do{
        if(noAux->pai->chave <= noAux->chave){
            noAux->pai->fb++;
        }
        else{
            noAux->pai->fb--;
        }
        noAux = noAux->pai;
    }while(noAux->pai != arv->sentinela && noAux->fb != 0 && (noAux->fb != 2 && noAux->fb != -2));
    
    if((noAux->fb == 2) || (noAux->fb == -2)){
        balanceamento(arv, noAux);
    }
}

//Atualiza o valor do fator de balanceamento dos nós após a remoção de um nó
//Condições de parada : após ajuste do FB => chegar na sentinela ou o nó ficar com fb 1, -1, 2 ou -2
void atualizaFB_Remocao(avl *arv, no *pai, int chave){
    no* noAux = pai;

    if(noAux->chave <= chave){
        noAux->fb--;
    }
    else{
        noAux->fb++;
    }

    while(noAux != arv->sentinela && noAux->fb == 0){
        noAux = noAux->pai;
        if(noAux->chave <= chave){
            noAux->fb--;
        }
        else{
            noAux->fb++;
        }
    }

    if(noAux->fb == 2 || noAux->fb == -2){
        balanceamento(arv, noAux);
        noAux = noAux->pai;

        if(noAux != arv->sentinela && noAux->fb == 0){
            atualizaFB_Remocao(arv, noAux->pai, chave);
        }
    }
}

//Verifica a estratégia de balanceamento do nó e ajusta o fator de balanceamento
void balanceamento(avl* arv, no* noDesbalanceado){
    no* filho = NULL, *neto;

    if(noDesbalanceado->fb == 2){ //inicio fator = 2
        filho = noDesbalanceado->dir;
        if(filho->fb == -1){ //rotação dupla, dir-esq
            neto = filho->esq;
            rotacaoDir(arv, filho);
            rotacaoEsq(arv, noDesbalanceado);
            if(neto->fb == 0){
                noDesbalanceado->fb = 0;
                filho->fb = 0;
            }
            else if(neto->fb == 1){
                noDesbalanceado->fb = -1;
                filho->fb = 0;
            }
            else if(neto->fb == -1){
                noDesbalanceado->fb = 0;
                filho->fb = 1;
            }
            neto->fb = 0;

        }
        else if(filho->fb == 0){ //rotação simples a esquerda
            rotacaoEsq(arv, noDesbalanceado);
            noDesbalanceado->fb = 1;
            filho->fb = -1;
        }
        else{
            rotacaoEsq(arv, noDesbalanceado);
            if(filho->fb == 1){
                noDesbalanceado->fb = 0;
                filho->fb = 0;
            }
            else{
                noDesbalanceado->fb = 1;
                filho->fb = -1;
            }
        }
    }
    else{ //inicio fator = -2
        filho = noDesbalanceado->esq;
        if(filho->fb == 1){ //rotação dupla, esq-dir
            neto = filho->dir;
            rotacaoEsq(arv, filho);
            rotacaoDir(arv, noDesbalanceado);
            if(neto->fb == 0){
                noDesbalanceado->fb = 0;
                filho->fb = 0;
            }
            else if(neto->fb == 1){
                noDesbalanceado->fb = 0;
                filho->fb = -1;
            }
            else{
                noDesbalanceado->fb = 1;
                filho->fb = 0;
            }
            neto->fb = 0;
        }
        else if(filho->fb == 0){ //rotação simples a direita
            rotacaoDir(arv, noDesbalanceado);
            noDesbalanceado->fb = -1;
            filho->fb = 1;
        }
        else{
            rotacaoDir(arv, noDesbalanceado);
            if(filho->fb == -1){
                noDesbalanceado->fb = 0;
                filho->fb = 0;
            }
            else{
                noDesbalanceado->fb = -1;
                filho->fb = 1;
            }
        }
    }
}

//Rotação à esquerda no nó desbalanceado
void rotacaoEsq(avl *arv, no *noDesbalanceado){
    arv->rot++;
    no* filhoDir = noDesbalanceado->dir;
    noDesbalanceado->dir = filhoDir->esq;

    if(filhoDir->esq != NULL){
        filhoDir->esq->pai = noDesbalanceado;
    }

    filhoDir->esq = noDesbalanceado->pai;

    if(noDesbalanceado == noDesbalanceado->pai->esq){
        noDesbalanceado->pai->esq = filhoDir;
    }
    else{
        noDesbalanceado->pai->dir = filhoDir;
    }

    filhoDir->pai = noDesbalanceado->pai;
    filhoDir->esq = noDesbalanceado;
    noDesbalanceado->pai = filhoDir;
}

//Rotação à direita no no desbalanceado
void rotacaoDir(avl *arv, no *noDesbalanceado){
    arv->rot++;
    no* filhoEsq = noDesbalanceado->esq;
    noDesbalanceado->esq = filhoEsq->dir;

    if (filhoEsq->dir != NULL) {
        filhoEsq->dir->pai = noDesbalanceado;
    }

    filhoEsq->dir = noDesbalanceado->pai;

    if(noDesbalanceado == noDesbalanceado->pai->esq){
        noDesbalanceado->pai->esq = filhoEsq;
    }
    else{
        noDesbalanceado->pai->dir = filhoEsq;
    }

    filhoEsq->pai = noDesbalanceado->pai;
    filhoEsq->dir = noDesbalanceado;
    noDesbalanceado->pai = filhoEsq;
}


int esvaziaArvore(avl *arv, char *nomeArquivo){
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
            printf(" %d\n", chave);
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

void registraDados(double chargeT, double freeT, double searchT, char *nomeArquivo, int qtd, int altura, int type, int rotC, int rotL){

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
            fprintf(arq, "Rotações para carregar: %d\n", rotC);
            fprintf(arq, "Rotações para liberar: %d\n", rotL);
            fprintf(arq, "-------------\n\n");
        }else{
            if(type == 2){
                fprintf(arq, "-------------\n");
                fprintf(arq, "N = %d - Crescente\n", qtd);
                fprintf(arq, "Altura: %d\n", altura);
                fprintf(arq, "Tempo para carregar: %lf\n", chargeT);
                fprintf(arq, "Tempo para liberar: %lf\n", freeT);
                fprintf(arq, "TM consulta: %lf\n", searchT*1000);
                fprintf(arq, "Rotações para carregar: %d\n", rotC);
                fprintf(arq, "Rotações para liberar: %d\n", rotL);
                fprintf(arq, "-------------\n\n");
            }else{
                fprintf(arq, "-------------\n");
                fprintf(arq, "N = %d - Decrescente\n", qtd);
                fprintf(arq, "Altura: %d\n", altura);
                fprintf(arq, "Tempo para carregar: %lf\n", chargeT);
                fprintf(arq, "Tempo para liberar: %lf\n", freeT);
                fprintf(arq, "TM consulta: %lf\n", searchT*1000);
                fprintf(arq, "Rotações para carregar: %d\n", rotC);
                fprintf(arq, "Rotações para liberar: %d\n", rotL);
                fprintf(arq, "-------------\n\n");
            }
        } 
    }
    fclose(arq);
}